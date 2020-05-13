#ifndef _RBTREE_H_
#define _RBTREE_H_

#include<iostream>
#include<fstream>

using namespace std;

enum Color {
    RED, BLACK
};

template<class T, class K>
class Node {
public:
    Color color;//color
    T key;//key
    K value;//value, lecture ID
    Node *parent;//parent
    Node *left;//left child
    Node *right;//right child
    int s, m, o, p;

    //initialization
    Node(T k, K v, Color c, Node *parent, Node *l, Node *r) :
            key(k), value(v), color(c), parent(parent), left(l), right(r), s(0), m(0), o(k) {}
};

template<class T, class K>
class RBTree {
public:
    RBTree();

    ~RBTree();

    //pre-order visit the RBT
    void preOrder();

    //in-order visit the RBT
    void inOrder();

    //postorder visit the RBT
    void postOrder();

    //search by key
    Node<T, K> *search(T key);

    //find minimum key value
    T minimum();

    //find maximum key value
    T maximum();

    //find the successor, which is the smallest key value that greater than the current key value of the node
    Node<T, K> *successor(Node<T, K> *x);

    //find the predecessor
    Node<T, K> *predecessor(Node<T, K> *x);

    //insert a node (base on key value) into RBT
    void insert(T key, K value, int p);

    //delete a node (base on key value) from RBT
    void remove(T key);

    // find the point of maximum overlap
    Node<T, K> *getRoot();

    //destory the RBT
    void destroy();

    //print the RBT
    void print();

protected:
    Node<T, K> *rbRoot;//root
    Node<T, K> *NIL = new Node<T, K>(-1, 0, BLACK, NULL, NULL, NULL); // NIL NODE
    //pre-order visit the RBT
    void preOrder(Node<T, K> *tree);

    //in-order visit the RBT
    void inOrder(Node<T, K> *tree);

    //postorder visit the RBT
    void postOrder(Node<T, K> *tree);

    //search by key
    Node<T, K> *search(Node<T, K> *x, T key);

    //find minimum key value
    Node<T, K> *minimum(Node<T, K> *tree);

    //find maximum key value
    Node<T, K> *maximum(Node<T, K> *tree);

    // update the extra info s, m, o, p
    Node<T, K> *maintain(Node<T, K> *node);

    // update the extra info s, m, o, p for all nodes
    void maintainAll(Node<T, K> *node);

    //left rotate
    void leftRotate(Node<T, K> *&root, Node<T, K> *x);

    //right rotate
    void rightRotate(Node<T, K> *&root, Node<T, K> *y);

    //insert a node into the RBT
    void insert(Node<T, K> *&root, Node<T, K> *node);

    //fix the violation after insertion
    void insertFixUp(Node<T, K> *&root, Node<T, K> *node);

    //delete a node from the RBT
    void remove(Node<T, K> *&root, Node<T, K> *node);

    //fix the violation after deletion
    void removeFixUp(Node<T, K> *&root, Node<T, K> *node, Node<T, K> *parent);

    // find the point of maximum overlap
    Node<T, K> *getRoot(Node<T, K> *root);

    //destructor function
    void destroy(Node<T, K> *&tree);

    //print out the RBT
    void print(Node<T, K> *tree, T key, int direction);

    int max_3(int a, int b, int c);
};

struct TimeInterval {
    int t1;//start time index
    int t2;//end time index
};

/*
 * constructor
 */
template<class T, class K>
RBTree<T, K>::RBTree():rbRoot(NULL) {
    rbRoot = NIL;
}

/*
 * destructor
 */
template<class T, class K>
RBTree<T, K>::~RBTree() {
    destroy();
}

/*
 * pre-order
 */
