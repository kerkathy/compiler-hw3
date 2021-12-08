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
	if(!decls->empty()) {
		for (auto &decl : *decls) {
			decl->accept(p_visitor);
		}
	}
	if(!statements->empty()){
		for (auto &stmt : *statements) {
			stmt->accept(p_visitor);
		}
	}
}
