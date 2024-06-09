#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

MinHeap::MinHeap() {
  heap_size = 0;
  heap_arr = new int[100]; // Default array of size 100
}

string MinHeap::printHeap() {
  string answer;
  for (int i = 0; i < heap_size; i++)
    answer += to_string(heap_arr[i]) + " ";
  return answer;
}

void swap(int* a, int* b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return;
}

void upHeapBubbling(int heap_arr[], int current_node_index) {
    int parent_node_index = (current_node_index - 1) / 2; // Parent's index of current node

    if (heap_arr[current_node_index] < heap_arr[parent_node_index]) { // If child is smaller then parant
        swap(&heap_arr[current_node_index], &heap_arr[parent_node_index]);
        upHeapBubbling(heap_arr, parent_node_index); // up-Heap Bubble parent node
    }

    return;
}

void MinHeap::insertKey(int k) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    
    // Create hole
    heap_arr[heap_size] = k;
    heap_size++;

    upHeapBubbling(heap_arr, heap_size - 1); // Restore min heap property

    return;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::deleteMin() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    
    // Replace root to last node
    heap_arr[0] = heap_arr[heap_size - 1];
    heap_size--;

    minHeapProp(0); // Down-heap Bubble root

    return;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::minHeapProp(int i) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    
    int left_child_index = 2 * i + 1;
    int right_child_index = 2 * i + 2;
    bool is_changed = false;
    int min_value_index = i;

    if (left_child_index < heap_size) { // If left child exists
        is_changed = (heap_arr[left_child_index] < heap_arr[min_value_index]) ? true : false; // check min_value_index should be changed
        min_value_index = (heap_arr[left_child_index] < heap_arr[min_value_index]) ? left_child_index : min_value_index; // choose smaller one
    }

    if (right_child_index < heap_size) { // If left child exsit
        is_changed = (heap_arr[right_child_index] < heap_arr[min_value_index] || is_changed) ? true : false; // check min_value_index should be changed
        min_value_index = (heap_arr[right_child_index] < heap_arr[min_value_index]) ? right_child_index : min_value_index; // choose smaller one
    }

    if (is_changed) { // If left child node of right child node is smaller then parent node
        swap(&heap_arr[min_value_index], &heap_arr[i]); // Swap child and parent
        minHeapProp(min_value_index); // Do down-heap bubble child again
    }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::deleteElement(int i) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    // Replace ith node to last node
    heap_arr[i] = heap_arr[heap_size - 1];
    heap_size--;

    minHeapProp(i); // Down-heap Bubble root ith node

    return;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}