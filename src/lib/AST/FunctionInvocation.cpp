#include "AST/FunctionInvocation.hpp"

// TODO
FunctionInvocationNode::FunctionInvocationNode(const uint32_t line,
                                               const uint32_t col,
											   std::string name,
											   std::vector<ExpressionNode*> *args)
    : ExpressionNode{line, col}, name{name}, args{args} {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionInvocationNode::print() {}

void FunctionInvocationNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	if(!args->empty()) {
		for (auto &arg : *args) {
			arg->accept(p_visitor);
		}
	}
}
