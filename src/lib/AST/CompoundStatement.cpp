#include "AST/CompoundStatement.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<AstNode*> *statements)
    : AstNode{line, col} {
		this->decls = decls;
		this->statements = statements;
	}

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print() {}

void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	// TODO
	std::vector<DeclNode*> decls_vec = *decls;
	for (auto &decl : decls_vec) {
		decl->accept(p_visitor);
	}
	std::vector<AstNode*> stmt_vec = *statements;
	for (auto &stmt : stmt_vec) {
		stmt->accept(p_visitor);
	}
}
