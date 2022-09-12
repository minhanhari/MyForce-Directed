#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

struct Edge
{
    struct Vertex *start;
    struct Vertex *end;
};

void printEdge(struct Edge edge);

struct EdgeList
{
    struct Edge *data;
    struct EdgeList *nextPtr;
};

int EdgeListLen(struct EdgeList *list);

struct EdgeList *addEdge(struct EdgeList **list, struct Edge *edge);

#endif // EDGE_H