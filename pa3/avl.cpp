#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
namespace avl {
    
    int get_height(Node* node) {
        return node == NULL ? -1 : node->height;
    }

    int bf(Node* node) {
        return get_height(node != NULL ? node->left : NULL) - get_height(node != NULL ? node->right : NULL);
    }

    int insert(int key, Node* node, Node** path, int depth) {

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
        path[depth] = node;

        if (node->left == NULL) {
            return depth;
        }
        else {
            return search_smallest_key(node->left, path, depth + 1);
        }
    }

    void LL_rotation(Node* pivot, Node* pivot_parent) {
        Node* temp;

        // Do a LL rotation
        temp = pivot->left;
        pivot->left = temp->right;
        temp->right = pivot;


        if (pivot_parent != NULL) { // link temp to parent
            if (pivot_parent->key > temp->key) pivot_parent->left = temp;
            else if (pivot_parent->key < temp->key) pivot_parent->right = temp;
        }
        else { // pivot is _root
            pivot = temp;
        }

        return;
    }

    void RR_rotation(Node* pivot, Node* pivot_parent) {
        Node* temp;

        // Do a RR rotation
        temp = pivot->right;
        pivot->right = temp->left;
        temp->left = pivot;

        if (pivot_parent != NULL) { // link temp to parent
            if (pivot_parent->key > temp->key) pivot_parent->left = temp;
            else if (pivot_parent->key < temp->key) pivot_parent->right = temp;
        }
        else { // pivot is _root
            pivot = temp;
        }

        return;
    }

    void LR_rotation(Node* pivot, Node* pivot_parent) {
        RR_rotation(pivot->left, pivot);
        LL_rotation(pivot, pivot_parent);

        return;
    }

    void RL_rotation(Node* pivot, Node* pivot_parent) {
        LL_rotation(pivot->right, pivot);
        RR_rotation(pivot, pivot_parent);

        return;
    }

    void restore_avl_property(Node** _root, Node** path, int target_node_depth) {

        // Search pivot, If AVL property violation is detected, rotate nodes.
        for (int i = target_node_depth; i >= 0; i--) {
            if (bf(path[i]) >= 2 && bf(path[i]->left) > 0) { // LL case
                // cout << "LL" << endl;
                LL_rotation(path[i], i - 1 >= 0 ? path[i - 1] : NULL);
                
                if (path[i] != NULL)path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
                if (path[i + 1] != NULL)path[i + 1]->height = max(get_height(path[i + 1]->left), get_height(path[i + 1]->right)) + 1;
                
                for (int j = i - 1; j >= 0; j--) path[j]->height = max(get_height(path[j]->left), get_height(path[j]->right)) + 1; // Update path's height
                if (i == 0) *_root = path[1];
                break;
            }
            else if (bf(path[i]) >= 2 && bf(path[i]->left) < 0) { // LR case
                // cout << "LR" << endl;
                LR_rotation(path[i], i - 1 >= 0 ? path[i - 1] : NULL);

                // Update path's height
                if (path[i + 1] != NULL)path[i + 1]->height = max(get_height(path[i + 1]->left), get_height(path[i + 1]->right)) + 1;
                if (path[i] != NULL)path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
                if (path[i + 2] != NULL)path[i + 2]->height = max(get_height(path[i + 2]->left), get_height(path[i + 2]->right)) + 1;

                for (int j = i - 1; j >= 0; j--) path[j]->height = max(get_height(path[j]->left), get_height(path[j]->right)) + 1;
                if (i == 0) *_root = path[2];
                break;
            }
            else if (bf(path[i]) <= -2 && bf(path[i]->right) > 0) { // RL case
                // cout << "RL" << endl;
                RL_rotation(path[i], i - 1 >= 0 ? path[i - 1] : NULL);

                // Update path's height
                if (path[i + 1] != NULL)path[i + 1]->height = max(get_height(path[i + 1]->left), get_height(path[i + 1]->right)) + 1;
                if (path[i] != NULL)path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
                if (path[i + 2] != NULL)path[i + 2]->height = max(get_height(path[i + 2]->left), get_height(path[i + 2]->right)) + 1;

                for (int j = i - 1; j >= 0; j--) path[j]->height = max(get_height(path[j]->left), get_height(path[j]->right)) + 1;
                if (i == 0) *_root = path[2];
                break;
            }
            else if (bf(path[i]) <= -2 && bf(path[i]->right) < 0) { // RR case
                // cout << "RR" << endl;
                RR_rotation(path[i], i - 1 >= 0 ? path[i - 1] : NULL);
                
                if (path[i] != NULL)path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
                if (path[i + 1] != NULL)path[i + 1]->height = max(get_height(path[i + 1]->left), get_height(path[i + 1]->right)) + 1;

                for (int j = i - 1; j >= 0; j--) path[j]->height = max(get_height(path[j]->left), get_height(path[j]->right)) + 1; // Update path's height
                if (i == 0) *_root = path[1];
                break;
            }
            
        }
        // cout << "bf[0] " << bf(path[0]) << " key " << (*_root)->key <<  " avlp end" << endl;
        return;
    }
}


///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int AVLTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int inserted_node_depth;
    int insertion_result = 0;
    int path_len = _root != NULL ? _root->height + 1 : 0;

    Node** path;

    using namespace avl;
    if (_root == NULL) {
        _root = new Node(key);
    }
    else {
        path = new Node * [path_len];
        for (int i = 0; i < path_len; i++) path[i] = NULL;
        inserted_node_depth = insert(key, _root, path, 0);
        if (inserted_node_depth == -1) insertion_result = -1;
        else {
            for (int i = inserted_node_depth - 1; i >= 0; i--) if (path[i] != NULL) path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
            restore_avl_property(&_root, path, inserted_node_depth);
        }
        // cout << "key " << key << " inserted_node_depth " << inserted_node_depth << endl;
        
        delete[] path;
    }

    return insertion_result;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::deletion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int target_depth, smallest_depth;
    int deletion_result = 0;
    int path_len = _root != NULL ? _root->height : 0;

    Node* parent, * target, * left_child, * right_child, * smallest, * smallest_parent;
    Node** path = new Node * [path_len];
    Node** smallest_path;

    using namespace avl;

    target_depth = search_target(key, _root, path, 0);
    if (target_depth == -1) deletion_result = -1;
    else {
        if (target_depth == 0) {
            target = path[target_depth];
            left_child = target->left;
            right_child = target->right;

            if (left_child == NULL && right_child == NULL) {
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

            for (int i = target_depth - 1; i >= 0; i--) if (path[i] != NULL) path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;

            // cout << "key " << key << " target_node_depth " << target_depth << endl;

            delete target;
            target = NULL;
        }
        else {
            parent = path[target_depth - 1];
            target = path[target_depth];
            left_child = target->left;
            right_child = target->right;

            if (left_child == NULL && right_child == NULL) {
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

                for (int i = smallest_depth; i >= 0; i--) { // update right subtree height
                    if (smallest_path[i] != NULL) smallest_path[i]->height = max(get_height(smallest_path[i]->left), get_height(smallest_path[i]->right)) + 1;
                }

                path[target_depth] = smallest;

                delete[] smallest_path;
            }

            // update height
            for (int i = target_depth - 1; i >= 0; i--) if (path[i] != NULL) path[i]->height = max(get_height(path[i]->left), get_height(path[i]->right)) + 1;
            
            // cout << "key " << key << " target_node_depth " << target_depth << endl;
            restore_avl_property(&_root, path, target_depth);

            delete target;
        }
    }
    delete[] path;

    return deletion_result;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
