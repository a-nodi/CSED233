#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

namespace bst {
    int get_height(Node* node);
    int insert(int key, Node* node, Node** path, int depth);
    int search_target(int key, Node* node, Node** path, int depth);
    int search_smallest_key(Node* node, Node** path, int depth);
}

int BinarySearchTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int inserted_node_depth;
    int insertion_result = 0;
    int path_len = _root != NULL ? _root->height + 1 : 0;

    Node** path;
    
    using namespace bst;
    if (_root == NULL) {
        _root = new Node(key);
    }
    else {
        path = new Node* [path_len];
        for (int i = 0; i < path_len; i++) path[i] = NULL;
        // search insertion location and record path, get inserted node's depth
        inserted_node_depth = insert(key, _root, path, 0);
        if (inserted_node_depth == -1) insertion_result = -1;
        else { // Update height
            for (int i = inserted_node_depth - 1; i >= 0; i--) if (path[i] != NULL) path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
        }

        delete[] path;
    }
    
    return insertion_result;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int target_depth, smallest_depth;
    int deletion_result = 0;
    int path_len = _root != NULL ? _root->height : 0;

    Node* parent, * target, * left_child, * right_child, * smallest, * smallest_parent;
    Node** path = new Node * [path_len];
    Node** smallest_path;

    using namespace bst;

    // Search target and record path, get target's depth
    target_depth = search_target(key, _root, path, 0);
    if (target_depth == -1) deletion_result = -1;
    else {
        if (target_depth == 0) {
            target = path[target_depth];
            left_child = target->left;
            right_child = target->right;

            if (left_child == NULL && right_child == NULL) { // Degree 0
                _root = NULL;
            }
            else if (left_child != NULL && right_child == NULL) { // Degree 1
                _root = left_child;
            }
            else if (left_child == NULL && right_child != NULL) { // Degree 1
                _root = right_child;
            }
            else if (left_child != NULL && right_child != NULL) { // Degree 2
                smallest_path = new Node * [right_child->height];
                smallest_depth = search_smallest_key(right_child, smallest_path, 0);
                
                smallest = smallest_path[smallest_depth];

                if (smallest_depth - 1 >= 0) {
                    smallest_parent = smallest_path[smallest_depth - 1];
                    smallest_parent->left = smallest->right;
                    _root = smallest;

                    smallest->left = left_child;
                    smallest->right = right_child;
                }
                else { // no child;
                    _root = smallest;
                    smallest->left = left_child;
                }
            }
            // Update height
            for (int i = target_depth - 1; i >= 0; i--) if (path[i] != NULL) path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;

            delete target;
            target = NULL;
        }
        else {
            parent = path[target_depth - 1];
            target = path[target_depth];
            left_child = target->left;
            right_child = target->right;

            if (left_child == NULL && right_child == NULL) { // Degree 0
                if (parent->key > key) parent->left = NULL;
                else if (parent->key < key) parent->right = NULL;
            }
            else if (left_child != NULL && right_child == NULL) { // Degree 1
                if (parent->key > key) parent->left = left_child;
                else if (parent->key < key) parent->right = left_child;
            }
            else if (left_child == NULL && right_child != NULL) { // Degree 1
                if (parent->key > key) parent->left = right_child;
                else if (parent->key < key) parent->right = right_child;
            }
            else if (left_child != NULL && right_child != NULL) { // Degree 2
                smallest_path = new Node * [right_child->height];
                smallest_depth = search_smallest_key(right_child, smallest_path, 0);

                smallest = smallest_path[smallest_depth];
                if (smallest_depth - 1 >= 0) {
                    smallest_parent = smallest_path[smallest_depth - 1];
                    smallest_parent->left = smallest->right;
                    if (parent->key > key) parent->left = smallest;
                    else if (parent->key < key) parent->right = smallest;

                    smallest->left = left_child;
                    smallest->right = right_child;
                }
                else {
                    if (parent->key > key) parent->left = smallest;
                    else if (parent->key < key) parent->right = smallest;
                    smallest->left = left_child;
                }

                for (int i = smallest_depth; i >= 0; i--) { // Update right subtree height
                    if (smallest_path[i] != NULL) smallest_path[i]->height = max(get_height(smallest_path[i]->left), get_height(smallest_path[i]->right)) + 1;
                }
                path[target_depth] = smallest;

                delete[] smallest_path;
            }

            // Update height
            for (int i = target_depth - 1; i >= 0; i--) if (path[i] != NULL) path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;

            delete target;
            target = NULL;
        }
    }
    delete[] path;

    return deletion_result;
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

namespace bst {
    int get_height(Node* node) {
        return node == NULL ? -1 : node->height;
    }

    int insert(int key, Node* node, Node** path, int depth) {
        // Searchs insertion location and inserts new node in tree recursively
        if (node == NULL) return depth;
        
        else if (node->key > key) {
            path[depth] = node;
            if (node->left == NULL) {
                node->left = new Node(key);
                path[depth + 1] = node->left;
                return depth + 1;
            }
            else return insert(key, node->left, path, depth + 1);
        }
        else if (node->key < key) {
            path[depth] = node;
            if (node->right == NULL) {
                node->right = new Node(key);
                path[depth + 1] = node->right;
                return depth + 1;
            }
            return insert(key, node->right, path, depth + 1);
        }
        else return -1;
    }

    int search_target(int key, Node* node, Node** path, int depth) {
        // Searchs target node in tree recursively
        if (node == NULL) return -1;
        else if (node->key > key) {
            path[depth] = node;
            return search_target(key, node->left, path, depth + 1);
        }
        else if (node->key < key) {
            path[depth] = node;
            return search_target(key, node->right, path, depth + 1);
        }
        else {
            path[depth] = node;
            return depth;
        }
    }

    int search_smallest_key(Node* node, Node** path, int depth) {
        // Searchs smallest key in tree recursively
        path[depth] = node;

        if (node->left == NULL) {
            return depth;
        }
        else {
            return search_smallest_key(node->left, path, depth + 1);
        }
    }
}

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

