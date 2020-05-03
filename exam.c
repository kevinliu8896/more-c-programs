// Name: Kevin Liu
// Student ID: 105191861
// File Name: final.c
// Academic Integryity filed has been signed in a pdf file submitted along with this file
#include <stdio.h> // input header files
#include <stdlib.h> // standard library header file to use functions like malloc,calloc,free,etc..
#define MAX_SIZE 19

struct ItemStruct{ // data structure called ItemStruct
  int ItemCode;
  int NumItems;
  int total; // create int total to aid in daily output summary report
  float ItemPrice;
  float TotSales;
  char ItemName[17];
  struct ItemStruct * nextItem;
};
struct CategoryName { // data structure called CategoryName
  int code;
  char value[MAX_SIZE];
  struct CategoryName * next;
};

//FUNCTION PROTOTYPES:*****************************************************
void insertAtEnd(struct ItemStruct **head,struct ItemStruct *newItem); // function that insertes a node at the end
void swap(struct ItemStruct *first,struct ItemStruct *sec); // swap function to sucesfully carry out bubble sort
void bSort(struct ItemStruct *head); // bubble sort function prototype
void ClearList(struct ItemStruct **head); // clear list function that will be use free() from standard library header file to clear the linkedlist
void Receipt(struct ItemStruct **r,struct ItemStruct **r2, int c); // function prototype to print totals, codes, item names, price, number of items, and total sales
void Inventory(struct ItemStruct **head,struct ItemStruct **head2); // function prototype for Inventory
//*************************************************************************

int main() { // beginning of main method
      struct ItemStruct * List = NULL; // creates empty category list
      FILE * fptr; //create file
      fptr = fopen("CategoryName.dat","r"); // Case 1: Input File Name: CategoryName.dat
      while(!feof(fptr)){ // while note end of file
        struct ItemStruct *Items = (struct ItemStruct *) malloc(sizeof(struct ItemStruct));
        fscanf(fptr, "%d\t%[^\n]", &(Items->ItemCode), (Items->ItemName));
        insertAtEnd(&List,Items); // call inserAtEnd function to inser a node at the end of the linked list
    }
  struct ItemStruct *head = NULL; // create empty linked list
  FILE * fptr2; // create file pointer fptr2 for a file pointer to CodeNamePrice.dat
  fptr2 = fopen("CodeNamePrice.dat", "r"); // Case 2: Input File Name: CodeNamePrice.dat
  while(!feof(fptr2)) {
    struct ItemStruct * Item = (struct ItemStruct *)malloc(sizeof(struct ItemStruct));
    fscanf(fptr2, "%d\t%[^\t]\t%f", &(Item->ItemCode), (Item->ItemName), &(Item->ItemPrice));
    insertAtEnd(&head,Item); // call inserAtEnd function to insert node at the end of the linked list
  }

  struct ItemStruct *Daily = NULL; // creating empty dailytransactions list
  FILE *fptr3; // create file pointer fptr3 is a file pointer for DailyTransactions.dat
  fptr3 = fopen("DailyTransactions.dat", "r");
  int c = 0; // create a counter variable starting at 1
    while(!feof(fptr3)){
        struct ItemStruct *item = (struct ItemStruct*) malloc(sizeof(struct ItemStruct));
        fscanf(fptr3,"%d%d", &(item->ItemCode), &(item->NumItems));
        if(item->ItemCode == 000){ //A final code of 000 (or just 0) denotes the end of the customer purchase list.
        fscanf(fptr3, "%d",&item->NumItems);
        Receipt(&Daily,&head,++c); // CALL RECEIPT FUNCTION

        Daily = NULL;// set Daily to NULL
        }
            // print out reciept
        else {
              insertAtEnd(&Daily,item);//call inserAtEnd function to inser a node at the end of the linked list
            // sort the list
            bSort(Daily); // call bSort function to use bubble sort algorithm
            } // end of else
    }
    Inventory(&List,&head); // call Inventory function
    int sold = 0;
      float amount = 0.0;
    printf("\nDaily Summary Report:\n");
    printf("Code\t\tCategory Name\t\t#Items Sold\t\tTotal Sales Amount\n"); // print layout of report
    while(List != NULL){ // while List not equal to NULL execute code..
        printf("%d\t\t\t%-19s\t\t%d\t\t\t%.2f\n\n",List->ItemCode, List->ItemName,List->total,List->ItemPrice); // print statement for values and stirng formatting to organize report
        sold += List->total; // calculations for total customers, items sold, and total sales
        amount += List->ItemPrice;
        List = List->nextItem;
    }
    printf("Total Customers: \t\t%d\n",c);
    printf("Total Items Sold: \t\t%d\n",sold);
    printf("Total Sales:      \t\t%.2f\n",amount);
    ClearList(&Daily); // clear list to deallocate memory
  //THE NEXT 3 LINES OF CODE WILL CLOSE THE FILES*************************
  fclose(fptr);
  fclose(fptr2);
  fclose(fptr3);
  //************************************************************************

} // end of main method

