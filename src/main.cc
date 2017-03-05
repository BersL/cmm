#include <fstream>
#include <iostream>
#include <string>
#include <signal.h>
#include <stdlib.h>

#include "cmmdriver.h"
#include "ast.h"

void handle_int(int sig);
void reset_terminal(void);
void segfault_sigaction(int signal, siginfo_t *si, void *arg);

static ControlIO conio;

int main(int argc, char **argv) {
	atexit(reset_terminal);
	signal(SIGINT, handle_int);
	struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);

	cmm::NProgram *program = new cmm::NProgram;
	cmm::Driver driver(program);

	conio.tabwidth = 4;
	conio.hide_cursor();

	bool file_flag = false;
	bool print_tree = false;
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i] == std::string ("-p")) {
	    	driver.trace_parsing = true;
		}
		else if (argv[i] == std::string ("-s")) {
	    	driver.trace_scanning = true;
		}else if (argv[i] == std::string ("-t")) {
			print_tree = true;
		}else{
	    	if(driver.parse_file(argv[i])){
	    		file_flag = true;
				if(print_tree)
	    			program->print(conio, 0, 1);
	    	}else{
				std::cerr<<driver.error_line.size()<<" errors generated."<<std::endl;
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
    	program->print(conio, 0, 1);
	}
	conio.movetoend();
	conio.show_cursor();
	return 0;
}

void reset_terminal(void) {
	conio.movetoend();
	conio.tty_reset();
	std::cout<<"\033[?25h";
}

void handle_int(int sig) {
	std::cout<<std::endl<<"\033[1;31m"<<"Keyboard Interrupt.\033[0m"<<std::endl;
	exit(2);
}

void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
	printf("\033[?25h");
    printf("Caught segfault at address \033[1;31m%p\033[0m\n", si->si_addr);
    exit(0);
}