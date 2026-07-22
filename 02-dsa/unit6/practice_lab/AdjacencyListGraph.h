#ifndef ADJACENCYLISTGRAPH_H
#define ADJACENCYLISTGRAPH_H

#include "DirectedGraph.h"
#include "AdjacencyListVertex.h"

class AdjacencyListGraph : public DirectedGraph {
protected:
   std::vector<AdjacencyListVertex*> vertices;
   
public:    
   virtual ~AdjacencyListGraph() {
      for (AdjacencyListVertex* vertex : vertices) {
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

      AdjacencyListVertex* newVertex = new AdjacencyListVertex(newVertexLabel);
      vertices.push_back(newVertex);
      return newVertex;
   }
    
   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
      if (fromVertex == nullptr || toVertex == nullptr) {
         return false;
      }

      // Don't add an edge that already exists
      if (HasEdge(fromVertex, toVertex)) {
         return false;
      }

      // fromVertex stores its outgoing edges as adjacent vertices
      AdjacencyListVertex* fromListVertex =
         static_cast<AdjacencyListVertex*>(fromVertex);
      fromListVertex->adjacent.push_back(toVertex);
      return true;
   }
    
   // Returns a vector of edges with the specified fromVertex.
   virtual std::vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
      std::vector<Edge> edges;
      if (fromVertex == nullptr) {
         return edges;
      }

      // Each adjacent vertex represents an edge from fromVertex to that vertex
      AdjacencyListVertex* fromListVertex =
         static_cast<AdjacencyListVertex*>(fromVertex);
      for (Vertex* toVertex : fromListVertex->adjacent) {
         edges.push_back(Edge(fromVertex, toVertex));
      }
      return edges;
   }
    
   // Returns a vector of edges with the specified toVertex.
   virtual std::vector<Edge> GetEdgesTo(Vertex* toVertex) override {
      std::vector<Edge> edges;
      if (toVertex == nullptr) {
         return edges;
      }

      // Search every vertex's adjacency list for toVertex
      for (AdjacencyListVertex* fromVertex : vertices) {
         for (Vertex* adjacentVertex : fromVertex->adjacent) {
            if (adjacentVertex == toVertex) {
               edges.push_back(Edge(fromVertex, toVertex));
            }
         }
      }
      return edges;
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual Vertex* GetVertex(std::string vertexLabel) override {
      for (AdjacencyListVertex* vertex : vertices) {
         if (vertex->GetLabel() == vertexLabel) {
            return vertex;
         }
      }
      return nullptr;
   }
    
   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
      if (fromVertex == nullptr || toVertex == nullptr) {
         return false;
      }

      AdjacencyListVertex* fromListVertex =
         static_cast<AdjacencyListVertex*>(fromVertex);
      for (Vertex* adjacentVertex : fromListVertex->adjacent) {
         if (adjacentVertex == toVertex) {
            return true;
         }
      }
      return false;
   }
};

#endif