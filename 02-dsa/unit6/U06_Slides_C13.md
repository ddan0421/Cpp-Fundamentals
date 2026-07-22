# Chapter 13 — Graphs (Comprehensive Lecture Notes)

> Notes compiled from the Chapter 13 lecture slides, with corresponding code
> examples pulled from the textbook (*C++ Plus Data Structures* / Dale). Each
> concept pairs the slide-level explanation with the actual implementation used
> in the book.

---

## Table of Contents

1. [Graphs: Logical Level](#1-graphs-logical-level)
2. [Edge Direction](#2-edge-direction)
3. [Formal Definition](#3-formal-definition)
4. [Adjacency & Paths](#4-adjacency--paths)
5. [Completeness](#5-completeness)
6. [Weighted Graphs](#6-weighted-graphs)
7. [Graph ADT Operations](#7-graph-adt-operations)
8. [Graphs: Application Level (Traversals)](#8-graphs-application-level-traversals)
9. [Depth-First Search (DFS)](#9-depth-first-search-dfs)
10. [Breadth-First Search (BFS)](#10-breadth-first-search-bfs)
11. [The Single-Source Shortest-Path Problem](#11-the-single-source-shortest-path-problem)
12. [Implementation Level: Array-Based](#12-implementation-level-array-based)
13. [Implementation Level: Linked (Adjacency Lists)](#13-implementation-level-linked-adjacency-lists)
14. [zyBooks Implementation: Hash-Map Adjacency Lists](#14-zybooks-implementation-hash-map-adjacency-lists)
15. [zyBooks BFS Example (Visitor Pattern)](#15-zybooks-bfs-example-visitor-pattern)
16. [zyBooks DFS Example (Visitor Pattern)](#16-zybooks-dfs-example-visitor-pattern)
17. [zyBooks Dijkstra's Shortest Path](#17-zybooks-dijkstras-shortest-path)
18. [zyBooks Bellman-Ford Shortest Path](#18-zybooks-bellman-ford-shortest-path)
19. [zyBooks Topological Sort](#19-zybooks-topological-sort)
20. [Which Version to Use?](#20-which-version-to-use)
21. [Summary](#21-summary)

---

## 1. Graphs: Logical Level

A **graph** is a set of **vertices** (nodes) and a set of **edges** that relate
the vertices to one another.

- Each **vertex** is a "thing" or data point — such as a person or a city.
- **Edges** are represented as pairs of vertices.
- Graphs are similar to binary trees, but have **no restrictions** on the
  connections between nodes.

Binary trees restrict each node to at most one parent and at most two children.
Removing the two-children limit gives a **general tree**; also removing the
single-parent (shape) restriction gives a **graph**. The vertices usually
represent objects (people, houses, cities, courses); the edges represent
relationships between those objects.

**Key terms:**

| Term | Definition |
|------|------------|
| **Graph** | A data structure consisting of a set of nodes and a set of edges relating the nodes to one another |
| **Vertex** | A node in a graph |
| **Edge (arc)** | A pair of vertices representing a connection between two nodes |

---

## 2. Edge Direction

- **Directed Graph (digraph):** Each edge is directed from one vertex to another
  vertex. *Example:* on a graph of cities, a directed edge from Houston to Austin
  could represent a **flight**. The existence of a flight Houston → Austin does
  **not** guarantee a flight Austin → Houston.
- **Undirected Graph:** Edges have **no direction**. *Example:* an undirected edge
  from Houston to Austin could represent a **road** (the road runs both ways).

> In pictures of digraphs, the arrows indicate the direction of the relationship.

| Term | Definition |
|------|------------|
| **Undirected graph** | A graph in which the edges have no direction |
| **Directed graph (digraph)** | A graph in which each edge is directed from one vertex to another (or the same) vertex |

---

## 3. Formal Definition

Graphs are based on a mathematical concept. Formally, a graph `G` is defined as:

```
G = (V, E)
```

where

- `V(G)` is a **finite, nonempty set of vertices**.
- `E(G)` is a **set of edges** (written as pairs of vertices).

**Specifying a graph in set notation** — vertices are listed within `{ }` braces,
and each edge is written as the two vertices it connects in parentheses:

```
V(Graph1) = {A, B, C, D}
E(Graph1) = {(A, B), (A, D), (B, C), (B, D)}
```

Because `Graph1` is **undirected**, the order within each edge is unimportant, so
this is the same graph:

```
E(Graph1) = {(B, A), (D, A), (C, B), (D, B)}
```

For a **digraph**, order matters: the edge `(5, 7)` is a link *from* vertex 5 *to*
vertex 7, and does **not** imply the edge `(7, 5)`.

> A **tree** is a special case of a directed graph in which each vertex is
> adjacent from only one other vertex (its parent) and one vertex (the root) is
> not adjacent from any other vertex.

---

## 4. Adjacency & Paths

Two vertices are **adjacent** if they are connected by an edge.

- For a **directed** edge from A to B:
  - The first vertex is **adjacent to** the second (A is adjacent to B).
  - The second vertex is **adjacent from** the first (B is adjacent from A).
- A **path** is a sequence of vertices that connects two vertices in the graph.
  For a path to exist, an uninterrupted sequence of edges must go from the first
  vertex, through any number of vertices, to the second vertex.

*Example:* In a digraph, a path may go from vertex 5 to vertex 3 but **not** from
3 to 5. In a tree, a **unique** path exists from the root to every other node.

| Term | Definition |
|------|------------|
| **Adjacent vertices** | Two vertices connected by an edge |
| **Path** | A sequence of vertices that connects two nodes in a graph |

---

## 5. Completeness

In a **complete graph**, every vertex is directly connected to every other vertex.

For `N` vertices:

- A complete **directed** graph has `N * (N − 1)` edges.
- A complete **undirected** graph has `N * (N − 1) / 2` edges (half, since each
  undirected edge would otherwise be counted twice).

| Term | Definition |
|------|------------|
| **Complete graph** | A graph in which every vertex is directly connected to every other vertex |

---

## 6. Weighted Graphs

In a **weighted graph**, each edge carries an associated value (a **weight**).

- A weight typically represents the **cost** of moving between two vertices.
- *Example:* on a graph of cities, weights could be the **distance** between
  cities. The total distance between two cities is the sum of the weights on the
  path between them.

The textbook's running example is the **Air Busters Airlines** graph: vertices are
cities, directed edges are flights, and weights are air distances (in miles)
between connected cities (Figure 13.3).

| Term | Definition |
|------|------------|
| **Weighted graph** | A graph in which each edge carries a value |

---

## 7. Graph ADT Operations

The chapter specifies a small but useful set of operations. Many others are
possible, but these are all that the applications in this chapter need.

- **Transformers:** `AddVertex`, `AddEdge`, and `MakeEmpty`.
- **Observers:** `IsFull`, `IsEmpty`, `GetWeight`, and `GetToVertices` (returns a
  **queue** of adjacent vertices).

**Graph ADT specification (paraphrased):**

| Operation | Function | Pre / Postconditions |
|-----------|----------|----------------------|
| `MakeEmpty` | Initializes the graph to empty | Post: graph is empty |
| `IsEmpty` | Tests whether the graph is empty | Post: returns (graph is empty) |
| `IsFull` | Tests whether the graph is full | Post: returns (graph is full) |
| `AddVertex(vertex)` | Adds `vertex` to the graph | Pre: graph not full · Post: `vertex` is in `V(graph)` |
| `AddEdge(fromVertex, toVertex, weight)` | Adds a weighted edge | Pre: both vertices in `V(graph)` · Post: `(fromVertex, toVertex)` is in `E(graph)` with the weight |
| `GetWeight(fromVertex, toVertex)` | Weight of the edge | Pre: both in `V(graph)` · Post: returns weight, or a special **null-edge** value if no edge |
| `GetToVertices(vertex, vertexQ)` | Queue of vertices adjacent **from** `vertex` | Pre: `vertex` in `V(graph)` · Post: `vertexQ` holds all vertices adjacent from `vertex` |

The **mark** operations (added later, needed for traversals) are:

| Operation | Function | Postcondition |
|-----------|----------|---------------|
| `ClearMarks` | Clears marks on all vertices | All marks set to `false` |
| `MarkVertex(vertex)` | Marks a vertex as visited | `IsMarked(vertex)` is `true` |
| `IsMarked(vertex)` | Tests whether a vertex is marked | Returns (vertex is marked `true`) |

---

## 8. Graphs: Application Level (Traversals)

Graph traversal is a commonly used operation. Like trees, there are multiple ways
to do it. Because **traversing the graph is independent of the graph itself**, the
traversal methods are kept **separate** from the graph operations — they are
implemented as graph *applications* using only the ADT operations, without knowing
how the graph is represented internally.

Two systematic strategies (both borrowed from tree traversals):

- **Depth-first** — go down a branch to its deepest point, then back up (analogous
  to a postorder tree traversal).
- **Breadth-first** — visit all vertices on one "level" before moving to the next
  level.

---

## 9. Depth-First Search (DFS)

Depth-first search follows a path **as far as possible before backtracking**. It
is useful for checking whether a **path exists** between two nodes. When you must
backtrack, you take the branch closest to where you dead-ended.

### DFS Algorithm

- Push the start node onto the **stack**.
- Pop a node off the stack and examine it.
- If it is the target, stop.
- Otherwise, push all of its (unmarked) adjacent nodes onto the stack.
- Continue until the target node is found or the stack is empty (no more nodes).

```
DepthFirstSearch
    Set found to false
    stack.Push(startVertex)
    do
        stack.Pop(vertex)
        if vertex = endVertex
            Write final vertex
            Set found to true
        else
            Write this vertex
            Push all adjacent vertices onto stack
    while !stack.IsEmpty() AND !found
    if (!found)
        Write "Path does not exist"
```

### Example — Austin → Washington (Figure 13.3)

- Push **Austin** onto the stack.
- Pop **Austin**; push **Dallas** and **Houston**.
- Pop **Houston**; push **Atlanta**.
- Pop **Atlanta**; it leads to **Houston** and **Washington**.
- **Houston is already visited**, so ignore it; push **Washington**.
- Pop **Washington** → destination found.

### Marking (avoiding cycles)

Atlanta leads to both Houston and Washington, but Houston was already visited.
**By marking nodes, DFS avoids revisiting nodes, which would otherwise lead to
cycles (infinite loops).** Three operations support this: the `MarkVertex`
transformer, the `IsMarked` observer, and `ClearMarks`. **Marked nodes are not
added to the stack.**

### DFS Source Code

The function receives a graph, a start vertex, and a target vertex. Nothing in it
depends on how the graph is implemented — it uses only the ADT operations. It
assumes `StackType` and `QueType` headers are included and that `VertexType`
defines `==` and `<<`.

```cpp
template<class VertexType>
void DepthFirstSearch(GraphType<VertexType> graph,
    VertexType startVertex, VertexType endVertex)
// Assumes VertexType is a type for which the "==" and "<<"
// operators are defined.
{
    using namespace std;
    StackType<VertexType> stack;
    QueType<VertexType> vertexQ;
    bool found = false;
    VertexType vertex;
    VertexType item;
    graph.ClearMarks();
    stack.Push(startVertex);
    do
    {
        stack.Pop(vertex);
        if (vertex == endVertex)
        {
            cout << vertex;
            found = true;
        }
        else
        {
            if (!graph.IsMarked(vertex))
            {
                graph.MarkVertex(vertex);
                cout << vertex;
                graph.GetToVertices(vertex, vertexQ);
                while (!vertexQ.IsEmpty())
                {
                    vertexQ.Dequeue(item);
                    if (!graph.IsMarked(item))
                        stack.Push(item);
                }
            }
        }
    } while (!stack.IsEmpty() && !found);
    if (!found)
        cout << "Path not found." << endl;
}
```

---

## 10. Breadth-First Search (BFS)

Breadth-first search examines **all possible paths of the same length** before
going deeper. In the flight example, BFS checks all **one-stop** connections
before checking any **two-stop** connections — the preferred approach for most
travelers.

> DFS backtracks **as little as possible** (uses a stack, LIFO — most recent route
> first). BFS backtracks **as far as possible** (uses a **queue**, FIFO — earliest
> route first). In a binary tree, BFS explores all nodes at one level before the
> next level.

### Example — Austin → Washington

- Enqueue **Dallas** and **Houston** (reachable directly from Austin).
- Dequeue **Dallas**; enqueue **Chicago** and **Denver**.
- Dequeue **Houston**; enqueue **Atlanta**.
- Continue until **Washington** is dequeued.
- BFS explored all one-flight paths before checking two-flight paths.

### Marking and BFS

A node adjacent to multiple nodes may be added to the queue twice (e.g., **Denver**
is enqueued by both Dallas and Chicago). Two options:

- **Mark when dequeued:** a node may appear in the queue multiple times, so you
  must check whether it is marked *after* dequeuing (useful if you want to know
  whether alternative routes exist).
- **Mark when enqueued:** prevents multiple copies of a node in the queue.

Either approach can be useful, depending on the processing you need.

### BFS Source Code

The source is **identical to DFS except the stack is replaced by a FIFO queue**
(`Push`/`Pop` become `Enqueue`/`Dequeue`).

```cpp
template<class VertexType>
void BreadthFirstSearch(GraphType<VertexType> graph,
    VertexType startVertex, VertexType endVertex)
// Assumption: VertexType is a type for which the "==" and
// "<<" operators are defined.
{
    using namespace std;
    QueType<VertexType> queue;
    QueType<VertexType> vertexQ;
    bool found = false;
    VertexType vertex;
    VertexType item;
    graph.ClearMarks();
    queue.Enqueue(startVertex);
    do
    {
        queue.Dequeue(vertex);
        if (vertex == endVertex)
        {
            cout << vertex;
            found = true;
        }
        else
        {
            if (!graph.IsMarked(vertex))
            {
                graph.MarkVertex(vertex);
                cout << vertex;
                graph.GetToVertices(vertex, vertexQ);
                while (!vertexQ.IsEmpty())
                {
                    vertexQ.Dequeue(item);
                    if (!graph.IsMarked(item))
                        queue.Enqueue(item);
                }
            }
        }
    } while (!queue.IsEmpty() && !found);
    if (!found)
        cout << "Path not found." << endl;
}
```

---

## 11. The Single-Source Shortest-Path Problem

Goal: find the **shortest path** from the starting city to **every other city** on
the map — where "shortest" means the path whose **edge weights sum to the smallest
total**, not the fewest flights.

> Fewer flights ≠ shorter distance. DFS/BFS ignore weights; the shortest-path
> traversal must use the number of miles (edge weights).

### Choosing the auxiliary structure

- DFS uses a **stack** (keeps going forward: 1-flight, then 2-flight, …).
- BFS uses a **queue** (all 1-flight, then all 2-flight, …).
- Shortest path needs the node with the **next-shortest distance** → use a
  **minimum priority queue**, with the distance as the priority.

The algorithm is basically the same as DFS/BFS, with two differences:

1. It uses a **priority queue** rather than a stack or FIFO queue.
2. It **has no destination** — it stops only when there are no more cities to
   process (the priority queue is empty).

### Shortest-Path Algorithm

```
ShortestPath
    graph.ClearMarks()
    Set item.fromVertex to startVertex
    Set item.toVertex   to startVertex
    Set item.distance   to 0
    pq.Enqueue(item)
    do
        pq.Dequeue(item)
        if item.toVertex is not marked
            Mark item.toVertex
            Write item.fromVertex, item.toVertex, item.distance
            Set item.fromVertex to item.toVertex
            Set minDistance to item.distance
            Get queue vertexQ of vertices adjacent from item.fromVertex
            while more vertices in vertexQ
                Get next vertex from vertexQ
                if vertex not marked
                    Set item.toVertex to vertex
                    Set item.distance to minDistance + graph.GetWeight(fromVertex, vertex)
                    pq.Enqueue(item)
    while !pq.IsEmpty()
```

### Shortest-Path Source Code

The priority-queue items are `struct`s with three members: `fromVertex`,
`toVertex`, and `distance`. `ItemType` overloads the relational operators so that
a **smaller distance = higher priority** — i.e., the priority queue is a
**minimum heap** (`item.distance` ≤ the distance of each child).

```cpp
template<class VertexType>
struct ItemType
{
    bool operator<(ItemType otherItem);   // "<" means shorter distance.
    bool operator==(ItemType otherItem);
    bool operator<=(ItemType otherItem);
    VertexType fromVertex;
    VertexType toVertex;
    int distance;
};

template<class VertexType>
void ShortestPath(GraphType<VertexType> graph, VertexType startVertex)
{
    using namespace std;
    ItemType item;
    int minDistance;
    PQType<VertexType> pq(10);   // Assume at most 10 vertices.
    QueType<VertexType> vertexQ;
    VertexType vertex;

    graph.ClearMarks();
    item.fromVertex = startVertex;
    item.toVertex = startVertex;
    item.distance = 0;
    pq.Enqueue(item);
    cout << "Last Vertex   Destination   Distance" << endl;
    cout << "-----------------------------------" << endl;
    do
    {
        pq.Dequeue(item);
        if (!graph.IsMarked(item.toVertex))
        {
            graph.MarkVertex(item.toVertex);
            cout << item.fromVertex;
            cout << " ";
            cout << item.toVertex;
            cout << " " << item.distance << endl;

            item.fromVertex = item.toVertex;
            minDistance = item.distance;
            graph.GetToVertices(item.fromVertex, vertexQ);
            while (!vertexQ.IsEmpty())
            {
                vertexQ.Dequeue(vertex);
                if (!graph.IsMarked(vertex))
                {
                    item.toVertex = vertex;
                    item.distance = minDistance +
                        graph.GetWeight(item.fromVertex, vertex);
                    pq.Enqueue(item);
                }
            }
        }
    } while (!pq.IsEmpty());
}
```

### Reading the output

Calling `ShortestPath(graph, Washington)` prints a table of city pairs (edges)
showing the total distance from the start to each city, plus the **last vertex**
visited before each destination:

```
Last Vertex   Destination   Distance
Washington    Washington    0
Washington    Atlanta       600
Washington    Dallas        1300
Atlanta       Houston       1400
Dallas        Austin        1500
Dallas        Denver        2080
Dallas        Chicago       2200
```

To reconstruct a path, follow the first column backward. For Chicago: the vertex
before Chicago is **Dallas**; the vertex before Dallas is **Washington**. So the
shortest path is **Washington → Dallas → Chicago** (2,200 miles).

---

## 12. Implementation Level: Array-Based

There are two main approaches — array-based and linked-list-based. The biggest
design question is **how to handle edges**.

**Array-based representation:**

- **Vertices** are stored in a one-dimensional array `vertices`.
- **Edges** are stored in an **adjacency matrix** — an `N × N` table showing the
  existence (and weight) of each edge. `Row[0]` contains the edges that start at
  `Vertex[0]`.
- The matrix stores **Boolean** values (unweighted) or **numbers/weights**
  (weighted). Here `edges[1][3] = 200` means a 200-mile flight from Austin to
  Dallas; a `NULL_EDGE` (0) means no direct flight.

| Term | Definition |
|------|------------|
| **Adjacency matrix** | For a graph with N nodes, an N × N table showing the existence (and weight) of all edges |

At any time within the representation:

- `numVertices` = number of vertices.
- `V(graph)` is `vertices[0]..vertices[numVertices-1]`.
- `E(graph)` is `edges[0][0]..edges[numVertices-1][numVertices-1]`.

### Class Definition

Dynamically allocating a 2-D array is complex, so the textbook **fixes the
adjacency matrix at 50×50** and dynamically allocates the `vertices` and `marks`
arrays.

```cpp
template<class VertexType>
// Assumption: VertexType is a type for which the "=",
// "==", and "<<" operators are defined.
class GraphType
{
public:
    GraphType();          // Default is 50 vertices
    GraphType(int maxV);  // maxV <= 50
    ~GraphType();
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    void AddVertex(VertexType);
    void AddEdge(VertexType, VertexType, int);
    int  GetWeight(VertexType, VertexType);
    void GetToVertices(VertexType, QueType<VertexType>&);
    void ClearMarks();
    void MarkVertex(VertexType);
    bool IsMarked(VertexType);
private:
    int numVertices;
    int maxVertices;
    VertexType* vertices;
    int edges[50][50];
    bool* marks;          // marks[i] is the mark for vertices[i].
};
```

### Constructors and Destructor

The default constructor sets up space for 50 vertices/marks; the parameterized
constructor lets the caller specify the maximum. `edges` is *not* dynamically
allocated (2-D dynamic allocation is complex and would distract from the ADT).

```cpp
template<class VertexType>
GraphType<VertexType>::GraphType()
{
    numVertices = 0;
    maxVertices = 50;
    vertices = new VertexType[50];
    marks = new bool[50];
}

template<class VertexType>
GraphType<VertexType>::GraphType(int maxV)
{
    numVertices = 0;
    maxVertices = maxV;
    vertices = new VertexType[maxV];
    marks = new bool[maxV];
}

template<class VertexType>
GraphType<VertexType>::~GraphType()
{
    delete [] vertices;
    delete [] marks;
}
```

### AddVertex

Puts the vertex in the next free slot and initializes its row and column of
`edges` to `NULL_EDGE` (the new vertex has no edges yet).

```cpp
const int NULL_EDGE = 0;

template<class VertexType>
void GraphType<VertexType>::AddVertex(VertexType vertex)
// Post: vertex stored in vertices; its row/column of edges set to
//       NULL_EDGE; numVertices incremented.
{
    vertices[numVertices] = vertex;
    for (int index = 0; index < numVertices; index++)
    {
        edges[numVertices][index] = NULL_EDGE;
        edges[index][numVertices] = NULL_EDGE;
    }
    numVertices++;
}
```

### IndexIs helper + AddEdge

`AddEdge` receives vertices of `VertexType`, but the matrix is indexed by array
position, so a small helper finds a vertex's index. Because the precondition
guarantees the vertices exist, `IndexIs` can be very simple.

```cpp
template<class VertexType>
int IndexIs(VertexType* vertices, VertexType vertex)
// Post: Returns the index of vertex in vertices.
{
    int index = 0;
    while (!(vertex == vertices[index]))
        index++;
    return index;
}

template<class VertexType>
void GraphType<VertexType>::AddEdge(VertexType fromVertex,
    VertexType toVertex, int weight)
// Post: Edge (fromVertex, toVertex) is stored in edges.
{
    int row;
    int col;
    row = IndexIs(vertices, fromVertex);
    col = IndexIs(vertices, toVertex);
    edges[row][col] = weight;
}
```

### GetWeight

The mirror image of `AddEdge` — look up the weight in the matrix.

```cpp
template<class VertexType>
int GraphType<VertexType>::GetWeight
    (VertexType fromVertex, VertexType toVertex)
// Post: Returns the weight associated with edge (fromVertex, toVertex).
{
    int row;
    int col;
    row = IndexIs(vertices, fromVertex);
    col = IndexIs(vertices, toVertex);
    return edges[row][col];
}
```

### GetToVertices

Loops through the vertex's row in `edges`; whenever a value is not `NULL_EDGE`, the
corresponding vertex is enqueued (it is adjacent from the given vertex).

```cpp
template<class VertexType>
void GraphType<VertexType>::GetToVertices(VertexType vertex,
    QueType<VertexType>& adjVertices)
// Post: Returns a queue of vertices adjacent from vertex.
{
    int fromIndex;
    int toIndex;
    fromIndex = IndexIs(vertices, vertex);
    for (toIndex = 0; toIndex < numVertices; toIndex++)
        if (edges[fromIndex][toIndex] != NULL_EDGE)
            adjVertices.Enqueue(vertices[toIndex]);
}
```

---

## 13. Implementation Level: Linked (Adjacency Lists)

An **adjacency list** is a linked list that identifies all vertices to which a
particular vertex is connected. **Each vertex has its own adjacency list.** There
are two common ways to implement them.

| Term | Definition |
|------|------------|
| **Adjacency list** | A linked list that identifies all vertices to which a particular vertex is connected; each vertex has its own list |

### Array of Vertices (Figure 13.9)

- The list of vertices is an **array**. Each array entry holds the vertex data and
  a **pointer to that vertex's adjacency list**.
- Each node in an adjacency list contains: the **index** of the adjacent vertex,
  the **weight** of the edge, and a **pointer to the next node** in the list.

*Example:* Denver's adjacency list has a node "index 0 (Atlanta), 1400 miles" then
a node "index 2 (Chicago), 1000 miles."

### Linked List of Vertices (Figure 13.10)

- The vertices themselves are stored in a **linked list** (no arrays).
- Each vertex entry points to the **next vertex node** and to the vertex's
  **adjacency list**.
- Each adjacency-list node contains a **pointer to a vertex node** (rather than an
  index), the **weight** of the edge, and a **pointer to the next node**.

> The textbook leaves implementing the `GraphType` member functions with these
> linked representations as programming assignments.

---

## 14. zyBooks Implementation: Hash-Map Adjacency Lists

zyBooks presents a modern, self-contained C++ graph implementation that is a
practical variation of the **adjacency-list** idea from Section 13. Instead of an
`NxN` matrix (Dale's array version) or a hand-built linked list per vertex, it uses
the standard library: **`Vertex` and `Edge` are heap-allocated objects**, and the
graph keeps two **hash maps** (`std::unordered_map`) from a vertex to a vector of
its edges.

Key differences from the Dale versions:

1. **First-class `Vertex` and `Edge` objects** (each in its own header) rather than
   raw indices/weights in a matrix. Edges store **pointers** to their endpoints, so
   they can be traversed in either direction.
2. **Two adjacency maps** — `fromEdges` (outgoing edges of each vertex) and
   `toEdges` (incoming edges of each vertex). Maintaining both makes "flights from"
   *and* "flights to" a location **O(1)** to look up. (Dale's single matrix only
   directly answers "adjacent from.")
3. **Directed edges are the primitive.** `AddUndirectedEdge` is just **two directed
   edges** (A→B and B→A) with the same weight — matching the slides' note that an
   undirected edge is a bidirectional connection.
4. **Ownership / cleanup:** the destructor gathers the *distinct* vertices and edges
   (each undirected edge is stored in multiple vectors) into `unordered_set`s before
   deleting, so nothing is `delete`d twice.

### `Vertex.h`

A vertex is just a labeled node.

```cpp
#ifndef VERTEX_H
#define VERTEX_H

#include <string>

class Vertex {
public:
   std::string label;

   Vertex(const std::string& vertexLabel) {
      label = vertexLabel;
   }
};

#endif
```

### `Edge.h`

An edge stores pointers to its two endpoints and a weight. Storing `fromVertex`
*and* `toVertex` on the edge is what lets a single `Edge*` be found from either the
`fromEdges` or the `toEdges` map and still report both endpoints.

```cpp
#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge {
public:
   Vertex* fromVertex;
   Vertex* toVertex;
   double weight;

   Edge(Vertex* from, Vertex* to, double edgeWeight) {
      fromVertex = from;
      toVertex = to;
      weight = edgeWeight;
   }
};

#endif
```

### `Graph.h`

The graph owns everything. Every vertex is a key in **both** maps (each mapped to a
dynamically allocated `vector<Edge*>`), so a vertex with no edges still appears.

```cpp
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph {
private:
   // Maps a vertex to a vector of all edges that start from that vertex
   std::unordered_map<Vertex*, std::vector<Edge*>*> fromEdges;

   // Maps a vertex to a vector of all edges that go to that vertex
   std::unordered_map<Vertex*, std::vector<Edge*>*> toEdges;

public:
   virtual ~Graph() {
      // Build sets of distinct vertices and edges
      std::unordered_set<Vertex*> distinctVertices;
      std::unordered_set<Edge*> distinctEdges;
      for (auto& keyValue : fromEdges) {
         distinctVertices.insert(keyValue.first);
         for (Edge* edge : *keyValue.second) {
            distinctEdges.insert(edge);
         }

         // Free dynamically allocated vector of edges
         delete keyValue.second;
      }
      for (auto& keyValue : toEdges) {
         distinctVertices.insert(keyValue.first);
         for (Edge* edge : *keyValue.second) {
            distinctEdges.insert(edge);
         }

         // Free dynamically allocated vector of edges
         delete keyValue.second;
      }

      // Clear each map
      fromEdges.clear();
      toEdges.clear();

      // Free each edge and each vertex
      for (Edge* edge : distinctEdges) {
         delete edge;
      }
      for (Vertex* vertex : distinctVertices) {
         delete vertex;
      }
   }

   Vertex* AddVertex(const std::string& newVertexLabel) {
      // Create the new Vertex object
      Vertex* newVertex = new Vertex(newVertexLabel);

      // Every vertex must exist as a key in both maps
      fromEdges[newVertex] = new std::vector<Edge*>();
      toEdges[newVertex] = new std::vector<Edge*>();

      return newVertex;
   }

   Edge* AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex, double weight = 1.0) {
      // Don't add the same edge twice
      if (HasEdge(fromVertex, toVertex)) {
         return nullptr;
      }

      // Create the Edge object
      Edge* newEdge = new Edge(fromVertex, toVertex, weight);

      // Add the edge to the appropriate vector in both maps
      fromEdges[fromVertex]->push_back(newEdge);
      toEdges[toVertex]->push_back(newEdge);

      return newEdge;
   }

   std::pair<Edge*, Edge*> AddUndirectedEdge(Vertex* vertexA, Vertex* vertexB,
      double weight = 1.0) {
         return std::pair<Edge*, Edge*>(
            AddDirectedEdge(vertexA, vertexB, weight),
            AddDirectedEdge(vertexB, vertexA, weight));
   }

   // Returns an unordered_set of all of this graph's edges
   std::unordered_set<Edge*> GetEdges() const {
      std::unordered_set<Edge*> edgesSet;
      for (auto& keyValue : fromEdges) {
         std::vector<Edge*>* edges = keyValue.second;
         for (Edge* edge : *edges) {
            edgesSet.insert(edge);
         }
      }
      return edgesSet;
   }

   // Returns a vector of edges with the specified fromVertex
   const std::vector<Edge*>* GetEdgesFrom(Vertex* fromVertex) const {
      return fromEdges.at(fromVertex);
   }

   // Returns a vector of edges with the specified toVertex
   const std::vector<Edge*>* GetEdgesTo(Vertex* toVertex) const {
      return toEdges.at(toVertex);
   }

   // Returns a vertex with a matching label, or nullptr if no such vertex exists
   Vertex* GetVertex(const std::string& vertexLabel) {
      for (auto& keyValue : fromEdges) {
         Vertex* vertex = keyValue.first;
         if (vertex->label == vertexLabel) {
            return keyValue.first;
         }
      }
      return nullptr;
   }

   // Returns a vector of all of this graph's vertices
   std::vector<Vertex*> GetVertices() const {
      std::vector<Vertex*> vertices;
      for (auto& keyValue : fromEdges) {
         vertices.push_back(keyValue.first);
      }
      return vertices;
   }

   // Returns true if this graph has an edge from fromVertex to toVertex
   bool HasEdge(Vertex* fromVertex, Vertex* toVertex) const {
      if (0 == fromEdges.count(fromVertex)) {
         // fromVertex is not in this graph
         return false;
      }

      // Search the vector of edges for an edge that goes to toVertex
      std::vector<Edge*>& edges = *fromEdges.at(fromVertex);
      for (Edge* edge : edges) {
         if (edge->toVertex == toVertex) {
            return true;
         }
      }

      return false;
   }
};

#endif
```

**Operation cheat sheet:**

| Method | What it does | Notes |
|--------|--------------|-------|
| `AddVertex(label)` | Creates a `Vertex`, adds it as a key in both maps | Returns the `Vertex*` (used later to add edges) |
| `AddDirectedEdge(from, to, w)` | Adds one directed edge | Skips duplicates via `HasEdge`; returns `nullptr` if it already exists |
| `AddUndirectedEdge(a, b, w)` | Adds edges a→b **and** b→a | Returns a `pair` of the two `Edge*` |
| `GetEdgesFrom(v)` / `GetEdgesTo(v)` | Outgoing / incoming edges of `v` | **O(1)** map lookup (returns the stored vector) |
| `GetEdges()` | Set of all distinct edges | Dedupes with an `unordered_set` |
| `GetVertex(label)` | Finds a vertex by label | Linear scan of the keys |
| `GetVertices()` | All vertices | Collected from the `fromEdges` keys |
| `HasEdge(from, to)` | Whether a from→to edge exists | Scans that vertex's outgoing vector |

### Driver — `FlightsGraphDemo.cpp`

Builds the airline example as an **undirected, weighted** graph (flights that run
both ways, weighted by miles), then prints every location's outgoing and incoming
flights.

```cpp
#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
   // Create a new Graph object
   Graph graph1;

   // Add vertices and edges representing plane flights
   Vertex* vertexA = graph1.AddVertex("Tokyo");
   Vertex* vertexB = graph1.AddVertex("New York");
   Vertex* vertexC = graph1.AddVertex("London");
   Vertex* vertexD = graph1.AddVertex("Sydney");
   graph1.AddUndirectedEdge(vertexA, vertexB, 6743);
   graph1.AddUndirectedEdge(vertexA, vertexC, 5941);
   graph1.AddUndirectedEdge(vertexA, vertexD, 4863);
   graph1.AddUndirectedEdge(vertexB, vertexC, 3425);
   graph1.AddUndirectedEdge(vertexB, vertexD, 9868);
   graph1.AddUndirectedEdge(vertexC, vertexD, 10562);

   // Show the graph's vertices and edges
   for (Vertex* vertex : graph1.GetVertices()) {
      cout << "Location: " << vertex->label << endl;

      // Show outgoing edges (flights from location)
      cout << "  Flights from " << vertex->label << ":" << endl;
      for (Edge* outgoingEdge : *graph1.GetEdgesFrom(vertex)) {
         cout << "   - " << vertex->label << " to ";
         cout << outgoingEdge->toVertex->label << ", ";
         cout << (int)outgoingEdge->weight << " miles" << endl;
      }

      // Show incoming edges (flights to location)
      cout << "  Flights to " << vertex->label << ":" << endl;
      for (Edge* incomingEdge : *graph1.GetEdgesTo(vertex)) {
         cout << "   - " << incomingEdge->fromVertex->label << " to ";
         cout << vertex->label << ", ";
         cout << (int)incomingEdge->weight << " miles" << endl;
      }
   }

   return 0;
}
```

> Because each `AddUndirectedEdge` inserts both directions, every location's
> "flights from" and "flights to" lists mirror each other here. The exact print
> order of vertices and of each edge list depends on `unordered_map`/`vector`
> iteration order, not on insertion order — the maps are **unordered**.

**How this maps back to the concepts:**

- It is an **adjacency-list** representation (Section 13), realized with hash maps
  and vectors instead of raw linked nodes — so it gets **O(1)** average edge
  insertion and neighbor lookup while using **O(V + E)** space (good for sparse
  graphs).
- Keeping a separate `toEdges` map is the practical way to answer "who is adjacent
  *to* this vertex?" quickly — something the single adjacency matrix / single
  adjacency list does not give directly.
- The `Vertex*`/`Edge*` object model generalizes the ADT: you could hang extra data
  or behavior off `Vertex`/`Edge`, exactly the kind of generalization the chapter
  summary mentions.

---

## 15. zyBooks BFS Example (Visitor Pattern)

This example runs a **breadth-first search** on the hash-map graph from Section 14,
but decouples "what to *do* at each vertex" from "how to *traverse*" using the
**visitor design pattern**. Instead of hard-coding a `cout` into the traversal (as
the textbook's `BreadthFirstSearch` in Section 10 does), the graph calls a
`Visit(...)` method on a **visitor object** for each vertex it reaches. Different
visitors produce different behavior with the same traversal code.

It reuses `Vertex.h`, `Edge.h`, and `Graph.h` from Section 14 (the `Graph` class is
extended with a `BreadthFirstSearch` member — see below), and adds two small files:
a visitor **interface** and one concrete visitor.

### `VertexVisitor.h` — the abstract base class

An abstract base class with a single **pure virtual** method (`= 0`). It defines the
*contract*: "anything that wants to observe a traversal must provide a `Visit`."
Because it has a pure virtual method, `VertexVisitor` cannot be instantiated
directly — only subclasses can.

```cpp
#ifndef VERTEXVISITOR_H
#define VERTEXVISITOR_H

#include "Graph.h"

class VertexVisitor {
public:
   virtual void Visit(Vertex* vertexToVisit) = 0;
};

#endif
```

### `VectorVertexVisitor.h` — a concrete visitor

Inherits from `VertexVisitor` and implements `Visit` by **appending each visited
vertex to a `vector`**. After the traversal, `visitedVertices` holds the vertices in
the exact order BFS reached them — a convenient way to capture the traversal order
without printing during the search.

```cpp
#ifndef VECTORVERTEXVISITOR_H
#define VECTORVERTEXVISITOR_H

#include <vector>
#include "VertexVisitor.h"

// VectorVertexVisitor adds each visited vertex to a vector
class VectorVertexVisitor : public VertexVisitor {
public:
   std::vector<Vertex*> visitedVertices;

   void Visit(Vertex* vertex) {
      visitedVertices.push_back(vertex);
   }
};

#endif
```

### The `BreadthFirstSearch` member on `Graph`

The demo calls `peopleGraph.BreadthFirstSearch(startVertex, visitor,
vertexDistances)`, so the Section 14 `Graph` class must be extended with this
method. It is the standard BFS from Section 10 adapted to (a) call the **visitor**
instead of `cout`, and (b) record each vertex's **distance in hops** from the start
in an `unordered_map`. (Add `#include <queue>` to `Graph.h`.)

```cpp
// Add inside the Graph class (public section)
void BreadthFirstSearch(Vertex* startVertex, VertexVisitor& visitor,
   std::unordered_map<Vertex*, double>& vertexDistances) {
   std::queue<Vertex*> vertexQueue;
   std::unordered_set<Vertex*> discovered;

   // The start vertex is distance 0 from itself
   vertexQueue.push(startVertex);
   discovered.insert(startVertex);
   vertexDistances[startVertex] = 0;

   while (!vertexQueue.empty()) {
      Vertex* currentVertex = vertexQueue.front();
      vertexQueue.pop();

      // "Do the work" — delegated to the visitor
      visitor.Visit(currentVertex);

      // Enqueue each undiscovered neighbor, one hop farther out
      for (Edge* edge : *GetEdgesFrom(currentVertex)) {
         Vertex* adjacentVertex = edge->toVertex;
         if (discovered.count(adjacentVertex) == 0) {
            discovered.insert(adjacentVertex);
            vertexDistances[adjacentVertex] =
               vertexDistances[currentVertex] + 1;
            vertexQueue.push(adjacentVertex);
         }
      }
   }
}
```

> This mirrors the Section 10 algorithm: a **FIFO queue** drives the search and a
> "discovered" set does the **marking** (here vertices are marked when *enqueued*,
> so no vertex is queued twice). The one addition is the `vertexDistances` map,
> which records how many edges from the start each vertex is. If your zyBooks
> `Graph.h` provides its own `BreadthFirstSearch`, use that one — this reconstruction
> is included so the notes are self-contained and runnable.

### Driver — `BFSDemo.cpp`

Builds an **undirected, unweighted** "people" graph (edges use the default weight
`1.0`), runs BFS from `"Eva"`, and prints each vertex with its hop-distance in the
order it was visited.

```cpp
#include <iostream>
#include "Graph.h"
#include "VectorVertexVisitor.h"
using namespace std;

int main() {
   // Starting vertex name
   string startName = "Eva";

   // Create the graph
   Graph peopleGraph;
   Vertex* vertexA = peopleGraph.AddVertex("Joe");
   Vertex* vertexB = peopleGraph.AddVertex("Eva");
   Vertex* vertexC = peopleGraph.AddVertex("Taj");
   Vertex* vertexD = peopleGraph.AddVertex("Chen");
   Vertex* vertexE = peopleGraph.AddVertex("Lily");
   Vertex* vertexF = peopleGraph.AddVertex("Jun");
   Vertex* vertexG = peopleGraph.AddVertex("Ken");

   // Add graph edges
   peopleGraph.AddUndirectedEdge(vertexA, vertexB);  // Edge from Joe to Eva
   peopleGraph.AddUndirectedEdge(vertexA, vertexC);  // Edge from Joe to Taj
   peopleGraph.AddUndirectedEdge(vertexB, vertexE);  // Edge from Eva to Lily
   peopleGraph.AddUndirectedEdge(vertexC, vertexD);  // Edge from Taj to Chen
   peopleGraph.AddUndirectedEdge(vertexC, vertexE);  // Edge from Taj to Lily
   peopleGraph.AddUndirectedEdge(vertexD, vertexF);  // Edge from Chen to Jun
   peopleGraph.AddUndirectedEdge(vertexE, vertexF);  // Edge from Lily to Jun
   peopleGraph.AddUndirectedEdge(vertexF, vertexG);  // Edge from Jun to Ken

   // Get the start vertex
   Vertex* startVertex = peopleGraph.GetVertex(startName);

   // Create a vertex visitor that adds visited vertices to a vector
   VectorVertexVisitor visitor;

   if (startVertex) {
      unordered_map<Vertex*, double> vertexDistances;
      peopleGraph.BreadthFirstSearch(startVertex, visitor, vertexDistances);

      // Output the result
      cout << "Breadth-first search traversal" << endl;
      cout << "Start vertex: " << startVertex->label << endl;
      for (Vertex* vertex : visitor.visitedVertices) {
         cout << vertex->label << ": " << vertexDistances[vertex] << endl;
      }
   }
   else {
      cout << "Start vertex \"" << startName << "\" not found" << endl;
   }

   return 0;
}
```

### The graph being searched

`AddUndirectedEdge` adds edges in **both** directions, so the friendships are
symmetric:

```
        Joe
       /   \
     Eva    Taj
      |     / \
     Lily--/   Chen
      |  \      |
      |   \     |
      +--- Jun -+
            |
           Ken
```

- Joe — Eva, Taj
- Eva — Joe, Lily
- Taj — Joe, Chen, Lily
- Chen — Taj, Jun
- Lily — Eva, Taj, Jun
- Jun — Chen, Lily, Ken
- Ken — Jun

### Expected output

BFS from Eva discovers vertices level by level (by number of hops). Neighbors are
visited in the order they sit in each vertex's outgoing-edge vector (insertion
order):

```
Breadth-first search traversal
Start vertex: Eva
Eva: 0
Joe: 1
Lily: 1
Taj: 2
Jun: 2
Chen: 3
Ken: 3
```

- **Distance 0:** Eva (the start).
- **Distance 1:** Joe and Lily (Eva's direct friends).
- **Distance 2:** Taj (via Joe) and Jun (via Lily).
- **Distance 3:** Chen (via Taj) and Ken (via Jun).

> The distances here count **edges (hops)**, not summed weights — every edge used
> the default weight `1.0`, and BFS assigns `parentDistance + 1`. This is BFS's
> "fewest edges" notion of shortest path (Section 10), **not** the weighted
> shortest path of Section 11. The exact ordering of equal-distance vertices
> depends on neighbor (vector) order, so it is deterministic given this insertion
> order.

### Why the visitor pattern?

- **Separation of concerns:** `BreadthFirstSearch` only knows *how to walk* the
  graph; the visitor decides *what happens* at each vertex. Swap in a different
  `VertexVisitor` subclass (e.g., one that prints, counts, or searches for a target)
  and the traversal code stays unchanged.
- **Reusability:** the same visitor could be handed to a depth-first traversal.
- This is the object-oriented answer to the chapter's point that traversal is a
  graph *application* kept separate from the graph's core operations (Section 8).

---

## 16. zyBooks DFS Example (Visitor Pattern)

This example runs a **depth-first search** on the hash-map graph from Section 14,
using the **same visitor pattern** as the BFS example (Section 15). It swaps the
FIFO queue for a **stack**, so instead of fanning out in rings it plunges down one
path as far as possible before backtracking (the strategy from Section 9). It also
introduces a second concrete visitor — one that *prints* — and runs the traversal
on **three different graphs** built from the same vertices, to show how the edge set
(not the vertices) determines the traversal order.

It reuses `Vertex.h`, `Edge.h`, `Graph.h` (extended with a `DepthFirstSearch`
member — see below), and `VertexVisitor.h` from earlier sections, and adds one file.

### `PrintVertexVisitor.h` — a print-as-you-go visitor

Another concrete `VertexVisitor` (compare with `VectorVertexVisitor` in Section 15).
Where that one *stored* each vertex, this one *prints* each vertex's label followed
by a space, right as it is visited. Same traversal engine, different behavior —
exactly the point of the visitor pattern.

```cpp
#ifndef PRINTVERTEXVISITOR_H
#define PRINTVERTEXVISITOR_H

#include <iostream>
#include "VertexVisitor.h"

// PrintVertexVisitor prints each visited vertex's label, followed by a space
class PrintVertexVisitor : public VertexVisitor {
public:
   void Visit(Vertex* vertex) {
      std::cout << vertex->label << " ";
   }
};

#endif
```

### The `DepthFirstSearch` member on `Graph`

The demo calls `graphs[i]->DepthFirstSearch(startVertex, visitor)`, so the Section 14
`Graph` must be extended with this method. It is the Section 9 depth-first algorithm
made iterative with an explicit **`std::stack`**, calling the **visitor** instead of
`cout`. (Add `#include <stack>` to `Graph.h`.)

```cpp
// Add inside the Graph class (public section)
void DepthFirstSearch(Vertex* startVertex, VertexVisitor& visitor) {
   std::stack<Vertex*> vertexStack;
   std::unordered_set<Vertex*> visited;

   vertexStack.push(startVertex);
   while (!vertexStack.empty()) {
      // Pop the most recently added vertex (LIFO → go deep first)
      Vertex* currentVertex = vertexStack.top();
      vertexStack.pop();

      // Mark/visit only the first time this vertex is popped
      if (visited.count(currentVertex) == 0) {
         visitor.Visit(currentVertex);
         visited.insert(currentVertex);

         // Push every neighbor; duplicates are filtered when popped
         for (Edge* edge : *GetEdgesFrom(currentVertex)) {
            vertexStack.push(edge->toVertex);
         }
      }
   }
}
```

> This mirrors DFS from Section 9: a **stack** (LIFO) is the auxiliary structure, so
> the search dives down one branch before backtracking. Marking is checked/applied
> **on pop** — a vertex may be pushed multiple times (once per edge into it), but the
> `visited` set guarantees it is *visited* only the first time it comes off the
> stack. If your zyBooks `Graph.h` provides its own `DepthFirstSearch`, use that —
> this reconstruction is included so the notes stay self-contained.

### Driver — `DFSDemo.cpp`

Creates **three graphs** with the same vertices `A`–`F` but different edges, then
runs DFS from `"A"` on each with the printing visitor.

```cpp
#include <iostream>
#include "Graph.h"
#include "VertexVisitor.h"
#include "PrintVertexVisitor.h"
using namespace std;

int main() {
   // Starting vertex label
   string startVertexLabel = "A";

   // Main program - Creates 3 different graphs, each with vertices A through
   // F, but with different sets of edges. Traverses each with DFS.
   string vertexNames[] = { "A", "B", "C", "D", "E", "F" };

   // Add the same set of vertices to 3 different graphs
   Graph graph1;
   Graph graph2;
   Graph graph3;
   Graph* graphs[] = { &graph1, &graph2, &graph3 };
   for (string& vertexName : vertexNames) {
      for (Graph* graph : graphs) {
         graph->AddVertex(vertexName);
      }
   }

   // Add graph 1's edges
   graph1.AddUndirectedEdge(graph1.GetVertex("A"), graph1.GetVertex("B"));
   graph1.AddUndirectedEdge(graph1.GetVertex("A"), graph1.GetVertex("D"));
   graph1.AddUndirectedEdge(graph1.GetVertex("B"), graph1.GetVertex("E"));
   graph1.AddUndirectedEdge(graph1.GetVertex("B"), graph1.GetVertex("F"));
   graph1.AddUndirectedEdge(graph1.GetVertex("C"), graph1.GetVertex("F"));
   graph1.AddUndirectedEdge(graph1.GetVertex("E"), graph1.GetVertex("F"));

   // Add graph 2's edges
   graph2.AddUndirectedEdge(graph2.GetVertex("A"), graph2.GetVertex("B"));
   graph2.AddUndirectedEdge(graph2.GetVertex("B"), graph2.GetVertex("C"));
   graph2.AddUndirectedEdge(graph2.GetVertex("C"), graph2.GetVertex("F"));
   graph2.AddUndirectedEdge(graph2.GetVertex("D"), graph2.GetVertex("E"));
   graph2.AddUndirectedEdge(graph2.GetVertex("E"), graph2.GetVertex("F"));

   // Add graph 3's edges
   graph3.AddUndirectedEdge(graph3.GetVertex("A"), graph3.GetVertex("B"));
   graph3.AddUndirectedEdge(graph3.GetVertex("A"), graph3.GetVertex("E"));
   graph3.AddUndirectedEdge(graph3.GetVertex("B"), graph3.GetVertex("C"));
   graph3.AddUndirectedEdge(graph3.GetVertex("B"), graph3.GetVertex("E"));
   graph3.AddUndirectedEdge(graph3.GetVertex("C"), graph3.GetVertex("E"));
   graph3.AddUndirectedEdge(graph3.GetVertex("D"), graph3.GetVertex("E"));
   graph3.AddUndirectedEdge(graph3.GetVertex("E"), graph3.GetVertex("F"));

   // Create the visitor that displays a vertex's label
   PrintVertexVisitor visitor;

   // Visit vertices in each graph with DFS
   cout << "Depth-first search traversal" << endl;
   for (int i = 0; i < sizeof(graphs) / sizeof(graphs[0]); i++) {
      cout << "Graph " << (i + 1) << ": ";
      Vertex* startVertex = graphs[i]->GetVertex(startVertexLabel);
      if (startVertex) {
         graphs[i]->DepthFirstSearch(startVertex, visitor);
      }
      else {
         cout << "Starting vertex \"" << startVertexLabel << "\" not found";
      }
      cout << endl;
   }

   return 0;
}
```

### The three graphs

Adjacency lists below are in **insertion order** (the order each vertex's outgoing
edges were added), which is what fixes the DFS order.

**Graph 1** — edges A–B, A–D, B–E, B–F, C–F, E–F:

| Vertex | Neighbors |
|--------|-----------|
| A | B, D |
| B | A, E, F |
| C | F |
| D | A |
| E | B, F |
| F | B, C, E |

**Graph 2** — edges A–B, B–C, C–F, D–E, E–F:

| Vertex | Neighbors |
|--------|-----------|
| A | B |
| B | A, C |
| C | B, F |
| D | E |
| E | D, F |
| F | C, E |

**Graph 3** — edges A–B, A–E, B–C, B–E, C–E, D–E, E–F:

| Vertex | Neighbors |
|--------|-----------|
| A | B, E |
| B | A, C, E |
| C | B, E |
| D | E |
| E | A, B, C, D, F |
| F | E |

### Expected output

```
Depth-first search traversal
Graph 1: A D B F E C
Graph 2: A B C F E D
Graph 3: A E F D C B
```

### Trace — Graph 1

Watch the stack (top on the right). A vertex is visited only the first time it is
popped while unvisited; every neighbor is pushed, so already-visited ones reappear
and are simply skipped.

| Step | Pop | Visit? | Push neighbors | Stack after |
|------|-----|--------|----------------|-------------|
| init | — | — | push A | `[A]` |
| 1 | A | **A** | B, D | `[B, D]` |
| 2 | D | **D** | A | `[B, A]` |
| 3 | A | skip (visited) | — | `[B]` |
| 4 | B | **B** | A, E, F | `[A, E, F]` |
| 5 | F | **F** | B, C, E | `[A, E, B, C, E]` |
| 6 | E | **E** | B, F | `[A, E, B, C, B, F]` |
| 7 | F | skip | — | `[A, E, B, C, B]` |
| 8 | B | skip | — | `[A, E, B, C]` |
| 9 | C | **C** | F | `[A, E, B, F]` |
| 10+ | F,B,E,A | all skip | — | `[]` |

Visit order → **A D B F E C**. Notice how DFS commits to A→D first (going deep),
backtracks, then dives A→B→F→E before finally reaching C — very different from BFS,
which would have taken A's neighbors (B, D) before going any deeper.

### DFS vs. BFS at a glance

- **Same vertices, different edges → different order.** All three graphs start at A
  and contain A–F, yet each prints a distinct sequence, because DFS order is driven
  entirely by *which edges exist* and *the order neighbors are stored*.
- **DFS uses a stack** (go deep, backtrack least); **BFS uses a queue** (stay
  shallow, explore level by level). That single data-structure swap is the whole
  difference — compare this `DepthFirstSearch` with the `BreadthFirstSearch` in
  Section 15.
- **No distance map here.** DFS answers "**can I reach it / visit everything
  reachable**," not "how far is it." For fewest-hops distance you'd use BFS
  (Section 15); for weighted shortest path, the priority-queue method (Section 11).
- All three graphs are **connected**, so DFS from A visits all six vertices; on a
  disconnected graph it would only reach A's component.

---

## 17. zyBooks Dijkstra's Shortest Path

This is the **weighted** shortest-path problem from Section 11, implemented on the
hash-map graph from Section 14. Where BFS (Section 15) finds the path with the
*fewest edges*, **Dijkstra's algorithm** finds the path with the *smallest total
edge weight* — the true "cheapest route." It computes the shortest path from one
start vertex to **every** other vertex (single-source), and records enough
information to reconstruct each actual path, not just its cost.

It reuses `Vertex.h`, `Edge.h`, and `Graph.h` (extended with `DijkstraShortestPath`
and `GetShortestPath` members — see below), and adds one helper class.

### `PathVertexInfo.h` — per-vertex bookkeeping

Dijkstra tracks three things for each vertex, bundled into `PathVertexInfo`:

- **`distance`** — best-known total weight from the start to this vertex (starts at
  **infinity**, meaning "no path found yet").
- **`predecessor`** — the vertex we arrived *from* on that best path (starts
  `nullptr`). Following predecessors backward reconstructs the whole route.
- **`vertex`** — a back-pointer to the vertex this info describes.

It also provides `RemoveMin`, a static helper that scans a vector and removes/returns
the info with the **smallest `distance`** — this is the "give me the closest
unvisited vertex" step at the heart of Dijkstra (a simple linear-scan stand-in for a
priority queue).

```cpp
#ifndef PATHVERTEXINFO_H
#define PATHVERTEXINFO_H

#include <limits>
#include <vector>
#include "Vertex.h"

class PathVertexInfo {
public:
   Vertex* vertex;
   double distance;
   Vertex* predecessor;

   PathVertexInfo(Vertex* vertex = nullptr) {
      this->vertex = vertex;
      distance = std::numeric_limits<double>::infinity();
      predecessor = nullptr;
   }

   // Utility function to remove and return the PathVertexInfo from the vector
   // that has the minimum distance
   static PathVertexInfo* RemoveMin(std::vector<PathVertexInfo*>& items) {
      if (0 == items.size()) {
         return nullptr;
      }

      int minIndex = 0;
      for (int i = 1; i < items.size(); i++) {
         if (items[i]->distance < items[minIndex]->distance) {
            minIndex = i;
         }
      }

      // Get the info with the minimum distance
      PathVertexInfo* infoWithMinDistance = items[minIndex];

      // Remove the info with the minimum distance
      items.erase(items.begin() + minIndex);

      return infoWithMinDistance;
   }
};

#endif
```

### The `DijkstraShortestPath` and `GetShortestPath` members on `Graph`

For this lab, the Section 14 `Graph` class gains two members (and `Graph.h` adds
`#include "PathVertexInfo.h"`). These are the **actual zyBooks implementations**:

```cpp
// Added to the Graph class (public section); Graph.h now #includes "PathVertexInfo.h"

std::unordered_map<Vertex*, PathVertexInfo> DijkstraShortestPath(
   Vertex* startVertex) {
   using namespace std;

   // Create the unordered_map for vertex information
   unordered_map<Vertex*, PathVertexInfo> info;

   // Populate info map with a (vertex, PathVertexInfo) pair for each vertex
   for (Vertex* vertex : GetVertices()) {
      info[vertex] = PathVertexInfo(vertex);
   }

   // Create the vector of PathVertexInfo pointers for unvisited vertices
   vector<PathVertexInfo*> unvisited;
   for (Vertex* vertex : GetVertices()) {
      unvisited.push_back(&info[vertex]);
   }

   // startVertex has a distance of 0 from itself
   info[startVertex].distance = 0.0;

   // Iterate through all vertices in the priority queue
   while (unvisited.size() > 0) {
      // Remove info with minimum distance
      PathVertexInfo* currentInfo = PathVertexInfo::RemoveMin(unvisited);

      // Check potential path lengths from the current vertex to all neighbors
      for (Edge* edge : *GetEdgesFrom(currentInfo->vertex)) {
         Vertex* adjacentVertex = edge->toVertex;
         double alternativePathDistance = currentInfo->distance + edge->weight;

         // If a shorter path from startVertex to adjacentVertex is found,
         // update adjacentVertex's distance and predecessor
         PathVertexInfo& adjacentInfo = info[adjacentVertex];
         if (alternativePathDistance < adjacentInfo.distance) {
            adjacentInfo.distance = alternativePathDistance;
            adjacentInfo.predecessor = currentInfo->vertex;
         }
      }
   }

   return info;
}

static std::string GetShortestPath(Vertex* startVertex, Vertex* endVertex,
   const std::unordered_map<Vertex*, PathVertexInfo>& infoMap) {

   // Start from endVertex and build the path in reverse
   std::string path = "";
   Vertex* currentVertex = endVertex;
   while (currentVertex != startVertex) {
      path = " -> " + currentVertex->label + path;
      currentVertex = infoMap.find(currentVertex)->second.predecessor;
   }
   path = startVertex->label + path;
   return path;
}
```

A few details worth noting in the real code:

- **`unvisited` holds pointers into `info`.** After filling `info` with one
  `PathVertexInfo` per vertex, the loop pushes `&info[vertex]` — the *addresses* of
  the map's values. `unordered_map` guarantees element addresses stay valid, so when
  `RemoveMin` returns one and the relax step writes through `info[adjacentVertex]`,
  everything refers to the same objects. That's why setting
  `info[startVertex].distance = 0.0` *after* building `unvisited` still works.
- **`GetShortestPath` is `static`** and takes the map by `const&`. It builds the
  string by **prepending** `" -> " + label` while walking `predecessor` links, and
  stops when it reaches `startVertex` (not `nullptr`) — so no separate reverse step
  is needed. Because it dereferences `predecessor`, the caller must not call it for
  an unreachable vertex (the demo's `if` guard handles that).

> **How it relates to Section 11:** the textbook `ShortestPath` pushes *edges* onto
> a minimum **priority queue** keyed by distance; this version keeps a
> `PathVertexInfo` per *vertex* and pulls the minimum out of a plain vector via
> `RemoveMin`. Same greedy idea — always finalize the closest unvisited vertex next
> — but this one also stores a `predecessor` so it can rebuild the actual path, not
> just print the distance.

### Driver — `DijkstrasDemo.cpp`

Builds an **undirected, weighted** graph, runs Dijkstra from `A`, then prints the
shortest path and total weight to every vertex.

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Graph.h"
using namespace std;

int main() {
   Graph graph;

   Vertex* vertexA = graph.AddVertex("A");
   Vertex* vertexB = graph.AddVertex("B");
   Vertex* vertexC = graph.AddVertex("C");
   Vertex* vertexD = graph.AddVertex("D");
   Vertex* vertexE = graph.AddVertex("E");
   Vertex* vertexF = graph.AddVertex("F");
   Vertex* vertexG = graph.AddVertex("G");
   vector<Vertex*> vertices = {
      vertexA, vertexB, vertexC, vertexD, vertexE, vertexF, vertexG
   };

   graph.AddUndirectedEdge(vertexA, vertexB, 8);
   graph.AddUndirectedEdge(vertexA, vertexD, 3);
   graph.AddUndirectedEdge(vertexA, vertexC, 7);
   graph.AddUndirectedEdge(vertexB, vertexE, 6);
   graph.AddUndirectedEdge(vertexC, vertexD, 1);
   graph.AddUndirectedEdge(vertexC, vertexE, 2);
   graph.AddUndirectedEdge(vertexD, vertexF, 15);
   graph.AddUndirectedEdge(vertexD, vertexG, 12);
   graph.AddUndirectedEdge(vertexE, vertexF, 4);
   graph.AddUndirectedEdge(vertexF, vertexG, 1);

   // Run Dijkstra's algorithm first
   unordered_map<Vertex*, PathVertexInfo> infoMap =
      graph.DijkstraShortestPath(vertexA);

   // Display shortest path for each vertex from vertexA.
   for (Vertex* vertex : vertices) {
      PathVertexInfo& info = infoMap[vertex];
      if (info.predecessor == nullptr && vertex != vertexA) {
         cout << "A to " << vertex->label << ": no path exists" << endl;
      }
      else {
         cout << "A to " << vertex->label << ": ";
         cout << graph.GetShortestPath(vertexA, vertex, infoMap);
         cout << " (total weight: " << (int)info.distance << ")" << endl;
      }
   }

   return 0;
}
```

### The graph

Undirected, weighted (each edge's weight is its cost):

| Vertex | Edges (neighbor : weight) |
|--------|---------------------------|
| A | B:8, D:3, C:7 |
| B | A:8, E:6 |
| C | A:7, D:1, E:2 |
| D | A:3, C:1, F:15, G:12 |
| E | B:6, C:2, F:4 |
| F | D:15, E:4, G:1 |
| G | D:12, F:1 |

### Trace — greedily finalizing the closest vertex

Each row removes the minimum-distance unvisited vertex and **relaxes** its edges
(updates a neighbor if a cheaper route through the current vertex is found).
Tentative distances (with predecessor) shown after each step:

| Finalize (dist) | B | C | D | E | F | G |
|-----------------|---|---|---|---|---|---|
| start | ∞ | ∞ | ∞ | ∞ | ∞ | ∞ |
| **A** (0) | 8 (A) | 7 (A) | 3 (A) | ∞ | ∞ | ∞ |
| **D** (3) | 8 (A) | **4 (D)** | — | ∞ | 18 (D) | 15 (D) |
| **C** (4) | 8 (A) | — | — | **6 (C)** | 18 (D) | 15 (D) |
| **E** (6) | 8 (A) | — | — | — | **10 (E)** | 15 (D) |
| **B** (8) | — | — | — | — | 10 (E) | 15 (D) |
| **F** (10) | — | — | — | — | — | **11 (F)** |
| **G** (11) | — | — | — | — | — | — |

Notice the payoff of using weights: the cheapest route to C is **A → D → C** (cost
4), *not* the direct edge A–C (cost 7). Likewise G is reached cheapest via
A→D→C→E→F→G (11), beating the direct A→D→G (15).

### Expected output

```
A to A: A (total weight: 0)
A to B: A -> B (total weight: 8)
A to C: A -> D -> C (total weight: 4)
A to D: A -> D (total weight: 3)
A to E: A -> D -> C -> E (total weight: 6)
A to F: A -> D -> C -> E -> F (total weight: 10)
A to G: A -> D -> C -> E -> F -> G (total weight: 11)
```

### How the pieces fit

- **`DijkstraShortestPath`** does the computation and returns the `infoMap`
  (distance + predecessor for every vertex).
- **`GetShortestPath`** does *reconstruction*: starting at the destination, it hops
  backward through `predecessor` links, **prepending** each label (`" -> " + label`)
  until it reaches the start, so the finished string reads `A -> … -> dest`. This is
  exactly the "follow the last-vertex column backward" idea from the Section 11
  output table, automated.
- The **`no path exists`** branch in the driver handles a disconnected vertex: if a
  vertex still has `distance == infinity` and `predecessor == nullptr` (and isn't the
  start), Dijkstra never reached it. In this connected graph that never happens.

### Analysis

- **Greedy and correct for non-negative weights.** Once a vertex is removed by
  `RemoveMin`, its distance is final. (Dijkstra assumes **no negative edge
  weights** — negatives would break that guarantee.)
- **Cost of this implementation:** `RemoveMin` is a linear scan (**O(V)**), called
  once per vertex, and every edge is relaxed once — so overall **O(V² + E)**. A real
  binary-heap/`priority_queue` would bring this to **O((V + E) log V)**; the linear
  vector is used here for clarity, mirroring the Section 11 discussion of using a
  priority queue for the "next shortest distance."
- **BFS vs. Dijkstra:** on an *unweighted* graph (all weights equal), Dijkstra
  reduces to BFS. The weights are what make it necessary here.

---

## 18. zyBooks Bellman-Ford Shortest Path

**Bellman-Ford** solves the same single-source shortest-path problem as Dijkstra
(Section 17), but trades speed for generality: it works even when some edges have
**negative weights**, and it can **detect a negative-weight cycle** (a loop whose
total weight is negative, which would make "shortest path" meaningless because you
could keep looping to lower the cost forever). Dijkstra's greedy "finalize the
closest vertex" logic breaks with negative edges; Bellman-Ford avoids the issue by
simply **relaxing every edge, repeatedly**.

It reuses `Vertex.h`, `Edge.h`, and `Graph.h` — including the **`GetShortestPath`**
member from Section 17 — plus a trimmed `PathVertexInfo`.

### `PathVertexInfo.h` — trimmed for Bellman-Ford

Same three fields as Section 17 (`vertex`, `distance` starting at infinity,
`predecessor`), but **without** the `RemoveMin` helper — Bellman-Ford never needs
to pull out the minimum-distance vertex, so the priority-queue helper is gone.

```cpp
#ifndef PATHVERTEXINFO_H
#define PATHVERTEXINFO_H

#include <limits>
#include <vector>
#include "Graph.h"


class PathVertexInfo {
public:
   Vertex* vertex;
   double distance;
   Vertex* predecessor;

   PathVertexInfo(Vertex* vertex = nullptr) {
      this->vertex = vertex;
      distance = std::numeric_limits<double>::infinity();
      predecessor = nullptr;
   }
};

#endif
```

### The `BellmanFord` member on `Graph`

The demo calls `graph.BellmanFord(startVertex, result)`, which returns a **`bool`**:
`true` if shortest paths were computed successfully, `false` if a negative-weight
cycle was detected. The Section 14 `Graph` is extended with this method (and it
reuses `Graph::GetShortestPath` from Section 17 for path reconstruction).

```cpp
// Added to the Graph class (public section)
bool BellmanFord(Vertex* startVertex,
   std::unordered_map<Vertex*, PathVertexInfo>& info) {
   // One PathVertexInfo per vertex; start is distance 0, all others infinity
   for (Vertex* vertex : GetVertices()) {
      info[vertex] = PathVertexInfo(vertex);
   }
   info[startVertex].distance = 0.0;

   std::vector<Vertex*> vertices = GetVertices();

   // Relax all edges |V| - 1 times
   for (unsigned int i = 0; i < vertices.size() - 1; i++) {
      for (Edge* edge : GetEdges()) {
         double alternativePathDistance =
            info[edge->fromVertex].distance + edge->weight;

         // A shorter path to edge->toVertex? Record distance and predecessor.
         if (alternativePathDistance < info[edge->toVertex].distance) {
            info[edge->toVertex].distance = alternativePathDistance;
            info[edge->toVertex].predecessor = edge->fromVertex;
         }
      }
   }

   // One more pass: if any edge can still be relaxed, a negative cycle exists
   for (Edge* edge : GetEdges()) {
      double alternativePathDistance =
         info[edge->fromVertex].distance + edge->weight;
      if (alternativePathDistance < info[edge->toVertex].distance) {
         return false;   // negative-weight cycle detected
      }
   }

   return true;
}
```

> This is the standard Bellman-Ford. If your zyBooks `Graph.h` provides its own
> `BellmanFord`, use that — this reconstruction keeps the notes self-contained.
> Note it iterates **`GetEdges()`** (the set of *directed* edges from Section 14);
> each undirected edge added by the demo is already stored as two directed edges, so
> both directions get relaxed.

### Why "relax all edges |V| − 1 times"?

A shortest path in a graph with `V` vertices visits at most `V − 1` edges (any more
would repeat a vertex). Each full pass over all edges guarantees that paths one edge
longer become correct. So after `V − 1` passes, every shortest path — no matter how
many edges it uses — has been found. **Relaxing** an edge means: *if going to
`toVertex` via `fromVertex` is cheaper than its current best, update its distance and
predecessor.*

The **extra pass** at the end is the negative-cycle check: if any edge can *still* be
relaxed after `V − 1` passes, distances are still dropping, which is only possible if
a negative-weight cycle exists → return `false`.

### Driver — `BellmanFordDemo.cpp`

Builds a **mixed directed/undirected, weighted** graph, runs Bellman-Ford from `A`,
and either prints each shortest path or reports a negative cycle.

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include "Graph.h"
#include "PathVertexInfo.h"
using namespace std;

int main() {
   Graph graph;
   Vertex* vertexA = graph.AddVertex("A");
   Vertex* vertexB = graph.AddVertex("B");
   Vertex* vertexC = graph.AddVertex("C");
   Vertex* vertexD = graph.AddVertex("D");
   Vertex* vertexE = graph.AddVertex("E");
   Vertex* vertexF = graph.AddVertex("F");
   Vertex* vertices[] = { vertexA, vertexB, vertexC, vertexD, vertexE, vertexF };
   graph.AddDirectedEdge(vertexA, vertexB, 1);
   graph.AddDirectedEdge(vertexA, vertexC, 2);
   graph.AddUndirectedEdge(vertexB, vertexC, 1);
   graph.AddUndirectedEdge(vertexB, vertexD, 3);
   graph.AddDirectedEdge(vertexB, vertexE, 2);
   graph.AddUndirectedEdge(vertexC, vertexE, 2);
   graph.AddDirectedEdge(vertexD, vertexC, 1);
   graph.AddUndirectedEdge(vertexD, vertexE, 4);
   graph.AddDirectedEdge(vertexD, vertexF, 3);
   graph.AddDirectedEdge(vertexE, vertexF, 3);

   // Set starting vertex for shortest paths
   Vertex* startVertex = vertexA;

   // Run Bellman-Ford's shortest path algorithm. Display results if
   // successful, or error message if a negative edge weight cycle exists.
   unordered_map<Vertex*, PathVertexInfo> result;
   if (graph.BellmanFord(startVertex, result)) {
      for (Vertex* vertex : vertices) {
         string path = Graph::GetShortestPath(startVertex, vertex, result);
         cout << startVertex->label << " -> " << vertex->label << ": ";
         cout << path << " (" << (int)result[vertex].distance << ")" << endl;
      }
   }
   else {
      cout << "Bellman-Ford failed, negative edge weight cycle detected." << endl;
   }

   return 0;
}
```

### The graph

Some edges are **directed** (one-way), some **undirected** (stored as two directed
edges). Outgoing adjacency (neighbor : weight):

| Vertex | Outgoing edges | From |
|--------|----------------|------|
| A | B:1, C:2 | both directed |
| B | C:1, D:3, E:2 | C/D undirected, E directed |
| C | B:1, E:2 | B/E via undirected edges |
| D | B:3, C:1, E:4, F:3 | B/E undirected, C/F directed |
| E | C:2, D:4, F:3 | C/D undirected, F directed |
| F | *(none)* | F only has incoming edges |

All weights are **positive**, so there is no negative cycle → `BellmanFord` returns
`true` and the success branch runs.

### Expected output

```
A -> A: A (0)
A -> B: A -> B (1)
A -> C: A -> C (2)
A -> D: A -> B -> D (4)
A -> E: A -> B -> E (3)
A -> F: A -> B -> E -> F (6)
```

- **A→B** (1): the direct edge.
- **A→C** (2): the direct edge `A→C` costs 2, which ties with `A→B→C` (1 + 1). Both
  total 2. *Which predecessor is recorded for a tie depends on the order edges come
  out of `GetEdges()`* (an `unordered_set`), so the path could print as `A -> B -> C`
  on some runs — the total weight is 2 either way.
- **A→D** (4): `A→B→D` (1 + 3); cheaper than any route through C.
- **A→E** (3): `A→B→E` (1 + 2); beats `A→C→E` (2 + 2 = 4).
- **A→F** (6): `A→B→E→F` (3 + 3); beats `A→B→D→F` (4 + 3 = 7).

Because every weight here is positive, Bellman-Ford produces the **same distances**
Dijkstra would — this demo showcases the algorithm's mechanics and its success/`bool`
return, not negative edges specifically.

### Dijkstra vs. Bellman-Ford

| | Dijkstra (Section 17) | Bellman-Ford (this section) |
|---|---|---|
| Strategy | Greedy — finalize the closest unvisited vertex | Brute force — relax **all** edges, `V − 1` times |
| Negative edge weights | **Not allowed** (greedy choice breaks) | **Allowed** |
| Detects negative cycles | No | **Yes** (the extra relaxation pass) |
| Auxiliary structure | Min "priority queue" (`RemoveMin`) | None — just repeated edge scans |
| Time complexity | ~O(V² + E) here (O((V+E) log V) with a heap) | **O(V · E)** |
| When to use | Non-negative weights, want speed | Possible negative weights, or need cycle detection |

Both stop at the same idea from Section 11 — build shortest paths from a single
source and record a predecessor per vertex so the route can be reconstructed
(here via the shared `Graph::GetShortestPath`).

---

## 19. zyBooks Topological Sort

A **topological sort** orders the vertices of a **directed acyclic graph (DAG)** so
that for every directed edge `X → Y`, `X` comes **before** `Y` in the ordering. It
answers "in what order can I do these tasks so every prerequisite comes first?" —
think course prerequisites, build/compilation dependencies, or job scheduling.

Two important facts:

- It only works on a **DAG**. If the graph has a **cycle**, no valid ordering exists
  (the items in the cycle each depend on one another).
- The ordering is **not unique** — a graph can have many valid topological orders.

It reuses `Vertex.h`, `Edge.h`, and `Graph.h` (extended with a `TopologicalSort`
member — see below) with no new helper files.

### The `TopologicalSort` member on `Graph`

The demo calls `graph->TopologicalSort()`, which returns a `vector<Vertex*>` in
topological order. The standard approach (**Kahn's algorithm**) repeatedly removes a
vertex that has **no remaining incoming edges**: such a vertex has no unmet
prerequisites, so it can go next. "Removing" it decrements the incoming-edge count of
each of its neighbors, which may expose new no-incoming vertices.

```cpp
// Added to the Graph class (public section)
std::vector<Vertex*> TopologicalSort() {
   std::vector<Vertex*> resultList;
   std::unordered_map<Vertex*, int> remainingEdgeCount;

   // Count how many incoming edges each vertex starts with (its in-degree)
   for (Vertex* vertex : GetVertices()) {
      remainingEdgeCount[vertex] = GetEdgesTo(vertex)->size();
   }

   // Vertices with no incoming edges have no unmet prerequisites
   std::vector<Vertex*> noIncoming;
   for (Vertex* vertex : GetVertices()) {
      if (remainingEdgeCount[vertex] == 0) {
         noIncoming.push_back(vertex);
      }
   }

   while (!noIncoming.empty()) {
      // Take any no-incoming vertex and append it to the result
      Vertex* currentVertex = noIncoming.back();
      noIncoming.pop_back();
      resultList.push_back(currentVertex);

      // "Remove" its outgoing edges: each neighbor loses one incoming edge
      for (Edge* edge : *GetEdgesFrom(currentVertex)) {
         Vertex* adjacentVertex = edge->toVertex;
         remainingEdgeCount[adjacentVertex]--;
         if (remainingEdgeCount[adjacentVertex] == 0) {
            noIncoming.push_back(adjacentVertex);
         }
      }
   }

   return resultList;
}
```

> This is the standard Kahn's-algorithm topological sort. If your zyBooks `Graph.h`
> provides its own `TopologicalSort`, use that — this reconstruction keeps the notes
> self-contained. Notice it leans on **`GetEdgesTo`** (the second map from Section 14)
> to get each vertex's in-degree in O(1) — a concrete payoff of storing incoming
> edges separately.
>
> **Cycle detection:** if the graph has a cycle, the vertices in it never reach a
> count of 0, so `resultList` ends up **smaller than the number of vertices**. Both
> graphs in this demo are DAGs, so every vertex is included.

### Driver — `TopologicalSortDemo.cpp`

Builds **two directed graphs** (both DAGs) with vertices `A`–`G` and different edge
sets, then prints a topological ordering of each.

```cpp
#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

int main() {
   // Make two graphs
   Graph graph1;
   Vertex* vertexA = graph1.AddVertex("A");
   Vertex* vertexB = graph1.AddVertex("B");
   Vertex* vertexC = graph1.AddVertex("C");
   Vertex* vertexD = graph1.AddVertex("D");
   Vertex* vertexE = graph1.AddVertex("E");
   Vertex* vertexF = graph1.AddVertex("F");
   Vertex* vertexG = graph1.AddVertex("G");
   graph1.AddDirectedEdge(vertexA, vertexB);
   graph1.AddDirectedEdge(vertexA, vertexC);
   graph1.AddDirectedEdge(vertexB, vertexF);
   graph1.AddDirectedEdge(vertexC, vertexD);
   graph1.AddDirectedEdge(vertexD, vertexF);
   graph1.AddDirectedEdge(vertexE, vertexF);
   graph1.AddDirectedEdge(vertexE, vertexG);
   graph1.AddDirectedEdge(vertexF, vertexG);

   Graph graph2;
   vertexA = graph2.AddVertex("A");
   vertexB = graph2.AddVertex("B");
   vertexC = graph2.AddVertex("C");
   vertexD = graph2.AddVertex("D");
   vertexE = graph2.AddVertex("E");
   vertexF = graph2.AddVertex("F");
   vertexG = graph2.AddVertex("G");
   graph2.AddDirectedEdge(vertexA, vertexE);
   graph2.AddDirectedEdge(vertexB, vertexC);
   graph2.AddDirectedEdge(vertexC, vertexF);
   graph2.AddDirectedEdge(vertexC, vertexG);
   graph2.AddDirectedEdge(vertexD, vertexA);
   graph2.AddDirectedEdge(vertexD, vertexB);
   graph2.AddDirectedEdge(vertexE, vertexG);
   graph2.AddDirectedEdge(vertexF, vertexG);

   // Perform a topological sort with each graph
   vector<Graph*> graphs = { &graph1, &graph2 };
   int graphNum = 1;
   for (Graph* graph : graphs) {
      vector<Vertex*> resultList = graph->TopologicalSort();

      // Display the sorted results
      cout << "Graph " << graphNum << ": ";
      if (resultList.size() > 0) {
         cout << resultList[0]->label;
      }
      for (int i = 1; i < resultList.size(); i++) {
         cout << ", " << resultList[i]->label;
      }
      cout << endl;
      graphNum++;
   }

   return 0;
}
```

### The graphs (in-degrees)

**Graph 1** — edges A→B, A→C, B→F, C→D, D→F, E→F, E→G, F→G:

| Vertex | In-degree | Incoming from |
|--------|-----------|---------------|
| A | 0 | — |
| B | 1 | A |
| C | 1 | A |
| D | 1 | C |
| E | 0 | — |
| F | 3 | B, D, E |
| G | 2 | E, F |

Sources (in-degree 0): **A, E**.

**Graph 2** — edges A→E, B→C, C→F, C→G, D→A, D→B, E→G, F→G:

| Vertex | In-degree | Incoming from |
|--------|-----------|---------------|
| A | 1 | D |
| B | 1 | D |
| C | 1 | B |
| D | 0 | — |
| E | 1 | A |
| F | 1 | C |
| G | 3 | C, E, F |

Source (in-degree 0): **D** only — so every valid ordering must start with `D`.

### Expected output (one valid ordering)

```
Graph 1: A, E, B, C, D, F, G
Graph 2: D, A, B, E, C, F, G
```

> **Topological order is not unique, and this implementation's exact output is
> order-dependent.** `GetVertices()` iterates an `unordered_map`, so which sources are
> found first (and the order they enter `noIncoming`) depends on hash ordering, not
> insertion order. `Graph 1: A, B, C, D, E, F, G` and `Graph 2: D, B, A, C, F, E, G`
> are equally valid. What every valid ordering **must** satisfy is that each edge
> points "forward": e.g., in Graph 1, `A` precedes `B`/`C`, `C` precedes `D`, and `F`
> precedes `G`; in Graph 2, `D` comes first and `G` comes last.

### How it works — trace of Graph 2

Because Graph 2 has a single source, its structure is easy to follow (using
back-of-list removal):

| `noIncoming` (before) | Take | Append to result | Decrement neighbors → new sources |
|-----------------------|------|------------------|-----------------------------------|
| `[D]` | D | D | A→0, B→0 → add A, B |
| `[A, B]` | B | D, B | C→0 → add C |
| `[A, C]` | C | D, B, C | F→0, G→2 → add F |
| `[A, F]` | F | D, B, C, F | G→1 |
| `[A]` | A | D, B, C, F, A | E→0 → add E |
| `[E]` | E | …, E | G→0 → add G |
| `[G]` | G | …, G | — |

That produces `D, B, C, F, A, E, G` — another perfectly valid ordering, illustrating
how the removal order (back vs. front, hash order) changes the result while keeping
every edge pointing forward.

### Relation to the rest of the chapter

- Topological sort is another **traversal-based application** (Section 8) built only
  from the ADT operations — here `GetVertices`, `GetEdgesFrom`, and `GetEdgesTo`.
- It is closely related to DFS (Section 16): a topological order can also be produced
  by a depth-first traversal that appends each vertex *after* visiting all its
  descendants, then reversing. Kahn's algorithm (used here) is the queue/count-based
  alternative.
- Unlike the shortest-path algorithms (Sections 17–18), it ignores edge **weights**
  entirely — only edge **direction** matters.

---

## 20. Which Version to Use?

| Aspect | Array-Based (adjacency matrix) | Linked (adjacency lists) | zyBooks (hash-map adjacency lists) |
|--------|--------------------------------|--------------------------|------------------------------------|
| Add / query an edge | **O(1)** — index directly into the matrix | Must **walk the list** for that vertex | **O(1)** avg map lookup; `HasEdge` walks one vertex's vector |
| Space | **O(N²)** for the matrix (wasted if few edges; half redundant for undirected graphs) | **O(N)** for **sparse** graphs; up to **O(N²)** if there are many edges | **O(V + E)** — good for sparse graphs |
| Simplicity | Simple and fast | More algorithmic complexity managing lists | Simple to use via the STL; manual pointer ownership to manage |

- **Adjacency matrix:** fast and simple, but wastes space when the graph is
  sparse.
- **Adjacency lists:** space-efficient for sparse graphs (allocate memory only as
  needed), but edge lookups require walking the lists.
- **Hash-map adjacency lists (zyBooks):** the practical modern take on adjacency
  lists — average **O(1)** neighbor lookups and **O(V + E)** space, with a second
  map for fast incoming-edge queries (Section 14).

---

## 21. Summary

- A **graph** relaxes the shape property of a linked structure to represent
  **arbitrary networks** of information. It is a set of **vertices** connected by
  **edges**; vertices usually represent objects and edges represent relationships.
- Edges can be **undirected or directed**, and can carry **weights**.
- Like trees, graphs can be traversed multiple ways. **Depth-first** (stack) and
  **breadth-first** (queue) are two common strategies; both use **marking** to
  avoid revisiting nodes and cycling.
- The **single-source shortest-path** traversal uses a **minimum priority queue**
  keyed on distance to find minimal-cost paths from a start vertex to all others.
- A related classic goal (not implemented here) is the **minimum spanning tree** —
  a tree of links reaching every vertex with minimal total cost.
- Graphs are commonly represented by an **adjacency matrix** (fast, O(1) edge
  access, but O(N²) space — wasteful for sparse graphs) or by **adjacency lists**
  (O(N) space for sparse graphs, but slower edge lookups). A modern, practical form
  of adjacency lists uses **hash maps of `Vertex*` → `vector<Edge*>`** (Section 14)
  for average O(1) neighbor lookups and O(V + E) space.
- Graph algorithms make heavy use of the earlier ADTs: **stacks, queues, and
  priority queues**.

### Quick reference — traversal comparison

| Traversal | Auxiliary structure | Order explored | Stops when | Uses weights? |
|-----------|---------------------|----------------|------------|---------------|
| **Depth-First Search** | Stack (LIFO) | Deepest path first, backtrack least | Target found or stack empty | No |
| **Breadth-First Search** | Queue (FIFO) | All same-length paths first | Target found or queue empty | No |
| **Shortest Path** | Min priority queue | Next-closest vertex first | No target — priority queue empty | **Yes** |
