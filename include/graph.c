#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "graph.h"

const int LENGTH = 100;

struct Graph *newGraph(struct VertexList *vertexes, struct EdgeList *edges)
{
    int v_num = listLen(vertexes);
    int e_num = listLen(edges);
    struct Vertex **v_list = malloc(sizeof(struct Vertex *) * v_num);
    struct Edge *e_list = malloc(sizeof(struct Edge) * e_num);

    struct VertexList *v = vertexes;
    int i = 0;
    while (v != NULL)
    {
        v_list[i] = v->data;
        v = v->nextPtr;
        i++;
    }

    struct EdgeList *e = edges;
    i = 0;
    while (e != NULL)
    {
        e_list[i] = *e->data;
        e = e->nextPtr;
        i++;
    }

    struct Graph *gr = malloc(sizeof(struct Graph));
    gr->vertexes = v_list;
    gr->edges = e_list;
    gr->vertexes_num = v_num;
    gr->edges_num = e_num;

    return gr;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void initVerticesPosition(struct Graph *graph, bool random)
{
    int v_num = graph->vertexes_num;
    printf("Initializing vertexes' positions...\n");
    if (random)
    {
        for (int i = 0; i < v_num; i++)
        {
            graph->vertexes[i]->location.x = fRand(0, LENGTH);
            graph->vertexes[i]->location.y = fRand(0, LENGTH);
        }
    }
    else
    {
        double angle = 2.0 * M_PI / v_num;
        for (int i = 0; i < v_num; i++)
        {
            graph->vertexes[i]->location.x = cos(angle * i) * LENGTH / 4;
            graph->vertexes[i]->location.y = sin(angle * i) * LENGTH / 4;
        }
    }
    printf("Positions initialized!\n");
}

/* Attraction force */
double Fa(double distance, double k)
{
    return distance * distance / k;
}

/* Repulsion force */
double Fr(double distance, double k)
{
    return k * k / distance;
}

double cool(double t)
{
    double cold_t = 0.0001;
    if (t > cold_t)
    {
        return t * 0.999;
    }
    else
    {
        return cold_t;
    }
}

void ForceDirectedLayout(struct Graph *graph, int max_iteration)
{
    int v_num = graph->vertexes_num;
    double k = sqrt(LENGTH * LENGTH / v_num);
    double t = 20;

    int stop_count = 0;

    // Stop when total movement falls under a certain range
    // for (int i = 0; i < max_iteration; i++)
    while (stop_count < max_iteration)
    {
        struct Vector displacement[v_num];
        // Calculate the repulsive forces on vertexes/electrons
        for (int i = 0; i < v_num; i++)
        {
            displacement[i] = new_vector(0, 0);

            for (int j = 0; j < v_num; j++)
            {
                if (i != j)
                {
                    struct Vector diff = sub(graph->vertexes[i]->location, graph->vertexes[j]->location);
                    // displacement = displacement + (diff / |diff|) * Fr
                    displacement[i] = add(displacement[i], multiply(devide(diff, absolute(diff)), Fr(absolute(diff), k)));
                }
            }
        }

        // Calculate the attractive forces on edges/springs
        for (int i = 0; i < graph->edges_num; i++)
        {
            int start_i = findVIndex(graph->edges[i].start, graph);
            int end_i = findVIndex(graph->edges[i].end, graph);

            struct Vector diff = sub(graph->vertexes[start_i]->location, graph->vertexes[end_i]->location);
            // displacement = displacement +- (diff / |diff|) * Fa
            displacement[start_i] = sub(displacement[start_i], multiply(devide(diff, absolute(diff)), Fa(absolute(diff), k)));
            displacement[end_i] = add(displacement[end_i], multiply(devide(diff, absolute(diff)), Fa(absolute(diff), k)));
        }

        double total_displacement = 0;

        // Limit the max displacement to a temperature t and keep them inside the frame
        // The temperature t allows for large movements at the beginning of the loop
        // and smaller, more refined movements near the end. AKA Simulated Annealing
        for (int i = 0; i < v_num; i++)
        {
            struct Vector disp = displacement[i];
            struct Vector lim_disp = multiply(devide(disp, absolute(disp)), __min(absolute(disp), t));

            graph->vertexes[i]->location = add(graph->vertexes[i]->location, lim_disp);
            total_displacement += absolute(lim_disp);
        }

        // Stop when total movement falls under a certain range
        if (total_displacement < 0.0001 * (v_num))
            stop_count++;

        t = cool(t);
    }
    printf("Graph placed with force-directed layout!\n");
}

int findVIndex(struct Vertex *vertex, struct Graph *graph)
{
    for (int i = 0; i < graph->vertexes_num; i++)
    {
        if (vertex->name == graph->vertexes[i]->name)
        {
            return i;
        }
    }
    printf("Index not found!\n");
    return graph->vertexes_num;
}

int **floyd_warshall(struct Graph gr)
{
    int v_num = gr.vertexes_num;
    int e_num = gr.edges_num;
    int **dist = (int **)malloc(sizeof(int *) * v_num);
    for (int i = 0; i < v_num; i++)
    {
        dist[i] = (int *)malloc(sizeof(int) * v_num);
        for (int j = 0; j < v_num; j++)
        {
            dist[i][j] = 1000000000;
        }
    }
    for (int i = 0; i < e_num; i++)
    {
        int u = findVIndex(gr.edges[i].start, &gr);
        int v = findVIndex(gr.edges[i].end, &gr);
        dist[u][v] = dist[v][u] = 1;
    }
    for (int i = 0; i < v_num; i++)
    {
        dist[i][i] = 0;
    }
    for (int k = 0; k < v_num; k++)
    {
        for (int i = 0; i < v_num; i++)
        {
            for (int j = 0; j < v_num; j++)
            {
                dist[i][j] = __min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

void LocalMinimum(struct Graph *gr, double Lo, double K)
{
    // Two dimensional array of shortest path between two vertexes
    // Calculate using Floyd-Warshall algorithm
    int **d = floyd_warshall(*gr);
    int v_num = gr->vertexes_num;

    int d_max = d[0][0];
    for (int i = 0; i < v_num; i++)
    {
        for (int j = i + 1; j < v_num; j++)
        {
            d_max = __max(d_max, d[i][j]);
        }
    }

    // Initializing l_ij, k_ij
    double **l = (double **)malloc(sizeof(double *) * v_num);
    double **k = (double **)malloc(sizeof(double *) * v_num);
    for (int i = 0; i < v_num; i++)
    {
        l[i] = (double *)malloc(sizeof(double) * v_num);
        k[i] = (double *)malloc(sizeof(double) * v_num);
        for (int j = 0; j < v_num; j++)
        {
            l[i][j] = Lo / d_max * d[i][j];
            k[i][j] = K / pow(d[i][j], 2);
        }
    }

    // Moving the vertex with highest energy decrease
    double *Delta = (double *)malloc(sizeof(double) * v_num);
    int max_i = calcDelta(gr, k, l, Delta);
    double eps = 0.001;
    while (Delta[max_i] > eps)
    {
        while (Delta[max_i] > eps)
        {
            struct Vector dE = new_vector(0, 0);
            double Exx = 0;
            double Exy = 0;
            double Eyy = 0;
            for (int i = 0; i < v_num; i++)
            {
                if (i == max_i)
                    continue;

                struct Vector dmax_i = sub(gr->vertexes[max_i]->location, gr->vertexes[i]->location);
                double n = 1.0 - l[max_i][i] / absolute(dmax_i);
                dE = add(dE, multiply(multiply(dmax_i, n), k[max_i][i]));

                Exy += k[max_i][i] * l[max_i][i] * dmax_i.x * dmax_i.y / pow(absolute(dmax_i), 3);
                Exx += k[max_i][i] * (1.0 - l[max_i][i] * dmax_i.y * dmax_i.y / pow(absolute(dmax_i), 3));
                Eyy += k[max_i][i] * (1.0 - l[max_i][i] * dmax_i.x * dmax_i.x / pow(absolute(dmax_i), 3));
            }

            double D = Exx * Eyy - Exy * Exy;
            struct Vector d;
            d.x = -(Eyy * dE.x - Exy * dE.y) / D;
            d.y = -(-Exy * dE.x + Exx * dE.y) / D;

            gr->vertexes[max_i]->location = add(gr->vertexes[max_i]->location, d);

            Delta[max_i] = absolute(dE);
        }

        max_i = calcDelta(gr, k, l, Delta);
    }
    printf("Graph placed with local minimum layout!\n");
}

int calcDelta(struct Graph gr, double **k, double **l, double *Delta)
{
    double maxDelta = 0;
    int m_i = 0;
    for (int i = 0; i < gr.vertexes_num; i++)
    {
        // dE is vector energy
        struct Vector dE = new_vector(0, 0);
        for (int j = 0; j < gr.vertexes_num; j++)
        {
            if (i == j)
                continue;

            struct Vector d = sub(gr.vertexes[i]->location, gr.vertexes[j]->location);
            double n = 1.0 - l[i][j] / absolute(d);
            dE = add(dE, multiply(multiply(d, n), k[i][j]));
        }
        // Find vertex with highest energy
        Delta[i] = absolute(dE);
        if (Delta[i] > maxDelta)
        {
            maxDelta = Delta[i];
            m_i = i;
        }
    }
    return m_i;
}