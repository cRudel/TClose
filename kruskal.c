/*
	kruskal.c
	Christopher Rudel & Tucker Parr
	CS 182
	I pledge my Honor that I have abided by the Stevens Honor System
*/
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

//Returns 1 for true, 0 for false
int cycHelp(Graph g, int* arr, int* visit, int* rec, int x)
{
	if(!visit[x])
	{
	visit[x] = 1;
	rec[x] = 1;
	int i = 0;
	while(arr[i]!=-1)
	{
		if(!visit[i] && cycHelp(g, arr, visit, rec, i))
			return 1;
		else if(rec[i])
			return 1;
		i++;
	}

	rec[x] = 0;
	return 0;

	}
}

//again 1 if cyclic, 0 otherwise
int cyclic(Graph g)
{
	int visited[numVerts(g)];
	int rec[numVerts(g)];
	for(int i=0; i<numVerts(g); i++)
	{
		visited[i] = 0;
		rec[i] = 0;
	}

	for(int i=0; i<numVerts(g); i++)
	{
		int* succ = successors(g, 0);
		if(!visited[i])
			if(cycHelp(g, succ, visited, rec,  i))
				return 1;
	}
	return 0;
}





void insertionsort(Thing arr[], int l, int r)
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
	for(int i = 0; i< numV*numV; i++)
		tracking[i] = (Thing) malloc(sizeof(Thing));
	int num = 0;
	for(int i=0;i< numV; i++)
	{
		for(int j=0; j< numV; j++)
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
		list[i] = (Thing) malloc(sizeof(Thing));
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

