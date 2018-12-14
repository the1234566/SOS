#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "buildTree.h"

int increase = 0;
int decrease = 0;
int maxinc = 0;
int maxdec = 0;

// make a node at given location (x,y) and level

Node *makeNode( double x, double y, int level ) 
{

  	int i;

  	Node *node = (Node *)malloc(sizeof(Node));

  	node->level = level;

  	node->xy[0] = x;
  	node->xy[1] = y;

  	for( i=0;i<4;++i )
    	node->child[i] = NULL;

  	return node;
}

// split a leaf nodes into 4 Children

void makeChildren( Node *parent ) 
{

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
	if( node!= NULL  )
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

void setflag( Node *node ) 
{
  	int i;
  	if (node->child[0] == NULL && nodeValue(node, 0.0)>0.5) node->flag = 1;
  	else if (node->child[0] == NULL && nodeValue(node, 0.0)<-0.5) node->flag = -1;
  	else node->flag = 0;
}

int add( Node *node )
{
	int i;
	setflag(node);
	if (node->level < 6)
	{
		for (i=0; i<4; ++i)
		{
			if (node->child[i] != NULL) add(node->child[i]);
		}
		if(node->child[0] == NULL && node->flag == 1) 
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
	setflag(node);
	if (node->child[0] != NULL)
	{
		for (i=0; i<4; ++i) cut(node->child[i]);			
		if ( node->child[0]->flag == -1 && node->child[1]->flag == -1 
			&& node->child[2]->flag == -1 && node->child[3]->flag == -1)
		{
			 removeChildren(node);
			 decrease += 4;
		}
	}
	return decrease;
}


void adapt(Node *node)
{ 	do
	{
	increase = 0;
	decrease = 0;
	printf("\n+%i nodes",add(node));
	printf("\n-%i nodes\n",cut(node));
	}while(increase != 0 || decrease != 0 )	; 
}
