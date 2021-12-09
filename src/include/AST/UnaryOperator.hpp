#ifndef __AST_UNARY_OPERATOR_NODE_H
#define __AST_UNARY_OPERATOR_NODE_H

#include "AST/expression.hpp"
#include "AST/operator.hpp" 
#include "visitor/AstNodeVisitor.hpp"

class UnaryOperatorNode : public ExpressionNode {
  public:
    UnaryOperatorNode(const uint32_t line, const uint32_t col,
                      Operator oprt,
                      ExpressionNode *opnd
					  /* TODO: operator, expression */);
    ~UnaryOperatorNode() = default;
	
	const char *getOpCString();
    
	void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: operator, expression
	  Operator oprt;
	  ExpressionNode *opnd;
};

#endif
