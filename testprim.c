#include <stdio.h>
#include "primmst.h"
#include "minprio.h"
#include "graph.h"
#include "graphio.h"

int comp(void* lhs , void* rhs)
{
	if(lhs>rhs)
		return 1;
	else if(rhs>lhs)
		return -1;
	else
		return 0;
}

int main()
{
	MinPrio m = makeQueue(comp, 10);
	Handle t[11];
	for(int b=10; b>0; b--)
	{
		int* a = (int*)malloc(sizeof(int));
		a[0] = b;
		t[b] = enqueue(m,a);
	}
	for(int i=0; i<10; i++)
		printf("%i\n", *(int*)dequeueMin(m));


}