#ifndef H_BTREE
#define H_BTREE
#include "node.h"

typedef enum {left_side, right_side } SIDE;

SIDE rnd(){ 
    return rand()%2 ? right_side : left_side;
}// End of rnd()

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

//constructor that sets the root of tree to nullptr
template <class T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr; 
}

//public function that calls private function of getSize()
template <class T>
unsigned BinaryTree<T>::getSize() const
{
    return _getSize(root); 
}

//public function that calls private function of getHeight()
template <class T>
unsigned BinaryTree<T>::getHeight() const
{
    return _getHeight(root); 
}

//public function that calls private function of Insert()
template <class T>
void BinaryTree<T>::Insert(const T& temp)
{
    _Insert(root,temp);
}

//public function that calls private function of Inorder
template <class T>
void BinaryTree<T>::Inorder(void (*print)(const T&))
{
    _Inorder(root,print);
}

//private function that gets called by getSize()
template <class T>
unsigned BinaryTree<T>::_getSize(Node<T> *node) const  
{
    if(node == nullptr)
    {
        return 0; //the root node will be 0 always
    }
    else
    {
       return 1 + _getSize(node->left) + _getSize(node->right); //both sides of the tree are added together to count size recursively
    }
}

//private function that gets called by getHeight()
template <class T>
unsigned BinaryTree<T>::_getHeight(Node<T> *root) const 
{
    if(root == nullptr)
    {
        return 0; //the root node will be 0 always
    }
    else
    {
        //recursive methods to get the heights of each side are store into variables
        int heightLeft = _getHeight(root->left); 
        int heightRight = _getHeight(root->right);

        //anytime a height increases in each side the counter increases
        if(heightLeft > heightRight)
        {
            return (1+heightLeft);
        }
        else
        {
            return (1+heightRight);
        }
    } 
}

//private function that gets called by Insert()
template <class T>
void BinaryTree<T>::_Insert(Node<T> *& node, const T& temp) 
{
    //if there is no node a new one is created
    if(node == nullptr)
    {
        Node<T> *newNode;
        newNode = new Node<T>(temp);
        node = newNode;
    }

    //deciding where to insert the node
    else
    {
        //using "rnd()" we can randomly select what side to insert
        SIDE s = rnd();
        if(s==left_side)
        {
            _Insert(node->left,temp);
        }
        else
        {
            _Insert(node->right,temp);
        }
    }
}

//private function that gets called by Inorder()
template <class T>
void BinaryTree<T>:: _Inorder(Node<T> *node, void (*print)(const T&)) 
{
    //recursively print out elements Inorder method
    if(node != nullptr)
    {
        _Inorder(node->left,print);
        print(node->data);
        _Inorder(node->right,print);
    }
}


#endif // End of H_BTREE
