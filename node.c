#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node* create_node(int value, int adj_capacity) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(1);
    }
    new_node->val = value;
    new_node->adj_size = 0;
    new_node->adj = (Node**)malloc(adj_capacity * sizeof(Node*));
    if (new_node->adj == NULL) {
        free(new_node);
        exit(1);
    }
    return new_node;
}

void add_edge(Node* node, Node* neighbor) {
    node->adj[node->adj_size] = neighbor;
    node->adj_size++;
}

void free_node(Node* node) {
    if (node != NULL) {
        free(node->adj);
        free(node);
    }
}

void print_node(const Node* node) {
    if (node == NULL) {
        return;
    }
    printf("Node %d -> ", node->val);
    for (int i = 0; i < node->adj_size; i++) {
        printf("%d ", node->adj[i]->val);
    }
    printf("\n");
}

