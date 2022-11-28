#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertex.h"

double getX(struct Vertex vertex)
{
    return vertex.location.x;
}

double getY(struct Vertex vertex)
{
    return vertex.location.y;
}

void printVertex(struct Vertex vertex)
{
    printf("%s : %lf , %lf\n", vertex.name, getX(vertex), getY(vertex));
}

int VertexListLen(struct VertexList *list)
{
    int out = 0;
    while (list != NULL)
    {
        out++;
        list = list->nextPtr;
    }
    return out;
}

struct VertexList *addVertex(struct VertexList **list, struct Vertex *vertex)
{
    // create the vertex to add
    struct VertexList *toAdd = (struct VertexList *)malloc(sizeof(struct VertexList));
    toAdd->data = vertex;
    toAdd->nextPtr = NULL;

    if (*list == NULL)
    {
        *list = toAdd;
    }
    else
    {
        struct VertexList *lastVertex = *list;

        while (lastVertex->nextPtr != NULL)
        {
            if (strcmp(lastVertex->data->name, vertex->name) == 0)
            {
                // printf("Vertex %s already exist in graph.\n", vertex->name);
                return lastVertex;
            }
            else
                lastVertex = lastVertex->nextPtr;
        }
        if (strcmp(lastVertex->data->name, vertex->name) == 0)
        {
            // printf("Vertex %s already exist in graph.\n", vertex->name);
            return lastVertex;
        }
        else
            lastVertex->nextPtr = toAdd;
    }

    printf("Vertex %s added to graph.\n", vertex->name);
    return toAdd;
}