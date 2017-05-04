#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "graphio.h"
#include "minprio.h"
#include "dijkstra.h"

/* Print the lengths and predecessor in a shortest path from s,
 * for each vertex that is reachable from s.  (For vertices that  
 * are not reachable from s, print nothing.)  Also print the 
 * name of the predecessor in a shortest path.
 *
 * Assume GI is non-null and valid.
 * Assume the source number, s, is in the graph GI->graph.
 * 
 * Use Dijkstra's algorithm and an implementation of minprio.h.
 * Use a format like this to show length and predecessor:
 * 
 * Shortest paths from vertex A 
 *   to B is 9.000000 via E
 *   to C is 10.000000 via B
 *   to D is 6.000000 via A
 *   to E is 7.000000 via A
 *   to F is 15.000000 via C
 */

struct thing{
	int vertex;
	float distance;
};
typedef struct thing* Thing;

int comp(void* lhs, void* rhs)
{
	Thing l = (Thing)lhs;
	Thing r = (Thing)rhs;
	if(l->distance < r->distance)
		return -1;
	else if(l->distance > r->distance)
		return 1;
	else 
		return 0;
}

void shortestPaths(GraphInfo GI, int s)
{
	Graph g = GI->graph;
	//printf("verts\n");
	Thing *verts = (Thing*) malloc(sizeof(Thing) * numVerts(g));
	for(int i=0; i<numVerts(g); i++)
		verts[i] = (Thing) malloc(sizeof(Thing));
	//printf("Comparator\n");
	MinPrio q = makeQueue(comp, numVerts(g));
	//printf("prio works\n");
	Handle hand[numVerts(g)];
	float d[numVerts(g)];
	d[s] = 0.0; 
	verts[s]->vertex = s;
	verts[s]->distance = 0.0;
	hand[s] = enqueue(q,verts[s]);
	int pred[numVerts(g)];
	for(int i=0; i<numVerts(g); i++)
	{
		//printf("works\n");
		//void* x = &i;
		pred[i] = -1;
		if(i != s)
		{
			verts[i]->vertex = i;
			verts[i]->distance = INFINITY;
			d[i] = INFINITY;
			hand[i] = enqueue(q, verts[i]);
		}
	}

	printf("Shortest paths from vertex %s:\n" , GI->vertnames[s]);
	while(nonempty(q))
	{
		int v = ((Thing)dequeueMin(q))->vertex;
		//d[v]=edge(g,s,v); //what does this do
		int* succ = successors(g, v);

		for(int i = 0; succ[i] != -1; i++)
		{
			if(d[v] + edge(g, v, succ[i]) < d[succ[i]]) //is this right
			{
				//if(pred[i] != -1) 				
				d[succ[i]] = d[v] + edge(g,v,succ[i]);
				verts[succ[i]]->distance=d[v] + edge(g,v,succ[i]);
				decreasedKey(q, hand[succ[i]]);
				pred[succ[i]] = v;
			}

		}
	}

	for(int i=0; i<numVerts(g); i++)
		{
			if( i!=s && pred[i]!=-1)
			{	
				printf("to %s is %f via %s\n", GI->vertnames[i], d[i], GI->vertnames[pred[i]]);
			}
		}
}
