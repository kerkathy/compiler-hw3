#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp" 
#include "AST/operator.hpp" 
#include "visitor/AstNodeVisitor.hpp"

#include <memory>

class BinaryOperatorNode : public ExpressionNode {
  public:
    BinaryOperatorNode(const uint32_t line, const uint32_t col,
                       Operator oprt,
					   ExpressionNode *left_opnd, ExpressionNode *right_opnd
                       /* TODO: operator, expressions */);
    ~BinaryOperatorNode() = default;

    const char *getOpCString();
	void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	   Operator oprt;
	   ExpressionNode *left_opnd;
	   ExpressionNode *right_opnd;
    // TODO: operator, expressions
};

#endif
