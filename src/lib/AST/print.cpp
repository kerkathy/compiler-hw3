#include "AST/print.hpp"

// TODO
PrintNode::PrintNode(const uint32_t line, const uint32_t col, ExpressionNode *target)
    : AstNode{line, col}, target{target} {}

// TODO: You may use code snippets in AstDumper.cpp
void PrintNode::print() {}

void PrintNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	if(target) target->accept(p_visitor);
}
