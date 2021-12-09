#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include "AST/AstDumper.hpp"  

#include <vector>
#include <string>

class CompoundStatementNode : public AstNode {
  public:
    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<CompoundStatementNode*> *statements); 
						  //std::vector<AstNode*> *statements); 

                          /* TODO: declarations, statements );*/
    ~CompoundStatementNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
	void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	std::vector<DeclNode*> *decls;
	std::vector<CompoundStatementNode*> *statements;
	// TODO: declarations, statements
};

#endif
