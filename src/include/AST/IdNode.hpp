#ifndef AST_ID_NODE_H
#define AST_ID_NODE_H

/* To store ID info */
struct IdNode {
    uint32_t line;
    uint32_t col;
    std::string name;

    IdNode(const uint32_t line, const uint32_t col, std::string name) : line(line), col(col), name(name) {}
};

#endif
