#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"  
#include "AST/CompoundStatement.hpp"  
#include "visitor/AstNodeVisitor.hpp"                                 


class IfNode : public AstNode {
  public:
    IfNode(const uint32_t line, const uint32_t col,
		   ExpressionNode *cond, 
		   CompoundStatementNode *body, CompoundStatementNode *body_ofelse
           /* TODO: expression, compound statement, compound statement */);
    ~IfNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	ExpressionNode *cond;
	CompoundStatementNode *body, *body_ofelse = nullptr;
    // TODO: expression, compound statement, compound statement
};

#endif
