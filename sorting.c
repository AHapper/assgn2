// Aneka Happer
// June 28, 2018
// Assgn2
// getopt.c

# include <stdlib.h>
# include <stdio.h>
# include <getopt.h>
#include <unistd.h>

#ifdef _INSTRUMENTED
#define SWAP(x,y) {uint32_t t = x; x = y; y = t; moveCount += 3;}  
#else
#define SWAP(x,y) {uint32_t t = x; x = y; y = t;}
#endif

// functions
void printArray(uint32_t a[], uint32_t length); // prints array elements

void minSort(uint32_t a[], uint32_t length); // min-sort

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last); // function used in min-sort

void bubbleSort(uint32_t a[], uint32_t length); // bubble sort

void insertionSort(uint32_t a[], uint32_t length); // insertion sort

void quickSort(uint32_t *a,uint32_t len); // quick sort - (credited to J. Happer)

void MergeSort(uint32_t *a, uint32_t len); // merge sort

void merge(uint32_t *a, uint32_t *aleft, uint32_t *aright, uint32_t lenleft, uint32_t lenright); // merges two "halves" array


// initialization for move/compare counts
unsigned long long int mcompare = 0;
unsigned long long int bcompare = 0;
unsigned long long int icompare = 0;
unsigned long long int qcompare = 0;
unsigned long long int Mcompare = 0;

unsigned long long int mmove = 0;
unsigned long long int bmove = 0;
unsigned long long int imove = 0;
unsigned long long int qmove = 0;
unsigned long long int Mmove = 0;

int main(int argc, char **argv){
    int c = 0; // options

    // allocate some memory for the array
    uint32_t *astation; // "stationary" array that holds random numbers so the array can reset
    astation = calloc(sizeof(uint32_t),100000);

    uint32_t *array;
    array = calloc(sizeof(uint32_t),100000);

    // initialize arguments
    int elements;
    int seed;
    int size;

    // initialize flags, used to mark which algorithms are to be implemented by using the getopt 
    // so they can be run later in the program 
    int Aflag = 0;
    int mflag = 0;
    int bflag = 0;
    int iflag = 0;
    int qflag = 0;
    int Mflag = 0;
    int pflag = 0;
    int rflag = 0;
    int nflag = 0;

    // options, getopt switch cases: the user can specify which sorting algorithms they would like to implement when 
    // running the program by including -A/m/b/i/q/M (each stands for specific alorigthm) and can assign parameters 
    // by including -p/r/n followed by an integer that specifies how many elements to print, the seed, and/or specify
    // how many elements should be in the array. The use of the flags allow each alorigthm to work independantly of 
    // one another, or in any set of combinations the user desires.
    while ((c = getopt(argc, argv, "AmbiqMp:r:n:")) != -1){
    
        switch(c){

            case 'A' : // enables all sorting algorithms
                Aflag++;
                break;

            case 'm' : // enables min sort
                mflag++;
                break;

            case 'b' : // enables bubble sort
                bflag++;                
                break;

            case 'i' : // enables insertion sort
                iflag++;
                break;

            case 'q' : // enables quick sort
                qflag++;
                break;

            case 'M' : // enables merge sort
                Mflag++;
                break; 

            case 'p' : // prints the first n elements of the array, where n is the input
                elements = atoi(optarg);
                pflag++;
                break;

            case 'r' : // sets the random seed to input 
                seed = atoi(optarg);
                rflag++;                
                break;

            case 'n' : // sets the array size to input
                size = atoi(optarg);
                nflag++;
                break;

            default : 
                printf("Error, it's probably invalid"); // prints when an invalid option is entered
                return 1; 
        }
    }

    // checks to see if inputs for parameters have been entered

    // sets n to input or default to determine how many elements to print
    uint32_t n;

    if(pflag == 1){
        n = elements;
    } 
    else if(nflag == 1){
        n = size;
    }
    else {
        n = 100;
    }

    // sets random seed to input or default 
    if(rflag == 1){
        srand(seed);
    } 
    else {
        srand(8222022);
    }

    // sets length of array to input or default 
    uint32_t length;

    if(nflag == 1){
        length = size;
    }
    else {
        length = 100;
    }

    // creates array of random numbers, used in all sorting algorithms 
    for(int i = 0; i < length; i++){

            astation[i] = rand()%16777216;
            array[i] = astation[i];

        } 


    // checks flags to determine which algorithms to implement, applies the algorithm to the random array, prints:  
    // the name of the algorithm, the data gathered (number of elements, moves, and, compares) and prints the sorted 
    // array. Then resets the array back to the random order so the next algorithm can sort. 
    if(Aflag == 1){
        // Min Sort
        minSort(array, length);

        printf("Min Sort: \n");
        printf("%d elements\n %llu moves\n %llu compares\n", length, mmove, mcompare);
        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }


        // Bubble Sort
        bubbleSort(array, length);

        printf("Bubble Sort: \n");
        printf("%d elements\n %llu moves\n %llu compares\n", length, bmove, bcompare);
        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }


        // Insertion Sort
        insertionSort(array, length);

        printf("Insertion Sort: \n");
        printf("%d elements\n %llu moves\n %llu compares\n", length, imove, icompare);
        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }


        // Quick Sort
        quickSort(array, length);

        printf("Quick Sort: \n"); 
        printf("%d elements\n %llu moves\n %llu compares\n", length, qmove, qcompare);
        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }


        // Merge Sort
        MergeSort(array, length);

        printf("Merge Sort: \n"); 
        printf("%d elements\n %llu moves\n %llu compares\n", length, Mmove, Mcompare);
        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }
    }

    if(mflag == 1){
        minSort(array, length);

        printf("Min Sort: \n");
        
        printf("%d elements\n %llu moves\n %llu compares\n", length, mmove, mcompare);

        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }

    } 
    
    if(bflag == 1){
        bubbleSort(array, length);

        printf("Bubble Sort: \n");

        printf("%d elements\n %llu moves\n %llu compares\n", length, bmove, bcompare);

        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }
    }
    
    if(iflag == 1){
        insertionSort(array, length);

        printf("Insertion Sort: \n");

        printf("%d elements\n %llu moves\n %llu compares\n", length, imove, icompare);

        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }
    }  
    
    if(qflag == 1){
        quickSort(array, length);

        printf("Quick Sort: \n");

        printf("%d elements\n %llu moves\n %llu compares\n", length, qmove, qcompare);

        printArray(array, n);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }
    } 
    
    if(Mflag == 1){
        MergeSort(array, length);

        printArray(array, n);

        printf("%d elements\n %llu moves\n %llu compares\n", length, Mmove, Mcompare);

        // reset
        for(int n = 0; n < length; n++){
            array[n] = astation[n];
        }
    } 

    return 0;
}

