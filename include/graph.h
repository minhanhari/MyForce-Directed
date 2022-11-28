#ifndef INCLUDE_GRAPH_H
#define INCLUDE_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vertex.h"
#include "edge.h"
#include "vector.h"

struct Graph
{
  struct Vertex **vertexes;
  struct Edge *edges;
  int vertexes_num;
  int edges_num;
};

struct Graph *newGraph(struct VertexList *vertexes, struct EdgeList *edges);

#define listLen(list) _Generic((list),             \
                               struct VertexList * \
                               : VertexListLen,    \
                                 struct EdgeList * \
                               : EdgeListLen)(list)

void initVerticesPosition(struct Graph *graph, bool random);

void ForceDirectedLayout(struct Graph *graph, int max_iteration);

void LocalMinimum(struct Graph *gr, double eps);

#endif // INCLUDE_GRAPH_H