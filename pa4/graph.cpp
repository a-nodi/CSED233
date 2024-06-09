#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

bool is_exist(Adjacency_list *aList, int len, string node_label) {
  bool flag = false;

  for (int i = 0; i < len; i++) {
    if (aList[i].label == node_label) {
      flag = true;
      break;
    }
  }

  return flag;
}

Adjacency_list *insert_adjacency_list(Adjacency_list *aList, int len,
                                      string node_label) {

  bool found_location = false;
  Adjacency_list *temp;
  if (aList == NULL)
    temp = (Adjacency_list *)malloc(sizeof(Adjacency_list) * 100);
  else
    temp = (Adjacency_list *)realloc(aList, sizeof(Adjacency_list) *
                                                size_t(len + 100));

  aList = temp;
  aList[len].label = node_label;
  aList[len].head = NULL;
  aList[len].count = 0;
  aList[len].aList_index = len;

  return aList;
}

void insert_node(Adjacency_list *aList, string node_label, int aList_index) {

  Node *temp = new Node;
  Node *pre_node = aList->head;
  Node *cur_node = aList->head;
  bool found_location = false;
  bool is_first_node = true;
  temp->label = node_label;
  temp->aList_index = aList_index;
  temp->next = NULL;

  if (!temp)
    return;
  else if (aList->count == 0)
    aList->head = temp;
  else {
    while (cur_node != NULL) {
      if ((cur_node->label)[0] == node_label[0]) {
        delete temp;
        return;
      } else if ((cur_node->label)[0] > node_label[0]) {
        if (is_first_node) {
          aList->head = temp;
          temp->next = cur_node;
        } else {
          pre_node->next = temp;
          temp->next = cur_node;
        }
        found_location = true;
        break;
      } else {
        pre_node = cur_node;
        cur_node = cur_node->next;
      }
      is_first_node = false;
    }
    if (!found_location) {
      pre_node->next = temp;
    }
  }
  aList->count++; // Update count
  return;
}

int locate_adjacency_list(Adjacency_list *aList, int len, string node_label) {

  for (int i = 0; i < len; i++) {
    if (aList[i].label == node_label)
      return i;
  }

  return -1;
}

int **reallocate_path_cost(int **path_cost, int len) {

  int **temp1;
  int *temp2;

  if (path_cost == NULL) {
    temp1 = (int **)malloc(sizeof(int *) * 100);
    if (temp1 != NULL)
      path_cost = temp1;
    temp2 = (int *)malloc(sizeof(int) * 100);
    if (temp2 != NULL) {
      path_cost[0] = temp2;
      path_cost[0][0] = 0;
    }

  } else {

    temp1 = (int **)realloc(path_cost, (len + 1) * sizeof(int *));
    if (temp1 != NULL)
      path_cost = temp1;
    for (int i = 0; i < len + 1; i++) {
      temp2 = (int *)realloc(path_cost[i], (len + 1) * sizeof(int));
      if (temp2 != NULL) {
        path_cost[i] = temp2;
        path_cost[i][len] = INF;
      }
    }
    for (int i = 0; i < len + 1; i++) {
      path_cost[len][i] = INF;
    }
    path_cost[len][len] = 0;
  }
  return path_cost;
}

int *reallocate_num_parent(int *num_parent, int len) {
  int *temp;

  if (num_parent == NULL) {
    temp = (int *)malloc(sizeof(int) * 100);
    if (temp != NULL) {
      num_parent = temp;
      num_parent[0] = 0;
    }

  } else {
    temp = (int *)realloc(num_parent, (len + 1) * sizeof(int));
    if (temp != NULL) {
      num_parent = temp;
      num_parent[len] = 0;
    }
  }

  return num_parent;
}

bool is_all_traveled(bool *mark, int len) {
  for (int i = 0; i < len; i++) {
    if (!mark[i])
      return false;
  }
  return true;
}

void print_list(Adjacency_list *aList, int len) {

  for (int i = 0; i < len; i++) {
    cout << aList[i].label << ": ";
    for (Node *temp = aList[i].head; temp != NULL; temp = temp->next)
      cout << temp->label << temp->aList_index << " ";
    cout << endl;
  }
}

