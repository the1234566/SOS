#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "treeStructure.h"
#include "buildTree.h"
#include "writeTree.h"

// main
int main( int argc, char **argv ) 
{

  	Node *head;

  // make the head node
  	head = makeNode( 0.0,0.0, 0 );

  // make a tree
	 /* 
     growtree(head);
     growtree(head);
     writeTree( head ); 
	 destroytree( head );//level 2 full---task 1-1 */  
    
    /* 
     growtree(head);
     makeChildren(head->child[1]);
     writeTree( head );
     destroytree(head);
     // print the tree for Gnuplot task1-2*/ 
    
    /*
     growtree(head);
     growtree(head);
     removeChildren(head->child[1]);// task2-1
     writeTree( head );
     destroytree(head);
	*/
    
    /*
     growtree(head);
     makeChildren( head->child[1]);
     makeChildren( head->child[2]);
     removeChildren(head->child[1]);
     writeTree( head );
     destroytree(head);//task2-2
	*/
     
    /* 
    growtree(head);
    growtree(head);
    growtree(head);
	add(head);
	cut(head);
  	printf("\nadded %i nodes\n",increase);
  	printf("\nremoved %i nodes\n",decrease);
    writeTree( head );//task3-1
     */ 
     
    /*
    growtree(head);
    growtree(head);
    growtree(head);
    adapt(head);
    writeTree(head);  //task3-2*/
    

  	return 0;
}



