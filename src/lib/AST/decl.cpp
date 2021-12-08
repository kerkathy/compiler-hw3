#include "AST/decl.hpp"
#include <string> // for debug

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

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print() {}

void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if (!variables.empty()) {
		// for dedug
		int cnt = 0;
		for (auto &vari : variables) {
			//for debug
			//std::printf("var cnt: %d\n", cnt);
			vari->accept(p_visitor);	
		}
	}
}
