#include <stdlib.h>
#include "graph.h"
#include "graphio.h"
#include "tclose.h"

/* Construct a new graph that is the transitive closure of g.
 * Do not modify g.
 * Assume g is non-null pointer to non-empty graph.
 * Ignore the weights of g.  The weights of the new graph
 * should all be 0. There is an edge u->v in the new graph
 * if and only if there is a path from u to v in g.
 * 
 * Implement this using Warshall's algorithm and matrix 
 * representation for the result graph.
 * Note that Levitin's presentation is described in terms of a matrix of
 * 1s and 0s where 0 means there is no edge.  In our graph.h API,
 * the edge() function returns INFINITY to indicate no edge, and otherwise
 * the weight of an existing edge, which can be 0.0. 
 */
Graph transClose(Graph g)
{
	int verts = numVerts(g);
	int arr[verts][verts];

	for(int a=0; a<verts; a++)
		for(int b=0; b<verts; b++)
			arr[a][b] = (edge(g, a,b)!=-1)? 0:INFINITY;

	int i, j, k;
	for(k=0; k<verts; k++)
	{
		for(i=0; i<verts; i++)
		{
			for(j=0; j<verts; j++)
			{
				if(!arr[i][j] || !arr[i][k] && !arr[k][j])
					arr[i][j] = 0;
				else
					arr[i][j] = INFINITY;
			}
		}
	}

	Graph R = makeGraph(verts, MATRIX);
	for(int x = 0; x<verts; x++)
		for(int y = 0; y<verts; y++)
			addEdge(R, x, y, arr[x][y]);
	return R;


}

