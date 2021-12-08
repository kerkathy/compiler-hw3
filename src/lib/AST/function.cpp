#include "AST/function.hpp"

FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,
                 		   //std::string *name,
                 		   const char *name,
		                   std::vector<DeclNode*> *decls,
                 		   Scalar return_type,
                 		   CompoundStatementNode *compound)
    : AstNode{line, col},
	  name{name},
	  decls{decls},
	  return_type{return_type},
	  compound{compound} { }
FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,
                 		   const char *name,
		                   std::vector<DeclNode*> *decls,
                 		   Scalar return_type) 
    : AstNode{line, col},
	  name{name},
	  decls{decls},
	  return_type{return_type} { }

const char *FunctionNode::getNameCString() const { return name.c_str(); }
const char *FunctionNode::getTypeCString() const { 
	std::string str_type;
	switch(return_type) {
		case Scalar::INTEGER_SC:
			str_type = "integer";
			break;
		case Scalar::REAL_SC:
			str_type = "real";
			break;
		case Scalar::STRING_SC:
			str_type = "string";
			break;
		case Scalar::BOOLEAN_SC:
			str_type = "boolean";
			break;
		case Scalar::VOID_SC:
			str_type = "void";
			break;
	}
	return str_type.c_str(); }

const std::vector<std::string> FunctionNode::getProtoCString() const {
	std::vector<std::string> proto_cstr;
	for (auto &decl : *decls) {
		std::vector<std::string> decl_cstr = decl->getAllTypeCString();
		proto_cstr.insert(proto_cstr.end(), decl_cstr.begin(), decl_cstr.end());
	}
	//std::printf("in function.cpp\n");

//	for (auto &str :proto_cstr) {
//		std::printf("%s ", str);
//	}
//	std::printf("\n");
	return proto_cstr;
}


// TODO: You may use code snippets in AstDumper.cpp
void FunctionNode::print() {}

void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
	if (!decls->empty()) {
		for (auto &decl : *decls) {
			decl->accept(p_visitor);
		}
	}
	if (compound) {
		compound->accept(p_visitor);
	}
}
