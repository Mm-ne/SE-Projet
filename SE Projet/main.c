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

/*
typedef struct QueueNode {
    memoryBlock *block;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *allocationQueue = NULL;
*/

int Menu() {
    int choice;

    printf("\n--------MENU--------\n");
    printf("1-Create Memory Block.\n");
    printf("2-Display Memory Block.\n");
    printf("3-First Fit Search.\n");
    printf("4-Best Fit Search.(Still on Work) \n");
    printf("5-Worst Fit Search.(Still on Work)\n");
    printf("6-Allocate Memory.\n");
    printf("7-Deallocate Memory.\n");
    printf("8-Deallocate Memory using FIFO.\n\n");
    printf("0-End Program.\n");

    printf("\n--> Your Choice : ");
    scanf("%d", &choice);
    printf("\n");

    return choice;
}



/**************Creation Section***************/
memoryBlock *createNode(int newSize, int isOccupied) {
    memoryBlock *temp = (memoryBlock *)malloc(sizeof(memoryBlock));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    temp->size = newSize;
    temp->occupied = isOccupied;
    temp->next = NULL;

    //printf("\n--> Node Created Successfully!!\n\n");
    return temp;
}
///////////////////////////
void upAdsMem(){
    memoryBlock* ptr = head;
    int holdAddress = head->address;

    while(ptr->next!=NULL){
        ptr->next->address = ptr->address + ptr->size;

        ptr=ptr->next;
    }

}
void updateAdrs(memoryBlock *ptr, int newAddress){

    ptr->address = newAddress;

    printf("\n--New Memory Block : \n");
    printf("  -Address = %d | Occupied = %d | Size = %d\n\n", ptr->address, ptr->occupied, ptr->size);
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
        printf("\n--> Head Created Successfully!!\n");
    }else{

        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = createNode(sizeNewBlock, isOccupied);


        calcAddressTotal = 0;
        while (ptr2->next != NULL) {
            //printf("calcAdd = %d\n",calcAddressTotal);
            calcAddressTotal = ptr2->address + ptr2->size;
            //printf("calcAdd = %d\n\n",calcAddressTotal);
            ptr2 = ptr2->next;
        }

        updateAdrs(ptr->next, calcAddressTotal);
    }
}



///////////////////////////


/**************End of Creation Section***************/


/* Display Section */
void displayMemory(memoryBlock *head) {
    memoryBlock *temp2 = head;
    printf("\n-----------------Memory---------------------\n\n");
    while (temp2 != NULL) {
        printf("Address : %d | Occupied : %d | Size : %d\n", temp2->address, temp2->occupied, temp2->size);
        temp2 = temp2->next;
    }
    printf("\n--------------------------------------------\n");
}
void displayPreviousState(memoryBlock *prevStateBlock){
    printf("   -Before : \n");
    printf("    Address : %d || Occupied : %d || Size : %d\n", prevStateBlock->address, prevStateBlock->occupied, prevStateBlock->size);
    printf("\n");
}
void displayUpdatedState(memoryBlock *updtStateBlock){
    printf("   -After : \n");
    printf("    Address : %d || Occupied : %d || Size : %d\n", updtStateBlock->address, updtStateBlock->occupied, updtStateBlock->size);
    printf("    Address : %d || Occupied : %d || Size : %d\n", updtStateBlock->next->address, updtStateBlock->next->occupied, updtStateBlock->next->size);

    printf("\n");
}
/* End of Display Section */



/* FIFO Selection Algo not Working needs fixing
void fifoEnqueue(memoryBlock *block) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->block = block;
    newNode->next = NULL;

    if (allocationQueue->rear == NULL) {
        allocationQueue->front = allocationQueue->rear = newNode;
    } else {
        allocationQueue->rear->next = newNode;
        allocationQueue->rear = newNode;
    }
}

memoryBlock *fifoDequeue() {
    if (allocationQueue->front == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    QueueNode *temp = allocationQueue->front;
    memoryBlock *block = temp->block;
    allocationQueue->front = allocationQueue->front->next;
    if (allocationQueue->front == NULL) {
        allocationQueue->rear = NULL;
    }
    free(temp);
    return block;
}

void deallocateMemoryFIFO() {
    memoryBlock *block = fifoDequeue();
    if (block != NULL) {
        block->occupied = 0;
        printf("Deallocated memory block: Address %d, Size %d\n", block->address, block->size);
    } else {
        printf("No memory blocks to deallocate\n");
    }
}
*/



