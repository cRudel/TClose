/*
	disjsets.c
	Christopher Rudel & Tucker Parr
	CS 182
	I pledge my Honor that I have abided by the Stevens Honor System
*/
#include <stdlib.h>
#include "disjsets.h"
/* Disjoint subsets sets, a.k.a. union-find structure.
 * 
 * Represents a partition of the numbers 0,1,...size-1 
 * where size is a fixed number > 0.  
 * 
 */

struct node{
	int value;
	struct node* next;
};
typedef struct node* Node;

struct nodelist{
	int length;
	Node last;
	Node first;
};
typedef struct nodelist* NodeList;
/* the type */
struct disjsets{
	NodeList* list;
	int size;
}; /* to be defined by the implementation */



/* Make a DisjSets with each element a singleton set.
 */
DisjSets makeDisjSets(int size)
{
	DisjSets set = (DisjSets) malloc(sizeof(DisjSets));
	set->list = (NodeList*)malloc(sizeof(NodeList) * size);
	set->size = size;
	for (int i = 0; i<size; i++)
	{
		set->list[i] = (NodeList)malloc(sizeof(NodeList));
		NodeList temp = set->list[i];
		temp->length=0;
		temp->last=NULL;
		temp->first=NULL;
		set->list[i]=temp;
	}
	return set;
}


/* Find the representative element of the subset containing n. 
 * Requires djs!=null and 0 <= n < size */
int find(DisjSets djs, int n)
{
	int found = -1;
	for(int i=0; i<djs->size; i++)
	{
		NodeList temp = djs->list[i];
		if(temp->length>0)
		{
			Node tempNode = temp->first;
			for(int j = 0; j<temp->length; j++)
			{
				if(tempNode->value == n)
					found = i;
				tempNode = tempNode->next;
			}
		}
	}
	return found;
}


/* Replace two subsets, designated by their representatives n and m,
 * by a single combined subset.
 * Requires djs!=null and 0 <= n, m < size and n!=m
 * Requires that n and m are representatives.
 * 
 * We can't call this 'union' since that's a keyword in C. 
 */
void make_union(DisjSets djs, int n, int m)
{
	NodeList n1 = djs->list[n];
	NodeList m1 = djs->list[m];
	Node tempNode = n1->last;
	tempNode->next = m1->first;
	n1->last = m1->last;
	n1->length += m1->length;
	djs->list[n] = n1;
	m1->length = 0;
	m1->first =	NULL;
	m1->last = NULL;
}


/* Current number of subsets */
int numSets(DisjSets djs)
{
	int num = 0;
	for(int i=0; i<djs->size; i++)
	{
		NodeList temp = djs->list[i];
		if(temp->length > 0)
			num++;
	}
	return num;
}