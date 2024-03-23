#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct MemoryBlock {
    int address;
    int size;
    int occupied;

    struct MemoryBlock *next;
} memoryBlock;

memoryBlock *head = NULL; 

int Menu() {
    int choice;

    printf("\n--------MENU--------\n");
    printf("1-Create Memory Block.\n");
    printf("2-Display Memory Block.\n");
    printf("3-First Fit Search.\n");
    printf("4-Best Fit Search.\n");
    printf("5-Worst Fit Search.\n");
    printf("6-Allocate Memory.\n");
    printf("7-Deallocate Memory.\n\n");
    printf("0-End Program.\n");

    printf("\n--> Your Choice : ");
    scanf("%d", &choice);
    printf("\n");

    return choice;
}

memoryBlock *createNode(int newSize, int isOccupied) {
    memoryBlock *temp = (memoryBlock *)malloc(sizeof(memoryBlock));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    temp->size = newSize;
    temp->occupied = isOccupied;
    temp->next = NULL;

    printf("\n-->Node Created Successfully!!\n\n");
    return temp;
}

void createMemoryBlock(int sizeNewBlock, int isOccupied) {
    int adrsNew;
    int calcAddressTotal;
    memoryBlock *ptr = head;
    memoryBlock *ptr2 = head;
    memoryBlock *newNode;

    if(head==NULL){
        printf(" -> Enter the Address : ");
        scanf("%d",&adrsNew);
        head = createNode(sizeNewBlock, isOccupied);
        head->address = adrsNew;
        printf("-->Head Created Successfully!!\n");
    }else{

        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = createNode(sizeNewBlock, isOccupied);


        calcAddressTotal = 0;
        while (ptr2->next != NULL) {
            //printf("calcAdd = %d\n",calcAddressTotal);
            calcAddressTotal = ptr2->address;
            //printf("calcAdd = %d\n\n",calcAddressTotal);
            ptr2 = ptr2->next;
        }

        updateAdrs(ptr->next, calcAddressTotal+sizeNewBlock);
    }
}

void updateAdrs(memoryBlock *ptr, int newAddress){

    ptr->address = newAddress;

    printf("New Memory Block : \n");
    printf("-Address = %d | Occupied = %d | Size = %d\n\n", ptr->address, ptr->occupied, ptr->size);
}



void displayMemory(memoryBlock *head) {
    memoryBlock *temp2 = head;
    printf("\n-----------------Memory---------------------\n\n");
    while (temp2 != NULL) {
        printf("Address : %d | Occupied : %d | Size : %d\n", temp2->address, temp2->occupied, temp2->size);
        temp2 = temp2->next;
    }
    printf("\n--------------------------------------------\n");
}



memoryBlock *firstFit( int sizeOfNewElement ) {
    memoryBlock *ptr = head;
    
    while(ptr!=NULL){
        if(sizeOfNewElement<=ptr->size && ptr->occupied != 1){
            printf("--First Fit Search Successfull....\n");
            printf("Memory Block Located : \n");
            printf(" -Address : %d | Occupied : %d | Size : %d\n", ptr->address, ptr->occupied, ptr->size);
            return ptr;
        }
        ptr=ptr->next;
    }
    if(ptr==NULL) {
        printf("--First Fit Search Unsuccessfull....\n");
        printf("--Unable to locate the memory block.\n\n");
    }

}

int main() {
    int choice;
    int newSize;

    int firstFitValue;
    int isOccupied;

    memoryBlock *ptr;

    do {
        choice = Menu();

        switch (choice) {
            case 1:
                printf(" -> Enter the new Size : ");
                scanf("%d", &newSize);
                printf(" -> Is Occupied [ 1 for yes || 0 for no ] : ");
                scanf("%d", &isOccupied);
                createMemoryBlock(newSize, isOccupied);
                printf("\n");
                break;
            case 2:
                displayMemory(head);
                printf("\n");
                break;
            case 3:
                printf(" -> Enter Size to search : ");
                scanf("%d",&firstFitValue);
                printf("\n");
                ptr = firstFit(firstFitValue);
                break;
            case 4:
                printf("---Not Built Yet---\n");
                break;
            case 5:
               
                printf("---Not Built Yet---\n");
                break;
            case 6:
                printf("---Not Built Yet---\n");
                break;
            case 7:
                printf("---Not Built Yet---\n");
                break;

            default:
                printf("--Choose a correct number in the list pls!!\n");
                break;        
        }
    } while (choice != 0);

    return 0;
}