int find_smallest_unfound_node(Adjacency_list *aList, bool *mark, int len) {
  char smallest_label;
  int smallest_index = -1;
  for (int i = 0; i < len; i++) {
    if (!mark[i]) {
      smallest_label = (aList[i].label)[0];
      smallest_index = aList[i].aList_index;
    }
  }

  for (int i = 0; i < len; i++) {
    if (!mark[i]) {
      if (int(smallest_label) > int(aList[i].label[0])) {
        smallest_label = aList[i].label[0];
        smallest_index = aList[i].aList_index;
      }
    }
  }

  return smallest_index;
}

bool push(string label, Stack *pstack) {

  Node *temp = new Node;

  if (!temp) {
    return false;
  } else {
    temp->next = pstack->top;
    temp->label = label;
    pstack->top = temp;
    pstack->count++;
  }

  return true;
}

string pop(Stack *pstack) {

  Node *temp;
  string label = "";
  if (pstack->count == 0) {
    return "";
  } else {
    temp = pstack->top;
    label = temp->label;
    pstack->top = temp->next;
    pstack->count--;

    delete temp;
  }

  return label;
}

string top(Stack *pstack) {

  Node *temp;

  if (pstack->count == 0) { // Stack is empty
    return "";              // Return empty
  } else {
    temp = pstack->top; // Top node
    return temp->label; // Return value of top node
  }
}

string _DFS(Adjacency_list *aList, bool *mark, int len, string node_label) {
  int index = locate_adjacency_list(aList, len, node_label);
  mark[index] = true;
  string path = node_label;
  path += " ";

  for (Node *temp = aList[index].head; temp != NULL; temp = temp->next) {
    if (!mark[temp->aList_index]) {
      path += _DFS(aList, mark, len, temp->label);
    }
  }
  return path;
}

bool enqueue(string node_label, Queue *pqueue) {
  /*
   * The function that performs 'Enqueue' operation on the queue
   * @param: int value: Value to be enqueued into queue
   * @param: QUEUE* pqueue: Pointer of queue
   * @return: bool is_success: true if enqueue was successful, else false
   */

  Node *temp = new Node;

  if (!temp) {    // Dynamic allocation failed
    return false; // Return error
  } else {
    temp->label = node_label;
    temp->next = NULL;

    if (pqueue->count == 0) { // Queue is empty
      pqueue->front = temp;
      pqueue->rear = temp;
    } else {
      pqueue->rear->next = temp;
      pqueue->rear = temp;
    }
    pqueue->count++; // Update count
  }

  return true; // Return success
}

string dequeue(Queue *pqueue) {
  /*
   * The function that performs 'Dequeue' operation on the queue
   * @param: QUEUE* pqueue: Pointer of queue
   * @return: bool is_success: true if dequeue was successful, else false
   */

  Node *temp;
  string label;
  if (pqueue->count == 0) { // Queue is empty
    return "";              // Return error
  }

  temp = pqueue->front;

  if (pqueue->count == 1) { // Only one node in queue
    pqueue->front = NULL;
    pqueue->rear = NULL;
    pqueue->count--;
  } else {
    pqueue->front = temp->next;
    pqueue->count--;
  }
  label = temp->label;

  delete temp; // Free node

  return label; // Return success
}

void _DFS(Adjacency_list *aList, int *mark, int len, int *count,
          string node_label, string parent_label) {
  int index = locate_adjacency_list(aList, len, node_label);
  enum Mark { UNVISITED, VISITED, CLOSED };

  mark[index] = VISITED;

  for (Node *temp = aList[index].head; temp != NULL; temp = temp->next) {
    if (temp->label != parent_label) {
      if(mark[locate_adjacency_list(aList, len, temp->label)] == UNVISITED) _DFS(aList, mark, len, count, temp->label, node_label);
      else if (mark[locate_adjacency_list(aList, len, temp->label)] == VISITED) (*count)++;
    }
  }

  mark[index] = CLOSED;
  return;
}

string _topSort(Adjacency_list *aList, bool *mark, int *num_parent,
                Stack *pstack, int len, string topsorted_string) {
  string aux_topsorted_string = "";
  string temp_str = "";
  Stack aux_stack;
  aux_stack.count = 0;
  aux_stack.top = NULL;

  for (int i = 0; i < len; i++) {
    if (num_parent[i] == 0 && mark[i] == false) {
      for (Node *temp = aList[i].head; temp != NULL; temp = temp->next) {
        num_parent[temp->aList_index]--;
      }
      push(aList[i].label, pstack);
      mark[i] = true;
      topsorted_string =
          _topSort(aList, mark, num_parent, pstack, len, topsorted_string);

      for (Node *temp = aList[i].head; temp != NULL; temp = temp->next) {
        num_parent[temp->aList_index]++;
      }
      pop(pstack);
      mark[i] = false;
    }
  }
  if (pstack->count == len) {
    for (int i = 0; i < len; i++) {
      temp_str = pop(pstack);
      push(temp_str, &aux_stack);
      aux_topsorted_string =
          (temp_str.append(" ")).append(aux_topsorted_string);
    }
    if (topsorted_string == "" || aux_topsorted_string < topsorted_string)
      topsorted_string = aux_topsorted_string;
    for (int i = 0; i < len; i++) {
      push(pop(&aux_stack), pstack);
    }
  }
  return topsorted_string;
}