/* Search Section */
memoryBlock *firstFit( int sizeOfNewElement ) {
    memoryBlock *ptr = head;
    
    while(ptr!=NULL){
        if(sizeOfNewElement<=ptr->size && ptr->occupied != 1){
            printf("-> First Fit Search Successfull....\n");
            printf("--Memory Block Located : \n");
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
memoryBlock *bestFit(int sizeOfNewElement) {
    memoryBlock *bestFitBlock = NULL;
    memoryBlock *ptr = head;

    int minFragmentation = INT_MAX; // Initialize to maximum possible value

    while (ptr != NULL) {
        if (sizeOfNewElement <= ptr->size && ptr->occupied != 1) {
            int fragmentation = ptr->size - sizeOfNewElement;
            if (fragmentation >= 0 && fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitBlock = ptr;
            }
        }
        ptr = ptr->next;
    }

    if (bestFitBlock != NULL) {
        printf("-> Best Fit Search Successful....\n");
        printf("-- Memory Block Located:\n");
        printf("  - Address: %d | Occupied: %d | Size: %d\n", bestFitBlock->address, bestFitBlock->occupied, bestFitBlock->size);
        return bestFitBlock;
    } else {
        printf("-- Best Fit Search Unsuccessful....\n");
        printf("-- Unable to locate a suitable memory block.\n\n");
        return NULL;
    }
}
/* End of Search Section */



/* Allo/Deallo Section */
void allocateMemory(int newSize, memoryBlock* searchResultNode){

    printf("\n-----------------Memory Allocation---------------------\n\n");

    int isOccupied = 1;
    int notOccupied = 0;
    int newAddress;
    int holdPrevAddress = searchResultNode->address;

    memoryBlock* holdNextNode;
    memoryBlock* remainderNode;
    
    displayPreviousState(searchResultNode);

    if(newSize == searchResultNode->size){
        searchResultNode->occupied = isOccupied;
        printf("--Size Match Memory Allocated Successfully!!\n\n");
    }else{
        int remainderSizeNode = searchResultNode->size - newSize; 
        searchResultNode->size = newSize;
        searchResultNode->occupied = isOccupied;

        remainderNode = createNode(remainderSizeNode, notOccupied);

        holdNextNode = searchResultNode->next;

        searchResultNode->next = remainderNode;
        remainderNode->next = holdNextNode;


        remainderNode->address = holdPrevAddress + remainderNode->size;
    }
    upAdsMem();
    printf("\n");
    displayUpdatedState(searchResultNode);

    holdNextNode = NULL;
    remainderNode = NULL;
    fifoEnqueue(searchResultNode);

    printf("\n-------------------------------------------------------\n");
}
///////////////////////
void deallocateMemory(memoryBlock* ptrSearchRes){
    memoryBlock* ptr=head;
    memoryBlock* holdNext;
    
    if(ptrSearchRes==NULL){
        exit(1);
   
    }else if(ptrSearchRes == head && ptrSearchRes->occupied == 1){ // if we want to delete the head and its occupied

        printf("\n--Head Address Changed!!\n");
        if(ptr->next->occupied == 0){ // if next is not occupied
            ptr->size += ptr->next->size;

            ptr->address += ptr->next->size;

            if(ptr->next->next != NULL){
                holdNext = ptr->next->next;
                ptr->next = holdNext;
                free(ptr->next->next);
            }else{
                ptr->next = NULL;
                free(ptr->next);
            }
        
            printf("\n--Memory Deallocated Successfully--\n");
            
        }else{ // if next is occupied change the state only
            ptr->occupied = 0;
            printf("\n--Memory Deallocated Successfully--\n");
        }

    }else{
        
        while( ptr->next->size != ptrSearchRes->size ){
            ptr=ptr->next;
        }
        if(ptrSearchRes->next == NULL){ // if we want to delete tha last node
            if(ptr->occupied == 0){
                ptr->size += ptrSearchRes->size;
                ptr->address += ptrSearchRes->size;

                ptr->next = NULL;

                free(ptrSearchRes);
                
                printf("\n--Memory Deallocated Successfully--\n");

            }else if(ptr->occupied == 1){
                ptrSearchRes->occupied = 0;
                printf("\n--Memory Deallocated Successfully--\n");
            }

        }

        else if(ptr->occupied == 0 && ptrSearchRes->next->occupied == 1){ // prev not occupied(0)  deleteThisBlock(1)  next occupied(1)

            ptr->size += ptrSearchRes->size;

            holdNext = ptrSearchRes->next;

            free(ptrSearchRes);

            printf("\n--Memory Deallocated Successfully--\n");

            ptr->next = holdNext;

        }else if(ptr->occupied == 0 && ptrSearchRes->next->occupied == 0){ // prev not occupied(0)  deleteThisBlock(1)  next not occupied(0)

                ptr->size += ptrSearchRes->size + ptrSearchRes->next->size;

                holdNext = ptrSearchRes->next->next;

                free(ptrSearchRes->next);
                free(ptrSearchRes);
                printf("\n--Memory Deallocated Successfully--\n");
                ptr->next = holdNext;

        }else if(ptr->occupied == 1 && ptrSearchRes->next->occupied == 0){ // prev occupied(1)  deleteThisBlock(1)  next not occupied(0)
            ptr=ptr->next;
            ptrSearchRes = ptrSearchRes->next;

            ptr->size += ptrSearchRes->size;

            ptr->address += ptrSearchRes->size;
            ptr->next = ptrSearchRes->next;

            free(ptrSearchRes);
            printf("\n--Memory Deallocated Successfully--\n");

        }else if(ptr->occupied == 1 && ptrSearchRes->next->occupied == 1){ // prev occupied(1)  deleteThisBlock(1)  next occupied(1)
            ptr=ptr->next; 

            ptr->occupied = 0;
            printf("\n--Memory Deallocated Successfully--\n");
        }

    }

    // Dequeue and free the memory block
    memoryBlock *block = fifoDequeue();
    if (block != ptrSearchRes) {
        printf("Error: Dequeued block does not match deallocation block\n");
        exit(1);
    }
    free(block);

}
//////////////////////
memoryBlock* findMemoryDeallo(int address){

    memoryBlock* ptr=head;

    while(ptr->address != address){
        ptr=ptr->next;
    }
    if(ptr->occupied == 1){

        printf("--Memory Block Located : \n");
        printf(" -Address : %d | Occupied : %d | Size : %d\n", ptr->address, ptr->occupied, ptr->size);

    }else if(ptr->occupied==0){// deleteThisBlock not occupied -> No need to deallocate.

        printf("--Memory Block is not Occupied no need for memory deallocation.\n");
        ptr=NULL;
        
    }
    return ptr;

}
/* End of Allo/Deallo Section */







///////////////////////////////////



/* Main */
int main() {

    allocationQueue = (Queue *)malloc(sizeof(Queue));
    if (allocationQueue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    allocationQueue->front = allocationQueue->rear = NULL;

    int choice;//menu choice
    
    int newSize;//input new node
    int isOccupied;//input new node

    int searchSize;//first Fit search
    int searchAddress;//Deallocation Search


    memoryBlock *ptrSearch=NULL;



    do {

        choice = Menu();

        switch (choice) {
            case 1:

                createMemoryBlock(400, 1);
                createMemoryBlock(1000, 0);
                createMemoryBlock(800, 1);
                createMemoryBlock(3000, 1);
                createMemoryBlock(500, 0);
                createMemoryBlock(200, 1);

                printf("\n");

                break;


            case 2:

                displayMemory(head);

                printf("\n");

                break;


            case 3:

                printf(" -> Enter Size to search : ");
                scanf("%d",&searchSize);

                printf("\n");

                ptrSearch = firstFit(searchSize);

                break;


            case 4:

                printf(" -> Enter Size to search : ");
                scanf("%d",&searchSize);

                printf("\n");

                ptrSearch = bestFit(searchSize);
                        

                break;


            case 5:
               
                printf("---Not Built Yet---\n");
                break;


            case 6:

                if(ptrSearch!=NULL)
                    allocateMemory(searchSize, ptrSearch);

                else printf("--Try Searching for the memory Block first!!\n");

                //printf("---Not Built Yet---\n");

                break;


            case 7:

                printf("-> Enter Address to find the memory block : ");
                scanf("%d",&searchAddress);

                printf("\n");

                ptrSearch = findMemoryDeallo(searchAddress);

                if(ptrSearch!=NULL) deallocateMemory(ptrSearch);
                upAdsMem();
                
                //printf("---Not Built Yet---\n");
                break;

            case 8:

                deallocateMemoryFIFO();
                printf("\n");

            default:

                printf("--Choose a correct number in the list pls!!\n");

                break;        
        }

    } while (choice != 0);

    free(allocationQueue);

    return 0;
}
