#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct Vertex
{
    int name;
    struct Vector location;
};

double getX(struct Vertex vertex);

double getY(struct Vertex vertex);

void printVertex(struct Vertex vertex);

struct VertexList
{
    struct Vertex *data;
    struct VertexList *nextPtr;
};

int VertexListLen(struct VertexList *list);

struct VertexList *addVertex(struct VertexList **list, struct Vertex *vertex);

#endif // NODE_H