// FUNCTIONS TO CARRY OUT CERTAIN ASPECTS OF THE PROGRAM
void insertAtEnd(struct ItemStruct **head,struct ItemStruct *newItem) { // insert at end function
  if (*head == NULL) { // if *head equals NULL *head is set to value of newItem
    *head = newItem;
    return; //return
  }
  struct ItemStruct *temp; // declare temporary variable of type struct ItemStruct
  temp = *head; // set temp equal to *head
  while(temp->nextItem != NULL) {
    temp = temp->nextItem; // while temp points to nextItem does not equal NULL temp becomes temp->nextItem
  }
  temp->nextItem = newItem; // set temp pointing to nextItem to equal the newItem
} // end insertAtEnd function

void swap(struct ItemStruct *first,struct ItemStruct *sec){ // swap first and second node function
    int temp = first->ItemCode; // create integer temp and set it to first node pointing to ItemCode
    first->ItemCode = sec->ItemCode; // first node is pointing to ItemCode which is set to second node(sec) pointing to ItemCode
    sec->ItemCode = temp; // secon node (sec) poionting to ItemCode which becomes temp
 // the next few lines will  be the swapping process to sucesfully carry out bubble sort function below
    temp = first->NumItems;
    first->NumItems = sec->NumItems;
    sec->NumItems = temp;
} // end swap function

void bSort(struct ItemStruct *head) { // function to sort from smallest to biggest
    int swap2; // create a variable to keep track of the nodes being swapped
    struct ItemStruct *ptr,*fp=NULL;
    if (head == NULL) // if head is equal to exactly NULL then...
        return;
    do { // do while
        swap2 = 0; // set swap2 to 0
        ptr = head;  // set ptr equal to head
        while (ptr->nextItem != fp) {  // while ptr pointing to nextItem does not equal fp then..
            if (ptr->ItemCode > ptr->nextItem->ItemCode) {  // if ptr pointing to ItemCode is bigger than ptr pointing to next which points to ItemCode then..
                swap(ptr,ptr->nextItem);  // call swap function to swap nodes
                swap2 = 1; // set swap2 to 1 when nodes are sucesfully swapped
            } // end if
            ptr=ptr->nextItem; // ptr points to nextItem
        } // end while
        fp = ptr; // fp equals ptr
    }//  end do while
    while(swap2);
}// end of bSort function

void ClearList(struct ItemStruct **head) { // function made to deallocate all memory locations
  struct ItemStruct * current = *head; // create variable *current of type struct ItemStruct and set it to *head
  while(current!= NULL) { // while current!=NULL do code below..
    current = current->nextItem;
    free(*head); // deallocates all memory stored in *head
    *head = current; // set *head to current
  } // end while
} // end of ClearList function