void insert_node(StringList *string_list, string path) {

  StringNode *temp = new StringNode;
  StringNode *pre_node = string_list->head;
  StringNode *cur_node = string_list->head;
  bool found_location = false;
  bool is_first_node = true;
  temp->path = path;
  temp->next = NULL;

  if (!temp)
    return;
  else if (string_list->count == 0)
    string_list->head = temp;
  else {
    while (cur_node != NULL) {
      if (cur_node->path == path) {
        delete temp;
        return;
      } else if (cur_node->path > path) {
        if (is_first_node) {
          string_list->head = temp;
          temp->next = cur_node;
        } else {
          pre_node->next = temp;
          temp->next = cur_node;
        }
        found_location = true;
        break;
      } else {
        pre_node = cur_node;
        cur_node = cur_node->next;
      }
      is_first_node = false;
    }
    if (!found_location) {
      pre_node->next = temp;
    }
  }
  string_list->count++; // Update count
  return;
}

void _DFS(Adjacency_list *aList, bool *mark, int **path_cost,
          StringList *string_list, Stack *pstack, int len, string node_label,
          int dist, int min_d, string source, string destination) {

  string aux_string = "";
  string temp_str = "";
  Stack aux_stack;
  StringNode *temp;
  int index = locate_adjacency_list(aList, len, node_label);
  int stack_size;
  aux_stack.count = 0;
  aux_stack.top = NULL;
  if (pstack->count == 0) {
    push(source, pstack);
    mark[index] = true;
  }

  for (Node *temp = aList[index].head; temp != NULL; temp = temp->next) {
    if (mark[temp->aList_index] == false) {
      push(temp->label, pstack);
      mark[temp->aList_index] = true;
      dist += path_cost[index][temp->aList_index];
      if (top(pstack) == destination && dist == min_d) {
        stack_size = pstack->count;
        for (int i = 0; i < stack_size; i++) {
          temp_str = pop(pstack);
          push(temp_str, &aux_stack);
          aux_string = (temp_str.append(" ")).append(aux_string);
        }
        insert_node(string_list, aux_string);

        for (int i = 0; i < stack_size; i++) {
          push(pop(&aux_stack), pstack);
        }
      } else {

        _DFS(aList, mark, path_cost, string_list, pstack, len, temp->label,
             dist, min_d, source, destination);
      }

      pop(pstack);
      mark[temp->aList_index] = false;
      dist -= path_cost[index][temp->aList_index];
    }
  }
  return;
}

void swap(int *a, int *b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;

  return;
}

void swap(PNode *a, PNode *b) {
  PNode temp;
  temp = *a;
  *a = *b;
  *b = temp;

  return;
}

void swap(EdgeNode *a, EdgeNode *b) {
  EdgeNode temp;
  temp = *a;
  *a = *b;
  *b = temp;

  return;
}

void quickSort(Adjacency_list *aList, int *arr, int left, int right) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int pivot = int(aList[arr[left]].label[0]);
  int l_mover_index = left + 1;
  int r_mover_index = left + 1;
  int rightmost_smallest_index = left;

  if (right - left <= 0)
    return; // If only one element exists in subarray

  if (right - left == 1) { // If two element exist in subarray
    if (pivot > int(aList[arr[right]].label[0])) {
      swap(&arr[left], &arr[right]);
    }
    return;
  }

  // If more then 3 elements exist in subarray
  for (int i = left + 1; i <= right; i++) {
    l_mover_index = i;
    r_mover_index = i + 1;
    if (int(aList[arr[l_mover_index]].label[0]) >= pivot)
      break;
  }

  // Do In-place partitioning
  while (r_mover_index <= right) {
    if (int(aList[r_mover_index].label[0]) < pivot) {
      swap(&arr[r_mover_index], &arr[l_mover_index]);
      l_mover_index = r_mover_index;
    }
    r_mover_index++;
  }

  // find rightmost smallest index
  for (int i = right; i >= left + 1; i--) {
    if (int(aList[arr[i]].label[0]) < pivot) {
      rightmost_smallest_index = i;
      break;
    }
  }

  // Swap if rightmost smallest element is smaller than pivot
  if (rightmost_smallest_index != left) {
    swap(&arr[left], &arr[rightmost_smallest_index]);
  }

  // Sort left and right subarray
  quickSort(aList, arr, left, rightmost_smallest_index - 1);
  quickSort(aList, arr, rightmost_smallest_index + 1, right);

  return;
}

