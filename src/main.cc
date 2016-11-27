#include <fstream>
#include <iostream>
#include <string>
#include <signal.h>

#include "cmmdriver.h"
#include "ast.h"

void handle_int(int sig);

static ControlIO conio;

int main(int argc, char **argv) {
	signal(SIGINT, handle_int);

	cmm::NProgram program;
	cmm::Driver driver(program);

	conio.tabwidth = 6;
	conio.hide_cursor();
	bool file_flag = false;
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i] == std::string ("-p")) {
	    	driver.trace_parsing = true;
		}
		else if (argv[i] == std::string ("-s")) {
	    	driver.trace_scanning = true;
		}else{
	    	if(driver.parse_file(argv[i])){
	    		file_flag = true;
	    		program.print(conio, 0, 1);
	    	}else{
				perror(argv[i]);
				return 1;
	    	}
		}
	}

	if(!file_flag) {
		std::cout << "\033[33mReading expressions from stdin\033[0m" << std::endl;

    	std::string line;
    	while( std::cout << "input: " && std::getline(std::cin, line) && !line.empty() ) {
    		if(driver.parse_string(line, "stdin")){
    			
	    	}
    	}
    	program.print(conio, 0, 1);
	}
	conio.movetoend();
	conio.show_cursor();
	return 0;
}

void handle_int(int sig) {
	conio.movetoend();
	conio.tty_reset();
	std::cout<<std::endl<<"\033[?25h\033[1;31m"<<"Keyboard Interrupt.\033[0m"<<std::endl;
	exit(2);
}