void Receipt(struct ItemStruct **r,struct ItemStruct **r2, int c){ // this function is used to print out the receipt:
    int totalI = 0;// create a integer value called total to keep track of total items
    float totalP = 0.00;// create a integer value called total to keep track of total price
    int totalItems;
    printf("Customer Receipt # %d\n",c); // print customer receipt and the number which is c(counter variable for customer #)
    printf("Code\tItem Name\t\t\tPrice\t\tNum Item\tTotSale\n");// string formatting to display item nam tab, price tab, num item tab, and totsale tab
    struct ItemStruct *temp4r = *r, *temp4i = *r2; // declare variables of type struct ItemStruct
    while(temp4r != NULL){
        if(temp4r->ItemCode != temp4i->ItemCode){ // if temp4r points to ItemCode is NOT EQUAL TO  temp4i pointing to ItemCode
            temp4i = temp4i->nextItem; // set temp4i to temp4i poinintg to nextItem
            continue; // continue through the if statment
        }
        totalItems = 0; // set totalItems to 0
        totalI = totalI + temp4r->NumItems; // totalI is equal to value of totalI plus temp4r poinitng to NumItems
        totalItems = totalItems + temp4r->NumItems; // totlaItems is equal to totalItems plus temp4r poinintg to NumItems
        temp4i->NumItems += totalItems; // temp4i->NumItems is incremented by the value of totalItems
        totalP = totalP + (temp4i->ItemPrice * temp4r->NumItems); // calculation for totalP
        printf("%d\t\t%-12s\t\t%.2f\t\t%d\t\t\t%.2f\t\t\n", (temp4r->ItemCode), (temp4i->ItemName),(temp4i->ItemPrice), (temp4r->NumItems),(temp4i->ItemPrice * temp4r->NumItems)); // string formatting for values
        temp4r= temp4r->nextItem; //set temp4r to temp4r points to nextItem
        temp4i = temp4i->nextItem;// set temp4i to temp4i poinintg to nextItem
    }
    printf("\n\t\t\t\t\t\t\tTOTALS:\t\t%d\t\t\t%.2f\n",totalI,totalP ); // string formatting to print out total items and total of the price
}
void Inventory(struct ItemStruct **head,struct ItemStruct **head2){ // Inventory function
  FILE *fptr4; // file pointer called fptr4
  char path[20];
  int totalItemSold; // integer type called totalItemSold
  float totalSales;// float value that will be rounded up to .2f later in print statements called totalSales
  struct ItemStruct *c =*head, *i = *head2; // create variables of type struct ItemStruct
  while(c != NULL) { // while c(category) is not NULL
    sprintf(path, "Inventory%d.dat", c->ItemCode); // concatenate
    fptr4 = fopen(path, "wb"); // open file pointer fptr4 to a written binary
    if (i->ItemCode < c->ItemCode + 100) { // if statement
      printf("\nCategory Name: %s\n", c->ItemName); // print statements for the next lines
      printf("Category Code: %d\n", c->ItemCode);
      printf("Code\t\tItem Name\t\tNum Item\tTotSale\n");
      totalItemSold = 0; // set totalItemSold to 0 and float value of totalSales to 0.0
      totalSales = 0.0;
      while(i!= NULL) { // while i(inventory) does not equal NULL.. execute code below
         if ((i->ItemCode > c->ItemCode) && i->ItemCode < c->ItemCode+100) { // if statemnet..
          totalItemSold += i->NumItems; // calculation
          totalSales += i->ItemPrice * i->NumItems;//calculation
          c->total = totalItemSold;
          c->ItemPrice = totalSales;
          printf("%d\t\t\t%-12s\t\t%d\t\t%.2f\n",i->ItemCode,i->ItemName,i->NumItems,i->NumItems * i->ItemPrice); // print statement and string formatting
          fwrite(i,sizeof(struct ItemStruct),1, fptr4);
        i=i->nextItem; // i points to nextItem in the linked list
      }
      else { // else break
        break;
      } //end else
    } // end while
    printf("\nTOTAL ITEMS SOLD:\t%d\nTOTAL SALES:\t%.2f\n",totalItemSold,totalSales); // print statement and formatting
  } // end if
    c = c->nextItem; // c(category) points to nextItem
   } // end while
  fclose(fptr4); // close fptr4 (file pointer)
} // end Inventory function

// END OF PROGRAM CHECK ACADEMIC INTEGRITY PDF FILE
