#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "ast.h"

class SymbolTable {
    std::unordered_map<std::string, const cmm::NFunctionDecStatement*> func_table;
    std::unordered_map<std::string, const cmm::NVariableDeclaration*> var_table;
    std::unordered_map<std::string, const cmm::NStructStatement*> type_table;
    std::unordered_map<std::string, size_t> type_size;
    SymbolTable *parent;
public:
    enum NodeType { Func, Var, Type };
    const cmm::Node* lookup_symbol(const std::string &key, NodeType type, bool upward = true) const;
    bool set_symbol(const cmm::Node *node, NodeType type);
    SymbolTable(SymbolTable *_parent = NULL);

    std::string get_expr_type(const cmm::NExpression *expr) const;
    size_t struct_size(const cmm::NStructStatement *str_dec);
};