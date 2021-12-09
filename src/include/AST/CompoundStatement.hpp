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
						  std::vector<AstNode*> *statements); 
/*
    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<CompoundStatementNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<AssignmentNode*> *statements);        

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<PrintNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<ReadNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<IfNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<WhileNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<ForNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<ReturnNode*> *statements); 

    CompoundStatementNode(const uint32_t line, const uint32_t col,
						  std::vector<DeclNode*> *decls, 
						  std::vector<FunctionNode*> *statements); 
*/	
                          /* TODO: declarations, statements );*/
    ~CompoundStatementNode() = default;

    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
	void visitChildNodes(AstNodeVisitor &p_visitor);

  private:
	std::vector<DeclNode*> *decls;
	std::vector<AstNode*> *statements;
	// TODO: declarations, statements
};

#endif
