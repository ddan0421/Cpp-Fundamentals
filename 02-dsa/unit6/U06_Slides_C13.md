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
15. [Which Version to Use?](#15-which-version-to-use)
16. [Summary](#16-summary)

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

## 15. Which Version to Use?

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

## 16. Summary

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
