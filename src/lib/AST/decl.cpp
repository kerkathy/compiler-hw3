#include "AST/decl.hpp"

DeclNode::DeclNode(const uint32_t line, const uint32_t col, 
				   const std::vector<IdNode*> *identifiers,
				   VarType *type)
    : AstNode{line, col} {
		for (int i = 0; i < identifiers->size(); i++) {
			IdNode *id_node = (*identifiers)[i];
			VariableNode *var_node = new VariableNode(id_node->line, id_node->col, id_node->name, type);
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
	for (auto &vari : variables) {
		all_type.push_back(vari->getTypeCString());
	}
	return all_type;
}

void DeclNode::print() {}

void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
	if (!variables.empty()) {
		for (auto &vari : variables) {
			vari->accept(p_visitor);	
		}
	}
}
