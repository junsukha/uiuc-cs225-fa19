/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
//#include "avltree.h"
 //helper fucntion
template <class K, class V>
int AVLTree<K, V>::computeHeight(Node*& subRoot){
  return (1 + std::max(heightOrNeg1(subRoot->left), heightOrNeg1(subRoot->right)));
}
// int AVLTree<K, V>::getHeight(Node* subRoot){
//   if (subRoot == nullptr)
//     return -1;
//   else
//     return subRoot->height;
// }
//helper fucntion
template <class K, class V>
int AVLTree<K, V>::balanceFactor(Node*& root) {
  if(root == nullptr)
    return 0;
  else
    return (heightOrNeg1(root->left) - heightOrNeg1(root->right));
 // if(root == nullptr)
 //    return 0;
 // return root->left->height
 //return computeHeight(root->left) - computeHeight(root->right);
}
//helper function
template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findIOP(Node* root){
  while(root->right != nullptr){
    root = root->right;
  }
  return root;
}


template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;

    //t = temp;
    //update height
    t->height = computeHeight(t);
    t = temp;// the parameter is Node*&  !!!
    t->height = computeHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;

    //t = temp;
    //update height
    t->height = computeHeight(t);
    t = temp;
    t->height = computeHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

/*
You must implement rebalance() function. rebalance() should, given a subtree,
rotate the subtree so that it is balanced.
You should assume that the subtree’s left and right children are both already balanced trees.
The node’s height should always be updated, even if no rotations are required.*/

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  //LR or R rotation
  if(balanceFactor(subtree) > 1){
    //LR rotation
    if(balanceFactor(subtree->left) == -1){
      rotateLeftRight(subtree);
    }//LR
    //R rotation
    else if(balanceFactor(subtree->left) == 1){
      rotateRight(subtree);
    }//R
  }

  //RL or L rotation
  else if(balanceFactor(subtree) < -1){
    //RL
    if(balanceFactor(subtree->right) == 1){
      rotateRightLeft(subtree);
    }
    //L
    else if(balanceFactor(subtree->right) == -1){
      rotateLeft(subtree);
    }
  }
  //update height after rebalancing
  subtree->height = computeHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == nullptr){
      subtree = new Node(key, value);
      //subtree->height = 0; //exist
      //return;
    }
    if (!subtree) subtree = new Node(key, value);
    else if (key < subtree->key)
      insert(subtree->left, key, value);
    else if (key > subtree->key)
      insert(subtree->right, key, value);


    //(subtree->key > key) ? insert(subtree->left, key, value) : insert(subtree->right, key, value);
    rebalance(subtree);
    //return;
}


template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {//locate the key
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
            //return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //Node*& IOP = findIOP(subtree->left);
            //Node* temp = IOP;
            Node* IOP = subtree->left;
            while(IOP->right != nullptr){//while(iop != nullptr) is wrong!!
                IOP = IOP->right;
            }

            swap(subtree, IOP);
            remove(subtree->left, key);
            //IOP = IOP->left;//no matter there's a node at IOP->left, it works.
            //delete(IOP);

            //delete temp;
            //IOP = nullptr;
        } else {
            /* one-child remove */
            // your code here
            Node* temp = subtree;

            if(subtree->left != nullptr)
              subtree = subtree->left;
            else if(subtree->right != nullptr)
              subtree = subtree->right;
            delete temp;//avoid leak
        }
        // your code here

    }
    if(subtree != nullptr)
      rebalance(subtree);
}
