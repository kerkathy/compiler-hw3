#include "AST/variable.hpp"
#include <string>
#include <sstream>

VariableNode::VariableNode(const uint32_t line, const uint32_t col, 
						   std::string name, VarType *type,
						   ConstantValueNode *constant)
    : AstNode{line, col} {
		this->name = name;
		this->type = type;
		this->constant = constant;
	}
VariableNode::VariableNode(const uint32_t line, const uint32_t col, 
						   std::string name, VarType *type)
    : AstNode{line, col} {
		this->name = name;
		this->type = type;
	}

const char *VariableNode::getNameCString() const { return name.c_str(); }
const char *VariableNode::getTypeCString() const { 
	std::stringstream ss;
	switch (type->scalar_type) {
		case Scalar::INTEGER_SC:
			ss << "integer";
			break;
		case Scalar::BOOLEAN_SC:
			ss << "boolean";
			break;
		case Scalar::REAL_SC:
			ss << "real";
			break;
		case Scalar::STRING_SC:
			ss << "string";
			break;
	}
	if (!type->array_dim->empty()) {
		ss << " ";
		for (auto &dim : *(type->array_dim)) {
			ss << "[" << dim << "]";
		}
	}
	return ss.str().c_str(); 
}

// TODO: You may use code snippets in AstDumper.cpp
void VariableNode::print() {}

void VariableNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	// for debug
	//std::printf("about to accept constant node.\n");
	if (constant)
		constant->accept(p_visitor);
}
