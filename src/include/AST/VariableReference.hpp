#ifndef __AST_VARIABLE_REFERENCE_NODE_H
#define __AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp"  
#include "visitor/AstNodeVisitor.hpp"                                 

#include <vector>
#include <string>

class VariableReferenceNode : public ExpressionNode {
  public:
    // normal reference
    VariableReferenceNode(const uint32_t line, const uint32_t col,
						  std::string name
						 /* TODO: name */);
    // array reference
	VariableReferenceNode(const uint32_t line, const uint32_t col,
						  std::string name,
						  std::vector<ExpressionNode*> *indices
                          /* TODO: name, expressions */);
    ~VariableReferenceNode() = default;

	const char *getNameCString() const { return name.c_str(); } ;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: variable name, expressions
	std::string name;
	std::vector<ExpressionNode*> *indices;
};

#endif