// function defs are below //

// prints array elements
void printArray(uint32_t a[], uint32_t len){ 
    
    printf("Sorted Array: ");
    for(int i = 0; i < len; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

}

// minSort: sort by repeatedly finding the least element (credited to D. Long-assgn2) 
// checks array for smallest element and swaps it with the first index, continues until sorted.  
void minSort(uint32_t a[], uint32_t length) 
{

    for (uint32_t i = 0; i < length - 1; i += 1) {

        uint32_t smallest = minIndex(a, i, length);

        if (smallest != i){
            SWAP(a[smallest], a[i]);
            mmove += 3;
        }

    }
    return; 
}

// minIndex: find the index of the least element, used in minSort to find where the smallest number in the array is 
// located so it can be placed at the front of the array.
uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last) 
{
    uint32_t smallest = first; // Assume the first is the least

    for (uint32_t i = first; i < last; i += 1)
    {
        smallest = a[i] < a[smallest] ? i : smallest; 
        mcompare++;
    }

    return smallest;
}

// bubbleSort: sort by comparing elements adjacent to each other
// compares a number in the array with the number to the left, if the number adjacent is larger, the two are swapped
void bubbleSort(uint32_t a[], uint32_t length) 
{
    int n = length;
    
    for(;;){

        int swapped = 0;

        for(int i = 0; i < n; i++){
            
            if(a[i-1] > a[i]){
                SWAP(a[i-1], a[i]);
                swapped = 1;
                bmove += 3;
                bcompare++;
            }
        }

        n = n - 1;
        bmove++;

        if(swapped == 0) break;
    }
}

// insertionSort: sort by inserting number into correct position in array
// goes through elements in array and determines where it should be placed in relation to the previous elements
void insertionSort(uint32_t a[], uint32_t length) 
{
    for(int i = 1; i < length; i++){

        int tmp = a[i];
        int j = i - 1; 

        while(j >= 0 && a[j] > tmp){
            a[j + 1] = a[j];
            j = j - 1;
            imove++;
            icompare++;
        }

        a[j + 1] = tmp;
        imove++;
    }
}

