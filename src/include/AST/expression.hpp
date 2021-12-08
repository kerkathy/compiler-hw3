#ifndef __AST_EXPRESSION_NODE_H
#define __AST_EXPRESSION_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp" 
#include "visitor/AstNodeVisitor.hpp"

class ExpressionNode : public AstNode {
  public:
    ExpressionNode(const uint32_t line, const uint32_t col);
    ~ExpressionNode() = default;
//    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

  protected:
    // for carrying type of result of an expression
    // TODO: for next assignment
};

#endif
