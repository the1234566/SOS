
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// tree data structure

struct qnode {
  int level;
  double xy[2];
  struct qnode *child[4];
};
typedef struct qnode Node;

// function definitions

Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );
void growtree( Node *node);
void destroytree( Node *node );
void removechildren( Node *node);
// main

int main( int argc, char **argv ) {

  Node *head;

  // make the head node
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  destroytree(head);
  /*makeChildren( head->child[3] );
  makeChildren( head->child[1] );
  makeChildren( head->child[2] );*/
  // print the tree for Gnuplot
	writeTree( head );

  return 0;
}

// make a node at given location (x,y) and level

Node *makeNode( double x, double y, int level ) {

  int i;

  Node *node = (Node *)malloc(sizeof(Node));

  node->level = level;

  node->xy[0] = x;
  node->xy[1] = y;

  for( i=0;i<4;++i )
    node->child[i] = NULL;

  return node;
}

// split a leaf nodes into 4 children

void makeChildren( Node *parent ) {

  double x = parent->xy[0];
  double y = parent->xy[1];

  int level = parent->level;

  double hChild = pow(2.0,-(level+1));

  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );

  return;
}

// write out the tree to file 'quad.out'

void writeTree( Node *head ) {

  FILE *fp = fopen("quad.out","w");

  writeNode(fp,head);

  fclose(fp);

  return;
}

// recursively visit the leaf nodes

void writeNode( FILE *fp, Node *node ) {

  int i;

  if( node->child[0] == NULL )
    printOut( fp, node );
  else {
    for ( i=0; i<4; ++i ) {
      writeNode( fp, node->child[i] );
    }
  }
  return;
}

// write out the (x,y) corners of the node

void printOut( FILE *fp, Node *node ) {
  double x = node->xy[0];
  double y = node->xy[1];
  int level = node->level;
  double h = pow(2.0,-level);

  fprintf(fp, " %g %g\n",x,y);
  fprintf(fp, " %g %g\n",x+h,y);
  fprintf(fp, " %g %g\n",x+h,y+h);
  fprintf(fp, " %g %g\n",x,y+h);
  fprintf(fp, " %g %g\n\n",x,y);

  return;
}

void growtree( Node *node ) 
{

  int i;

  if( node->child[0] == NULL )
    makeChildren(node );
  else 
  {
    for ( i=0; i<4; ++i ) 
	{
      growtree( node->child[i] );
    }
  }
  return;
}

void destroytree( Node *node )
{
	int i;
	if( node != NULL  )
	{
		for( i=0;i<4;++i )
		{
			destroytree( node->child[i] );
		}
	free(node);
	node = NULL;
	
	}

}

void removeChildren(Node *node)
{
	int i;
	for (i=0; i<4; ++i)
	{
		if( node->child[i] != NULL )
		{			
    		removeChildren(node->child[i]);
    		free(node->child[i]);
    		node->child[i] = NULL;
		}
   }
} 

double nodeValue( Node *node, double time ) 
{
  	int level = node->level;
  	double x = node->xy[0];
  	double y = node->xy[1];

  	double h = pow(2.0,-level);

  	return( value( x+0.5*h, y+0.5*h, time ) );
}

// Data function

double value( double x, double y, double time ) 
{
  	return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}

int setflag( Node *node ) 
{
  	int flag;
  	if (nodeValue(node, 0.0)>0.5) flag = 1;
  	else if (nodeValue(node, 0.0)<-0.5) flag = -1;
  	else flag = 0;
  	return flag;
}

int add( Node *node )
{
	int i;
	if (node->level < 6)
	{
		for (i=0; i<4; ++i)
		{
			if (node->child[i] != NULL) add(node->child[i]);
		}
		if(node->child[0] == NULL && setflag(node) == 1) 
		{
			makeChildren(node);
			increase += 4;
		}
	}
	return increase;
}

int cut(Node *node)
{
	int i;
	if (node->child[0] != NULL)
	{
		for (i=0; i<4; ++i) cut(node->child[i]);			
		if ( setflag(node->child[0]) == -1 && setflag(node->child[0]) == -1 
			&& setflag(node->child[0]) == -1 && setflag(node->child[0]) == -1)
		{
			 removeChildren(node);
			 decrease += 4;
		}
	}
	return decrease;
}


void adapt(Node *node)
{
	while(add(node) > maxinc) maxinc += 4;
	while(cut(node) > maxdec) maxdec += 4;
}