#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "btree.h"
template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};

//function to check if nodes are leaf nodes
template <typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> *node) const
{
    //if there are no more nodes to the left and right of the node it is a leaf
    if(node->left == nullptr && node->right == nullptr)
    {
        return true;
    }
    else
        return false;
}

//public function that calls private version
template <typename T>
void BinarySearchTree<T>::Insert(const T &x)
{
    _Insert(this->root, x);
}

//public function that calls private version
template <typename T>
bool BinarySearchTree<T>::Search(const T &x) const
{
    return _Search(this->root,x);
}

//public function that searches for leaf nodes and removes them
template <typename T>
bool BinarySearchTree<T>::Remove(const T &x)
{
    //Search() looks for leaf nodes
    if(Search(x))
    {
        _Remove(this->root,x);
        return true;
    }    
    else
        return false;
}

//function to insert nodes into tree
template <typename T>
void BinarySearchTree<T>::_Insert(Node<T> *&node, const T &data)
{
    //base case
    if(node == nullptr) 
    {
        node = new Node<T>(data);
    }
    //deciding which side to insert node depending on the size of inserted node and current node
    else
    {
        if (node->data > data)
        {
            _Insert(node->left,data);
        }
        else if(node->data < data)
        {
            _Insert(node->right, data);
        }
    }
}

//function to search for leaf nodes
template <typename T>
bool BinarySearchTree<T>::_Search(Node<T> *node, const T &data) const
{
    //base case
    if(node == nullptr)
    {
        return false;
    }
    else
    {
        //if node is a leaf and found itself
        if( _Leaf(node) && node->data == data)
        {
            return true;
        }
        //if value is less than current node, go left
        else if(data < node->data)
        {
            return _Search(node->left, data);
        }
        //if value is more than current node go right
        else
        {
            return _Search(node->right,data);
        }
    }
}

//removing the leaf nodes
template <typename T>
void BinarySearchTree<T>::_Remove(Node<T> *&node, const T &data)
{
    //if the node was found, delete said node
    if(node->data == data)
    {
        delete node;
        node = nullptr;   
    }
    else
    {
        //if node is less that current delete left node
        if (data < node->data)
        {
            _Remove(node->left,data);
        }
        //if node is more than current delete right node
        else
        {
            _Remove(node->right,data);
        }
    }
}

#endif // End of BINARYSEARCHTREE_H_
