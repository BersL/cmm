#include <fstream>
#include <iostream>

#include "cmmscanner.h"
#include "cmmphaser.h"

#define _DEBUG

int main(int argc, char **argv) {
	cmm::Scanner scanner(&std::cin, &std::cout);
	/// Semantic value of the look-ahead.
    cmm::Parser::semantic_type yylval;
    /// Location of the look-ahead.
    cmm::Parser::location_type yylloc;
	while(scanner.lex(&yylval, &yylloc)!=0) {
		std::cout<<"Location:"<<yylloc<<std::endl;
	}
	return 0;

}