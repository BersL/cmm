#pragma once

#include <string>
#include <vector>
#include <map>
#include "ast.h"
#include "symbol.h"
#include "location.hh"
#include "codegen.h"

namespace cmm {

class Driver {
    enum SymError { Undefinition, Redefinition };
    bool vardec_symbol_check(SymbolTable &table, const NVariableDecStatement *stmt, bool is_struct_dec = false);
    bool block_symbol_check(const NFunctionDecStatement *func_stmt, SymbolTable *table, const NBlock *block);
    void symbol_error(const std::string symbol, const location &loc, const location &loc2, Driver::SymError type);
    bool is_valid_expr(SymbolTable *table, const NExpression *expr);
    bool is_expr_type_valid(SymbolTable *table, const NExpression *expr);
    bool is_valid_func_vall(SymbolTable *table, const NFunctionCallExpression *fcall);
    bool is_valid_variable(SymbolTable *table, const NExpression *expr);
    bool is_valid_inblock_stmt(const NFunctionDecStatement *func_stmt, SymbolTable *table, const cmm::NInBlockStatement *stmt);
public:
    bool trace_scanning;
    bool trace_parsing;
    std::string streamname;

    Driver(class NProgram *prog);

    bool parse_stream(std::istream& in,
              const std::string& sname = "stream input");
    bool parse_string(const std::string& input,
              const std::string& sname = "string stream");
    bool parse_file(const std::string& filename);

    bool semantic_analyze();

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void error(const class location& l, const std::string& m);
    void message(const class location& l, const std::string& m);
    ~Driver();

    class Scanner *lexer;
    class NProgram *program;

    typedef std::vector<std::string> StrVec;
    StrVec *filebuf;
    SymbolTable *symbol_table;
    std::vector<int> error_line;
    CodeGenMgr *code_gen_mgr;
};

}