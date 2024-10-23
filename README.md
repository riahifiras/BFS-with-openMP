# BFS with OpenMP

A C implementation of the Breadth-First Search (BFS) algorithm using OpenMP for parallel processing.

## Overview

This project demonstrates a parallel BFS algorithm on a graph, allowing multiple threads to explore nodes concurrently.

## Installation

1. Clone the repository:

   ```bash
    git clone https://github.com/riahifiras/BFS-with-openMP.git
    cd BFS-with-openMP
   ```

1. Compile the code:

   ```bash
    gcc -o main main.c node.c -fopenmp
    ```

1. Run:

   ```bash
    ./main
   ```