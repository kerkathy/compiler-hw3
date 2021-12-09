#include "AST/if.hpp"

// TODO
IfNode::IfNode(const uint32_t line, const uint32_t col,
           ExpressionNode *cond, 
           CompoundStatementNode *body, CompoundStatementNode *body_ofelse)
    : AstNode{line, col}, cond{cond}, body{body}, body_ofelse{body_ofelse} {}

// TODO: You may use code snippets in AstDumper.cpp
void IfNode::print() {}

void IfNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	cond->accept(p_visitor);
	body->accept(p_visitor);
	if (body_ofelse) body_ofelse->accept(p_visitor);
}
