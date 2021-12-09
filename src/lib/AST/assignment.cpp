#include "AST/assignment.hpp"

// TODO
AssignmentNode::AssignmentNode(const uint32_t line, const uint32_t col,
							   VariableReferenceNode *lval,
							   ExpressionNode *expr)
    : AstNode{line, col}, lval{lval}, expr{expr} {}

// TODO: You may use code snippets in AstDumper.cpp
void AssignmentNode::print() {}

void AssignmentNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	lval->accept(p_visitor);
	expr->accept(p_visitor);
}
