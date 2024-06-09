#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Define node
typedef struct node {
    int value;
    struct node* next; // Pointer that points to the next node
} NODE;

// Define header of linked list
typedef struct {
    int count; // # of elements in the current list
    NODE* head; // Pointer that points to the head node of list
    NODE* tail; // Pointer that points to the tail node of list
} LIST;

// Define header of stack
typedef struct {
    int count; // # of elements in the current stack
    NODE* top; // Pointer that points to the top node of stack
} STACK;

// Define header of queue
typedef struct {
    int count; // # of elements in the current queue
    NODE* front; // Pointer that points to the front node of queue
    NODE* rear; // Pointer that points to the rear node of queue 
} QUEUE;

// Define header of circular queue
typedef struct {
    int count; // # of elements in the current circular queue
    int queue_size; // Size of queue
    int front; // Array index that points to the front value of circular queue
    int rear; // Array index that points to the rear value of circular queue
    int* arr; // Array that contains circular queue values
} CIRCULAR_QUEUE;

/* 
    [Task 1] Choose the TIGHT bound of the following arraySum function
    
    *arraySum*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n >= 1 integers
        Output
        - int: Sum of given array A
	int arraySum(int n, int* A) {
	    int currSum = 0;
	    for (int i = 0; i < n; i++)
	        currSum += A[i];
	    return currSum;
	}


    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
    int answer = 2;  // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the TIGHT bound of the following primeSearch function

    *primeSearch*
        Input
        - int n: input number for ending range
        Output
        - int numPrimes: The total number of prime numbers less than n
	int primeSearch(int n) {
	    int numPrimes = 0;
	    int ctr = 0;
	    for (int i = 0; i < n; i++) {
	        for(int j = 2; j <= sqrt(i); j++) {
	            if(i % j == 0) {
			ctr++;
			break;
	            }
	        }
		if(ctr == 0 && i > 1)
	            numPrimes++;
	        ctr=0;
	    }
	    return numPrimes;
	}


    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n^(1/2) )
        4: O( n*n^(1/2) )
*/
void task_2(ofstream &fout) {
    int answer = 4;  // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the list.
        An user can insert or delete an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,index): insert “# of elements in the current list” at the
   index in the list. index indicates zero-based index.
        - (‘delete’,index): delete an element at the index in the list. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/

NODE* locate_node(int index, LIST* plist) {
    /*
    * The function that locates index th node of linked list
    * @param: int index: Index of target node
    * @param: LIST* plist: Pointer of linked list 
    * @return: temp: Pointer of target node
    */

    NODE* temp = plist->head;
    
    // Walk node
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp; // Return target node
}

bool insert_node(int value, int index, LIST* plist) {
    /*
    * The function that inserts node in linked list
    * @param: int value: Value to be inserted into linked list
    * @param: int index: Index of target node
    * @param: LIST* plist: Pointer of linked list
    * @return: bool is_success: true if insertion of node was successful, else false
    */
    
    NODE* temp = new NODE;
    NODE* pre_node;
    NODE* cur_node;

    // Initialize node
    temp->value = value;
    temp->next = NULL;
    
    if (!temp) { // Dynamic allocation failed
        return false;
    }
    else if (0 <= index && index <= plist->count) { // Vaild index
        if (plist->count != 0) { // Not empty list
            if (index == 0) { // Insert as first node
                cur_node = locate_node(0, plist);
                temp->next = cur_node;
                plist->head = temp;
            }
            else if (index == plist->count) { // Insert as last node
                pre_node = locate_node(plist->count - 1, plist);
                pre_node->next = temp;
                plist->tail = temp;
            }
            else { // Insert as intermediate node
                pre_node = locate_node(index - 1, plist);
                cur_node = pre_node->next;
                pre_node->next = temp;
                temp->next = cur_node;
            }
        }
        else { // Empty list
            plist->head = temp;
            plist->tail = temp;
        }
        plist->count++; // Update count
    }
    else { // Index out of range
        delete temp; // Free node
        return false; // Return error
    }
    return true; // Return success
}

bool delete_node(int index, LIST* plist) {
    /*
    * The function that deletes node in linked list
    * @param: int index: Index of target node
    * @param: LIST* plist: Pointer of linked list
    * @return: bool is_success: true if deletion of node was successful, else false
    */

    NODE* pre_node = NULL;
    NODE* cur_node = NULL;
    NODE* post_node = NULL;

    if (0 <= index && index < plist->count) { // Vaild index
        cur_node = plist->head;
        post_node = cur_node->next;
        
        // Walk node
        for (int i = 0; i < index - 1; i++) { 
            pre_node = cur_node;
            cur_node = post_node;
            post_node = post_node->next;
        }

        if (pre_node == NULL && post_node == NULL) { // Only one node in list
            plist->head = NULL; // 
            plist->tail = NULL;
        }
        else if (pre_node == NULL) { // Delete first node
            plist->head = cur_node->next; // Link 
        }
        else if (post_node == NULL) { // Delete last node
            plist->tail = pre_node;
            pre_node->next = NULL;
        }
        else { // Delete intermidiate node
            pre_node->next = cur_node->next;
        }

        plist->count--; // Update count
        delete cur_node; // Free node
    }
    else { // Index out of range
        return false; // Return error
    }
    return true; // Return success
}

