#include "AST/for.hpp"

// TODO
ForNode::ForNode(const uint32_t line, const uint32_t col,
            DeclNode *loop_var,
            AssignmentNode *init_stmt,
            ConstantValueNode *cond,
            CompoundStatementNode *body)
    : AstNode{line, col}, loop_var{loop_var}, init_stmt{init_stmt},
	  cond{cond}, body{body} {}

// TODO: You may use code snippets in AstDumper.cpp
void ForNode::print() {}

void ForNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	loop_var->accept(p_visitor);
	init_stmt->accept(p_visitor);
	cond->accept(p_visitor);
	body->accept(p_visitor);
}
