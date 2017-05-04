#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "minprio.h"
#include "graph.h"
#include "graphio.h"

int main()
{
	GraphInfo gi = readGraph("sixMST.txt", MATRIX);
	shortestPaths(gi,0);
}