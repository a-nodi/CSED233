#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}

void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;

    return;
}

void sortAlg::quickSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    // If swapping happens, print the array values after the swapping using "printArray(fout);"
    // You can freely add other functions (e.g., a function for partitioning) to either sort.cpp or sort.h.
    
    int pivot = arr[left];
    int l_mover_index = left + 1;
    int r_mover_index = left + 1;
    int rightmost_smallest_index = left;

    if (right - left <= 0) return; // If only one element exists in subarray
    
    if (right - left == 1) { // If two element exist in subarray
        if (pivot > arr[right]) {
            swap(&arr[left], &arr[right]);
            printArray(fout);
        }
        return;
    }
    
    // If more then 3 elements exist in subarray
    for (int i = left + 1; i <= right; i++) {
        l_mover_index = i;
        r_mover_index = i + 1;
        if (arr[l_mover_index] >= pivot) break;
    }
    
    // Do In-place partitioning
    while (r_mover_index <= right) {
        if (arr[r_mover_index] < pivot) {
            swap(&arr[r_mover_index], &arr[l_mover_index]);
            l_mover_index = r_mover_index;
            printArray(fout);
        }
        r_mover_index++;
    }
    
    // find rightmost smallest index
    for (int i = right; i >= left + 1; i--) {
        if (arr[i] < pivot) {
            rightmost_smallest_index = i;
            break;
        }
    }

    // Swap if rightmost smallest element is smaller than pivot
    if (rightmost_smallest_index != left) {
        swap(&arr[left], &arr[rightmost_smallest_index]);
        printArray(fout);
    }
    
    // Sort left and right subarray
    quickSort(fout, left, rightmost_smallest_index - 1);
    quickSort(fout, rightmost_smallest_index + 1, right);

    return;


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::merge(int left, int mid, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int* temp_arr = new int[right - left + 1];

    for (int i = left, left_barrier = left, right_barrier = mid + 1; i <= right; i++) {
        if (left_barrier <= mid && right_barrier <= right) { // Choose smaller elements from two subarrays.
            if (arr[left_barrier] < arr[right_barrier]) { // left < right
                temp_arr[i - left] = arr[left_barrier];
                left_barrier++;
            }
            else { // left > right
                temp_arr[i - left] = arr[right_barrier];
                right_barrier++;
            }
        }

        else { // Append leftover elements
            if (left_barrier <= mid) { // Left subarray is left.
                temp_arr[i - left] = arr[left_barrier];
                left_barrier++;
            }
            else if (right_barrier <= right) { // Right subarray is left.
                temp_arr[i - left] = arr[right_barrier];
                right_barrier++;
            }
        }
    }

    for (int i = left; i <= right; i++) { // Apply merged list.
        arr[i] = temp_arr[i - left];
    }

    delete[] temp_arr;

    return;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int mid = (left + right) / 2;

    if (left < right) { // If number of element is bigger then 1
        mergeSort(fout, left, mid);
        mergeSort(fout, mid + 1, right);
        merge(left, mid, right);
        printArray(fout);// DO NOT ERASE THIS LINE
    }

    return;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}
