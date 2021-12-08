#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp" 
#include "visitor/AstNodeVisitor.hpp"

class FunctionInvocationNode : public ExpressionNode {
  public:
    FunctionInvocationNode(const uint32_t line, const uint32_t col
                           /* TODO: function name, expressions */);
    ~FunctionInvocationNode() = default;

    const char *getNameCString() const;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: function name, expressions
};

#endif
