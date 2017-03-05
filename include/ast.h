#ifndef AST_H
#define AST_H

#include <deque>
#include <list>
#include <string>
#include <iostream>
#include "ControlIO.h"
#include "location.hh"

#define AST_OS ControlIO

#define INT_TYPE "int"
#define DOUBLE_TYPE "double"
#define ARRAY_TYPE "array"

class SymbolTable;

namespace cmm {

// 节点抽象类
class Node {
public:
	location loc;
	virtual ~Node() {};
	virtual void print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const = 0;
	void depth_print(AST_OS &os, unsigned int depth) const {
		for(int i = 0; i<depth; ++i) {
			os<<"    ";
		}
	}
};

class NIdentifier: public Node {
public:
	std::string identifier;
	NIdentifier(std::string *_identifier): identifier(*_identifier) {}
	NIdentifier(const std::string &_identifier): identifier(_identifier) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual ~NIdentifier() {}
	operator std::string() const {
		return identifier;
	}
	bool operator==(const NIdentifier& rhs) const  {
		return this->identifier == rhs.identifier;
	}
};

class NSpecifier: public Node {
public:
	std::string type;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NSpecifier(std::string *_type):
		type(*_type) {}

	NSpecifier(const std::string &_type):
		type(_type) {}

	NSpecifier(NIdentifier *_type):
		type(_type->identifier) {}
};


class NExpression: public Node {
public:
	NIdentifier *identifier;
	std::deque<NIdentifier*> member;
	NExpression *index;
	NExpression(NIdentifier *_identifier): identifier(_identifier), index(NULL) {}
	NExpression(): identifier(NULL), index(NULL) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual bool isVariable() const;

	virtual std::string codeGen(const SymbolTable *table, std::ostream &os) const;

	virtual ~NExpression() {
		delete identifier;
		delete index;
	}
};

class NVariableType: public NSpecifier {

};

class NStructType: public NSpecifier {

};

class NStatement: public Node {

};

class NProgram: public Node  {
public:
	std::deque<NStatement*> statement_list;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	virtual ~NProgram() {
		for (std::deque<NStatement*>::iterator i = statement_list.begin(); i != statement_list.end(); ++i){
			NStatement* stmt = *i;
			delete stmt;
		}
	}
};

class NVariableDeclaration: public Node {
public:
	NSpecifier *type;
	int count;
	NIdentifier *identifier;
	NExpression *assignmentExp;

	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	NVariableDeclaration(NIdentifier *_identifier, int _count = 1): 
		identifier(_identifier), count(_count), assignmentExp(NULL), type(NULL) {}

	NVariableDeclaration(NSpecifier *_type, NIdentifier *_identifier):
		identifier(_identifier), count(1), assignmentExp(NULL), type(_type) {}

	virtual ~NVariableDeclaration() {
		delete identifier;
		delete assignmentExp;
	}

	void codeGen(const SymbolTable *table, std::ostream &os) const;
};

class NVariableDecStatement: public NStatement {
public:
	NSpecifier *type;
	std::deque<NVariableDeclaration*> declaration_list;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	static const char* className() { return "N3cmm21NVariableDecStatementE"; }

	const NVariableDeclaration* operator [] (const std::string &identifier) const;

	NVariableDecStatement(NSpecifier *_type, std::deque<NVariableDeclaration*> *dec_list):
	 	declaration_list(dec_list->begin(), dec_list->end()) {
		for (std::deque<NVariableDeclaration*>::iterator i = declaration_list.begin(); i != declaration_list.end(); ++i){
			NVariableDeclaration *dec = *i;
			dec->type = _type;
		}
	}

	virtual ~NVariableDecStatement() {
		for (std::deque<NVariableDeclaration*>::iterator i = declaration_list.begin(); i != declaration_list.end(); ++i){
			NVariableDeclaration *dec = *i;
			delete dec;
		}
	}
	void codeGen(const SymbolTable *table, std::ostream &os) const;
};

class NStructStatement: public NStatement {
public:
	NIdentifier *identifier;
	std::deque<NVariableDecStatement*> declaration_statement_list;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	static const char* className() { return "N3cmm16NStructStatementE"; }

	NStructStatement(NIdentifier *_identifier, std::deque<NVariableDecStatement*> *dec_stmt_list):
		identifier(_identifier), declaration_statement_list(dec_stmt_list->begin(), dec_stmt_list->end()) {}

	virtual ~NStructStatement() {
		delete identifier;
		for (std::deque<NVariableDecStatement*>::iterator i = declaration_statement_list.begin(); i != declaration_statement_list.end(); ++i){
			NVariableDecStatement* stmt = *i;
			delete stmt;
		}
	}

	std::string member_type(const NIdentifier *member) const;
};

class NInBlockStatement: public NStatement {
public:
	// virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual void codeGen(const SymbolTable *table, std::ostream &os) const = 0;
};


class NBlock: public Node {
public:
	std::deque<NVariableDecStatement*> var_dec_list;
	std::deque<NInBlockStatement*> stmt_list;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NBlock(std::deque<NVariableDecStatement*> *_var_dec_list, std::deque<NInBlockStatement*> *_stmt_list):
		var_dec_list(_var_dec_list->begin(), _var_dec_list->end()), stmt_list(_stmt_list->begin(), _stmt_list->end()) {}
	NBlock(std::deque<NInBlockStatement*> *_stmt_list):
		stmt_list(_stmt_list->begin(), _stmt_list->end()) {}
	NBlock() {}
	void codeGen(const SymbolTable *table, std::ostream &os) const;
};

class NBlockStatement: public NInBlockStatement {
public:
	NBlock *block;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	static const char* className() { return "N3cmm15NBlockStatementE"; }

