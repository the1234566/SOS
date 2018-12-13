#include <stdio.h>
#include "treeStructure.h"
#ifndef writeTree_H
#define writeTree_H
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );
#endif
