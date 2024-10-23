#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "node.h"

void bfs_search(Node* start_node, int target_value, FILE *output_file) {

    Node** queue = (Node**)malloc(100 * sizeof(Node*));
    int front = 0, rear = 0;
    bool visited[100] = {false};
    bool found = false;
    int mvp = -1;

    queue[rear++] = start_node;
    visited[start_node->val] = true;

    while (front < rear && !found) {
        Node* current = queue[front++];

        #pragma omp parallel
        {
            omp_set_num_threads(12);
            Node* local_queue[100];
            int local_rear = 0;

            #pragma omp for schedule(dynamic)
            for (int i = 0; i < current->adj_size; i++) {
                Node* neighbor = current->adj[i];
                bool was_visited = false;

                #pragma omp critical
                {
                    if (!visited[neighbor->val]) {
                        visited[neighbor->val] = true;
                        was_visited = true;
                    }
                }

                if (was_visited) {
                    if (neighbor->val == target_value) {
                        found = true; 
                        mvp = omp_get_thread_num();
                    }

                    local_queue[local_rear++] = neighbor;
                    fprintf(output_file, "Thread %d visited node %d\n", omp_get_thread_num(), neighbor->val);
                }
            }

            #pragma omp critical
            {
                for (int i = 0; i < local_rear; i++) {
                    queue[rear++] = local_queue[i];
                }
            }
        }
    }

    if (found) {
        fprintf(output_file, "Thread %d found the node with value %d\n", mvp, target_value);
    } else {
        fprintf(output_file, "Node with value %d not found in the graph.\n", target_value);
    }

    free(queue);
}

int main() {
    FILE *output_file = fopen("output.txt", "a");
    if (!output_file) {
        perror("Unable to open output file");
        return EXIT_FAILURE;
    }

    Node* nodes[20];
    for (int i = 0; i < 20; i++) {
        nodes[i] = create_node(i + 1, 6);
    }

    add_edge(nodes[0], nodes[1]);
    add_edge(nodes[0], nodes[2]);
    add_edge(nodes[1], nodes[3]);
    add_edge(nodes[1], nodes[4]);
    add_edge(nodes[2], nodes[5]);
    add_edge(nodes[2], nodes[6]);
    add_edge(nodes[3], nodes[7]);
    add_edge(nodes[3], nodes[8]);
    add_edge(nodes[4], nodes[9]);
    add_edge(nodes[5], nodes[10]);
    add_edge(nodes[6], nodes[11]);
    add_edge(nodes[7], nodes[12]);
    add_edge(nodes[8], nodes[13]);
    add_edge(nodes[9], nodes[14]);
    add_edge(nodes[10], nodes[15]);
    add_edge(nodes[11], nodes[16]);
    add_edge(nodes[12], nodes[17]);
    add_edge(nodes[13], nodes[18]);
    add_edge(nodes[14], nodes[19]);

    int target_value = 5;
    fprintf(output_file, "\nBreadth-First Search looking for Node with value %d:\n", target_value);
    bfs_search(nodes[0], target_value, output_file);

    fprintf(output_file, "\n--------------------------\n");

    for (int i = 0; i < 20; i++) {
        free_node(nodes[i]);
    }

    fclose(output_file);
    return 0;
}
