/* primmst.c
Christopher Rudel and Tucker Parr
4/18/17
I pledge my Honor that I have abided by the Stevens Honor System
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "graph.h"
#include "primmst.h"
#include "minprio.h" 

/* Assume g is non-null pointer to non-empty graph.
 * Assume g is a symmetric graph, so it can be 
 * considered as an undirected graph.  
 * (In particular, the weight u->v must equal weight v->u
 * for every u,v.)
 * Assume the weights are not INFINITY and g is connected.
 * 
 * Return a minimum spanning tree, as a new graph.
 * (So it will have the same number of vertices, 
 * but only some of the edges.  Weights same as in g.)
 * 
 * Implement this using Prim's algorithm.  The implementation only
 * needs to access the input graph via the graph.h API, so 
 * it shouldn't matter which representation the input uses.
 * Since the tree will be a sparse graph, use LIST representation 
 * for the output graph.
 * 
 */

struct thing{
	int vertex;
	float distance;
};
typedef struct thing* Thing;

 Comparator comp(void* lhs, void* rhs)
{
	if(lhs<rhs)
		return -1;
	else if(lhs>rhs)
		return 1;
	else if(lhs=rhs)
		return 0;
	else
		exit(0);
}
Graph minSpanTree(Graph g)
{
	int V = numVerts(g);
	Graph t = makeGraph(V, MATRIX);
	MinPrio q = makeQueue(comp , V);
	int link[V];
	for(int i=0; i<V; i++)
		link[i] = -1;

	int root = 0;
	enqueue(q, root); //how do you enqueue this
	for(int v = 1; v<V && v!=root; v++)
	{
		Thing i;
		i->vertex = v;
		i->distance = INFINITY;
		enqueue(q, i); //how do you enqueue this
	}

	while(nonempty(q))
	{
		Thing a = dequeueMin(q);
		int* succ = successors(g,0);
		

		for(int u=0; succ[u]!= -1; u++)
		{
			float uv = edge(t, a->vertex, u);
			if(link[u] == -1 && uv < a->distance)
			{
				link[u] = a->vertex;
				u = edge(t, a->vertex, u);
				decreasedKey(q,u);
			}
		}
	}

	for(int v=0; v<V; v++)
	{
		addEdge(t, v, link[v], INFINITY /*not sure if this is right*/);
		addEdge(t, link[v], v, INFINITY);
	}


}


