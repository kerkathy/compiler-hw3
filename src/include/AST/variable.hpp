#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include "AST/type.hpp" 

#include <string>

class VariableNode : public AstNode {
  public:
	// with const value
    VariableNode(const uint32_t line, const uint32_t col,
				 std::string name, VarType *type,
				 ConstantValueNode *constant);
				/* TODO: variable name, type, constant value */
	// zero const value
    VariableNode(const uint32_t line, const uint32_t col,
				 std::string name, VarType *type);
    ~VariableNode() = default;

	const char *getNameCString() const;
	const char *getTypeCString() const;
    void print() override;
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	std::string name;
	VarType *type;
    ConstantValueNode *constant;
	// TODO: variable name, type, constant value
};

#endif
