#include <string>
#include <term.h>
#include <sstream>
#include <algorithm>
#include "strutils.h"
#include "ControlIO.h"

void split(const std::string& s, std::vector<std::string>& v, const char c);

ControlIO::ControlIO(int _fd):
	fd(_fd), x(0), y(0), esc("\033[") {
		tcgetattr(_fd, &orig_settings);
		setupterm(0, 0, 0);
		char it[] = "it";
		tabwidth = tgetnum(it);	
		line.push_back(0);
}

int ControlIO::tty_cbreak() const {
	struct termios attr = this->orig_settings;
	attr.c_lflag &= ~(ECHO | ICANON);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	if(tcsetattr(this->fd, TCSAFLUSH, &attr) < 0)
		return -1;
	return 0;
}

int ControlIO::tty_reset() const {
	if(tcsetattr(this->fd, TCSAFLUSH, &(this->orig_settings)) < 0)
		return -1;
	return 0;
}

int ControlIO::getch() const {
	fflush(stdout);
	tty_cbreak();
	char ch[2];
	read(this->fd, ch, 2);
	tty_reset();
	return *ch;
}

ControlIO::CtrlKey ControlIO::getctrch() const {
	tty_cbreak();
	char ch[3];
	read(this->fd, ch, 3);
	tty_reset();
	if(*ch == '\033' || *(ch+1) == '[') {
		char ch2 = ch[2];
		switch(ch2) {
			case 'A': return Up;
			case 'B': return Down;
			case 'C': return Right;
			case 'D': return Left;
			default: return Other;
		}
	}else if(*ch == '\n'){
		return Return;
	}else if(*ch == '\t'){
		return Tab;
	}
	return Other;
}

ControlIO& ControlIO::show_cursor() {
	char output[] = "\033[?25h";
	write(STDOUT_FILENO, output, sizeof(output));
	return *this;
}

ControlIO& ControlIO::hide_cursor() {
	char output[] = "\033[?25l";
	write(STDOUT_FILENO, output, sizeof(output));
	return *this;
}

ControlIO& ControlIO::mov_cursor(CtrlKey direction, unsigned linenum) {
	char output[6];
	sprintf(output, "\033[%d%c", linenum, (int)direction);
	write(STDOUT_FILENO, output, sizeof(output));
	switch(direction) {
	case ControlIO::Up:
		if(this->y > 0) this->y -= linenum;
		break;
	case ControlIO::Down:
		if(this->y+1 < this->line.size()) this->y += linenum;
		break;
	case ControlIO::Left:
		if(this->x > 0) this->x -= linenum;
		break;
	case ControlIO::Right:
		this->x += linenum;
		break;
	default:
		break;
	}
	return *this;
}

ControlIO& ControlIO::movexy(unsigned tox, unsigned toy) {
	if(toy > this->line.size() - 1) {
		// toy = this->line.size() - 1;
		int movy = toy - this->y;
		std::string newlines(movy, '\n');
		std::cout<<newlines<<std::flush;
		int linecount = toy - this->line.size() + 1;
		for (int i = 0; i < linecount; i++){
			this->line.push_back(0);
		}
		this->y = toy;
		this->x = 0;
	}
	// if(tox > this->line[toy]){
	// 	tox = this->line[toy];
	// }
	int movx = tox - this->x;
	int movy = toy - this->y;
	char output[6] = { 0 };
	int directionx = movx>0 ? (int)Right : (int)Left;
	int directiony = movy>0 ? (int)Down : (int)Up;
	if(movx != 0) {
		sprintf(output, "\033[%d%c", abs(movx), directionx);
		write(STDOUT_FILENO, output, sizeof(output));
	}
	if(movy != 0) {
		sprintf(output, "\033[%d%c", abs(movy), directiony);
		write(STDOUT_FILENO, output, sizeof(output));
	}
	this->x = tox;
	this->y = toy;
	return *this;
}

ControlIO& ControlIO::movetoend() {
	for (int i = this->line.size()-1; i >=0; --i){
		if(this->line[i] != 0)  {
			this->movexy(0, i+1);
			return *this;
		}
	}
	this->movexy(0, 0);
	return *this;
}

ControlIO& operator<<(ControlIO& io, StandardEndLine manip) {
	manip(std::cout);
	++io.y;
	io.x = 0;
	if(io.line.size() < io.y + 1){
		io.line.push_back(0);
	}
	return io;
}

ControlIO& operator<<(ControlIO& io, const ControlIO::TextAttrib attr) {
	if(!strcmp(attr.val, "0")) {
		io.esc = "\033[";
		std::cout<<"\033[0m";
		return io;
	}
	io.esc += ";";
	io.esc += attr.val;
	return io;
}

ControlIO& operator<<(ControlIO& io, const ControlIO::Color color) {
	io.esc += ";";
	if(!strcmp(color.Font.val + 1, color.Background.val + 1)){
		io.esc += color.Font.val;
		return io;
	}
	io.esc += color.Font.val;
	io.esc += ";";
	io.esc += color.Background.val;
	return io;
}

ControlIO& operator<<(ControlIO& io, const char *str) {
	return io<<std::string(str);
}

bool strlen_cmp(std::string a, std::string b) {
	return a.size() < b.size();
}