void quickSort(EdgeNode *array_of_edge, int left, int right) {
  EdgeNode pivot = array_of_edge[left];
  int l_mover_index = left + 1;
  int r_mover_index = left + 1;
  int rightmost_smallest_index = left;

  if (right - left <= 0)
    return; // If only one element exists in subarray

  if (right - left == 1) { // If two element exist in subarray
    if (pivot.edge_cost > array_of_edge[right].edge_cost ||
        (pivot.edge_cost == array_of_edge[right].edge_cost &&
         pivot.source > array_of_edge[right].source) ||
        (pivot.edge_cost == array_of_edge[right].edge_cost &&
         pivot.source == array_of_edge[right].source &&
         pivot.destination ==
             array_of_edge[right].destination)) { ////////////////
      swap(&array_of_edge[left], &array_of_edge[right]);
    }
    return;
  }

  // If more then 3 elements exist in subarray
  for (int i = left + 1; i <= right; i++) {
    l_mover_index = i;
    r_mover_index = i + 1;
    if (!(pivot.edge_cost > array_of_edge[l_mover_index].edge_cost ||
          (pivot.edge_cost == array_of_edge[l_mover_index].edge_cost &&
           pivot.source > array_of_edge[l_mover_index].source) ||
          (pivot.edge_cost == array_of_edge[l_mover_index].edge_cost &&
           pivot.source == array_of_edge[l_mover_index].source &&
           pivot.destination >
               array_of_edge[l_mover_index].destination))) ///////////////////
      break;
  }

  // Do In-place partitioning
  while (r_mover_index <= right) {
    if (pivot.edge_cost > array_of_edge[r_mover_index].edge_cost ||
        (pivot.edge_cost == array_of_edge[r_mover_index].edge_cost &&
         pivot.source > array_of_edge[r_mover_index].source) ||
        (pivot.edge_cost == array_of_edge[r_mover_index].edge_cost &&
         pivot.source == array_of_edge[r_mover_index].source &&
         pivot.destination >
             array_of_edge[r_mover_index].destination)) { ///////////////
      swap(&array_of_edge[r_mover_index], &array_of_edge[l_mover_index]);
      l_mover_index = r_mover_index;
    }
    r_mover_index++;
  }

  // find rightmost smallest index
  for (int i = right; i >= left + 1; i--) {
    if (pivot.edge_cost > array_of_edge[i].edge_cost ||
        (pivot.edge_cost == array_of_edge[i].edge_cost &&
         pivot.source > array_of_edge[i].source) ||
        (pivot.edge_cost == array_of_edge[i].edge_cost &&
         pivot.source == array_of_edge[i].source &&
         pivot.destination > array_of_edge[i].destination)) { //////////////////
      rightmost_smallest_index = i;
      break;
    }
  }

  // Swap if rightmost smallest element is smaller than pivot
  if (rightmost_smallest_index != left) {
    swap(&array_of_edge[left], &array_of_edge[rightmost_smallest_index]);
  }

  // Sort left and right subarray
  quickSort(array_of_edge, left, rightmost_smallest_index - 1);
  quickSort(array_of_edge, rightmost_smallest_index + 1, right);

  return;
}

class MinHeap {

public:
  MinHeap();

  int heap_size;
  PNode *heap_arr;

  void minHeapProp(int);
  void upHeapBubbling(int);
  void insertKey(Adjacency_list *aList, int len, string node_label,
                 int aList_index, int distance);
  int locate_index(string label);
  void update_distance(int index, int distance);
  PNode deleteMin();

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};

MinHeap::MinHeap() {
  heap_size = 0;
  heap_arr = new PNode[53]; // Default array of size
}

