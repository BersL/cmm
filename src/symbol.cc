#include "symbol.h"
#include <sstream>
#include <typeinfo>
#include <cstring>

SymbolTable::SymbolTable(SymbolTable *_parent): parent(_parent) {
    type_size[INT_TYPE] = 4;
    type_size[DOUBLE_TYPE] = 8;
    
}

const cmm::Node* SymbolTable::lookup_symbol(const std::string &key, SymbolTable::NodeType type, bool upward) const {
    // std::string key = id->identifier;
    switch(type) {
    case SymbolTable::Func:
        if(upward) {
            for(const SymbolTable *table = this; table != NULL; table = upward ? table->parent : NULL) {
                std::unordered_map<std::string, const cmm::NFunctionDecStatement*>::const_iterator it = table->func_table.find(key);
                if(it != table->func_table.end()) {
                    return it->second;
                }
            }
        }
        break;
    case SymbolTable::Var:
        for(const SymbolTable *table = this; table != NULL; table = upward ? table->parent : NULL) {
            std::unordered_map<std::string, const cmm::NVariableDeclaration*>::const_iterator it = table->var_table.find(key);
            if(it != table->var_table.end()) {
                return it->second;
            }
        }
        break;
    case SymbolTable::Type:
        for(const SymbolTable *table = this; table != NULL; table = upward ? table->parent : NULL) {
            std::unordered_map<std::string, const cmm::NStructStatement*>::const_iterator it = table->type_table.find(key);
            if(it != table->type_table.end()) {
                return it->second;
            }
        }
        break;
    }
    return NULL;
}

bool SymbolTable::set_symbol(const cmm::Node *node, SymbolTable::NodeType type) {
    switch(type) {
    case SymbolTable::Func: {
        const cmm::NFunctionDecStatement *func = (const cmm::NFunctionDecStatement*)node;
        std::string key = *(func->identifier);
        if(this->func_table.count(key)) return false;
        this->func_table[key] = func;
    }
        break;
    case SymbolTable::Var: {
        const cmm::NVariableDeclaration *var = (const cmm::NVariableDeclaration*)node;
        std::string key = *(var->identifier);
        if(this->var_table.count(key)) return false;
        this->var_table[key] = var;
    }
        break;
    case SymbolTable::Type: {
        const cmm::NStructStatement *type = (const cmm::NStructStatement*)node;
        std::string key = *(type->identifier);
        if(this->type_table.count(key)) return false;
        this->type_table[key] = type;
    }
        break;
    }
    return true;
}
 

std::string SymbolTable::get_expr_type(const cmm::NExpression *expr) const {
    if(strcmp(typeid(*expr).name(), cmm::NFunctionCallExpression::className()) == 0) {
        // Check Return Type
        const cmm::NFunctionCallExpression *fcall = (const cmm::NFunctionCallExpression *)expr;
        const cmm::NFunctionDecStatement *func = (const cmm::NFunctionDecStatement*)lookup_symbol(fcall->identifier->identifier, SymbolTable::Func);
        if(func == NULL) {
            return "";
        }
        if(func->return_type == NULL){
            return "void";
        }
        return func->return_type->type;
    }else if(strcmp(typeid(*expr).name(), cmm::NUnaryExpression::className()) == 0) {
        const cmm::NUnaryExpression *unary = (const cmm::NUnaryExpression *)expr;
        return get_expr_type(unary->opd);
    }else if(strcmp(typeid(*expr).name(), cmm::NBinaryExpression::className()) == 0) {
        const cmm::NBinaryExpression *binary = (const cmm::NBinaryExpression *)expr;
        return get_expr_type(binary->lhs);
    }else if(strcmp(typeid(*expr).name(), cmm::NAssignmentExpression::className()) == 0) {
        const cmm::NAssignmentExpression *assignment = (const cmm::NAssignmentExpression *)expr;
        return get_expr_type(assignment->lhs);
    }else if(expr->isVariable()) {
        const cmm::NVariableDeclaration *var = (const cmm::NVariableDeclaration*)lookup_symbol(expr->identifier->identifier, SymbolTable::Var);
        if(var == NULL) {
            return "";
        }
        std::string cur_var_type = var->type->type;
        for (std::deque<cmm::NIdentifier*>::const_iterator i = expr->member.begin(); i != expr->member.end(); ++i) {
            const cmm::NIdentifier *member = *i;
            const cmm::NStructStatement *str_dec = (const cmm::NStructStatement*)this->lookup_symbol(cur_var_type, SymbolTable::Type);
            cur_var_type = str_dec->member_type(member);
        }
        if(var->count > 1 && expr->index == NULL) {
            return ARRAY_TYPE;
        }
        return cur_var_type;
    }else if(strcmp(typeid(*expr).name(), cmm::NLiteral::className()) == 0) {
        const cmm::NLiteral *literal = (const cmm::NLiteral *)expr;
        if(literal->type == cmm::NLiteral::Int) {
            return INT_TYPE;
        }else if(literal->type == cmm::NLiteral::Double){
            return DOUBLE_TYPE;
        }
    }
    return "";
}

size_t SymbolTable::struct_size(const cmm::NStructStatement *str_dec) {
	size_t size = 0;
	for (std::deque<cmm::NVariableDecStatement*>::const_iterator i = str_dec->declaration_statement_list.begin();
			i != str_dec->declaration_statement_list.end(); ++i) {
		const cmm::NVariableDecStatement* dec_stmt = *i;
        size_t type_s = 0;
        std::string type = dec_stmt->type->type;
        if(this->type_size.count(type)) {
            type_s = this->type_size[type];
        } else {
            const cmm::NStructStatement *str_dec = (const cmm::NStructStatement *)this->lookup_symbol(type, SymbolTable::Type);
            this->type_size[type] = this->struct_size(str_dec);
        }
		size += type_s * dec_stmt->declaration_list.size();
	}
	return size;
}