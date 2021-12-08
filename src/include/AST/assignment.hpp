#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"
#include "visitor/AstNodeVisitor.hpp"                                 


class AssignmentNode : public AstNode {
  public:
    AssignmentNode(const uint32_t line, const uint32_t col
                   /* TODO: variable reference, expression */);
    ~AssignmentNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: variable reference, expression
};

#endif
