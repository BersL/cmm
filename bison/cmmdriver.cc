#include <fstream>
#include <sstream>
#include <typeinfo>

#include "cmmdriver.h"
#include "cmmscanner.h"
#include "ast.h"
#include <cstring>

namespace cmm {

Driver::Driver(class NProgram *prog)
    : trace_scanning(false),
      trace_parsing(false),
      program(prog)
{
    this->symbol_table = new SymbolTable;
    this->filebuf = new StrVec;
    this->program = prog;
    this->code_gen_mgr = new CodeGenMgr(this->symbol_table);

    cmm::NSpecifier *int_type = new cmm::NSpecifier(INT_TYPE);
    cmm::NIdentifier *read_id = new cmm::NIdentifier("read");
    cmm::NIdentifier *write_id = new cmm::NIdentifier("write");
    cmm::NFunctionDecStatement *read_func = new cmm::NFunctionDecStatement(int_type, read_id, NULL, NULL);
    cmm::NIdentifier *param = new cmm::NIdentifier("val");
    cmm::NVariableDeclaration *param_dec = new cmm::NVariableDeclaration(int_type, param);
    std::deque<cmm::NVariableDeclaration *> *params = new std::deque<cmm::NVariableDeclaration *>;
    params->push_back(param_dec);
    cmm::NFunctionDecStatement *write_func = new cmm::NFunctionDecStatement(NULL, write_id, params, NULL);
    this->symbol_table->set_symbol(read_func, SymbolTable::Func);
    this->symbol_table->set_symbol(write_func, SymbolTable::Func);
}

bool Driver::parse_stream(std::istream& in, const std::string& sname) {
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);

    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename) {
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    std::string buf;
    while(getline(in, buf)){
        this->filebuf->push_back(buf);
    }
    in.clear();
    in.seekg(std::ios::beg);
    if(!parse_stream(in, filename)) return false;
    if(!semantic_analyze()) return false;
    // this->code_gen_mgr->gen_IR(this->program, std::cout);
    this->code_gen_mgr->gen_code(this->program, std::cout);
    return true;
}

