#pragma once

#include <string>
#include "ast.h"

namespace cmm {

class Driver {
public:

    bool trace_scanning;

    bool trace_parsing;

    std::string streamname;

    Driver(class NProgram& prog);

    /** Invoke the scanner and parser for a stream.
     * @param in    input stream
     * @param sname stream name for error messages
     * @return      true if successfully parsed
     */
    bool parse_stream(std::istream& in,
              const std::string& sname = "stream input");

    /** Invoke the scanner and parser on an input string.
     * @param input input string
     * @param sname stream name for error messages
     * @return      true if successfully parsed
     */
    bool parse_string(const std::string& input,
              const std::string& sname = "string stream");

    /** Invoke the scanner and parser on a file. Use parse_stream with a
     * std::ifstream if detection of file reading errors is required.
     * @param filename  input file name
     * @return      true if successfully parsed
     */
    bool parse_file(const std::string& filename);

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void error(const class location& l, const std::string& m);

    /** Pointer to the current lexer instance, this is used to connect the
     * parser to the scanner. It is used in the yylex macro. */
    class Scanner *lexer;

    class NProgram &program;
};

}