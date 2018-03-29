#include <iostream>

class BST {
private:

  struct node {
    int key;
    node* left;
    node* right;
  };
  node* root;

  node* insertNode(int key) {
    node* n = new node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;

    return n;
  }


  node* CreateLeaf(int key) {
    node* n = new node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    
    return n;
  }


  void AddLeafPvt(int key, node* n) {
    if(root == NULL)
      root = CreateLeaf(key);
    
    else if(key < n->key) {
      if(n->left != NULL)
        AddLeafPvt(key, n->left);
      else
        n->left = CreateLeaf(key);
    }

    else if(key > n->key) {
      if(n->right != NULL)
        AddLeafPvt(key, n->right);
      else
        n->right = CreateLeaf(key);
    }

    else
      std::cout << "Key '" << key << "' is already added to the tree";
  }


  void PrintInOrderPvt(node* n) {

  }


public:

  BST() {
    
  }


  void AddLeaf(int key) {
    AddLeafPvt(key, root);
  }


  void PrintInOrder() {
    PrintInOrderPvt(root);
  }
  
};