bool Driver::parse_string(const std::string &input, const std::string& sname) {
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::symbol_error(const std::string symbol, const location &loc, const location &loc2, Driver::SymError type) {
    switch(type) {
#pragma mark Error - undeclared identifier
    case Undefinition: {
        std::string msg("use of undeclared identifier '");
        error(loc, msg + symbol + "'");
    }
        break;
#pragma mark Error - identifier redefinition
    case Redefinition: {
        std::string msg("redefinition of '");
        std::string msg2("previous definition is here");
        error(loc, msg + symbol + "'");
        message(loc2, msg2);
    }
        break;
    }
}


/// table为引用
bool Driver::vardec_symbol_check(SymbolTable &table, const cmm::NVariableDecStatement *stmt, bool is_struct_dec) {
    bool success = true;
    for (std::deque<NVariableDeclaration*>::const_iterator dec_it = stmt->declaration_list.begin();
        dec_it != stmt->declaration_list.end(); ++dec_it) {
        const NVariableDeclaration* dec = *dec_it;
        // Type Check
        if(dec->type->type != INT_TYPE 
        && dec->type->type != DOUBLE_TYPE) {
            if(this->symbol_table->lookup_symbol(dec->type->type, SymbolTable::Type) == NULL) {
#pragma mark Error - unknown type
                error(dec->type->loc, "variable has unknown type 'struct " + dec->type->type + "'");
                return false;
            }
        }
        // Symbol Check
        if(table.lookup_symbol(dec->identifier->identifier, SymbolTable::Type, false) != NULL || !table.set_symbol(dec, SymbolTable::Var)) {
            const cmm::NVariableDeclaration* prev_dec = (const cmm::NVariableDeclaration*)
                table.lookup_symbol(dec->identifier->identifier, SymbolTable::Var);
            if(prev_dec == NULL) {
                const cmm::NStructStatement *struct_stmt = (const cmm::NStructStatement*)
                    table.lookup_symbol(dec->identifier->identifier, SymbolTable::Type);
                symbol_error(*(dec->identifier), dec->identifier->loc, struct_stmt->identifier->loc, Redefinition);
            }else {
                symbol_error(*(dec->identifier), dec->identifier->loc, prev_dec->identifier->loc, Redefinition);
            }
            success = false;
        }
        // Expression Type Check
        const NExpression *expr = dec->assignmentExp;
        if(expr) {
            if(is_struct_dec) {
#pragma mark Error - variable initialization in struct
                error(expr->loc, "variable initialization in struct definition");
                return false;
            }
            if(!is_valid_expr(&table, expr)) {
                success = false;
            }else {
                std::string expr_type = table.get_expr_type(expr);
                std::string var_type = dec->type->type;
                if(var_type != expr_type) {
#pragma mark Error - invalid operands
                    error(expr->loc, "assigning to '" + var_type +"' from incompatible type '" + expr_type + "'");
                    success = false;
                }
            }
                
        }
    }
    return success;
}

/// table应为指针类型
bool Driver::block_symbol_check(const NFunctionDecStatement *func_stmt, SymbolTable *table, const cmm::NBlock *block) {
    bool success = true;
    for (std::deque<NVariableDecStatement*>::const_iterator i = block->var_dec_list.begin();
        i != block->var_dec_list.end(); ++i) {
        if(!vardec_symbol_check(*table, *i)) {
            success = false;
        }
	}
    for (std::deque<NInBlockStatement*>::const_iterator i = block->stmt_list.begin(); 
        i != block->stmt_list.end(); ++i){
        if(!is_valid_inblock_stmt(func_stmt, table, *i)) {
            success = false;
        }
	}
    return success;
}

bool Driver::is_valid_inblock_stmt(const NFunctionDecStatement *func_stmt, SymbolTable *table, const cmm::NInBlockStatement *stmt) {
    bool success = true;
    if(strcmp(typeid(*stmt).name(), NBlockStatement::className()) == 0) {
        const NBlockStatement* block_stmt = (const NBlockStatement*)stmt;
        SymbolTable *sub_table = new SymbolTable(table);
        if(!block_symbol_check(func_stmt, sub_table, block_stmt->block)) {
            success = false;
        }
        delete sub_table;
    }else if(strcmp(typeid(*stmt).name(), NReturnStatement::className()) == 0) {
        const cmm::NReturnStatement *ret_stmt = (const cmm::NReturnStatement*)stmt;
        const NSpecifier *ret_sprcifier = func_stmt->return_type;
        if(ret_sprcifier == NULL && ret_stmt->exp != NULL) {
#pragma mark - return value in a void function
            error(stmt->loc, "void function '" + func_stmt->identifier->identifier + "' should not return a value");
            return false;
        }
        if(!is_valid_expr(table, ret_stmt->exp)) {
            return false;
        }
        std::string expr_type = table->get_expr_type(ret_stmt->exp);
        if(ret_sprcifier->type != expr_type) {
#pragma mark Error - return value type incompatible
            error(ret_stmt->exp->loc, "returning '" + ret_sprcifier->type + "' from a function with incompatible result type '" + expr_type + "'");
            return false;
        }
    }else if(strcmp(typeid(*stmt).name(), NIfStatement::className()) == 0) {
        const cmm::NIfStatement *if_stmt = (const cmm::NIfStatement*)stmt;
        if(!is_valid_expr(table, if_stmt->condition)) {
            success = false;
        }
        SymbolTable *sub_table1 = new SymbolTable(table);
        if(!is_valid_inblock_stmt(func_stmt, sub_table1, if_stmt->statement)) {
            success = false;
        }
        delete sub_table1;
        if(if_stmt->else_stmt) {
            SymbolTable *sub_table2 = new SymbolTable(table);
            if(!is_valid_inblock_stmt(func_stmt, sub_table2, if_stmt->else_stmt)) {
                success = false;
            }
            delete sub_table2;
        }
    }else if(strcmp(typeid(*stmt).name(), NWhileStatement::className()) == 0) {
        const cmm::NWhileStatement *while_stmt = (const cmm::NWhileStatement*)stmt;
        if(!is_valid_expr(table, while_stmt->condition)) {
            success = false;
        }
        SymbolTable *sub_table = new SymbolTable(table);
        if(!is_valid_inblock_stmt(func_stmt, sub_table, while_stmt->statement)) {
            success = false;
        }
        delete sub_table;
    }else if(strcmp(typeid(*stmt).name(), NExpressionStatement::className()) == 0) {
        const cmm::NExpressionStatement *exp_stmt = (const cmm::NExpressionStatement*)stmt;
        if(!is_valid_expr(table, exp_stmt->exp)) {
            success = false;
        }
    }
    return success;
}

bool Driver::semantic_analyze() {
    bool success = true;
    for(std::deque<cmm::NStatement*>::const_iterator it = this->program->statement_list.begin(); 
        it != this->program->statement_list.end(); ++it) {
        const cmm::NStatement *stmt = *it;
        if(strcmp(typeid(*stmt).name(), NVariableDecStatement::className()) == 0) {
            const cmm::NVariableDecStatement *stmt = (const cmm::NVariableDecStatement *)*it;
            if(!vardec_symbol_check(*(this->symbol_table), stmt)) {
                success = false;
            }
        }else if(strcmp(typeid(*stmt).name(), NStructStatement::className()) == 0) {
            // Struct类型名本身检查
            cmm::NStructStatement *stmt = (cmm::NStructStatement*)*it;
            if(this->symbol_table->lookup_symbol(stmt->identifier->identifier, SymbolTable::Var) != NULL || 
                !this->symbol_table->set_symbol(stmt, SymbolTable::Type)) {
                const cmm::NStructStatement* prev_stmt = (const cmm::NStructStatement *)
                    this->symbol_table->lookup_symbol(stmt->identifier->identifier, SymbolTable::Type);
                if(prev_stmt == NULL) { 
                    const cmm::NVariableDeclaration *prev_dec = (const cmm::NVariableDeclaration *)
                        this->symbol_table->lookup_symbol(stmt->identifier->identifier, SymbolTable::Var);
                    symbol_error(*(stmt->identifier), stmt->identifier->loc, prev_dec->identifier->loc, Redefinition);
                }else {
                    symbol_error(*(stmt->identifier), stmt->identifier->loc, prev_stmt->identifier->loc, Redefinition);
                }
            }
            SymbolTable sub_table(this->symbol_table);
            for (std::deque<NVariableDecStatement*>::const_iterator dec_it = stmt->declaration_statement_list.begin();
		        dec_it != stmt->declaration_statement_list.end(); ++dec_it) {
		        const NVariableDecStatement* dec_stmt = *dec_it;
                if(!vardec_symbol_check(sub_table, dec_stmt, true)) {
                    success = false;
                }

	        } 
        }else if(strcmp(typeid(*stmt).name(), NFunctionDecStatement::className()) == 0) {
            const cmm::NFunctionDecStatement *stmt = (const cmm::NFunctionDecStatement*)*it;
            // 函数名检查
            if(!this->symbol_table->set_symbol(stmt, SymbolTable::Func)) {
                const cmm::NFunctionDecStatement* node = 
                    (const cmm::NFunctionDecStatement*)this->symbol_table->lookup_symbol(stmt->identifier->identifier, SymbolTable::Func);
                symbol_error(*(stmt->identifier), stmt->identifier->loc, node->identifier->loc, Redefinition);
            }
            // 参数检查
            SymbolTable *sub_table = new SymbolTable(this->symbol_table);
            for (std::deque<NVariableDeclaration*>::const_iterator it = stmt->param_list.begin();
                it != stmt->param_list.end(); ++it) {
                const cmm::NVariableDeclaration* param = *it;
                if(!sub_table->set_symbol(param, SymbolTable::Var)) {
                    const cmm::NVariableDeclaration *node = (const cmm::NVariableDeclaration *)
                        sub_table->lookup_symbol(param->identifier->identifier, SymbolTable::Var);
                    symbol_error(*(param->identifier), param->identifier->loc, node->loc, Redefinition);
                    success = false;
                }
            }
            // 语句检查
            const cmm::NBlock *block = stmt->block;
            if(!block_symbol_check(stmt, sub_table, block)){
                success = false;
            }
            delete sub_table;
        }
    }
    return success;
}

bool Driver::is_valid_expr(SymbolTable *table, const NExpression *expr) {
    if(!expr) return true;
    if(strcmp(typeid(*expr).name(), cmm::NFunctionCallExpression::className()) == 0) {
        return is_valid_func_vall(table, (const NFunctionCallExpression*)expr);
    }else if(strcmp(typeid(*expr).name(), cmm::NUnaryExpression::className()) == 0) {
        const cmm::NUnaryExpression *unary = (const cmm::NUnaryExpression *)expr;
        if(!is_valid_expr(table, unary->opd)) {
            return false;
        }
        std::string expr_type = table->get_expr_type(expr);
        if(expr_type != INT_TYPE 
        && expr_type != DOUBLE_TYPE) {
            error(expr->loc, "invalid argument type '" + expr_type +"' to unary expression");
            return false;
        }
    }else if(strcmp(typeid(*expr).name(), cmm::NBinaryExpression::className()) == 0) {
        const cmm::NBinaryExpression *binary = (const cmm::NBinaryExpression *)expr;
        if(!is_valid_expr(table, binary->lhs) || !is_valid_expr(table, binary->rhs)) {
            return false;
        }
        return is_expr_type_valid(table, expr);
    }else if(strcmp(typeid(*expr).name(), cmm::NAssignmentExpression::className()) == 0) {
        const cmm::NAssignmentExpression *assignment = (const cmm::NAssignmentExpression *)expr;
        if(assignment->lhs->isVariable() == false) {
#pragma mark Error - expression not assignable
            error(assignment->lhs->loc, "expression is not assignable");
            return false;
        }
        if(!is_valid_expr(table, assignment->lhs) || !is_valid_expr(table, assignment->rhs)) {
            return false;
        }
        return is_expr_type_valid(table, expr);
    }else if(expr->isVariable()){
        const cmm::NVariableDeclaration *var = (const cmm::NVariableDeclaration*)
            table->lookup_symbol(expr->identifier->identifier, SymbolTable::Var);
        if(var == NULL) {
            // undefined
#pragma mark Error - undeclared identifier
            error(expr->identifier->loc, "use of undeclared identifier '" + expr->identifier->identifier + "'");
            return false;
        }
        if(!is_valid_variable(table, expr)) {
            return false;
        }
    }else{
        // Literal
        return true;
    }
    return true;
}

bool Driver::is_expr_type_valid(SymbolTable *table, const cmm::NExpression *expr) {
    if(strcmp(typeid(*expr).name(), cmm::NBinaryExpression::className()) == 0) {
        const cmm::NBinaryExpression *binary = (const cmm::NBinaryExpression *)expr;
        if(!is_expr_type_valid(table, binary->lhs) || !is_expr_type_valid(table, binary->rhs)) {
            return false;
        }
        std::string lhs_type = table->get_expr_type(binary->lhs);
        std::string rhs_type = table->get_expr_type(binary->rhs);
        if(lhs_type != rhs_type) {
#pragma mark Error - invalid operands
            error(expr->loc, "invalid operands to binary expression ('" + lhs_type + "' and '" + rhs_type + "')");
            return false;
        }
        return true;
    }else if(strcmp(typeid(*expr).name(), cmm::NAssignmentExpression::className()) == 0) {
        const cmm::NAssignmentExpression *assignment = (const cmm::NAssignmentExpression *)expr;
        if(!is_expr_type_valid(table, assignment->lhs) || !is_expr_type_valid(table, assignment->rhs)) {
            return false;
        }
        std::string lhs_type = table->get_expr_type(assignment->lhs);
        std::string rhs_type = table->get_expr_type(assignment->rhs);
        if(lhs_type != rhs_type) {
#pragma mark Error - invalid operands
            error(expr->loc, "assigning to '" + lhs_type +"' from incompatible type '" + rhs_type + "'");
            return false;
        }
        return true;
    }
    return true;
}

bool Driver::is_valid_func_vall(SymbolTable *table, const cmm::NFunctionCallExpression *fcall) {
    const cmm::NFunctionDecStatement *func = (const cmm::NFunctionDecStatement*)
        this->symbol_table->lookup_symbol(fcall->identifier->identifier, SymbolTable::Func); // 最顶层作用域搜索函数声明
    if(func == NULL) {
#pragma mark Error - undeclared function identifier
        error(fcall->loc, "use of undeclared function '" + fcall->identifier->identifier + "'");
        return false;
    }
    int fcall_param = fcall->argument_list.size();
    int fdec_param = func->param_list.size();
    if(fcall_param != fdec_param) {
#pragma mark Error - function call arguments number error
        std::stringstream ss;
        ss<<"too "<<(fcall_param > fdec_param ? "many" : "few")<<" arguments to function call, expected "<<fdec_param<<", have "<<fcall_param;
        error(fcall->loc, ss.str());
        message(func->loc, "'" + func->identifier->identifier + "' declared here");
        return false;
    }
    for (std::deque<NExpression*>::const_iterator i = fcall->argument_list.begin(); i != fcall->argument_list.end(); ++i) {
        const NExpression *expr = *i;
        if(!is_valid_expr(table, expr)) {
            return false;
        }
	}
    // Argument Type Check
    for (size_t i = 0; i != fdec_param; ++i) {
        const NVariableDeclaration *param = func->param_list[i];
        const NExpression *arg = fcall->argument_list[i];
        std::string arg_type = table->get_expr_type(arg);
        if(arg_type != param->type->type) {
#pragma mark Error - argument type not incompatible with parameter type
            error(arg->loc, "passing '" + arg_type + "' to parameter of incompatible type '" + param->type->type + "'");
            message(param->loc, "passing argument to parameter here");
            return false;
        }
    }
    return true;
}

bool Driver::is_valid_variable(SymbolTable *table, const cmm::NExpression *expr) {
    const cmm::NVariableDeclaration *var = (const cmm::NVariableDeclaration*)
         table->lookup_symbol(expr->identifier->identifier, SymbolTable::Var);
    if(expr->index) {
        if(!is_valid_expr(table, expr->index)) {
            return false;
        }
        std::string index_type = table->get_expr_type(expr->index);
        if(index_type != INT_TYPE) {
#pragma mark Error - array index not integer
            error(expr->index->loc, "array subscript is not an integer");
            return false;
        }
    }

    std::string cur_var_type = var->type->type;
    
    for (std::deque<NIdentifier*>::const_iterator i = expr->member.begin(); i != expr->member.end(); ++i) {
        const NIdentifier *member = *i;
        const cmm::NStructStatement *str_dec = (const cmm::NStructStatement*)
             this->symbol_table->lookup_symbol(cur_var_type, SymbolTable::Type); // 最顶层搜索结构体声明
        if(str_dec == NULL) {
#pragma mark Error - member reference base type is not a structure
            error(member->loc, "member reference base type is not a structure");
            return false;
        }
        cur_var_type = str_dec->member_type(member);
        if(cur_var_type != "") goto next_member;
#pragma mark Error - member reference not found
        error(member->loc, "no member named '" + member->identifier + "' in 'struct " + str_dec->identifier->identifier + "'");
        return false;
next_member:
        continue;
	}
    return true;
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

    this->error_line.push_back(l.end.line);
}

void Driver::message(const class location& l,
		        const std::string& m) {
    std::cerr<<"\033[1;m"<<*(l.begin.filename)<<":"<<l.begin.line<<":"<<l.begin.column<<":"
             <<"\033[1;38;5;243m"<<" note: "<<"\033[0m"
             <<m<<std::endl;
    std::cerr<<this->filebuf->at(l.begin.line - 1)<<std::endl;
    std::cerr<<std::string(l.begin.column - 1, ' ')<<"\033[1;32m"<<"^";
    if(l.begin.line == l.end.line && l.begin.column < l.end.column - 1) {
        std::cerr<<std::string(l.end.column - l.begin.column - 1, '~');
    }
    std::cerr<<"\033[0m"<<std::endl;
}

Driver::~Driver() {
    delete this->filebuf;
    delete this->symbol_table;
}

}