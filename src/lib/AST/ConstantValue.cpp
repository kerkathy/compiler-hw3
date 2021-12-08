#include "AST/ConstantValue.hpp"
#include <string>
#include <sstream>
#include <cstdio> // for debug
#include <iostream> // for debug

ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col, const uint32_t const_val_int)
    : ExpressionNode{line, col} {
		this->const_val_int = const_val_int;
		type = 1;
	}
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col, const double const_val_d)
    : ExpressionNode{line, col} {
		this->const_val_d = const_val_d;
		type = 2;
	}
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col, const char* const_val_ch)
    : ExpressionNode{line, col} {
		this->const_val_ch = const_val_ch;
		type = 3;
	}

const char *ConstantValueNode::getValueCString() const { 
	// for debug
	//std::printf("getValueCString from ConstantValueNode.cpp, type %d\n", type);
	if (type == 1) {
		//std::stringstream ss;
		//ss << const_val_int;
		//std::string intval = ss.str();
		std::string intval = std::to_string(const_val_int);
		char const *int_char = intval.c_str();
		return int_char;
	}
	else if (type == 2) {
		std::string dval = std::to_string(const_val_d);
		char const *d_char = dval.c_str();
		return d_char;
	}
	else if (type == 3) {
		char const *str_char = const_val_ch.c_str();
		return str_char;
	}
	else std::printf("type error in ConstantValueNode.cpp\n");
}

// TODO: You may use code snippets in AstDumper.cpp
void ConstantValueNode::print() {}