	NBlockStatement(NBlock *_block): block(_block) {}
	void codeGen(const SymbolTable *table, std::ostream &os) const;
}
;

class NFunctionDecStatement: public NStatement {
public:
	NSpecifier *return_type;
	NIdentifier *identifier;
	std::deque<NVariableDeclaration*> param_list;
	NBlock *block;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	static const char* className() { return "N3cmm21NFunctionDecStatementE"; }

	NFunctionDecStatement(NSpecifier *_ret, NIdentifier *_identifier, std::deque<NVariableDeclaration*> *_param_list, NBlock *_block):
		return_type(_ret), identifier(_identifier), block(_block) {
			if(_param_list != NULL) {
				param_list = *_param_list;
			}
		}

	virtual ~NFunctionDecStatement() {
		delete return_type;
		delete block;
		delete identifier;
		for (std::deque<NVariableDeclaration*>::iterator i = this->param_list.begin(); i != this->param_list.end(); ++i){
			delete *i;
		}
	}
	void codeGen(const SymbolTable *table, std::ostream &os) const;
};


class NExpressionStatement: public NInBlockStatement {
public:
	static const char* className() { return "N3cmm20NExpressionStatementE"; }
	NExpression *exp;
	NExpressionStatement(NExpression *_exp): exp(_exp) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	void codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NExpressionStatement() {
		delete exp;
	}
};

class NReturnStatement: public NInBlockStatement {
public:
	static const char* className() { return "N3cmm16NReturnStatementE"; }
	NExpression *exp;
	NReturnStatement(NExpression *_exp): exp(_exp) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	void codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NReturnStatement() {
		delete exp;
	}

};

class NIfStatement: public NInBlockStatement {
public:
	static const char* className() { return "N3cmm12NIfStatementE"; }
	NExpression *condition;
	NInBlockStatement *statement;
	NInBlockStatement *else_stmt;
	NIfStatement(NExpression *_condition, NInBlockStatement *_statement, NInBlockStatement *_else): 
		condition(_condition), statement(_statement), else_stmt(_else) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	void codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NIfStatement() {
		delete condition;
		delete statement;
		delete else_stmt;
	}
};

class NWhileStatement: public NInBlockStatement {
public:
	static const char* className() { return "N3cmm15NWhileStatementE"; }
	NExpression *condition;
	NInBlockStatement *statement;
	NWhileStatement(NExpression *_condition, NInBlockStatement *_statement): 
		condition(_condition), statement(_statement){}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	void codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NWhileStatement() {
		delete condition;
		delete statement;
	}
};

class NLiteral: public NExpression {
public:
	static const char* className() { return "N3cmm8NLiteralE"; }

	union {
		int int_val;
		double double_val;
	} value;
	enum ValueType { Int, Double };
	ValueType type;
	explicit NLiteral(int _val) { value.int_val = _val; type = Int; }
	explicit NLiteral(double _val) { value.double_val = _val; type = Double; }
	virtual bool isVariable() const;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	std::string codeGen(const SymbolTable *table, std::ostream &os) const;
};

class NBinaryExpression: public NExpression {
public:
	static const char* className() { return "N3cmm17NBinaryExpressionE"; }
	
	enum OprType { Add, Sub, Mul, Div, And, Or, Equal, NotEqual, Greater, Less, GreaterOrEqual, LessOrEqual };
	OprType opr;
	NExpression *lhs;
	NExpression *rhs;
	std::string oprstr() const;
	virtual bool isVariable() const;
	NBinaryExpression(NExpression *_lhs, NExpression *_rhs, OprType _opr):
		lhs(_lhs), rhs(_rhs), opr(_opr) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	std::string codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NBinaryExpression() {
		delete lhs;
		delete rhs;
	}
};

class NUnaryExpression: public NExpression {
public:
	static const char* className() { return "N3cmm16NUnaryExpressionE"; }
	enum OprType { Neg, Not };
	OprType opr;
	NExpression *opd;
	std::string oprstr() const;
	virtual bool isVariable() const;
	NUnaryExpression(NExpression *_opd, OprType _opr):
		opd(_opd), opr(_opr) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	std::string codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NUnaryExpression() {
		delete opd;
	}
};

class NAssignmentExpression: public NExpression {
public:
	static const char* className() { return "N3cmm21NAssignmentExpressionE"; }
	NExpression *lhs;
	NExpression *rhs;
	virtual bool isVariable() const;
	NAssignmentExpression(NExpression *_lhs, NExpression *_rhs):
		lhs(_lhs), rhs(_rhs) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	std::string codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NAssignmentExpression() {
		delete lhs; delete rhs;
	}
};

class NFunctionCallExpression: public NExpression {
public:
	static const char* className() { return "N3cmm23NFunctionCallExpressionE"; }

	std::deque<NExpression*> argument_list;
	virtual bool isVariable() const;

	NFunctionCallExpression(NIdentifier *_identifier, std::deque<NExpression*> *_arguments) {
		this->identifier = _identifier;
		if(_arguments) {
			this->argument_list = *_arguments;
		}
	}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	std::string codeGen(const SymbolTable *table, std::ostream &os) const;
	virtual ~NFunctionCallExpression() {
		for (std::deque<NExpression*>::iterator i = this->argument_list.begin(); i != this->argument_list.end(); ++i){
			delete *i;
		}
	}
};

}
#endif