#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primmst.h"
#include "minprio.h"
#include "graph.h"
#include "graphio.h"

struct thing{
	int from;
	int to;
	float weight;
};
typedef struct thing* Thing;


//Returns 1 if cyclic, 0 otherwise
int cyclic(Graph g)
{
	if(1)
		return 0;
	else 
		return 1;
}



void insertionsort(Thing* arr, int l, int r)
{
	int i=1;
	while (i<r)
	{
		int tPlaceHold;
		int fPlaceHold;
		float wPlaceHold;
		for(int j=i; j>0; j--)
		{
			if(arr[j]->weight < arr[j-1]->weight)
			{
				wPlaceHold = arr[j]->weight;
				tPlaceHold = arr[j]->to;
				fPlaceHold = arr[j]->from;

				arr[j]->weight = arr[j-1]->weight;
				arr[j]->to = arr[j-1]->to;
				arr[j]->from = arr[j-1]->from;

				arr[j-1]->weight = wPlaceHold;
				arr[j-1]->to = tPlaceHold;
				arr[j-1]->from = fPlaceHold;
			}
		}
		i++;
	}
}

Graph minSpanTree(Graph g)
{
	Graph minTree;
	int numV = numVerts(g);
	Thing* tracking = (Thing*) malloc(sizeof(Thing) *numV*numV);
	int num = 0;
	for(int i=0; edge(g,i,i) !=-1; i++)
	{
		for(int j=0; edge(g,i,j) !=-1; j++)
		{
			
			if(edge(g,i,j) != INFINITY)
			{
				tracking[num]->from = i;
				tracking[num]->to = j;
				tracking[num]->weight = edge(g,i,j);
				num++;
			}
			
		}
	}

	Thing* list = (Thing*) malloc(sizeof(Thing)*num);
	for(int i = 0; i<num; i++)
	{
		list[i]->from=tracking[i]->from;
		list[i]->to=tracking[i]->to;
		list[i]->weight=tracking[i]->weight;
	}
	insertionsort(list, 0, num);
	minTree = makeGraph(num, MATRIX);
	for(int i=0; i<num; i++)
	{
		addEdge(minTree, list[i]->from, list[i]->to, list[i]->weight);
		if(cyclic(minTree))
			delEdge(minTree, list[i]->from, list[i]->to);
	}

	return minTree;

}

