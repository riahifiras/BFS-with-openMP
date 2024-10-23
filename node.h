#ifndef NODE_H
#define NODE_H

typedef struct Node
{
    int val;
    struct Node** adj;
    int adj_size;
} Node;

Node* create_node(int value, int adj_capacity);
void add_edge(Node* node, Node* neighbor);
void print_node(const Node* node);
void free_node(Node* node);

#endif
