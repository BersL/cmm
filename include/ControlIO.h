#pragma once

#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>

 // this is the type of std::cout
typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
// this is the function signature of std::endl
typedef CoutType& (*StandardEndLine)(CoutType&);

class ControlIO {
	int fd;
	struct termios orig_settings;
	int x, y;
	std::vector<int> line;
	std::string esc;
public:
	int tabwidth;
	struct TextAttrib {
		char val[20];
		TextAttrib() {}
		TextAttrib(int _val) {
			int n = _val, i = 0;
			while(n) {
				++i; n /= 10;
			}
			n = _val;
			val[i] = 0;
			while(n) {
				val[--i] = (n%10) + '0';
				n /= 10;
			}
		}
		TextAttrib(const char *_val) {
			strncpy(val, _val, 19);
		}
	};
	struct Color {
		TextAttrib Font, Background;
		Color(int _val): Font((_val%10) + 30), Background((_val%10) + 40) {}
		Color(const char *_256_font, const char *_256_bkg) {
			char font[20] = "38;5;";
			char bkg[20] = "48;5;";
			strcat(font, _256_font);
			strcat(bkg, _256_bkg);
			Font = TextAttrib(font);
			Background = TextAttrib(bkg);
		}
	};

	static const Color Black, Red, Green, Yellow, Blue, Magenta, Cyan, White;
	static const TextAttrib Bold, Highlight, Reset;

	enum CtrlKey { Up = 'A' , Down = 'B', Right = 'C', Left = 'D', Return, Tab, Other };

	ControlIO(int _fd = STDIN_FILENO);

	int getch() const;
	CtrlKey getctrch() const;
	ControlIO& show_cursor();
	ControlIO& hide_cursor();
	ControlIO& mov_cursor(CtrlKey direction, unsigned linenum = 1);

	int getx() { return x; }
	int gety() { return y; }
	ControlIO& movexy(unsigned x, unsigned y);
	ControlIO& movetoend();

	int tty_cbreak() const;
	int tty_reset() const;

	friend ControlIO& operator<<(ControlIO&, const ControlIO::TextAttrib);
	friend ControlIO& operator<<(ControlIO&, const ControlIO::Color);
	friend ControlIO& operator<<(ControlIO&, const char *);
	friend ControlIO& operator<<(ControlIO&, const std::string);
	friend ControlIO& operator<<(ControlIO&, const int);
	friend ControlIO& operator<<(ControlIO&, const float);
	friend ControlIO& operator<<(ControlIO& io, StandardEndLine manip);

	~ControlIO() {
		tcsetattr(this->fd, TCSAFLUSH, &(this->orig_settings));
		std::cout<<"\033[0m";
	}
};