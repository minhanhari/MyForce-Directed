#include <stdio.h>
#include <string.h>
#include "include/graph.h"
#include "include/vertex.h"
#include "include/vector.h"

#include "include/global.h"

const int DEFAULT_MAX_ITERATIONS = 100;
const double DEFAULT_EPSILON = 0.01;

/* Arrange vertexes' positions so they will fit in drawing area */
void ArrangeVertexPosition(struct Graph *graph, double width, double height)
{
    double xMin = getX(*graph->vertexes[0]);
    double yMin = getY(*graph->vertexes[0]);
    double xMax = getX(*graph->vertexes[0]);
    double yMax = getY(*graph->vertexes[0]);

    for (int i = 0; i < graph->vertexes_num; i++)
    {
        struct Vertex v = *graph->vertexes[i];
        if (getX(v) < xMin)
        {
            xMin = getX(v);
        }
        if (getX(v) > xMax)
        {
            xMax = getX(v);
        }
        if (getY(v) < yMin)
        {
            yMin = getY(v);
        }
        if (getY(v) > yMax)
        {
            yMax = getY(v);
        }
    }
    double ratioX = width / (xMax - xMin);
    double ratioY = height / (yMax - yMin);
    double ratio = 0.9 * ((ratioX < ratioY) ? ratioX : ratioY);

    struct Vector center = devide(new_vector(xMax + xMin, yMax + yMin), 2.0);
    struct Vector offset = devide(new_vector(width, height), 2.0);

    for (int i = 0; i < graph->vertexes_num; i++)
    {
        struct Vector curr_loc = graph->vertexes[i]->location;
        graph->vertexes[i]->location = add(multiply(sub(curr_loc, center), ratio), offset);
    }
}

/* Read from file and create a graph */
struct Graph *readGraphFromFile(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Error opening file...\n");
        exit(1);
    }

    char *str = (char *)malloc(50);

    struct VertexList *vert_list = NULL;
    struct EdgeList *edge_list = NULL;

    while (fgets(str, 50, f) != NULL)
    {
        char *x = (char *)malloc(10);
        if (sscanf(str, "%s", x) == 1)
        {
            struct Vertex *a = (struct Vertex *)malloc(sizeof(struct Vertex));
            a->name = x;
            a->location = new_vector(0, 0);
            a = addVertex(&vert_list, a)->data;
            char *y = (char *)malloc(10);
            double w;
            if (sscanf(str, "%s %s %lf", x, y, &w) == 3)
            {
                struct Vertex *b = (struct Vertex *)malloc(sizeof(struct Vertex));
                b->name = y;
                b->location = new_vector(0, 0);
                b = addVertex(&vert_list, b)->data;

                struct Edge *e = (struct Edge *)malloc(sizeof(struct Edge));
                e->start = a;
                e->end = b;
                e->weight = w;
                e = addEdge(&edge_list, e)->data;
            }
        }
    }
    struct Graph *gr = newGraph(vert_list, edge_list);

    fclose(f);

    return gr;
}

int main()
{
    struct Graph *gr = readGraphFromFile("in_graph.txt");
    printf("Vertexes number: %i\n", gr->vertexes_num);

    printf("Edges number: %i\n", gr->edges_num);

    bool random = false;

    initVerticesPosition(gr, random);

    // ForceDirectedLayout(gr, DEFAULT_MAX_ITERATIONS);
    LocalMinimum(gr, DEFAULT_EPSILON);

    ArrangeVertexPosition(gr, CANVAS_WIDTH, CANVAS_HEIGHT);

    FILE *f = fopen("out_graph.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file...\n");
        exit(1);
    }

    for (int i = 0; i < gr->edges_num; i++)
    {
        struct Vertex v_st = *gr->edges[i].start;
        struct Vertex v_en = *gr->edges[i].end;
        fprintf(f, "e %i %i %i %i %f\n", (int)getX(v_st), (int)getY(v_st), (int)getX(v_en), (int)getY(v_en), gr->edges[i].weight);
    }

    for (int i = 0; i < gr->vertexes_num; i++)
    {
        struct Vertex t_vtx = *gr->vertexes[i];
        fprintf(f, "v %s %i %i\n", t_vtx.name, (int)getX(t_vtx), (int)getY(t_vtx));
    }

    fclose(f);

    return 0;
}