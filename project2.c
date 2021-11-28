
#include <stdio.h>
#include <stdlib.h>
#define SEQ_SIZE 50
#define CACHE_SIZE 3
int page_reference_sequence[SEQ_SIZE];
int read_file(char *filename)  // read in the page reference sequence from the file
{
   FILE *input;
   int i, n;
   if ((input = fopen(filename, "r")) == NULL) {
      printf("The input file does not exist.\n");
      exit(1);
   }
   for (i = 0; i < SEQ_SIZE; i++) {
      if (fscanf(input, "%d", &page_reference_sequence[i]) == EOF) {  // end of file
         n = i;  // total number of page reference
         i = SEQ_SIZE;  // stop reading from file
      }
   }
   fclose(input);
   printf("Input page reference sequence: ");
   for (i =0; i < n; i++) {
      printf("%d ", page_reference_sequence[i]);
   }
   printf("(total %d references)\n", n);
   return n;  // return the total number of page reference
}

int check_if_in_array(int arr[], int num) {
    for (int i = 0; i < 3; i++)
    {
        if (arr[i] == num){
            return 1;
        }
    }
    return 0;    
}

void print_array(int arr[]){
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

int find_in_array(int arr[], int num) {
    for (int i = 0; i < 3; i++)
    {
        if (arr[i] == num)
        {
            return i;
        }        
    }

    return 9;    
}

void FIFO(int n)
{
   // write your own code for the FIFO policy
   // based on the input file content, print out a table similar to the Figure 22.2
    int i;
    int fifoarr[3];
    int index;

    printf("FIFO  page reference sequence: ");
    for (i = 0; i < n; i++) {
        printf("%d ", page_reference_sequence[i]);
    }
    printf("(total %d references)\n", n);

    for (i = 0; i < n; i++)
    {
        if (i < 3) {
            fifoarr[i] = page_reference_sequence[i];
        }
        else if (check_if_in_array(fifoarr, page_reference_sequence[i]) == 0)
        {
            fifoarr[0] = fifoarr[1];
            fifoarr[1] = fifoarr[2];
            fifoarr[2] = page_reference_sequence[i];
        }   
        print_array(fifoarr);           
    }

    print_array(fifoarr);   

}

void LRU(int n)
{
    // write your own code for the LRU policy
    // based on the input file content, print out a table similar to the Figure 22.5
    int i;
    int lruarr[3];
    int index;
    printf("LRU   page reference sequence: ");
    for (i = 0; i < n; i++) {
        printf("%d ", page_reference_sequence[i]);
    }
    printf("(total %d references)\n", n);

    for (i = 0; i < n; i++)
    {
        if (i < 3) {
            lruarr[i] = page_reference_sequence[i];
        }
        else if (check_if_in_array(lruarr, page_reference_sequence[i]) == 1)
        {
            index = find_in_array(lruarr, page_reference_sequence[i]);
            if (index == 0) {
                lruarr[0] = lruarr[1];
                lruarr[1] = lruarr[2];
                lruarr[2] = page_reference_sequence[i];
            }
            if (index == 1) {                
                lruarr[1] = lruarr[2];
                lruarr[2] = page_reference_sequence[i];
            }
        } 
        else if (check_if_in_array(lruarr, page_reference_sequence[i]) == 0)
        {
            lruarr[0] = lruarr[1];
            lruarr[1] = lruarr[2];
            lruarr[2] = page_reference_sequence[i];
        }
          
        print_array(lruarr);           
    }

    print_array(lruarr);   
}

int main(int argc, char *argv[])
{
   int i, n;
   if (argc != 2) {
      printf("Usage: %s input_filename\n", argv[0]);
      exit(1);
   }
   n = read_file(argv[1]);
   FIFO(n);
   LRU(n);
}
