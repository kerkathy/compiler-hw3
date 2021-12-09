#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"                                 
#include "AST/decl.hpp" 
#include "AST/assignment.hpp" 
#include "AST/ConstantValue.hpp" 
#include "AST/CompoundStatement.hpp" 

class ForNode : public AstNode {
  public:
    ForNode(const uint32_t line, const uint32_t col,
			DeclNode *loop_var,
			AssignmentNode *init_stmt,
			ConstantValueNode *cond,
			CompoundStatementNode *body
			/* TODO: declaration, assignment, expression,
             *       compound statement */);
    ~ForNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: declaration, assignment, expression, compound statement
	DeclNode *loop_var;
	AssignmentNode *init_stmt;
	ConstantValueNode *cond;
	CompoundStatementNode *body;	
};

#endif
