#include "AST/program.hpp"

// TODO
ProgramNode::ProgramNode(const uint32_t line, const uint32_t col,
                         const char *p_name,
                         const char *p_type,
                         const std::vector<DeclNode*> *p_decls,
						 const std::vector<FunctionNode*> *p_functions,
						 CompoundStatementNode *p_compound)
    : AstNode{line, col}, name(p_name) {
		this->name = p_name;
		this->type = p_type;
		this->decls = p_decls;
		this->functions = p_functions;
		this->compound = p_compound;
	}

// visitor pattern version
const char *ProgramNode::getNameCString() const { return name.c_str(); }
const char *ProgramNode::getTypeCString() const { return type.c_str(); }

void ProgramNode::print() {
    // TODO
    // outputIndentationSpace();

    std::printf("program <line: %u, col: %u> %s %s\n",
                location.line, location.col,
                name.c_str(), "void");

    // TODO
    // incrementIndentation();
    // visitChildNodes();
    // decrementIndentation();
}

void ProgramNode::visitChildNodes(AstNodeVisitor &p_visitor) { // visitor pattern version
	if (!decls->empty()) {	
		for (auto &decl : *decls) {
	 		decl->accept(p_visitor);
	  	}
	}
	if (!functions->empty()) {
		for (auto &func : *functions) {
		   func->accept(p_visitor);
	   }
	}
   
	// functions
	compound->accept(p_visitor);
}
