#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#include "DirectedGraph.h"

class AdjacencyMatrixGraph : public DirectedGraph {
protected:
   std::vector<Vertex*> vertices;
   
   // If matrixRows[X][Y] is true, then an edge exists from vertices[X] to
   // vertices[Y]
   std::vector<std::vector<bool>> matrixRows;
   
   // Returns the index of vertex in the vertices vector, or -1 if not found
   int GetVertexIndex(Vertex* vertex) {
      for (int i = 0; i < (int)vertices.size(); i++) {
         if (vertices[i] == vertex) {
            return i;
         }
      }
      return -1;
   }
   
public:    
   virtual ~AdjacencyMatrixGraph() {
      for (Vertex* vertex : vertices) {
         delete vertex;
      }
   }

   // Creates and adds a new vertex to the graph, provided a vertex with the
   // same label doesn't already exist in the graph. Returns the new vertex on
   // success, nullptr on failure.
   virtual Vertex* AddVertex(std::string newVertexLabel) override {
      // A vertex with the same label must not already exist
      if (GetVertex(newVertexLabel) != nullptr) {
         return nullptr;
      }

      Vertex* newVertex = new Vertex(newVertexLabel);
      vertices.push_back(newVertex);

      // Grow the matrix to remain square: add a column to each existing row,
      // then add a new row for the new vertex (all entries false).
      int newSize = (int)vertices.size();
      for (std::vector<bool>& row : matrixRows) {
         row.push_back(false);
      }
      matrixRows.push_back(std::vector<bool>(newSize, false));

      return newVertex;
   }
   
   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
      int fromIndex = GetVertexIndex(fromVertex);
      int toIndex = GetVertexIndex(toVertex);
      if (fromIndex == -1 || toIndex == -1) {
         return false;
      }

      // Don't add an edge that already exists
      if (matrixRows[fromIndex][toIndex]) {
         return false;
      }

      matrixRows[fromIndex][toIndex] = true;
      return true;
   }
    
   // Returns a vector of edges with the specified fromVertex.
   virtual std::vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
      std::vector<Edge> edges;
      int fromIndex = GetVertexIndex(fromVertex);
      if (fromIndex == -1) {
         return edges;
      }

      // Each true entry in the row is an edge from fromVertex to vertices[col]
      for (int col = 0; col < (int)vertices.size(); col++) {
         if (matrixRows[fromIndex][col]) {
            edges.push_back(Edge(fromVertex, vertices[col]));
         }
      }
      return edges;
   }
    
   // Returns a vector of edges with the specified toVertex.
   virtual std::vector<Edge> GetEdgesTo(Vertex* toVertex) override {
      std::vector<Edge> edges;
      int toIndex = GetVertexIndex(toVertex);
      if (toIndex == -1) {
         return edges;
      }

      // Each true entry in the column is an edge from vertices[row] to toVertex
      for (int row = 0; row < (int)vertices.size(); row++) {
         if (matrixRows[row][toIndex]) {
            edges.push_back(Edge(vertices[row], toVertex));
         }
      }
      return edges;
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual Vertex* GetVertex(std::string vertexLabel) override {
      for (Vertex* vertex : vertices) {
         if (vertex->GetLabel() == vertexLabel) {
            return vertex;
         }
      }
      return nullptr;
   }
    
   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
      int fromIndex = GetVertexIndex(fromVertex);
      int toIndex = GetVertexIndex(toVertex);
      if (fromIndex == -1 || toIndex == -1) {
         return false;
      }

      return matrixRows[fromIndex][toIndex];
   }
};

#endif