#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include "AST/AstDumper.hpp" 
#include "AST/scalar.h"

class FunctionNode : public AstNode {
  public:
    FunctionNode(const uint32_t line, const uint32_t col,
				 const char *name,
				 std::vector<DeclNode*> *decls,
				 Scalar return_type,
				 CompoundStatementNode *compound
                 /* TODO: name, declarations, return type,
                  *       compound statement (optional) */);
    FunctionNode(const uint32_t line, const uint32_t col,
				 const char *name,
				 //std::string name,
				 std::vector<DeclNode*> *decls,
				 Scalar return_type);
     ~FunctionNode() = default;

    const char *getNameCString() const;
    const char *getTypeCString() const;
	const std::vector<std::string> getProtoCString() const;
    
	void print() override;
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	std::string name;
	std::vector<DeclNode*> *decls;
	Scalar return_type;
	CompoundStatementNode *compound;
	// TODO: name, declarations, return type, compound statement
};

#endif
