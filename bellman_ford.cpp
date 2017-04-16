#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>

using namespace std;

struct Edge
{
	int source;
	int destination;
	int weight;
};

struct Graph
{
	int V, E;
	Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge;

	return graph;
}

void printGraph(int dist[], int n)
{
	cout<<"Vertex   Distance from source"<<endl;
	for(int i = 0;i<n;i++)
	{
		cout<<i<<"   "<<dist[i]<<endl;
	}
}

void BellmanFord(Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	int dist[V],i,j;

	// Initialize
	for(i = 0;i < V;i++)
	{
		dist[i] = INT_MAX;
	}
	dist[src] = 0;

	// Shortest path for all vertices
	for(i = 1;i < V;i++)
	{
		for(j = 0;j < E;j++)
		{
			int u = graph->edge[j].source;
			int v = graph->edge[j].destination;
			int weight = graph->edge[j].weight;
			if(dist[u]!=INT_MAX && dist[u]+weight<dist[v])
				dist[v] = dist[u]+weight;
		}
	}

	// Checking for negative cycle
	for(i = 0;i<E;i++)
	{
		int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            cout<<"Graph contains negative weight cycle"<<endl;
	}

	printGraph(dist, V);

	return;
}

int main()
{
	// Create Graph
	int V = 5;  // Number of vertices in graph
    int E = 10;  // Number of edges in graph
    struct Graph* graph = createGraph(V, E);
 
    graph->edge[0].source = 0;
    graph->edge[0].destination = 1;
    graph->edge[0].weight = 6;
 
    graph->edge[1].source = 0;
    graph->edge[1].destination = 2;
    graph->edge[1].weight = 7;

    graph->edge[2].source = 4;
    graph->edge[2].destination = 0;
    graph->edge[2].weight = 2;

    graph->edge[3].source = 1;
    graph->edge[3].destination = 3;
    graph->edge[3].weight = 5;

    graph->edge[4].source = 3;
    graph->edge[4].destination = 1;
    graph->edge[4].weight = -2;

    graph->edge[5].source = 1;
    graph->edge[5].destination = 2;
    graph->edge[5].weight = 8;

    graph->edge[6].source = 1;
    graph->edge[6].destination = 4;
    graph->edge[6].weight = -4;

    graph->edge[7].source = 2;
    graph->edge[7].destination = 3;
    graph->edge[7].weight = -3;

    graph->edge[8].source = 2;
    graph->edge[8].destination = 4;
    graph->edge[8].weight = 9;

    graph->edge[9].source = 4;
    graph->edge[9].destination = 3;
    graph->edge[9].weight = 7;
 
    
    BellmanFord(graph, 0);
 
    return 0;
}



