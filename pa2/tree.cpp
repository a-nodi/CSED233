#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

int getDepth(int node_value, Node* node) {
    int depth = -1;

    if (node == NULL) { // !=이었음 원래
        return -1;
    }
    else {
        if (node->value - '0' == node_value) {
            return depth + 1;
        }
        else {
            // search left node
            depth = getDepth(node_value, node->left);
            if (depth >= 0) {
                return depth + 1;
            }

            // search right node
            depth = getDepth(node_value, node->right);
            if (depth >= 0) {
                return depth + 1;
            }
        }
    }

    return depth;
}

Node* getNode(int node_value, Node* node) {
    Node* curNode = NULL;
    if (node == NULL) {
        return NULL;
    }
    else {
        if (node->value - '0' == node_value) {
            return node;
        }
        else {
            curNode = getNode(node_value, node->left);
            if (curNode != NULL) {
                return curNode;
            }

            curNode = getNode(node_value, node->right);
            if (curNode != NULL) {
                return curNode;
            }

            return NULL;
        }
    }
}

int _getHeight(Node* node) {
    if (node == NULL) {
        return -1;
    }
    else {
        return max(_getHeight(node->left), _getHeight(node->right)) + 1;
    }
}

int getHeight(int node_value, Node* node) {
    Node* target_node;

    if (node == NULL) {
        return -1;
    }
    else {
        // search node
        target_node = getNode(node_value, node);

        // get height
        return _getHeight(target_node);
    }
}

string BinaryTree::getDepthHeight(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int depth = getDepth(node_value, _root);
  int height = getHeight(node_value, _root);
  string answer = "";

  if (depth == -1 || height == -1) { // target node doesn't exist
    answer = "error";
  }
  else { // target node exist
      answer = to_string(depth) + " " + to_string(height);
  }

  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string preOrderTraverse(string orderString, Node* node) {
    if (node != NULL) {
        orderString += node->value;
        orderString += " ";

        if (node->left != NULL) {
            orderString = preOrderTraverse(orderString, node->left);
        }
        if (node->right != NULL) {
            orderString = preOrderTraverse(orderString, node->right);
        }
    }

    return orderString;
}

string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string answer = "";

  answer = preOrderTraverse("", _root);

  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string postOrderTraverse(string orderString, Node* node) {
    if (node != NULL) {
        if (node->left != NULL) {
            orderString = postOrderTraverse(orderString, node->left);
        }
        if (node->right != NULL) {
            orderString = postOrderTraverse(orderString, node->right);
        }

        orderString += node->value;
        orderString += " ";
    }

    return orderString;
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer = "";

    answer = postOrderTraverse("", _root);

    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string inOrderTraverse(string orderString, Node* node) {

    if (node != NULL) {
        if (node->left != NULL) {
            orderString = inOrderTraverse(orderString, node->left);
        }

        orderString += node->value;
        orderString += " ";

        if (node->right != NULL) {
            orderString = inOrderTraverse(orderString, node->right);
        }
    }

    return orderString;
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer = "";

    answer = inOrderTraverse("", _root);

    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool isSubtreeProper(Node* node) {
    if (node == NULL) { // If No node
        return true;
    }

    if (node->left != NULL && node->right != NULL) { // If subtree has 2 children
        return isSubtreeProper(node->left) && isSubtreeProper(node->right); // invastigate children subtrees are proper
    }
    else if (node->left == NULL && node->right == NULL) { // If leaf node
        return true;
    }
    else { // If subtree has 1 child
        return false;
    }
}

string BinaryTree::isProper() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (isSubtreeProper(_root)) { // If root node is proper
    return "True";
  }
  else {
    return "False";
  }
  

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool isSubtreeFull(Node* node, int depth_of_node, int heightOfTree) {
    if (node == NULL) { // If No node
        return true;
    }

    if (node->left == NULL && node->right == NULL) { // If node is leaf node
        return (depth_of_node == heightOfTree);
    }
    else if (node->left != NULL && node->right != NULL) { // If node has 2 child
        return isSubtreeFull(node->left, depth_of_node + 1, heightOfTree) && isSubtreeFull(node->right, depth_of_node + 1, heightOfTree); // Invastigate children subtrees are full
    }
    else { // If node has 1 child
        return false;
    }
}

string BinaryTree::isFull() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    int height_of_tree = _getHeight(_root); // Get height of tree

    if (isSubtreeFull(_root, 0, height_of_tree)) { // If root node is full
        return "True";
    }
    else {
        return "False";
    }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}


int countNode(Node* node) {
    if (node == NULL) { // If no node
        return 0;
    }
    else {
        return 1 + countNode(node->left) + countNode(node->right); // Count subtree node
    }
}

bool isSubtreeComplete(Node* node, int i, int node_count) {
    
    int left_child_index = 2 * i + 1; // Index of node's left child
    int right_child_index = 2 * i + 2; // Index of node's right child
    bool is_complete = true;

    if (node == NULL) { // If no node
        return true;
    }
    
    if (node->left != NULL) { // check left child exists
        is_complete = (left_child_index >= node_count) ? false : true;
    }
    
    if (node->right != NULL) { // check right child exists
        is_complete = (right_child_index >= node_count) ? false : true;
    }

    if (node->left == NULL && node->right != NULL) { // no left child and one right child
        is_complete = false;
    }

    return is_complete && isSubtreeComplete(node->left, left_child_index, node_count) && isSubtreeComplete(node->right, right_child_index, node_count); // Invastigate children subtrees are complete
    
}

string BinaryTree::isComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    int node_count = countNode(_root); // Count tree's node

    if (isSubtreeComplete(_root, 0, node_count)) { // If root node is complete
        return "True";
    }
    else {
        return "False";
    }

  return "False";

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