void MinHeap::upHeapBubbling(int current_node_index) {
  int parent_node_index =
      (current_node_index - 1) / 2; // Parent's index of current node

  if (heap_arr[current_node_index].distance <
          heap_arr[parent_node_index].distance ||
      (heap_arr[current_node_index].distance ==
           heap_arr[parent_node_index].distance &&
       heap_arr[current_node_index].label <
           heap_arr[parent_node_index]
               .label)) { // If child is smaller then parant
    swap(&heap_arr[current_node_index], &heap_arr[parent_node_index]);
    upHeapBubbling(parent_node_index); // up-Heap Bubble parent node
  }

  return;
}

void MinHeap::insertKey(Adjacency_list *aList, int len, string node_label,
                        int aList_index, int distance) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  // Create hole
  heap_arr[heap_size].aList_index = aList_index;
  heap_arr[heap_size].label = node_label;
  heap_arr[heap_size].distance = distance;
  heap_size++;
  upHeapBubbling(heap_size - 1); // Restore min heap property

  return;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

PNode MinHeap::deleteMin() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  // Replace root to last node
  PNode min = heap_arr[0];
  heap_arr[0] = heap_arr[heap_size - 1];
  heap_size--;

  minHeapProp(0); // Down-heap Bubble root

  return min;
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
    is_changed =
        (heap_arr[left_child_index].distance <
             heap_arr[min_value_index].distance ||
         (heap_arr[left_child_index].distance ==
              heap_arr[min_value_index].distance &&
          heap_arr[left_child_index].label < heap_arr[min_value_index].label))
            ? true
            : false; // check min_value_index should be changed
    min_value_index =
        (heap_arr[left_child_index].distance <
             heap_arr[min_value_index].distance ||
         (heap_arr[left_child_index].distance ==
              heap_arr[min_value_index].distance &&
          heap_arr[left_child_index].label < heap_arr[min_value_index].label))
            ? left_child_index
            : min_value_index; // choose smaller one
  }

  if (right_child_index < heap_size) { // If left child exsit
    is_changed =
        (heap_arr[right_child_index].distance <
             heap_arr[min_value_index].distance ||
         (heap_arr[right_child_index].distance ==
              heap_arr[min_value_index].distance &&
          heap_arr[right_child_index].label < heap_arr[min_value_index].label))
            ? true
            : false; // check min_value_index should be changed
    min_value_index =
        (heap_arr[right_child_index].distance <
             heap_arr[min_value_index].distance ||
         (heap_arr[right_child_index].distance ==
              heap_arr[min_value_index].distance &&
          heap_arr[right_child_index].label < heap_arr[min_value_index].label))
            ? right_child_index
            : min_value_index; // choose smaller one
  }

  if (is_changed) { // If left child node of right child node is smaller then
                    // parent node
    swap(&heap_arr[min_value_index], &heap_arr[i]); // Swap child and parent
    minHeapProp(min_value_index); // Do down-heap bubble child again
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int MinHeap::locate_index(string label) {
  for (int i = 0; i < heap_size; i++)
    if (heap_arr[i].label == label)
      return i;
  return -1;
}

void MinHeap::update_distance(int index, int distance) {
  heap_arr[index].distance = distance;
  upHeapBubbling(index);
  return;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int find(int *p, int index) {
  if (p[index] != index)
    return find(p, p[index]);
  else
    return index;
}

void Union(int *p, EdgeNode temp) {
  int source_parent_index = find(p, temp.source_index);
  int destination_parent_index = find(p, temp.destination_index);
  if (temp.source < temp.destination)
    p[destination_parent_index] = source_parent_index;
  else if (temp.source > temp.destination)
    p[source_parent_index] = destination_parent_index;
  return;
}

string Graph::DFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string total_answer = "";
  string partial_path = "";

  // print_list(aList, len);
  bool *mark = (bool *)malloc((len + 100) * sizeof(bool));
  if (mark != NULL) {
    for (int i = 0; i < len; i++)
      mark[i] = false;
    while (!is_all_traveled(mark, len)) {
      partial_path =
          _DFS(aList, mark, len,
               aList[find_smallest_unfound_node(aList, mark, len)].label);
      total_answer += partial_path;
      total_answer += "\n";
    }
  }

  return total_answer;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::BFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int index;
  string cur_node_label = "";
  string total_answer = "";
  string partial_path = "";
  Queue queue;
  queue.count = 0;
  queue.front = NULL;
  queue.rear = NULL;
  bool *mark = (bool *)malloc(sizeof(bool) * (len + 100));
  if (mark != NULL) {
    for (int i = 0; i < len; i++)
      mark[i] = false;
    while (!is_all_traveled(mark, len)) {
      index = find_smallest_unfound_node(aList, mark, len);
      mark[index] = true;
      partial_path = "";
      enqueue(aList[index].label, &queue);
      while (queue.count > 0) {
        cur_node_label = dequeue(&queue);
        partial_path += cur_node_label;
        partial_path.append(" ");
        for (Node *temp =
                 aList[locate_adjacency_list(aList, len, cur_node_label)].head;
             temp != NULL; temp = temp->next) {
          index = locate_adjacency_list(aList, len, temp->label);
          if (!mark[index]) {
            enqueue(temp->label, &queue);
            mark[index] = true;
          }
        }
      }
      total_answer += partial_path;
      total_answer += "\n";
    }
  }

  return total_answer;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int nodeA_aList_index;
  int nodeB_aList_index;
  if (!is_exist(aList, len, nodeA)) {
    aList = insert_adjacency_list(aList, len, nodeA);
    num_parent = reallocate_num_parent(num_parent, len);
    len++;
  }
  if (!is_exist(aList, len, nodeB)) {
    aList = insert_adjacency_list(aList, len, nodeB);
    num_parent = reallocate_num_parent(num_parent, len);
    len++;
  }
  nodeA_aList_index = locate_adjacency_list(aList, len, nodeA);
  nodeB_aList_index = locate_adjacency_list(aList, len, nodeB);
  insert_node(&aList[nodeA_aList_index], nodeB, nodeB_aList_index);
  num_parent[nodeB_aList_index]++;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int nodeA_aList_index;
  int nodeB_aList_index;
  if (!is_exist(aList, len, nodeA)) {
    aList = insert_adjacency_list(aList, len, nodeA);
    num_parent = reallocate_num_parent(num_parent, len);
    path_cost = reallocate_path_cost(path_cost, len);
    len++;
  }
  if (!is_exist(aList, len, nodeB)) {
    aList = insert_adjacency_list(aList, len, nodeB);
    num_parent = reallocate_num_parent(num_parent, len);
    path_cost = reallocate_path_cost(path_cost, len);
    len++;
  }
  nodeA_aList_index = locate_adjacency_list(aList, len, nodeA);
  nodeB_aList_index = locate_adjacency_list(aList, len, nodeB);

  insert_node(&aList[nodeA_aList_index], nodeB, nodeB_aList_index);
  num_parent[nodeB_aList_index]++;

  path_cost[nodeA_aList_index][nodeB_aList_index] = weight;
  // path_cost[nodeB_aList_index][nodeA_aList_index] = INF;
  path_cost[nodeA_aList_index][nodeA_aList_index] = 0;
  path_cost[nodeB_aList_index][nodeB_aList_index] = 0;

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int nodeA_aList_index;
  int nodeB_aList_index;

  if (!is_exist(aList, len, nodeA)) {
    aList = insert_adjacency_list(aList, len, nodeA);
    num_parent = reallocate_num_parent(num_parent, len);
    len++;
  }
  if (!is_exist(aList, len, nodeB)) {
    aList = insert_adjacency_list(aList, len, nodeB);
    num_parent = reallocate_num_parent(num_parent, len);
    len++;
  }

  nodeA_aList_index = locate_adjacency_list(aList, len, nodeA);
  nodeB_aList_index = locate_adjacency_list(aList, len, nodeB);

  insert_node(&aList[nodeA_aList_index], nodeB, nodeB_aList_index);
  insert_node(&aList[nodeB_aList_index], nodeA, nodeA_aList_index);
  num_parent[nodeA_aList_index]++;
  num_parent[nodeB_aList_index]++;

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int nodeA_aList_index;
  int nodeB_aList_index;
  if (!is_exist(aList, len, nodeA)) {
    aList = insert_adjacency_list(aList, len, nodeA);
    num_parent = reallocate_num_parent(num_parent, len);
    path_cost = reallocate_path_cost(path_cost, len);
    len++;
  }
  if (!is_exist(aList, len, nodeB)) {
    aList = insert_adjacency_list(aList, len, nodeB);
    num_parent = reallocate_num_parent(num_parent, len);
    path_cost = reallocate_path_cost(path_cost, len);
    len++;
  }

  nodeA_aList_index = locate_adjacency_list(aList, len, nodeA);
  nodeB_aList_index = locate_adjacency_list(aList, len, nodeB);

  insert_node(&aList[nodeA_aList_index], nodeB, nodeB_aList_index);
  insert_node(&aList[nodeB_aList_index], nodeA, nodeA_aList_index);
  num_parent[nodeA_aList_index]++;
  num_parent[nodeB_aList_index]++;

  path_cost[nodeA_aList_index][nodeB_aList_index] = weight;
  path_cost[nodeB_aList_index][nodeA_aList_index] = weight;
  path_cost[nodeA_aList_index][nodeA_aList_index] = 0;
  path_cost[nodeB_aList_index][nodeB_aList_index] = 0;

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countUndirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int count = 0;
  int *mark = (int *)malloc(sizeof(int) * (len + 100));
  enum Mark { UNVISITED, VISITED, CLOSED };
  if (mark != NULL) {
    for (int i = 0; i < len; i++)
      mark[i] = UNVISITED;
    for (int i = 0; i < len; i++) {
      _DFS(aList, mark, len, &count, aList[i].label, " ");
    }
  }

  return count;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getTopologicalSort() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string topsort = "";

  int index, count = 0;
  Stack stack;
  int *list_of_0_parent_index = (int *)malloc(sizeof(int) * (len + 100));
  bool *mark = (bool *)malloc(sizeof(bool) * (len + 100));

  stack.count = 0;
  stack.top = NULL;

  for (int i = 0; i < len; i++)
    mark[i] = false;

  for (int i = 0; i < len; i++)
    list_of_0_parent_index[i] = -1;
  if (countUndirectedCycle() == 0)
    return _topSort(aList, mark, num_parent, &stack, len, "");
  else
    return "error";

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::countDirectedCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int count = 0;
  int *mark = (int *)malloc(sizeof(int) * (len + 100));
  enum Mark { UNVISITED, VISITED, CLOSED };
  if (mark != NULL) {
    for (int i = 0; i < len; i++)
      mark[i] = UNVISITED;
    for (int i = 0; i < len; i++) {
      _DFS(aList, mark, len, &count, aList[i].label, " ");
    }
  }

  return count;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getShortestPath(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int min_d = INF;
  int min_index = -1;
  int source_index = locate_adjacency_list(aList, len, source);
  int destination_index = locate_adjacency_list(aList, len, destination);
  int temp_index;
  string path = "";
  StringList string_list;
  bool *mark = (bool *)malloc(sizeof(bool) * (len + 100));
  int *p = (int *)malloc(sizeof(int) * (len + 100));
  bool path_rec = false;
  Stack stack;
  stack.count = 0;
  stack.top = NULL;

  for (int i = 0; i < len; i++) {
    p[i] = -1;
    mark[i] = false;
  }
  /////////////////////// <-
  // path.append(source);
  // path.append(" ");
  /////////////////////// <-
  mark[locate_adjacency_list(aList, len, source)] = true;
  distance = (int *)malloc(sizeof(int) * (len + 100));
  for (int i = 0; i < len; i++) {
    temp_index = locate_adjacency_list(aList, len, aList[i].label);
    distance[i] = path_cost[source_index][temp_index];
  }

  for (int i = 0; i < len - 1; i++) {
    min_d = INF;
    min_index = -1;
    for (int j = 0; j < len; j++) {
      if (distance[j] < min_d && mark[j] == false) {
        min_d = distance[j];
        min_index = j;
      }
    }
    mark[min_index] = true;
    if (min_d == INF)
      return "error";
    else {
      for (int j = 0; j < len; j++) {
        if (!mark[j] && path_cost[min_index][j] != INF &&
            distance[min_index] != INF) {
          if (distance[min_index] + path_cost[min_index][j] < distance[j]) {
            distance[j] = distance[min_index] + path_cost[min_index][j];
            p[j] = min_index;
          }
        }
      }
    }
  }

  min_d = distance[locate_adjacency_list(aList, len, destination)];

  for (int i = 0; i < len; i++)
    mark[i] = false;
  _DFS(aList, mark, path_cost, &string_list, &stack, len, source, 0, min_d,
       source, destination);
  for (StringNode *temp = string_list.head; temp != NULL; temp = temp->next) {

    path.append(temp->path);
    path.append(to_string(min_d));
    path.append("\n");
  }

  return path;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string Graph::getAllShortestPaths() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string matrix = "";
  int **A = (int **)malloc(sizeof(int *) * (len + 100));
  int *lexicographic_order = (int *)malloc(sizeof(int) * (len + 100));
  int **next = (int **)malloc(sizeof(int *) * (len + 100));

  for (int i = 0; i < len; i++)
    A[i] = (int *)malloc(sizeof(int) * (len + 100));
  for (int i = 0; i < len; i++)
    next[i] = (int *)malloc(sizeof(int) * (len + 100));
  for (int i = 0; i < len; i++)
    lexicographic_order[i] = i;

  quickSort(aList, lexicographic_order, 0, len - 1);

  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      A[i][j] = path_cost[i][j];
    }
  }
  for (int j = 0; j < len; j++) {
    for (int i = 0; i < len; i++) {
      next[i][j] = -1;
    }
  }
  for (int i = 0; i < len; i++) {
    for (Node *temp = aList[i].head; temp != NULL; temp = temp->next)
      next[i][temp->aList_index] = temp->aList_index;
  }
  for (int k = 0; k < len; k++) {
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        if (A[i][j] > A[i][k] + A[k][j] && A[i][k] != INF && A[k][j] != INF) {
          A[i][j] = A[i][k] + A[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
  matrix = "";
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      matrix.append(
          (A[lexicographic_order[i]][lexicographic_order[j]] != INF
               ? to_string(A[lexicographic_order[i]][lexicographic_order[j]])
               : "INF"));
      matrix.append(" ");
    }
    matrix.append("\n");
  }

  return matrix;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  MinHeap min_heap;
  PNode wNode;
  int v_index, total_distance = 0;
  int *p = (int *)malloc(sizeof(int) * (len + 100));
  bool *mark = (bool *)malloc(sizeof(bool) * (len + 100));

  int start_index = locate_adjacency_list(aList, len, startNode);

  for (int i = 0; i < len; i++) {
    p[i] = start_index;
    mark[i] = false;
  }

  for (int i = 0; i < len; i++) {
    if (i == start_index)
      min_heap.insertKey(aList, len, aList[i].label, i, 0);
    else
      min_heap.insertKey(aList, len, aList[i].label, i, INF);
  }
  while (min_heap.heap_size > 0) {

    wNode = min_heap.deleteMin();
    mark[wNode.aList_index] = true;
    for (Node *temp = aList[wNode.aList_index].head; temp != NULL;
         temp = temp->next) {
      v_index = min_heap.locate_index(temp->label);
      if (mark[temp->aList_index] == false &&
          path_cost[wNode.aList_index][temp->aList_index] <
              min_heap.heap_arr[v_index].distance) {
        min_heap.update_distance(
            v_index, path_cost[wNode.aList_index][temp->aList_index]);
        p[temp->aList_index] = wNode.aList_index;
      }
    }
    if (p[wNode.aList_index] != wNode.aList_index) {
      fout << aList[p[wNode.aList_index]].label << " "
           << aList[wNode.aList_index].label << " "
           << path_cost[p[wNode.aList_index]][wNode.aList_index] << endl;
      total_distance += path_cost[p[wNode.aList_index]][wNode.aList_index];
    }
  }

  return total_distance;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  EdgeNode *array_of_edge;
  EdgeNode temp;
  int *p = (int *)malloc(sizeof(int) * (len + 100));
  int edge_count = 0;
  int temp_index = 0;
  int total_cost = 0;

  for (int i = 0; i < len; i++)
    p[i] = i;

  for (int i = 0; i < len; i++)
    for (Node *temp = aList[i].head; temp != NULL; temp = temp->next)
      edge_count++;

  edge_count /= 2;
  array_of_edge = (EdgeNode *)malloc(sizeof(EdgeNode) * (edge_count + 100));

  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      if (path_cost[i][j] != 0 && path_cost[i][j] != INF &&
          aList[i].label < aList[j].label) {
        array_of_edge[temp_index].source = aList[i].label;
        array_of_edge[temp_index].source_index = i;
        array_of_edge[temp_index].destination = aList[j].label;
        array_of_edge[temp_index].destination_index = j;
        array_of_edge[temp_index].edge_cost = path_cost[i][j];
        temp_index++;
      }
    }
  }

  quickSort(array_of_edge, 0, edge_count - 1);

  for (int i = 0, temp_index = 0; temp_index < len - 1; i++) {
    temp = array_of_edge[i];
    if (find(p, temp.source_index) != find(p, temp.destination_index)) {
      fout << temp.source << " " << temp.destination << " " << temp.edge_cost
           << endl;
      Union(p, temp);
      temp_index++;
      total_cost += temp.edge_cost;
    }
  }

  return total_cost;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}