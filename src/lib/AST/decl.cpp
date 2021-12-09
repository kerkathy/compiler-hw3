#include "AST/decl.hpp"

// TODO: variable declaration
DeclNode::DeclNode(const uint32_t line, const uint32_t col, 
				   const std::vector<IdNode*> *identifiers,
				   VarType *type)
    : AstNode{line, col} {
		for (int i = 0; i < identifiers->size(); i++) {
			IdNode *id_node = (*identifiers)[i];
			VariableNode *var_node = new VariableNode(id_node->line, id_node->col, id_node->name, type);
			// for debug
			//std::printf("Created variable node in decl.cpp, name %s, type %d\n", id_node->name.c_str(), type->scalar_type);

			variables.push_back(var_node);
		}
	}

// TODO: constant variable declaration
DeclNode::DeclNode(const uint32_t line, const uint32_t col,
				   const std::vector<IdNode*> *identifiers,
				   VarType *type, 
				   ConstantValueNode *constant)
    : AstNode{line, col} {
		for (int i = 0; i < identifiers->size(); i++) {
			IdNode *id_node = (*identifiers)[i];
			VariableNode *var_node = new VariableNode(id_node->line, id_node->col, id_node->name, type, constant);
			variables.push_back(var_node);
		}	
	}

std::vector<std::string> DeclNode::getAllTypeCString() const {
	std::vector<std::string> all_type;
	//debug
	//std::printf("Reading from variables in decl.cpp: \n");
	for (auto &vari : variables) {
	//	std::printf("%s, ", vari->getTypeCString());
		all_type.push_back(vari->getTypeCString());
	}
	//std::printf("In decl.cpp: ");
	//for (auto &t : all_type) std::printf("%s, ", t);
	return all_type;
}

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print() {}

void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if (!variables.empty()) {
		// for dedug
		//int cnt = 0;
		for (auto &vari : variables) {
			//for debug
			//std::printf("var cnt: %d\n", cnt);
			vari->accept(p_visitor);	
		}
	}
}
