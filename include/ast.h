#pragma once

#include <deque>
#include <list>
#include <string>
#include <iostream>
#include "ControlIO.h"

#define AST_OS ControlIO

namespace cmm {

// 节点抽象类
class Node {
public:
	virtual ~Node() {};
	virtual void print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const = 0;
	inline void depth_print(AST_OS &os, unsigned int depth) const {
		for(int i = 0; i<depth; ++i) {
			os<<"      ";
		}
	}
};

class NIdentifier: public Node {
public:
	std::string identifier;
	NIdentifier(std::string *_identifier): identifier(*_identifier) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual ~NIdentifier() {}
};

class NSpecifier: public Node {
public:
	std::string type;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NSpecifier(std::string *_type):
		type(*_type) {}

	NSpecifier(NIdentifier *_type):
		type(_type->identifier) {}

	virtual ~NSpecifier() {}
};

class NVariableType: public NSpecifier {

};

class NStructType: public NSpecifier {

};

class NStatement: public Node {
public:
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
};

class NExpression: public Node {
public:
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
};

class NVariableDeclaration: public NExpression {
public:
	int count;
	NIdentifier *identifier;
	NIdentifier *member;
	NExpression *assignmentExp;

	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NVariableDeclaration(NIdentifier *_identifier, int _count = 0): 
		identifier(_identifier), count(_count), assignmentExp(NULL), member(NULL) {}

	NVariableDeclaration(NIdentifier *_identifier, NIdentifier *_member):
		identifier(_identifier), member(_member), assignmentExp(NULL), count(0) {}
	virtual ~NVariableDeclaration() {
		delete identifier;
		delete assignmentExp;
	}
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

class NVariableDecStatement: public NStatement {
public:
	NSpecifier *type;
	std::deque<NVariableDeclaration*> declaration_list;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NVariableDecStatement(NSpecifier *_type, std::deque<NVariableDeclaration*> *dec_list):
	 	type(_type), declaration_list(dec_list->begin(), dec_list->end()) {}

	virtual ~NVariableDecStatement() {
		delete type;
		for (std::deque<NVariableDeclaration*>::iterator i = declaration_list.begin(); i != declaration_list.end(); ++i){
			NVariableDeclaration *dec = *i;
			delete dec;
		}
	}
};

class NStructStatement: public NStatement {
public:
	NIdentifier *identifier;
	std::deque<NVariableDecStatement*> declaration_statement_list;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NStructStatement(NIdentifier *_identifier, std::deque<NVariableDecStatement*> *dec_stmt_list):
		identifier(_identifier), declaration_statement_list(dec_stmt_list->begin(), dec_stmt_list->end()) {}

	virtual ~NStructStatement() {
		delete identifier;
		for (std::deque<NVariableDecStatement*>::iterator i = declaration_statement_list.begin(); i != declaration_statement_list.end(); ++i){
			NVariableDecStatement* stmt = *i;
			delete stmt;
		}
	}
};

class NFunctionParameter: public Node {
public:
	NSpecifier *type;
	NIdentifier *identifier;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NFunctionParameter(NSpecifier *_type, NIdentifier *_identifier):
		type(_type), identifier(_identifier) {}

	virtual ~NFunctionParameter() {
		delete type;
		delete identifier;
	}
};

class NInBlockStatement: public NStatement {
public:
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
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
};

class NBlockStatement: public NInBlockStatement {
public:
	NBlock *block;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NBlockStatement(NBlock *_block): block(_block) {}
}
;

class NFunctionDecStatement: public NStatement {
public:
	NSpecifier *return_type;
	NIdentifier *identifier;
	std::deque<NFunctionParameter*> param_list;
	NBlock *block;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;

	NFunctionDecStatement(NSpecifier *_ret, NIdentifier *_identifier, std::deque<NFunctionParameter*> *_param_list, NBlock *_block):
		return_type(_ret), identifier(_identifier), block(_block) {
			if(_param_list != NULL) {
				param_list = *_param_list;
			}
		}

	virtual ~NFunctionDecStatement() {
		delete return_type;
		delete block;
		delete identifier;
		for (std::deque<NFunctionParameter*>::iterator i = this->param_list.begin(); i != this->param_list.end(); ++i){
			delete *i;
		}
	}
};


class NExpressionStatement: public NInBlockStatement {
public:
	NExpression *exp;
	NExpressionStatement(NExpression *_exp): exp(_exp) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual ~NExpressionStatement() {
		delete exp;
	}
};

class NReturnStatement: public NInBlockStatement {
public:
	NExpression *exp;
	NReturnStatement(NExpression *_exp): exp(_exp) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual ~NReturnStatement() {
		delete exp;
	}

};

class NIfStatement: public NInBlockStatement {
public:
	NExpression *condition;
	NInBlockStatement *statement;
	NInBlockStatement *else_stmt;
	NIfStatement(NExpression *_condition, NInBlockStatement *_statement, NInBlockStatement *_else): 
		condition(_condition), statement(_statement), else_stmt(_else) {}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual ~NIfStatement() {
		delete condition;
		delete statement;
		delete else_stmt;
	}
};

class NWhileStatement: public NInBlockStatement {
public:
	NExpression *condition;
	NInBlockStatement *statement;
	NWhileStatement(NExpression *_condition, NInBlockStatement *_statement): 
		condition(_condition), statement(_statement){}
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	virtual ~NWhileStatement() {
		delete condition;
		delete statement;
	}
}
;


class NFloat: public NExpression {
public:
	float value;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	NFloat(float _val = 0.0): value(_val) {}
	virtual ~NFloat() {}
};

class NInteger: public NExpression {
public:
	int value;
	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
	NInteger(int _val = 0.0): value(_val) {}
	virtual ~NInteger() {}
};


// class NAssignmentExpression: public NExpression {
// public:
// 	std::string lhs;
// 	NExpression *rhs;
// 	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
// 	virtual ~NAssignmentExpression() {
// 		delete rhs;
// 	}
// };

// class NBinaryExpression: public NExpression {
// public:
// 	int op;
// 	NExpression *lhs;
// 	NExpression *rhs;
// 	NBinaryExpression(NExpression *_lhs, NExpression *_rhs, int _op):
// 		lhs(_lhs), rhs(_rhs), op(_op) {}
// 	virtual void print(AST_OS &os, unsigned int depth, bool detail) const;
// 	virtual ~NBinaryExpression() {
// 		delete lhs;
// 		delete rhs;
// 	}
// }


}