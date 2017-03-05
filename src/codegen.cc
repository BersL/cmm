#include "codegen.h"
#include "strutils.h"
#include <sstream>
#include <queue>
#include <vector>
#include <map>

using std::string;
using std::queue;
using std::vector;
using std::stringstream;
using std::endl;
using std::map;

static map<string, string> const_table;

static string gen_temp_var() {
    static int cnt = 0;
    char temp[32];
    sprintf(temp, "t%d", ++cnt);
    return std::string(temp);
}

static string gen_temp_label() {
    static int cnt = 0;
    char temp[32];
    sprintf(temp, "label%d", ++cnt);
    return std::string(temp);
}

static string gen_temp(const std::string &expr, std::ostream &os) {
    string temp = gen_temp_var();
    os<<temp<<" := "<<expr<<endl;
    return temp;
}

void CodeGenMgr::gen_IR(const cmm::NProgram *program, std::ostream &os) const {
    for (std::deque<cmm::NStatement*>::const_iterator i = program->statement_list.begin(); i != program->statement_list.end(); ++i) {
        const cmm::NStatement *stmt = *i;
        if(strcmp(typeid(*stmt).name(), cmm::NVariableDecStatement::className()) == 0) {
            const cmm::NVariableDecStatement *stmt = (const cmm::NVariableDecStatement *)*i;
            stmt->codeGen(this->sym_table, os);
        }else if(strcmp(typeid(*stmt).name(), cmm::NFunctionDecStatement::className()) == 0) {
            os<<endl;
            const cmm::NFunctionDecStatement *stmt = (const cmm::NFunctionDecStatement*)*i;
            stmt->codeGen(this->sym_table, os);
        }
    }
}

static string binary_ins(const string &op) {
    if(op[0] == '=') return "beq ";
    else if(op[0] == '!') return "bne ";
    else if(op == ">=") return "bge ";
    else if(op == "<=") return "ble ";
    else if(op[0] == '>') return "bgt ";
    else if(op[0] == '<') return "blt ";
    else return "";
}

void CodeGenMgr::gen_code(const cmm::NProgram *program, std::ostream &os) {
    stringstream ss;
    this->gen_IR(program, ss);
    os<<"IR:"<<ss.str()<<endl;
    os<<".data"<<endl;
    os<<"_prompt: .asciiz \"Enter an integer:\""<<endl;
    os<<"_ret: .asciiz \"\\n\""<<endl;
    os<<".globl main"<<endl;
    os<<".text"<<endl;
    os<<"read:"<<endl;
    os<<"li $v0, 4"<<endl;
    os<<"la $a0, _prompt"<<endl;
	os<<"syscall"<<endl;
	os<<"li $v0, 5"<<endl;
	os<<"syscall"<<endl;
	os<<"jr $ra"<<endl;
	os<<"write:"<<endl;
	os<<"li $v0, 1"<<endl;
	os<<"syscall"<<endl;
	os<<"li $v0, 4"<<endl;
	os<<"la $a0, _ret"<<endl;
	os<<"syscall"<<endl;
	os<<"move $v0, $0"<<endl;
	os<<"jr $ra"<<endl<<endl;   
    this->gen_target(ss, os);
}

void CodeGenMgr::load_reg(const std::string &var, int index, std::ostream &os) {
    if(var_address.count(var) == 0) {
        var_address[var] = this->total_size;
        this->total_size += 4;
    }
    int addr = var_address[var];
    os<<"lw $t"<<index<<", "<<addr<<"($sp)"<<endl;
}

void CodeGenMgr::store_reg(const std::string &var, int index, std::ostream &os)  {
    int addr;
    if(var_address.count(var) == 0) {
        var_address[var] = this->total_size;
        this->total_size += 4;
    }
    addr = var_address[var];
    os<<"sw $t"<<index<<", "<<addr<<"($sp)"<<endl;
}