template<class T, class K>
void RBTree<T, K>::preOrder(Node<T, K> *tree) {
    if (tree != NIL) {
        cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template<class T, class K>
void RBTree<T, K>::preOrder() {
    preOrder(rbRoot);
}

/*
 * in-order
 */
template<class T, class K>
void RBTree<T, K>::inOrder(Node<T, K> *tree) {
    if (tree != NIL) {
        inOrder(tree->left);
        cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template<class T, class K>
void RBTree<T, K>::inOrder() {
    inOrder(rbRoot);
}

/*
 * post-order
 */
template<class T, class K>
void RBTree<T, K>::postOrder(Node<T, K> *tree) {
    if (tree != NIL) {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->key << " ";
    }
}

template<class T, class K>
void RBTree<T, K>::postOrder() {
    postOrder(rbRoot);
}

/*
 * search the node with key value
 */
template<class T, class K>
Node<T, K> *RBTree<T, K>::search(Node<T, K> *x, T key) {
    if (x == NIL)
        return NULL;
    if (x->key == key)
        return x;
    if (key < x->key) {
        return search(x->left, key);
    } else {
        return search(x->right, key);
    }
}

template<class T, class K>
Node<T, K> *RBTree<T, K>::search(T key) {
    return search(rbRoot, key);
}

/*
 * find minimum key value
 */
template<class T, class K>
Node<T, K> *RBTree<T, K>::minimum(Node<T, K> *tree) {
    if (tree == NIL)
        return NULL;
    while (tree->left != NIL)
        tree = tree->left;
    return tree;
}

template<class T, class K>
T RBTree<T, K>::minimum() {
    Node<T, K> *p = minimum(rbRoot);
    if (p != NIL)
        return p->key;
    return (T) NULL;
}

/*
 * find maximum key value
 */
template<class T, class K>
Node<T, K> *RBTree<T, K>::maximum(Node<T, K> *tree) {
    if (tree == NIL)
        return NULL;
    while (tree->right != NIL)
        tree = tree->right;
    return tree;
}

template<class T, class K>
T RBTree<T, K>::maximum() {
    Node<T, K> *p = maximum(rbRoot);
    if (p != NIL)
        return p->key;
    return (T) NULL;
}

template<class T, class K>
Node<T, K> *RBTree<T, K>::maintain(Node<T, K> *node) {
    node->s = node->left->s + node->p + node->right->s;
    node->m = max_3(node->left->m, node->left->s + node->p, node->left->s + node->p + node->right->m);
    if (node->m == node->left->m) {
        node->o = node->left->o;
    } else if (node->m == node->left->s + node->p) {
        node->o = node->key;
    } else {
        node->o = node->right->o;
    }
    return node->parent;
}

template<class T, class K>
void RBTree<T, K>::maintainAll(Node<T, K> *node) {
    while (node != NIL) {
        node = maintain(node);
    }
}

template<class T, class K>
void RBTree<T, K>::leftRotate(Node<T, K> *&root, Node<T, K> *x) {
    // CLRS Chapter 13 pp.313
    Node<T, K> *y = x->right; // set y
    x->right = y->left; // turn y's left subtree into x's right subtree
    if (y->left != NIL) {
        y->left->parent = x; // link x's parent to y
    }
    y->parent = x->parent;

    if (x->parent == NIL) {
        root = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x; // put x on y's left
    x->parent = y;
    maintain(x);
    maintain(y);
}

template<class T, class K>
void RBTree<T, K>::rightRotate(Node<T, K> *&root, Node<T, K> *y) {
    Node<T, K> *x = y->left;
    y->left = x->right;
    if (x->right != NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;

    if (y->parent == NIL) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
    maintain(y);
    maintain(x);
}

template<class T, class K>
void RBTree<T, K>::insertFixUp(Node<T, K> *&root, Node<T, K> *node) {
    // CLRS Chapter 13 pp.316
    Node<T, K> *y;
    while (node->parent->color == RED) {
        // Node's parent is the left child of its grand parent
        if (node->parent == node->parent->parent->left) {
            y = node->parent->parent->right; //uncle
            // Case 1: Node's uncle is red
            if (y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                continue;
            }
                // Case 2: Uncle is black and node is the right child
            else if (y->color == BLACK) {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(root, node);
                }

                // Case 3: Uncle is black and node is the left child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root, node->parent->parent);
            }
        } else if (node->parent == node->parent->parent->right) {
            // Similar for right child case
            y = node->parent->parent->left; //uncle
            // Case 1
            if (y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                continue;
            }
                // Case 2
            else if (y->color == BLACK) {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(root, node);
                }

                // Case 3
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

/*
 * Insert a node into a RBT
 */
template<class T, class K>
void RBTree<T, K>::insert(Node<T, K> *&root, Node<T, K> *node) {
// CLRS Chapter 13 pp.315
    Node<T, K> *y = NIL;
    Node<T, K> *x = root;
    while (x != NIL) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else if (node->key > x->key)
            x = x->right;
        else {
            if (node->p < 0)
                x->p--;
            else
                x->p++;
            maintainAll(x);
            return;
        }
    }
    node->parent = y;
    if (y == NIL) {
        root = node;
    } else {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    node->left = NIL;
    node->right = NIL;
    node->color = RED;
    insertFixUp(root, node);
    maintainAll(node);
}

/*
 * Insert a key and a value into the tree
 */
template<class T, class K>
void RBTree<T, K>::insert(T key, K value, int p) {
    Node<T, K> *x = NIL;
    if ((x = new Node<T, K>(key, value, RED, NIL, NIL, NIL)) == NULL) {
        cout << "Error: memory could not be allocated" << endl;
        return;
    }
    x->p = p;
    insert(rbRoot, x);
}

/*
 * fix up the violation of RB tree property after deletion
 */
template<class T, class K>
void RBTree<T, K>::removeFixUp(Node<T, K> *&root, Node<T, K> *node, Node<T, K> *parent) {
    Node<T, K> *brother;

    while (((node == NIL) || (node->color == BLACK)) && (node != root)) {
        //if current node is a left child
        if (parent->left == node) {
            brother = parent->right;
            //Case 1: x's brother is red
            if (brother->color == RED) {
                brother->color = BLACK;
                parent->color = RED;
                leftRotate(root, parent);
                brother = parent->right;
            }
            //Case 2: x's brother is black, and none of the children of x's brother are red
            if ((!brother->left || (brother->left->color == BLACK)) &&
                (!brother->right || (brother->right->color == BLACK))) {
                brother->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                //Case 3: x's brother is black, and x's brother's left child is red, x's brother's right child is black
                if ((brother->right == NIL) || (brother->right->color == BLACK)) {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rightRotate(root, brother);
                    brother = parent->right;
                }
                //Case 4: x's brother is black, and x's brother's right child is red
                brother->color = parent->color;
                parent->color = BLACK;
                brother->right->color = BLACK;
                leftRotate(root, parent);
                node = root;
                break;
            }
        } else//current node is a right child
        {
            brother = parent->left;
            //Case 1: x's brother is red
            if (brother->color == RED) {
                brother->color = BLACK;
                parent->color = RED;
                rightRotate(root, parent);
                brother = parent->left;
            }
            //Case 2: x's brother is black, and none of the children of x's brother are red
            if (((brother->left == NIL) || (brother->left->color == BLACK)) &&
                (!brother->right || (brother->right->color == BLACK))) {
                brother->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                //Case 3: x's brother is black, and x's brother's left child is red, x's brother's right child is black
                if ((brother->left == NIL) || (brother->left->color == BLACK)) {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    leftRotate(root, brother);
                    brother = parent->left;
                }
                //Case 4: x's brother is black, and x's brother's right child is red
                brother->color = parent->color;
                parent->color = BLACK;
                brother->left->color = BLACK;
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node != NIL)
        node->color = BLACK;
}

/*
 * delete a node from RBT
 */
template<class T, class K>
void RBTree<T, K>::remove(Node<T, K> *&root, Node<T, K> *node) {
    Node<T, K> *child, *parent;
    Color color;

    //current node has both children
    if ((node->left != NIL) && (node->right != NIL)) {
        //find the successor of the deleting node, then use that node temp to replace the current node
        Node<T, K> *temp = node;
        temp = temp->right;
        while (temp->left != NIL)
            temp = temp->left;

        //check the node is not root
        if (node->parent) {
            if (node->parent->left == node)
                node->parent->left = temp;
            else
                node->parent->right = temp;
        } else
            root = temp;

        parent = temp->parent;
        //let child be the temp's right child, which might need to be adjusted
        child = temp->right;
        //keep the color of the node temp
        color = temp->color;

        //if temp's parent is the deleting node
        if (parent == node)
            parent = temp;
        else {
            if (child != NIL)
                child->parent = parent;
            parent->left = child;
            temp->right = node->right;
            node->right->parent = temp;
        }

        temp->parent = node->parent;
        temp->color = node->color;
        temp->left = node->left;
        node->left->parent = temp;

        if (color == BLACK)
            removeFixUp(root, child, parent);
        delete node;
        return;
    }

    //case where current node has at most one child
    if (node->left != NIL)
        child = node->left;
    else
        child = node->right;
    parent = node->parent;
    color = node->color;
    if (child != NIL)
        child->parent = parent;

    //check the node is not root
    if (parent != NIL) {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    } else
        root = child;

    if (color == BLACK)
        removeFixUp(root, child, parent);
    delete node;
}

/*
 * delete a node based on its key value
 */
template<class T, class K>
void RBTree<T, K>::remove(T key) {
    Node<T, K> *node;
    if ((node = search(rbRoot, key)) != NIL)
        remove(rbRoot, node);
}

template<class T, class K>
Node<T, K> *RBTree<T, K>::getRoot(Node<T, K> *root) {
    return root;
}

template<class T, class K>
Node<T, K> *RBTree<T, K>::getRoot() {
    return getRoot(rbRoot);
}


/*
 * destructor
 */
template<class T, class K>
void RBTree<T, K>::destroy(Node<T, K> *&tree) {
    if (tree == NULL)
        return;
    if (tree->left != NIL)
        destroy(tree->left);
    if (tree->right != NIL)
        destroy(tree->right);
    delete tree;
    tree = NULL;
}

template<class T, class K>
void RBTree<T, K>::destroy() {
    destroy(rbRoot);
}

/*
 * print the RBT where direction 0 means root, -1 stands for left child, 1 stands for the right child
 */
template<class T, class K>
void RBTree<T, K>::print(Node<T, K> *tree, T key, int direction) {
    if (tree != NIL) {
        if (direction == 0)//is root node
            cout << tree->key << "(B) is root. "
                 << "o=" << tree->o << ". s=" << tree->s << ". m=" << tree->m
                 << ". p=" << tree->p << ". value=" << tree->value << endl;
        else//is non-root node
            cout << tree->key << ((tree->color == RED) ? "(R)" : "(B)") << " is " << key << "'s "
                 << (direction == 1 ? "right child. " : "left child. ")
                 << "o=" << tree->o << ". s=" << tree->s << ". m=" << tree->m
                 << ". p=" << tree->p << ". value=" << tree->value << endl;
        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template<class T, class K>
void RBTree<T, K>::print() {
    if (rbRoot != NIL)
        print(rbRoot, rbRoot->key, 0);
}

template<class T, class K>
int RBTree<T, K>::max_3(int a, int b, int c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

#endif
