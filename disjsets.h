#ifndef disjsets_H
#define disjsets_H

/* Disjoint subsets sets, a.k.a. union-find structure.
 * 
 * Represents a partition of the numbers 0,1,...size-1 
 * where size is a fixed number > 0.  
 * 
 */


/* the type */
struct disjsets; /* to be defined by the implementation */
typedef struct disjsets* DisjSets;


/* Make a DisjSets with each element a singleton set.
 */
DisjSets makeDisjSets(int size);


/* Find the representative element of the subset containing n. 
 * Requires djs!=null and 0 <= n < size */
int find(DisjSets djs, int n);


/* Replace two subsets, designated by their representatives n and m,
 * by a single combined subset.
 * Requires djs!=null and 0 <= n, m < size and n!=m
 * Requires that n and m are representatives.
 * 
 * We can't call this 'union' since that's a keyword in C. 
 */
void make_union(DisjSets djs, int n, int m);


/* Current number of subsets */
int numSets(DisjSets djs);

#endif
