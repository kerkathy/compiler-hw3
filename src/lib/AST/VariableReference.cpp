#include "AST/VariableReference.hpp"

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line,
                                             const uint32_t col,
											 std::string name)
    : ExpressionNode{line, col}, name{name} {}

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line,
                                             const uint32_t col,
											 std::string name,
											 std::vector<ExpressionNode*> *indices)
    : ExpressionNode{line, col}, name{name}, indices{indices} {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableReferenceNode::print() {}

void VariableReferenceNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	if(indices && !indices->empty()) {
		for (auto &idx : *indices) 
			idx->accept(p_visitor);
	}
}
