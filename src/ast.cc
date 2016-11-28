#include "ast.h"

namespace cmm {

void NProgram::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<ControlIO::Highlight<<"▶ NProgram"<<ControlIO::Reset;
	os.getch();
	os.movexy(depth * os.tabwidth, depth);
	os<<"▼ NProgram"<<std::endl;
	int sub_stmt_count = this->statement_list.size();
	int sub_stmt_pos_y[sub_stmt_count];

	for (int i = 0; i < sub_stmt_count; ++i){
		this->statement_list[i]->print(os, depth+1, 1);
		sub_stmt_pos_y[i] = depth+1+i;
	}

	// std::deque<NStatement*>::const_iterator it = this->statement_list.begin();
	// os.movexy((depth+1) * os.tabwidth, depth + 1);
	// os<<ControlIO::Highlight;
	// (*it)->print(os, depth, 0);
	// os<<ControlIO::Reset;
	// ControlIO::CtrlKey key = os.getctrch();
	// int cur_sel = 0;
	// bool fold_state[sub_stmt_count];
	// memset(fold_state, 0, sizeof(fold_state));

	// while(key != ControlIO::Return) {
	// 	os.movexy(depth * os.tabwidth, sub_stmt_pos_y[cur_sel]);
	// 	(*(it+cur_sel))->print(os, depth+1, fold_state[cur_sel]);
	// 	switch(key) {
	// 	case ControlIO::Up:
	// 		--cur_sel;
	// 		if(cur_sel<0)
	// 			cur_sel = sub_stmt_count - 1;
	// 		break;
	// 	case ControlIO::Down:
	// 		++cur_sel; 
	// 		cur_sel %= sub_stmt_count;
	// 		break;
	// 	case ControlIO::Tab:{
	// 		fold_state[cur_sel] = !fold_state[cur_sel];
	// 		os.movexy(depth * os.tabwidth, sub_stmt_pos_y[cur_sel]);
	// 		std::cout<<"\033[J";
	// 		// int cur_pos_y = os.gety();
	// 		(*(it+cur_sel))->print(os, depth+1, fold_state[cur_sel]);
	// 		// int delta_y = os.gety() - cur_pos_y - 1;
	// 		// for (int i = 0; i < delta_y; i++)
	// 		// {
	// 		// 	std::cout<<"\033[D";
	// 		// }
	// 		for(int i = cur_sel + 1; i<sub_stmt_count; ++i) {
	// 			sub_stmt_pos_y[i] = os.gety();
	// 			(*(it+i))->print(os, depth+1, fold_state[i]);
	// 		}
	// 	}
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// 	os.movexy((depth+1) * os.tabwidth, sub_stmt_pos_y[cur_sel]);
	// 	os<<ControlIO::Highlight;
	// 	(*(it+cur_sel))->print(os, depth, 0);
	// 	os<<ControlIO::Reset;

	// 	key = os.getctrch();
	// }
}

void NIdentifier::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NIdentifier: "<<ControlIO::Bold<<this->identifier<<ControlIO::Reset<<std::endl;
}

void NStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NStatement"<<std::endl;
}

void NExpression::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NExpression"<<std::endl;
}

void NVariableDecStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<< (detail ? "▼" : "▶") <<" NVariableDeclarationStatement"<<std::endl;
	if(detail) {
		this->type->print(os, depth+1, 1);
		for (std::deque<NVariableDeclaration*>::const_iterator i = this->declaration_list.begin(); i != this->declaration_list.end(); ++i){
			(*i)->print(os, depth+1, 1);
		}
	}
}

void NSpecifier::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NSpecifier: "<<ControlIO::Bold<<this->type<<ControlIO::Reset<<std::endl;
}

void NVariableDeclaration::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▼ NVariableDeclaration"<<std::endl;
	this->identifier->print(os, depth+1);
	if(this->count > 1) {
		this->depth_print(os, depth+2);
		os<<"Dimension: "<<this->count<<std::endl;
	}
	if(this->member && this->member->identifier != "") {
		this->depth_print(os, depth+2);
		os<<"Member: "<<this->member->identifier<<std::endl;
	}
	if(this->assignmentExp) {
		this->depth_print(os, depth+1);
		os<<"Assignment:"<<std::endl;
		this->assignmentExp->print(os, depth+2);
	}
}

void NFunctionParameter::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▼ NFunctionParameter"<<std::endl;
	this->type->print(os, depth+1);
	this->identifier->print(os, depth+1);
}

void NFunctionDecStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<< (detail ? "▼" : "▶") <<" NFunctionDecStatement"<<std::endl;
	if(detail) {
		if(this->return_type) {
			this->return_type->print(os, depth+1);
		}
		this->identifier->print(os, depth+1);
		for (std::deque<NFunctionParameter*>::const_iterator i = this->param_list.begin(); i != this->param_list.end(); ++i){
			(*i)->print(os, depth+1);
		}
		this->block->print(os, depth+1, 1);
	}
}

void NStructStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<< (detail ? "▼" : "▶") <<" NStructStatement"<<std::endl;
	if(detail) {
		this->identifier->print(os, depth+1);
		for (std::deque<NVariableDecStatement*>::const_iterator i = this->declaration_statement_list.begin(); i != this->declaration_statement_list.end(); ++i){
			(*i)->print(os, depth+1);
		}
	}
}

void NExpressionStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▼ NExpressionStatement"<<std::endl;
	this->exp->print(os, depth+1);
}

void NInBlockStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NInBlockStatement"<<std::endl;
}

void NBlockStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	// this->depth_print(os, depth);
	// os<<"▼ NBlockStatement"<<std::endl;
	this->block->print(os, depth, 1);
}

void NReturnStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<(this->exp ? "▼" : "▶")<<" NReturnStatement"<<std::endl;
	if(this->exp) {
		this->exp->print(os, depth+1);
	}
}

void NIfStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▼ NIfStatement"<<std::endl;
	if(this->condition) {
		this->condition->print(os, depth+1);
	}
	if(this->statement) {
		this->statement->print(os, depth+1);
	}
	if(this->else_stmt) {
		this->depth_print(os, depth);
		os<<"┗━ ElseStatement"<<std::endl;
		this->else_stmt->print(os, depth+1);
	}
}

void NWhileStatement::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▼ NWhileStatement"<<std::endl;
	if(this->condition) {
		this->condition->print(os, depth+1);
	}
	if(this->statement) {
		this->statement->print(os, depth+1);
	}
}

void NBlock::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▼ NBlock"<<std::endl;
	for (std::deque<NVariableDecStatement*>::const_iterator i = this->var_dec_list.begin(); i != this->var_dec_list.end(); ++i){
		(*i)->print(os, depth+1);
	}
	for (std::deque<NInBlockStatement*>::const_iterator i = this->stmt_list.begin(); i != this->stmt_list.end(); ++i){
		(*i)->print(os, depth+1);
	}
}

void NFloat::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NFloat: "<<ControlIO::Bold<<this->value<<ControlIO::Reset<<std::endl;
}

void NInteger::print(AST_OS &os, unsigned int depth = 0, bool detail = 1) const {
	this->depth_print(os, depth);
	os<<"▶ NInteger: "<<ControlIO::Bold<<this->value<<ControlIO::Reset<<std::endl;
}

}