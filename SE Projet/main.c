#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct MemoryBlock{
    int address;
    int size;
    bool occupied;

    struct MemoryBlock *next;
}memoryBlock;
memoryBlock *head;


int Menu(){
    int choice;

    printf("\n1-Create Memory Block.\n");
    printf("2-Display Memory Block.\n");
    printf("3-First Fit Search.\n");
    printf("4-Best Fit Search.\n");
    printf("5-Worst Fit Search.\n");
    printf("0-End Program.\n");

    printf("\n--> Your Choice : ");
    scanf("%d",&choice);
    printf("\n");

    return choice;
}

memoryBlock *createNode(int size){

    memoryBlock *temp = malloc(sizeof(memoryBlock));
        temp->size = size;
        temp->occupied = true;
        temp->next = NULL;

    if(temp!=NULL) return temp;
    else exit(1);
}
memoryBlock *createMemoryBlock(int nmbElements){

    int size;

    for (int i = 0; i < nmbElements; i++)
    {
        printf("\nEnter the Size : ");
        scanf("%d",&size);
        
        if(head==NULL){
            printf("Enter the address : ");
            scanf("%d",&adrs);
            head = createNode(size);
            return head;

        }else if(head!=NULL){
            memoryBlock *reachEnd = head;
            while(reachEnd!=NULL){
                reachEnd=reachEnd->next;
            }
            reachEnd = createNode(size);
            return reachEnd;
        }

    }

}
memoryBlock *allocateMemory(memoryBlock *ptr, int size){

    if(ptr!=NULL){
        memoryBlock *temp = createNode(size);
        ptr = temp;

        printf("\n-Memory Allocated Succefully.\n");

    }else exit(1);

}

memoryBlock *firstFitSearch(memoryBlock *head, int sizeOfNewElement){

    if(head!=NULL){

        memoryBlock *findFirstFit = head;

        while(findFirstFit!=NULL){

            if ((findFirstFit->size <= sizeOfNewElement)&&
                (findFirstFit->occupied == false ))
            {

                return findFirstFit;

            }else findFirstFit=findFirstFit->next;

        }

    }else{
        printf('\nEmpty List!! try filling it first.\n');
        return NULL;
    }

}




int main()
{
    int choice;
    int nmbElm;
    int newSize;

    memoryBlock *ptr;

    do{
        Menu();

        switch(choice){
            case 1:
                printf("\n-How many elements do you want : ");
                scanf("%d",&nmbElm);
                createMemoryBlock(nmbElm);
                break;
            case 2:
                break;
            case 3:
                printf("-Enter the Size of the new Element : ");
                scanf("%d",&newSize);

                ptr = firstFitSearch(head, newSize);
                if(ptr!=NULL){
                    printf("\n-Space located Succefully.\n");
                    printf("-Allocating Memory for new element.\n");
                    allocateMemory(ptr, newSize);    
                }
                

                break;
            case 4:
                break;


        }
    }while(Menu != 0);
}
