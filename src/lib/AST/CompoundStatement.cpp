#include "AST/CompoundStatement.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<AstNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}
/*
CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<CompoundStatementNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}

CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<AssignmentNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}

CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<PrintNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}


CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<ReadNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}


CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<IfNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}


CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<WhileNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}


CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<ForNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}


CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<ReturnNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}


CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
											 std::vector<DeclNode*> *decls,
											 std::vector<FunctionNode*> *statements)
    : AstNode{line, col}, decls{decls}, statements{statements} {}
*/

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print() {}

void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	//printf("before decl\n");
	if(!decls->empty()) {
		for (auto &decl : *decls) {
			decl->accept(p_visitor);
		}
	}
	//printf("finish decl\n");
	if(!statements->empty()) {
		// for debug
		//printf("accepting statement in compstmtnode.cpp\n");
		//printf("stmt size: %d\n", statements->size());
		for (auto &stmt : *statements) {
//			printf("in for loop\n");
			if (stmt)
				stmt->accept(p_visitor);
		}
	}
}
