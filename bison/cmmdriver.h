#pragma once

#include <string>
#include <vector>
#include <map>
#include "ast.h"

namespace cmm {

class Driver {
public:
    bool trace_scanning;
    bool trace_parsing;
    std::string streamname;

    Driver(class NProgram& prog);

    bool parse_stream(std::istream& in,
              const std::string& sname = "stream input");
    bool parse_string(const std::string& input,
              const std::string& sname = "string stream");
    bool parse_file(const std::string& filename);

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void error(const class location& l, const std::string& m);
    ~Driver();

    class Scanner *lexer;
    class NProgram &program;

    typedef std::vector<std::string> StrVec;
    StrVec *filebuf;

};

}