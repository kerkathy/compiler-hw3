#include "AST/BinaryOperator.hpp"

// TODO
BinaryOperatorNode::BinaryOperatorNode(const uint32_t line, const uint32_t col, 
									   Operator oprt, 
									   ExpressionNode *left_opnd, ExpressionNode *right_opnd)
    : ExpressionNode{line, col}, oprt{oprt}, 
	  left_opnd{left_opnd}, right_opnd{right_opnd} {}

// TODO: You may use code snippets in AstDumper.cpp
void BinaryOperatorNode::print() {}

const char *BinaryOperatorNode::getOpCString() {
	const char *ch;
	switch(oprt) {
		case Operator::UNARY_MINUS: 
			ch = "neg";
			break;
		case Operator::MULTIPLY: 
			ch = "*";
			break;
		case Operator::DIVIDE:
			ch = "/";
			break;
		case Operator::MOD: 
			ch = "mod";
			break;
		case Operator::PLUS: 
			ch = "+";
			break;
		case Operator::MINUS: 
			ch = "-";
			break;
		case Operator::LESS: 
			ch = "<";
			break;
		case Operator::LESS_OR_EQUAL: 
			ch = "<=";
			break;
		case Operator::GREATER: 
			ch = ">";
			break;
		case Operator::GREATER_OR_EQUAL: 
			ch = ">=";
			break;
		case Operator::EQUAL: 
			ch = "=";
			break;
		case Operator::NOT_EQUAL: 
			ch = "<>";
			break;
		case Operator::NOT: 
			ch = "not";
			break;
		case Operator::AND: 
			ch = "and";
			break;
		case Operator::OR: 
			ch = "or";
	}
	return ch;
}

void BinaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
   // TODO
	left_opnd->accept(p_visitor);
	right_opnd->accept(p_visitor);
}
