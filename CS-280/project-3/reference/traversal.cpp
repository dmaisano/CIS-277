#include <iostream>
#include <map>
#include "parse.h"
#include "parsetree.h"
using namespace std;
map<string,int> result;

ParseTree *postTraversalRec(ParseTree *tree, int toprint {
 	ParseTree *returnTree;

 	if(tree->GetLeftChild() != nullptr && tree->GetRightChild() != nullptr) {
    if(toprint == 1){ cout<<"N";}
    return 0;
  }
 	else if(tree->GetLeftChild() != 0) {
    //tree.left.left, tree.right.right
    ParseTree *left_child = tree->GetLeftChild();
    ParseTree *lc_left = left_child->GetLeftChild();
    ParseTree *lc_right = left_child->GetRightChild();
    
    returnTree = new StmtList(lc_left, lc_right);
    if(toprint == 1){cout<<"l";}
    postTraversalRec(returnTree, toprint);
    if(toprint == 1){cout<<"L";}
  }
 	else if(tree->GetRightChild() != 0){
     	//tree.right.left, tree.right.right
     	ParseTree *right_child = tree->GetRightChild();
     	ParseTree *rc_left = right_child->GetLeftChild();
     	ParseTree *rc_right = right_child->GetRightChild();
     
     	returnTree = new StmtList(rc_left, rc_right);
     	if(toprint == 1){cout<<"r";}
     	postTraversalRec(returnTree, toprint);
     	if(toprint == 1){cout<<"R";}
    }
 	result["leaf_count"]++;
 	if(toprint == 1){cout<<"N";}
 	return 0;
}

map<string,int> postTraversal(ParseTree *tree, int toprint){
 	result["leaf_count"] = 0;
 	result["ident_count"] = 0;
 
 	postTraversalRec(tree, toprint);
 	if(toprint == 1){ cout<<endl; }
 	return result;
}