// quickSort: sorts by dividing the array based on a number and placing all smaller elements to the left
// divides the array into three parts: elements less than a number (mid) on the left, the number (in the middle),
// and elements greater than the nnumber to the right. It organizes the left/right sides by comparing adjacent 
// elements and swapping them to move them to the correct side of the number. Produces two "lists" that are again
// sorted recursively using the function quickSort.
void quickSort(uint32_t *a,uint32_t len){

    uint32_t *aleft = a;             //pointer to beginning of the array--doesn't change 
    uint32_t *aright = a + 1;        //pointer to beginning of the "right" side--this shifts
    uint32_t lenleft = 0;            //number of elements in the left array
    uint32_t lenright = len - 1;     //number of elements in the right array
    int k = 0;                       //array index of rightmost value in middle group
    int mid = 1;                     //number of elements (identical) in the middle group

    if(len == 0){                   //return if there are no array elements left to sort
        return;
    } 
   
    
    for(int i = 1; i < len; i++){

        //if the element is equal to the middle value, we need to move it to the right
        //of our current rightmost middle value
        if(a[k] == a[i]){           
            aright++;
            SWAP(a[k+1],a[i]);
            qmove += 3;
            k++;
            mid++;
            lenright--;
            qcompare++;                  
        }
        
        //if the element is bigger than our middle value, it is already on the correct
        //side so we don't need to do anything and just move on to check the next element
        else if(a[k] < a[i]){
            qcompare++;                  
        }

        //if the element is smaller than our middle value, we need to shift it to the left
        //array, which we do in two steps. For example, if our array currently looks like
        //3 5 7 7 8 9 4 5 and we are about to check i = 6 with k = 3, the first SWAP will get us
        //3 5 7 7 4 9 8 5 and the second SWAP will move the leftmost middle value to become the 
        //rightmost middle value:
        //3 5 4 7 7 9 8 5 and we move on to check the last value of the array. Note that now
        //our right array has become one smaller and the left array has become one bigger.
        else{
            SWAP(a[k+1],a[i]);
            qmove += 3;
            SWAP(a[k+1],a[k+1-mid]);
            qmove += 3;
            aright++;
            lenright--;
            lenleft++;
            k++;
            qcompare++;
        }
    }

    quickSort(aleft,lenleft);
    quickSort(aright,lenright);

}


// MergeSort: sorts by dividing the array in two, recursively sorting the halves, and merging the halves back together
// divides the array into left and right "lists", the left side is then spilt again by recursively implementing the
// MergeSort function and continues to do so until the left "list" is only one element long, then it does the same with 
// the right sides, merging the two sides together as it goes by using the function "merge" (defined below)
void MergeSort(uint32_t *a, uint32_t len){
    if(len > 1){
        // pointers to left and right arrays
        uint32_t *aleft = a;                 
        uint32_t *aright = a + len/2;   
        // lengths of left and right arrays          
        uint32_t lenleft = len/2;                
        uint32_t lenright = len - len/2;

        // allocates memory for the left and right arrays
        aleft = (uint32_t*) malloc(sizeof(uint32_t)*(len/2)); 
	    aright = (uint32_t*) malloc(sizeof(uint32_t)*(len - len/2)); 

        // fills left and right arrays
        for(int i = 0; i < len/2; i++){
            aleft[i] = a[i];
            Mmove++;
        }

        for(int i = len/2; i < len; i++){
            aright[i - len/2] = a[i];
            Mmove++;
        }
         
        // recursively sorts left and right arrays 
        MergeSort(aleft, lenleft);
        MergeSort(aright, lenright);
        merge(a, aleft, aright, lenleft, lenright);

        free(aleft);
        free(aright);
    }

    return;

}

// merge: merges the left and right "lists" produced by MergeSort, to organize the elements from least to greatest
// compares the elements from the left and right "lists", determines which is smaller, and places them back into 
// the array in the correct order. 
void merge(uint32_t *a, uint32_t *aleft, uint32_t *aright, uint32_t lenleft, uint32_t lenright){
    int i = 0;  // marks index for array                   
    int b = 0;  // marks index for left array
    int c = 0;  // marks index for right array

    // compares left and right arrays to determine least element
    while(b < lenleft && c < lenright){
        Mcompare++;
        if(aleft[b] <= aright[c]){
            a[i] = aleft[b];
            b++;
            Mmove++;
        }
        else {
            a[i] = aright[c];
            c++;
            Mmove++;
        }
        i++;
    }      

    // accounts for remaining elements 
    while(b < lenleft){
        a[i] = aleft[b];
        b++;
        i++;
        Mmove++;
    }

    // accounts for remaining elements 
    while(c < lenright){
        a[i] = aright[c];
        c++;
        i++;
        Mmove++;
    }
}
