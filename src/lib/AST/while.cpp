#include "AST/while.hpp"

// TODO
WhileNode::WhileNode(const uint32_t line, const uint32_t col, ExpressionNode *cond, CompoundStatementNode *body)
    : AstNode{line, col}, cond{cond}, body{body} {}

// TODO: You may use code snippets in AstDumper.cpp
void WhileNode::print() {}

void WhileNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	cond->accept(p_visitor);
	body->accept(p_visitor);

}
