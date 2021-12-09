#ifndef AST_PROGRAM_NODE_H
#define AST_PROGRAM_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"

#include <string>
#include <vector>
#include <cstdio>

class ProgramNode final : public AstNode {
  private:
    std::string name;
	std::string type;
	const std::vector<DeclNode*> *decls;
	const std::vector<FunctionNode*> *functions;
	CompoundStatementNode *compound;

  public:
    ~ProgramNode() = default;
    ProgramNode(const uint32_t line, const uint32_t col,
                const char *p_name,
                const char *p_type,
				const std::vector<DeclNode*> *p_decls,	
				const std::vector<FunctionNode*> *p_functions,
				CompoundStatementNode *p_compound);

    // visitor pattern version: 
	const char *getNameCString() const;
	const char *getTypeCString() const;
    
	void print() override;
	
	void accept(AstNodeVisitor &p_visitor) override { 
		p_visitor.visit(*this); 
	}
	void visitChildNodes(AstNodeVisitor &p_visitor);
};

#endif
