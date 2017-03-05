#include "symbol.h"
#include "ast.h"
#include <map>
#include <stack>

class CodeGenMgr {
    SymbolTable *sym_table;
    int total_size;
    std::map<std::string, int> var_address;
    std::stack<int> sp_offset;
    void load_reg(const std::string &var, int index, std::ostream &os);
    void store_reg(const std::string &var, int index, std::ostream &os);
    void gen_target(std::istream &ir_is, std::ostream &os);
public:
    CodeGenMgr(SymbolTable *_table):
        sym_table(_table), total_size(0) {}
    void gen_IR(const cmm::NProgram *program, std::ostream &os) const;
    void gen_code(const cmm::NProgram *program, std::ostream &os);
};