void CodeGenMgr::gen_target(std::istream &ir_is, std::ostream &os) {
    string ir;
    int arg_count = 0;
    while(getline(ir_is, ir)) {
        vector<string> str_mem;
        str_split(ir, str_mem, ' ');
        if(str_mem.size() <= 1) continue;
        if(str_mem[0] == "LABEL") {
            os<<str_mem[1]<<":"<<endl;
        } else if(str_mem[0] == "GOTO") {
            os<<"j "<<str_mem[1]<<endl;
        } else if(str_mem[0] == "RETURN") {
            if(str_mem[1].size() > 0) {
                load_reg(str_mem[1], 0, os);
                os<<"move $v0, $t0"<<endl;
            }
            os<<"jr $ra"<<endl;
        } else if(str_mem[0] == "IF") {
            string op = str_mem[2];
            load_reg(str_mem[1], 0, os);
            load_reg(str_mem[3], 1, os);
            os<<binary_ins(op)<<"$t0, $t1, "<<str_mem[5]<<endl;
        } else if(str_mem[2] == "CALL" || str_mem[0] == "CALL" || str_mem[0] == "READ" || str_mem[0] == "WRITE") {
            os<<"addi $sp, $sp, -4"<<endl;
            os<<"sw $ra, 0($sp)"<<endl;
            sp_offset.push(total_size);
            total_size = 0;
            if(str_mem[0] == "CALL") {
                os<<"jal "<<str_mem[1]<<endl;
            } else {
                if(str_mem[0] == "READ") os<<"jal read"<<endl;
                else if(str_mem[0] == "WRITE") os<<"jal write"<<endl;
                else os<<"jal "<<str_mem[3]<<endl;
            }
            os<<"lw $ra, 0($sp)"<<endl;
            os<<"addi $sp, $sp, 4"<<endl;
            total_size = sp_offset.top();
            sp_offset.pop();
            if(str_mem[0] != "CALL") {
                os<<"move $v0, $t0"<<endl;
                load_reg(str_mem[0], 0, os);
            }
            arg_count = 0;
        } else if(str_mem[0] == "PARAM") {
            os<<"lw $t0, "<<arg_count*4<<"($sp)"<<endl;
            store_reg(str_mem[1], 0 , os);
            --arg_count;
        } else if(str_mem[0] == "ARG") {
            load_reg(str_mem[1], 0, os);
            os<<"sw $t0, "<<arg_count*4<<"($sp)"<<endl;
            ++arg_count;
        } else if(str_mem[0] == "FUNCTION") {
            os<<str_mem[1]<<":"<<endl;
            os<<"addi $sp, $sp, -"<<(arg_count+1)*4<<endl;
        } else {
            if(str_mem.size() == 5) {
                load_reg(str_mem[2], 1, os);
                load_reg(str_mem[4], 2, os);
                if(str_mem[3][0] == '+') {
                    os<<"add $t0, $t1, $t2"<<endl;
                    store_reg(str_mem[0], 0, os);
                } else if(str_mem[3][0] == '-') {
                    os<<"sub $t0, $t1, $t2"<<endl;
                } else if(str_mem[3][0] == '*') {
                    os<<"mul $t0, $t1, $t2"<<endl;
                } else if(str_mem[3][0] == '/') {
                    os<<"div $t1, $t2"<<endl;
                    os<<"mflo $t0"<<endl;
                }
                store_reg(str_mem[0], 0, os);
            } else if(str_mem[0][0] == '*') {
                load_reg(str_mem[3], 1, os);
                os<<"sw $t1, 0($t0)"<<endl;
                store_reg(str_mem[1], 0, os);
            } else if(str_mem[2][0] == '#') {
                os<<"li $t0, "<<str_mem[2].substr(1)<<endl;
                store_reg(str_mem[0], 0, os);
            } else if(str_mem[2][0] == '*') {
                load_reg(str_mem[3], 1, os);
                os<<"lw $t0, 0($t1)"<<endl;
                store_reg(str_mem[1], 0, os);
            } else {
                load_reg(str_mem[2], 1, os);
                os<<"move $t0, $t1"<<endl;
                store_reg(str_mem[1], 0, os);
            }
        }
    }
}

