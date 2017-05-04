#include <stdio.h>
#include "graph.h"
#include "graphio.h"
#include "kruskal.c"

int main()
{
	GraphInfo gi = readGraph("triangleMST.txt", MATRIX);
	Graph g = gi->graph;
	Graph minG = minSpanTree(g);
	gi->graph = minG;
	writeGraph(gi);
}