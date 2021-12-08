#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"
#include "AST/AstDumper.hpp" 

#include <string>

class ConstantValueNode : public ExpressionNode {
  public:
    ConstantValueNode(const uint32_t line, const uint32_t col,
					  const uint32_t const_val_int);
    ConstantValueNode(const uint32_t line, const uint32_t col,
					  const double const_val_d);
    ConstantValueNode(const uint32_t line, const uint32_t col,
					  const char* const_val_ch);
//    ConstantValueNode(const uint32_t line, const uint32_t col,
//					  const bool const_val_bool);
                      /* TODO: constant value );*/

    ~ConstantValueNode() = default;

	const char *getValueCString() const;

	void print() override;
    void accept(AstNodeVisitor &p_visitor) override { 
		// for debug
		//std::printf("in accept() in ConstantVAlueNode.hpp\n");
		p_visitor.visit(*this); }

	/* record data type: 1(int), 2(double), 3(str), 4(bool) */	
	int type;	
	
  private:
	uint32_t const_val_int;
	double const_val_d;
	std::string const_val_ch;
	// bool const_val_bool;
    // TODO: constant value
};

#endif