namespace cmm {
// Expression
string NExpression::codeGen(const SymbolTable *table, std::ostream &os) const {
    const NVariableDeclaration *expr_dec = 
        (const NVariableDeclaration *)table->lookup_symbol(this->identifier->identifier, SymbolTable::Var);
    const NStructStatement *str_dec;
    if(expr_dec) {
         str_dec = (const NStructStatement *)table->lookup_symbol(expr_dec->type->type, SymbolTable::Type);
    }
    string expr = this->identifier->identifier;
    if(this->index) {
        size_t size;
        if(str_dec == NULL) size = expr_dec->type->type == DOUBLE_TYPE ? 8 : 4;
        else size = ((SymbolTable *)table)->struct_size(str_dec);
        string offset = gen_temp_var();
        string index_expr = this->index->codeGen(table, os);
        if(index_expr.find(' ') != string::npos) {
            index_expr = gen_temp(index_expr, os);
        }
        os<<offset<<" := "<<index_expr<<" * #"<<size<<endl;
        string expr_ptr = gen_temp_var();
        os<<expr_ptr<<" := &"<<expr<<" + "<<offset<<endl;
        expr = "*"+expr_ptr;
    }
    return expr;
}

string NLiteral::codeGen(const SymbolTable *table, std::ostream &os) const {
    stringstream ss;
    if(this->type == Int) {
        ss<<"#"<<this->value.int_val;
    }else if(this->type == Double) {
        ss<<"#"<<this->value.double_val;
    }
    std::string const_val(ss.str());
    string temp ;
    if(const_table.count(const_val) == 0) {
        temp = gen_temp(const_val ,os);
        const_table[const_val] = temp;
    }else{
        temp = const_table[const_val];
    }
    return temp;
}

string NBinaryExpression::codeGen(const SymbolTable *table, std::ostream &os) const {
    string lhs_var = this->lhs->codeGen(table, os);
    if(lhs_var.find(' ') != string::npos) {
        lhs_var = gen_temp(lhs_var, os);
    }
    string rhs_var = this->rhs->codeGen(table, os);
    if(rhs_var.find(' ') != string::npos) {
        rhs_var = gen_temp(rhs_var, os);
    }
    return lhs_var + " " + this->oprstr() + " " + rhs_var;
}

string NAssignmentExpression::codeGen(const SymbolTable *table, std::ostream &os) const {
    string lhs_var = this->lhs->codeGen(table, os);
    if(lhs_var.find(' ') != string::npos) {
        lhs_var = gen_temp(lhs_var, os);
    }
    string rhs_var = this->rhs->codeGen(table, os);

    if(rhs_var.find(' ') != string::npos && rhs_var.find("CALL") != 0) {
        rhs_var = gen_temp(rhs_var, os);
    }
    os<<lhs_var<<" := "<<rhs_var;
    return lhs_var;
}

string NUnaryExpression::codeGen(const SymbolTable *table, std::ostream &os) const {
    string opd_var = this->opd->codeGen(table, os);
    if(opd_var.find(' ') != string::npos) {
        opd_var = gen_temp(opd_var, os);
    }
    if(this->opr == Neg) {
        return "#0 - " + opd_var;
    }
    return opd_var;
}

string NFunctionCallExpression::codeGen(const SymbolTable *table, std::ostream &os) const {
    if(this->identifier->identifier == "read") {
        std::string var = gen_temp_var();
        os<<"READ "<<var<<endl;
        return var;
    }else if(this->identifier->identifier == "write") {
        string arg = this->argument_list[0]->codeGen(table, os);
        if(arg.find(' ') != string::npos) {
            arg = gen_temp(arg, os);
        }
        return "WRITE " + arg;
    }
    vector<string> args;
    for(std::deque<NExpression*>::const_reverse_iterator i = this->argument_list.rbegin(); i != this->argument_list.rend(); ++i){
        string arg = (*i)->codeGen(table, os);
        if(arg.find(' ') != string::npos) {
            arg = gen_temp(arg, os);
        }
        args.push_back(arg);
    }
    for(vector<string>::const_iterator it = args.begin(); it != args.end(); ++it) {
        os<<"ARG "<<*it<<endl;
    }
    return "CALL " + this->identifier->identifier;
}

void NVariableDeclaration::codeGen(const SymbolTable *table, std::ostream &os) const {
    if(this->count > 1) {
        os<<"DEC #"<<count * (type->type == DOUBLE_TYPE ? 8 : 4)<<endl; 
    }
    if(this->assignmentExp) {
        this->assignmentExp->codeGen(table, os);
    }
}

// Statement
void NBlock::codeGen(const SymbolTable *table, std::ostream &os) const {
    for (std::deque<NVariableDecStatement*>::const_iterator i = this->var_dec_list.begin(); i != this->var_dec_list.end(); ++i){
        const NVariableDecStatement *var_dec_stmt = *i;
        for (std::deque<NVariableDeclaration*>::const_iterator i = var_dec_stmt->declaration_list.begin(); i != var_dec_stmt->declaration_list.end(); ++i){
			const NVariableDeclaration *dec = *i;
            dec->codeGen(table, os);
		}
    }
    for (std::deque<NInBlockStatement*>::const_iterator i = this->stmt_list.begin(); i != this->stmt_list.end(); ++i) {
        const NInBlockStatement *stmt = *i;
        stmt->codeGen(table, os);
    }
}

void NVariableDecStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    for (std::deque<NVariableDeclaration*>::const_iterator i = this->declaration_list.begin(); i != this->declaration_list.end(); ++i){
        const NVariableDeclaration *dec = *i;
        dec->codeGen(table, os);
    }
}


void NFunctionDecStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    os<<"FUNCTION "<<this->identifier->identifier<<" :"<<endl;
    for (std::deque<NVariableDeclaration*>::const_iterator i = this->param_list.begin(); i != this->param_list.end(); ++i) {
        const NVariableDeclaration *dec = *i;
        os<<"PARAM "<<dec->identifier->identifier<<endl;
    }
    this->block->codeGen(table, os);
}

void NBlockStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    this->block->codeGen(table, os);
}

void NExpressionStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    std::string expr = this->exp->codeGen(table, os);
    if(expr.find(' ') != string::npos) {
        os<<expr;
    }
    os<<endl;
}

void NReturnStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    string ret_var;
    if(this->exp) {
        ret_var = this->exp->codeGen(table, os);
        if(ret_var.find(' ') != string::npos) {
            ret_var = gen_temp(ret_var, os);
        }
    }
    os<<"RETURN "<<ret_var<<endl;
}

void NIfStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    string label1 = gen_temp_label();
    string label2 = gen_temp_label();

    string condition = this->condition->codeGen(table, os);
    if(condition.find(' ') == string::npos) {
        condition += " == 1";
    }
    os<<"IF "<<condition<<" GOTO "<<label1<<endl;
    this->else_stmt->codeGen(table, os);
    os<<"GOTO "<<label2<<endl;
    os<<"LABEL "<<label1<<" :"<<endl;
    this->statement->codeGen(table, os);
    os<<"LABEL "<<label2<<" :"<<endl;
}

void NWhileStatement::codeGen(const SymbolTable *table, std::ostream &os) const {
    string label1 = gen_temp_label();
    string label2 = gen_temp_label();
    string label3 = gen_temp_label();

    std::string condition = this->condition->codeGen(table, os);
    if(condition.find(' ') == string::npos) {
        condition += " == 1";
    }
    os<<"LABEL "<<label1<<" :"<<endl;
    os<<"IF "<<condition<<" GOTO "<<label2<<endl;
    os<<"GOTO "<<label3<<endl;
    os<<"LABEL "<<label2<<" :"<<endl;
    this->statement->codeGen(table, os);
    os<<"GOTO "<<label1<<endl;
    os<<"LABEL "<<label3<<" :"<<endl;
}
}