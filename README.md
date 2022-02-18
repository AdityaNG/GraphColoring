# TODO

1. Graph Coloring Dataset [OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/orlib/colourinfo.html)
2. Read up on [A New Technique For Distributed Symmetry Breaking
](https://www.researchgate.net/publication/221344365_A_New_Technique_For_Distributed_Symmetry_Breaking)
3. Look into [Graph Contraction](https://en.wikipedia.org/wiki/Graph_coloring#:~:text=sparse%20graphs%5B14%5D.-,Contraction,-%5Bedit%5D)
4. Look into [Heuristic algorithms](https://en.wikipedia.org/wiki/Graph_coloring#:~:text=of%20a%20graph.-,Heuristic%20algorithms,-%5Bedit%5D)
4. Look into [Exact algorithms](https://en.wikipedia.org/wiki/Graph_coloring#:~:text=Exact%20algorithms%5Bedit%5D)
    - [Brute-force search](https://en.wikipedia.org/wiki/Brute-force_search)
    - [Dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming)
5. Look into focusing on an application
    - Register Allocation
    - Map Coloring
    - Bipartite Graph Checking
    - Mobile Radio Frequency Assignment
    - Making timetables, etc.
    - N Queens, Sudoku, Placing n rooks


# Graph Coloring
Graph coloring is computationally hard. It is NP-complete to decide if a given graph admits a k-coloring for a given k except for the cases k ∈ {0,1,2} . In particular, it is NP-hard to compute the chromatic number. The 3-coloring problem remains NP-complete even on 4-regular planar graphs.[27] However, for every k > 3, a k-coloring of a planar graph exists by the four color theorem, and it is possible to find such a coloring in polynomial time.

## Graph Coloring using Welsh Powell algorithm

Welsh Powell algorithm is a greedy technique to solve the graph coloring problem

### Algorithm
```
0. Define X=0
1. Find the degree of each vertex
2. List the vertices in order of descending degrees.
3. Colour the first vertex with color X.
4. Move down the list and color all the vertices not connected to the coloured vertex, with the same color.
5. X=X+1
6. Repeat step 4 on all uncolored vertices with a new color, in descending order of degrees until all the vertices are coloured.
```

## Getting Started

Compilation on Linux:
```
make
```
Usage:
```
./bin/WelshPowellSerial < input.txt
```

## Sample input:
<p align="center">
    <img src="sample_input.png">
</p>

```
0 1 1 1 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 
1 1 0 1 1 0 0 0 0 0 
1 0 1 0 0 1 0 0 0 0 
0 0 1 0 0 1 1 0 1 0 
0 0 0 1 1 0 0 0 1 1 
0 0 0 0 1 0 0 1 0 0 
0 0 0 0 0 0 1 0 1 0 
0 0 0 0 1 0 0 1 0 1 
0 0 0 0 0 1 0 0 1 0
```

## Sample output:
```
C:color 1
F:color 1
G:color 1
K:color 1
E:color 2
A:color 2
J:color 2
L:color 2
D:color 3
B:color 3
Graph full colored
```