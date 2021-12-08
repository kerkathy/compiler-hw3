#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "AST/scalar.h"
#include <vector>
#include <cstdio>

struct VarType {
	Scalar scalar_type;
	std::vector<int> *array_dim;

	VarType(Scalar scalar_type, std::vector<int> *dim) : scalar_type(scalar_type), array_dim(dim) {}
	VarType(Scalar scalar_type) : scalar_type(scalar_type) {
		//debug
		array_dim = new std::vector<int>;
		array_dim->clear();
		//std::printf("bye\n");
	}
};

#endif
