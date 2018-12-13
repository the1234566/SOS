#ifndef treeStructure_H
#define treeStructure_H
struct qnode {
    int flag;
    int level;
    double xy[2];
    struct qnode *child[4];
};
typedef struct qnode Node;


#endif 
