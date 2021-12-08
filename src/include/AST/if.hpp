#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"  
#include "visitor/AstNodeVisitor.hpp"                                 


class IfNode : public AstNode {
  public:
    IfNode(const uint32_t line, const uint32_t col
           /* TODO: expression, compound statement, compound statement */);
    ~IfNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: expression, compound statement, compound statement
};

#endif