void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  answer = "";
  LIST list;
  NODE* node = NULL;
  bool is_success = true;

  // initialize list
  list.count = 0;
  list.head = NULL;
  list.tail = NULL;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("insert") == 0) {
        is_success = insert_node(list.count, value, &list); // Insert node
    } else if (command.compare("delete") == 0) {
        is_success = delete_node(value, &list); // Delete node
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }

    if (!is_success) { // Operation has failed
        break;
    }
  }

  if (is_success) { // Operations were all successful
      
      // Print values in linked list
      node = list.head;
      for (int i = 0; i < list.count; i++) {
          answer += to_string(node->value);
          answer += " ";
          node = node->next;
      }
  }
  else {
      answer = "error";
  }

  // Free all nodes in linked list
  while (list.count > 0) {
      delete_node(list.count - 1, &list);
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   stack is empty, and the “top” operation is called, then print “-1”, If “pop”
   operation from the empty stack then print “error”

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack (integer is
   always positive)
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack
*/

bool push(int value, STACK* pstack) {
    /*
    * The function that performs 'Push' operation on the stack
    * @param: int value: Value to be pushed into linked list
    * @param: STACK* pstack: Pointer of stack
    * @return: bool is_success: true if push was successful, else false
    */

    NODE* temp = new NODE;

    if (!temp) { // Dynamic allocation failed
        return false; // Return error
    }
    else {
        temp->next = pstack->top; // Link top of stack to node
        temp->value = value; // Put value into node
        pstack->top = temp; // Link temp to top of stack
        pstack->count++; // Update count
    }

    return true; // Return success
}

bool pop(STACK* pstack) {
    /*
    * The function that performs 'Pop' operation on the stack
    * @param: STACK* pstack: Pointer of stack
    * @return: bool is_success: true if pop was successful, else false
    */
    
    NODE* temp;
    
    if (pstack->count == 0) { // Stack is empty
        return false;  // Return error
    }
    else {
        temp = pstack->top; // Top node to be poped
        pstack->top = temp->next; // Link node to top of stack
        pstack->count--; // Update count

        delete temp; // Free node
    }

    return true; // Return success
}

int top(STACK* pstack) {
    /*
   * The function that performs 'Top' operation on the stack
   * @param: STACK* pstack: Pointer of stack
   * @return: int value: Value of top node 
   */

    NODE* temp;

    if (pstack->count == 0) { // Stack is empty
        return -1; // Return empty
    }
    else {
        temp = pstack->top; // Top node
        return temp->value; // Return value of top node
    }
}

void task_4(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  answer = "";
  STACK stack;
  bool is_success = true;

  // initialize queue
  stack.count = 0;
  stack.top = NULL;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("push") == 0) {
        is_success = push(value, &stack); // Push value

    } else if (command.compare("pop") == 0) {
        is_success = pop(&stack); // Pop value

    } else if (command.compare("top") == 0) {
        answer += to_string(top(&stack)); // Print value of top node
        answer += " ";

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }

    if (!is_success) { // Operation has failed 
        break;
    }
  }

  if (!is_success) { // Operation has failed
      answer = "error";
  }

  while(stack.count > 0){ // Free all nodes in stack
      pop(&stack);
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Queue

    Description:
        Implement a function which shows the value of a queue after the sequence
   of arbitrary queue operation. If the queue after the operations is empty,
   print “empty”. If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the queue from the head to the tail, in a string separated
   with spacebar
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on an empty queue
*/

bool enqueue(int value, QUEUE* pqueue) {
    /*
    * The function that performs 'Enqueue' operation on the queue
    * @param: int value: Value to be enqueued into queue
    * @param: QUEUE* pqueue: Pointer of queue
    * @return: bool is_success: true if enqueue was successful, else false
    */
    
    NODE* temp = new NODE;
    
    if (!temp) { // Dynamic allocation failed
        return false; // Return error
    }
    else {
        temp->value = value;
        temp->next = NULL;

        if (pqueue->count == 0) { // Queue is empty
            pqueue->front = temp;
            pqueue->rear = temp;
        }
        else {
            pqueue->rear->next = temp;
            pqueue->rear = temp;
        }
        pqueue->count++; // Update count
    }

    return true; // Return success
}

bool dequeue(QUEUE* pqueue) {
    /*
    * The function that performs 'Dequeue' operation on the queue
    * @param: QUEUE* pqueue: Pointer of queue
    * @return: bool is_success: true if dequeue was successful, else false
    */
    
    NODE* temp;

    if (pqueue->count == 0) { // Queue is empty
        return false; // Return error
    }

    temp = pqueue->front;
    
    if (pqueue->count == 1) { // Only one node in queue
        pqueue->front = NULL;
        pqueue->rear = NULL;
        pqueue->count--;
    }
    else {
        pqueue->front = temp->next;
        pqueue->count--;
    }

    delete temp; // Free node

    return true; // Return success
}


void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  answer = "";
  QUEUE queue;
  NODE* node;
  bool is_success = true;

  queue.count = 0;
  queue.front = NULL;
  queue.rear = NULL;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;

    if (command.compare("enqueue") == 0) {
        is_success = enqueue(value, &queue); // Enqueue value
    } else if (command.compare("dequeue") == 0) {
        is_success = dequeue(&queue); // Dequeue value
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }

    if (!is_success) { // Operation has failed
        break;
    }
  }

  if (is_success) { // Operations were all successful
      
      // Print values in linked list
      if (queue.count > 0) {
          node = queue.front;
          for (int i = 0; i < queue.count; i++) {
              answer += to_string(node->value);
              answer += " ";
              node = node->next;
          }
      }
      else { // Queue is empty
          answer = "empty";
      }
  }
  else {
      answer = "error";
  }

  // Free all nodes in queue
  while (queue.count > 0) {
      dequeue(&queue);
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Circular Queue

    Description:
        - a.	Implement a function which shows the value in the circular queue
   from the head to tale. If “enqueue” operates on full or “dequeue” operates
   on an empty queue, no change would happen.

    Input:
        Sequence of commands, which is one of the following,
        -(‘enqueue’,integer): enqueue integer into the current queue
        -(‘dequeue’,NULL): dequeue integer into the current queue

    Output:
        - Values in the queue from the head to the tail, in a size of 4.
   string separated with the spacebar, empy memory shows NULL -	No
   pointer movement if dequeue on empty, enqueue on full queue

*/

bool circular_enqueue(int value, CIRCULAR_QUEUE* circular_queue) {
    /*
    * The function that performs 'Enqueue' operation on the circular queue
    * @param: int value: Value to be enqueued into circular queue
    * @param: CIRCULAR_QUEUE* circular_queue: Pointer of circular queue
    * @return: bool is_success: true if enqueue was successful, else false
    */
    
    if (circular_queue->count == circular_queue->queue_size) { // Circular queue is full
        return true; // Return success
    }
    else {
        // Enqueue value and move rear pointer
        circular_queue->arr[circular_queue->rear] = value;
        circular_queue->rear = (circular_queue->rear + 1) % circular_queue->queue_size;
        circular_queue->count++; // Update count
    }
    
    return true; // Return success
}

bool circular_dequeue(CIRCULAR_QUEUE* circular_queue) {
   /*
   * The function that performs 'Dequeue' operation on the circular queue
   * @param: CIRCULAR_QUEUE* circular_queue: Pointer of circular queue
   * @return: bool is_success: true if dequeue was successful, else false
   */

    if (circular_queue->count == 0) { // Circular queue is empty
        return true; // Return success
    }
    else {
        // Dequeue value and move front pointer
        circular_queue->arr[circular_queue->front] = 0;
        circular_queue->front = (circular_queue->front + 1) % circular_queue->queue_size;
        circular_queue->count--; // Update count
    }
    
    return true; // Return success
}


void task_6(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;
  int queue_size = 4;
   
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  answer = "";
  CIRCULAR_QUEUE circular_queue;
  bool is_success = true;

  // Initialize circular queue
  circular_queue.count = 0;
  circular_queue.front = 0;
  circular_queue.rear = 0;
  circular_queue.queue_size = queue_size;
  circular_queue.arr = new int[queue_size];

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("enqueue") == 0) {
        is_success = circular_enqueue(value, &circular_queue); // Enqueue value

    } else if (command.compare("dequeue") == 0) {
        is_success = circular_dequeue(&circular_queue); // Dequeue value

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }

    if (!is_success) { // Operation has failed
        break;
    }
  }

  if (is_success) { // Operations were all successful
      
      // Print values in circular queue
      for (int i = circular_queue.front; i < circular_queue.front + circular_queue.count; i++) {
          answer += to_string(circular_queue.arr[i % circular_queue.queue_size]);
          answer += " ";
      }
  }
  else {
      answer = "error";
  }

  // Free circular queue
  delete circular_queue.arr;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 6]" << endl;
  fout << answer << endl;
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    try {
      instr_seq = ParseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 0:
    task_1(fout);

    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq_4);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}

