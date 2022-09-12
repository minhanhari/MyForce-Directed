#include <stdio.h>
#include <stdlib.h>

#include "edge.h"

void printEdge(struct Edge edge)
{
    printf("From: ");
    printVertex(*edge.start);
    printf("To: ");
    printVertex(*edge.end);
}

int EdgeListLen(struct EdgeList *list)
{
    int out = 0;
    while (list != NULL)
    {
        out++;
        list = list->nextPtr;
    }
    return out;
}

struct EdgeList *addEdge(struct EdgeList **list, struct Edge *edge)
{
    // create the edge to add
    struct EdgeList *toAdd = (struct EdgeList *)malloc(sizeof(struct EdgeList));
    toAdd->data = edge;
    toAdd->nextPtr = NULL;

    if (*list == NULL)
    {
        *list = toAdd;
    }
    else
    {
        struct EdgeList *lastEdge = *list;

        while (lastEdge->nextPtr != NULL)
        {
            struct Vertex *st_v = lastEdge->data->start;
            struct Vertex *en_v = lastEdge->data->end;
            if (st_v->name == edge->start->name && en_v->name == edge->end->name)
            {
                printf("Edge %i - %i already exist in graph.", edge->start->name, edge->end->name);
                return lastEdge;
            }
            else if (st_v->name == edge->end->name && en_v->name == edge->start->name)
            {
                printf("Edge %i - %i already exist in graph.\n", edge->start->name, edge->end->name);
                return lastEdge;
            }
            else
                lastEdge = lastEdge->nextPtr;
        }
        struct Vertex *st_v = lastEdge->data->start;
        struct Vertex *en_v = lastEdge->data->end;
        if (st_v->name == edge->start->name && en_v->name == edge->end->name)
        {
            printf("Edge %i - %i already exist in graph.", edge->start->name, edge->end->name);
            return lastEdge;
        }
        else if (st_v->name == edge->end->name && en_v->name == edge->start->name)
        {
            printf("Edge %i - %i already exist in graph.\n", edge->start->name, edge->end->name);
            return lastEdge;
        }
        else
            lastEdge->nextPtr = toAdd;
    }

    printf("Edge %i - %i added to graph.\n", edge->start->name, edge->end->name);
    return toAdd;
}