ControlIO& operator<<(ControlIO& io, const std::string _str) {
	std::vector<std::string> str_lines;
	std::string str(_str);
	str_replace(str, "\t", std::string(io.tabwidth, ' '));
	str_split(str, str_lines, '\n');

	for(int i = 0; i<str_lines.size(); ++i) {
		if(i>0) {
			++io.y;
			io.x = 0;
		}
		if(io.y + 1 > io.line.size()){
			io.line.push_back(0);
		}
		std::string &line = str_lines[i];
		std::vector<std::string> line_sub;
		str_split(line, line_sub, '\r');
		int maxlength = std::max_element(line_sub.begin(), line_sub.end(), strlen_cmp)->size();
		if(line_sub.size() > 1)  {
			io.x = 0;
		}
		io.line[io.y] = std::max(maxlength + io.x, io.line[io.y]);
		io.x = maxlength + io.x;
	}

	std::cout<<io.esc + "m"<<str<<std::flush;
	return io;
}

ControlIO& operator<<(ControlIO& io, const int ival) {
	std::ostringstream o;
	if (!(o << ival))
    	return io;
	return io<<std::string(o.str());
}

ControlIO& operator<<(ControlIO& io, const float fval) {
	std::ostringstream o;
	if (!(o << fval))
    	return io;
	return io<<std::string(o.str());
}

const ControlIO::Color ControlIO::Black = Color(30);
const ControlIO::Color ControlIO::Red = Color(31);
const ControlIO::Color ControlIO::Green = Color(32);
const ControlIO::Color ControlIO::Yellow = Color(33);
const ControlIO::Color ControlIO::Blue = Color(34);
const ControlIO::Color ControlIO::Magenta = Color(35);
const ControlIO::Color ControlIO::Cyan = Color(36);
const ControlIO::Color ControlIO::White = Color(37);
const ControlIO::TextAttrib ControlIO::Bold = TextAttrib(1);
const ControlIO::TextAttrib ControlIO::Highlight = TextAttrib("30;47");
const ControlIO::TextAttrib ControlIO::Reset = TextAttrib("0");

// int main(void) {
// 	ControlIO conio;
// 	conio<<ControlIO::Red<<"Hello"<<ControlIO::Cyan.Background<<" World!"<<ControlIO::Reset<<std::endl;
// 	conio<<"**************************"<<std::endl;
// 	conio<<"*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n*\t\t\t*\n";
// 	conio<<"**************************"<<std::endl;
// 	conio.movexy(5, 3)<<"<";
// 	conio.movexy(20, 10)<<">";
// 	conio.movexy(13, 6)<<"@";
// 	conio.hide_cursor();
// 	ControlIO::CtrlKey key = conio.getctrch();
// 	int cnt = 0;
// 	while(key != ControlIO::Return) {
// 		switch(key) {
// 			case ControlIO::Up:
// 				if	(conio.gety() <= 2 || 
// 					(conio.getx() == 6 && conio.gety() == 4) ||
// 					(conio.getx() == 21 && conio.gety() == 11)
// 				){
// 					std::cout<<std::flush;
// 					break;
// 				}
// 				conio.mov_cursor(ControlIO::Left)<<" ";
// 				conio.mov_cursor(ControlIO::Left).mov_cursor(key)<<"@";
// 				break;
// 			case ControlIO::Down:
// 				if	(conio.gety() >= 11 ||
// 					(conio.getx() == 6 && conio.gety() == 2) ||
// 					(conio.getx() == 21 && conio.gety() == 9)
// 				){
// 					std::cout<<std::flush;
// 					break;
// 				}
// 				conio.mov_cursor(ControlIO::Left)<<" ";
// 				conio.mov_cursor(ControlIO::Left).mov_cursor(key)<<"@";
// 				break;
// 			case ControlIO::Left:
// 				if	(conio.getx() <= 3 ||
// 					(conio.getx() == 22 && conio.gety() == 10)
// 				){
// 					std::cout<<std::flush;
// 					break;
// 				}
// 				if(conio.getx() == 7 && conio.gety() == 3) {
// 					conio.mov_cursor(ControlIO::Left)<<" ";
// 					conio.movexy(19, 10)<<"@";
// 					break;
// 				}
// 				conio.mov_cursor(ControlIO::Left)<<" ";
// 				conio.mov_cursor(ControlIO::Left).mov_cursor(key)<<"@";
// 				break;
// 			case ControlIO::Right:
// 				if	(conio.getx() >= 24 ||
// 					(conio.getx() == 5 && conio.gety() == 3)
// 				){
// 					std::cout<<std::flush;
// 					break;
// 				}
// 				if(conio.getx() == 20 && conio.gety() == 10) {
// 					conio.mov_cursor(ControlIO::Left)<<" ";
// 					conio.movexy(6, 3)<<"@";
// 					break;
// 				}
// 				conio.mov_cursor(ControlIO::Left)<<" ";
// 				conio.mov_cursor(ControlIO::Left).mov_cursor(key)<<"@";
// 				break;
// 			default:
// 				break;
// 		}
// 		key = conio.getctrch();
// 	}
// 	conio.movetoend();
// 	conio.show_cursor();
// 	return 0;
// }