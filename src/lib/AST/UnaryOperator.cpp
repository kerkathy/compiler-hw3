#include "AST/UnaryOperator.hpp"

// TODO
UnaryOperatorNode::UnaryOperatorNode(const uint32_t line, const uint32_t col, Operator oprt, ExpressionNode *opnd)
    : ExpressionNode{line, col}, oprt{oprt}, opnd{opnd} {}

const char *UnaryOperatorNode::getOpCString() {
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

// TODO: You may use code snippets in AstDumper.cpp
void UnaryOperatorNode::print() {}

void UnaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    opnd->accept(p_visitor);
}
