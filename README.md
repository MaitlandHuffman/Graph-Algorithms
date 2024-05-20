This program implements various graph algorithms, including Minimum Spanning Tree (MST) using Prim's algorithm and Single-Source Shortest Path (SSSP) 
using Dijkstra's and Bellman-Ford algorithms. 
It reads a graph from an input file, performs the specified algorithms, and outputs the results.

Prerequisites
  C++ compiler g++
 

Files
  main.cpp: Contains the implementation of the graph algorithms.
  ECLgraph.h: Header file defining the graph structure and input/output functions.
  Compilation

To compile the program, use the following command:
  g++ -o graph_simulation main.cpp

Execution
  Run the compiled program with the following command:
  ./graph_simulation input_file_name
  Replace input_file_name with the name of the input file containing the graph data.
  
Input File Format
  The input file should contain the graph data in a specified format compatible with the program's input functions. 
  
Output
The program outputs various results, including MST edges and distances for SSSP. The output will be displayed in the console.


Example output:
input: graph7.egr
nodes: 9
edges: 10
source: 0
(1 ,  0) and dist 0 
(2 ,  1) and dist 1 
(3 ,  2) and dist 4 
(4 ,  3) and dist 6 
(5 ,  4) and dist 3 
(6 ,  5) and dist 1 
(7 ,  6) and dist 4 
(8 ,  7) and dist 3 
BellmanFord runtime: 0.000000 s
vertex 8 has maximum distance 22
Dijkstra runtime: 0.000000 s
verification passed

Authors
Maitland Huffman
