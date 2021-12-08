#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include "AST/AstDumper.hpp" 

class FunctionNode : public AstNode {
  public:
    FunctionNode(const uint32_t line, const uint32_t col
                 /* TODO: name, declarations, return type,
                  *       compound statement (optional) */);
    ~FunctionNode() = default;

    void print() override;
	void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	std::string name;
	std::vector<DeclNode*> *decls;
	std::string type;
	CompoundStatementNode *compound;
	// TODO: name, declarations, return type, compound statement
};

#endif
