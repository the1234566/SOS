#include "treeStructure.h"
#ifndef buildTree_H
#define buildTree_H
extern int increase;
extern int decrease;
extern int maxinc, maxdec;


Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );
void growtree( Node *node);
void destroytree( Node *node );
void removeChildren( Node *node);
double value( double x, double y, double time );
int setflag(Node *node);
int add(Node *node);
int cut(Node *node);
void printflag(Node *node);
void adapt(Node *node);
#endif
