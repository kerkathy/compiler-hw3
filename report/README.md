# hw3 report

|||
|-:|:-|
|Name|柯婷文|
|ID|0710025|

## How much time did you spend on this project

48 hours.

## Project overview

### Visitor Pattern
First, I implemented visitor pattern according to the provided `hw3.pdf` and `tutorial`. In short, replacing
* `StoreVisitorBase` with `AstNodeVisitor`
* `Child/AdultVisitor` with `AstDumper`
* `Store` with `AstNode`
* `BookStore` with `ProgramNode`

will do the trick.

### C++ Union
Then, implement the nodes required in `guideline.md` one by one. The instructions are very clear to be followed when implementing the code. However, as stated in the _Implementation Hints_ section, while using C++ unions (`%union`) in `parser.y`, containers in STL (e.g., `vector` and `string`) and node classes for AST are not allowed to be used directly. Instead, we can only use **pointers**. Thus, when I implemented the components inside each node, I use 
* _pointer to node_ to refer to a _node_
* _pointer to vector_ to refer to a _list_

### Emptiness Check
When there exist a component consisting of _zero or more something_, I declared it as a pointer to vector, and use `empty()` to check if it's empty. Similary, when there exist a component consisting of _zero or **one** something_, I declared it as a pointer to node, and check if it's `null` in `visitChildNode`. 
For example, a `FunctionNode` consists of zero or one
`CompoundStatementNode` and zero or more `DeclNode`, so it is implemented as:
```c++
// in function.hpp:
std::vector<DeclarationNode*> *decls;
CompoundStatementNode *compound;

// in function.cpp:
void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    if (!decls->empty()) {                                                   
        for (auto &decl : *decls) {
            decl->accept(p_visitor);
        }
    }
    if (compound) compound->accept(p_visitor);
```

### Scalar Type
I use an [enum class](https://openhome.cc/Gossip/CppGossip/enumType.html) to define the return types:
```c++
// in scalar.h
enum class Scalar {
    BOOLEAN_SC, INTEGER_SC, REAL_SC, STRING_SC, VOID_SC
};
```
I added the suffix `_SC` for each type to avoid confuction with terminals coming from scanner in `parser.y`.
When I need to print out its type, I use `switch case` to control it. For example:
```c++
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
```
Besides, I forgot to use the `ifndef`-`define`-`endif` at first and it caused redeclaration (due to cyclic dependency?). Thus, it's also a lesson for me.

### ConstantValueNode
Since the value could be `int`, `double`, or `string` (and `boolean`, which I deal with it as if it were string), I took advantage of `overloading` in C++ to cope with it. Also, I set up another variable `type` to record whether it's `int`, `double`, or `string`.
```c++
ConstantValueNode(const uint32_t line, const uint32_t col,
                  const uint32_t const_val_int);
ConstantValueNode(const uint32_t line, const uint32_t col,
                  const double const_val_d);
ConstantValueNode(const uint32_t line, const uint32_t col,
                  const char* const_val_ch);
```
### Statements
Nodes classified as _Statements_ include _Compound statement node, Assignment node, Print node, Read node, If node, While node, For node, Return node, Function call node_. Notice that _Function call node_ is  classified not only as _Statements_ but also as _Expression Node_. Therefore, we cannot define another class to classify _Statements_. Consequently, I simply use `AstNode` to declare this type of nodes.

### ExpressionNode
As stated in the instruction, inheritance in C++ allows us to treat a pointer to `ConstantValueNode`, `BinaryOperatorNode`
`UnaryOperatorNode`, `ConstantValueNode`, `VariableReferenceNode`, and `FunctionNode` as a pointer to `ExpressionNode`.
```c++
// in function.hpp
class FunctionNode : public AstNode { /*...*/ }
```

### Operators
As for operators, I declared another `enum class` to deal with it:
```c++
// in operator.hpp
enum class Operator {
	UNARY_MINUS,
	MULTIPLY, DIVIDE, MOD, PLUS, MINUS, 
	LESS, LESS_OR_EQUAL, GREATER, GREATER_OR_EQUAL, EQUAL, NOT_EQUAL,
	NOT,
	AND, OR
};
```
In this way, I can easily assign its given value from `parser.y` :
```yacc
// in parser.y
Expression:
    L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2; } 
	|
    MINUS Expression %prec UNARY_MINUS { 
		$$ = new UnaryOperatorNode(@1.first_line, @1.first_column, Operator::UNARY_MINUS, $2);
	}
	|
    Expression MULTIPLY Expression { 
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::MULTIPLY, $1, $3);
   	}
    /* ... */
```
And it can also be easily printed as given value:
```c++
// in UnaryOperatorNode.cpp
const char *UnaryOperatorNode::getOpCString() {
    const char *ch;
    switch(oprt) {
        case Operator::UNARY_MINUS: 
            ch = "neg";
            break;
         case Operator::MULTIPLY: 
            ch = "*";
            break;
        case Operator::DIVIDE:
            ch = "/";
            break;
    /* ... */
```


## What is the hardest you think in this project

I think trying to know what we should do in this project in the very beginning is the most difficult part for me. After I passed the first and second test cases, things become acceptable and not that harsh.
Also, my confusion about `c string` (`const char*`) and `std::string` also caused me some trouble. Now I know that we should use `c string` in `printf(%s)`, and when we want to store strings in a vector, we should store `std::string` instead of `c string`. 

## Feedback to T.A.s

> Not required, but bonus point may be given.
