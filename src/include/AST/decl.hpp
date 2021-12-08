#ifndef __AST_DECL_NODE_H
#define __AST_DECL_NODE_H

#include <vector>
#include <string>
#include <cstdio>

#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"  
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/IdNode.hpp"
#include "AST/type.hpp"
#include "visitor/AstNodeVisitor.hpp"

class DeclNode : public AstNode {
  public:
    // variable declaration
    DeclNode(const uint32_t line, const uint32_t col,
			 const std::vector<IdNode*> *identifiers,
			 VarType *type
			/* TODO: identifiers, type */);

    // constant variable declaration
    DeclNode(const uint32_t line, const uint32_t col,
			 const std::vector<IdNode*> *identifiers,
			 VarType *type,
			 ConstantValueNode *constant);    		
   			/* TODO: identifiers, constant */

    ~DeclNode() = default;

    void print() override;
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
	void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
    // TODO: variables
	std::vector<VariableNode*> variables;
};

#endif
