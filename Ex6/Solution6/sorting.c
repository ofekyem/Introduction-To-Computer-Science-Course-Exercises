#include "sorting.h"
/***********************
* Ofek Yemini
* 6
***********************/


/******************
* Function Name:quicksort
* Input: a pointer to certain type(void* arr),the starting place of the sort(int start),
the ending place of the sort(int stop),a "Swap function" of certain type(void(*swap)(void*, int, int)),
"compare function" of certain type(int(*compare)(void*, int, int))).

* Output:none
* Function Operation: the function will sort the array it got(arr) from the "start" index to the "stop" index
in the way of the "quick sort" algorithm
******************/
void quicksort(void* arr, int start, int stop, void(*swap)(void*, int, int), int(*compare)(void*, int, int)){
    
    if (start >= stop - 1) {
        
        return; //there is no space to sort because the start is equal or bigger to the (stop-1)
    } 

    int pivot = start;
    int j = start; 

    for (int i = start + 1; i < stop; i++) {
        if (compare(arr,i,pivot)<0) {
            //if the arr[pivot] is bigger than arr[i] (in general)
            j++;
            if (i != j) {//if it's not the same place
               
                swap(arr, i, j);//swap the places of arr[i] and arr[j]
            }
        }
    }
    
    swap(arr, start, j);//now we swap the places of arr[start] and arr[j]
    quicksort(arr, start, j,swap,compare); 
    quicksort(arr, j + 1, stop,swap,compare);  
    //continue to sort in a recursive way untill there is no space between start and stop
}



