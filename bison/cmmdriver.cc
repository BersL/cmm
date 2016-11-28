#include <fstream>
#include <sstream>

#include "cmmdriver.h"
#include "cmmscanner.h"
#include "strutils.h"

namespace cmm {

Driver::Driver(class NProgram& prog)
    : trace_scanning(false),
      trace_parsing(false),
      program(prog)
{
    this->filebuf = new StrVec;
}

bool Driver::parse_stream(std::istream& in, const std::string& sname){
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);

    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename){
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    std::string buf;
    while(getline(in, buf)){
        this->filebuf->push_back(buf);
    }
    in.clear();
    in.seekg(std::ios::beg);
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m) {
    std::cerr<<"\033[1;m"<<*(l.begin.filename)<<":"<<l.begin.line<<":"<<l.begin.column<<":"
             <<"\033[1;31m"<<" error: "<<"\033[0m"
             <<"\033[1;m"<<m<<std::endl
             <<"\033[0m";
    std::cerr<<this->filebuf->at(l.begin.line - 1)<<std::endl;
    std::cerr<<std::string(l.begin.column - 1, ' ')<<"\033[1;32m"<<"^";
    if(l.begin.line == l.end.line && l.begin.column < l.end.column - 1) {
        std::cerr<<std::string(l.end.column - l.begin.column - 1, '~');
    }
    std::cerr<<"\033[0m"<<std::endl;
}

Driver::~Driver(){
    delete this->filebuf;
}

}