#include <stdio.h>
#include <stdlib.h>
#include "arrayQueue.h"
#include "types.h"

int main() {
    // write your code here
    Queue* Q[2];
    int i, number = 0, choice = 0;
    for(i = 0; i < 2; i++) Q[i] = initialize();
    
    while(choice != 5) {
        printf("--- Pharmacy Queueing System ---\n");
        printf("1. Enter Regular Queue\n");
        printf("2. Enter Priority Queue\n");
        printf("3. Call Next Customer\n");
        printf("4. Display Queues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(isFull(Q[0])) printf("Regular queue is full. Please try again later.\n\n");
                else {
                    number++;
                    enqueue(Q[0], number);
                    printf("You have entered the Regular queue. Your number is %d.\n\n", number);
                }
                break;
                
            case 2:
                if(isFull(Q[1])) printf("Regular queue is full. Please try again later.\n\n");
                else {
                    number++;
                    enqueue(Q[1], number);
                    printf("You have entered the Priority queue. Your number is %d.\n\n", number);
                }
                break;
                
            case 3:
                if(!isEmpty(Q[1])) {
                    printf("Calling next customer from Priority Queue. Customer number: %d\n\n", dequeue(Q[1]));
                } 
                else if(!isEmpty(Q[0])) {
                    printf("Calling next customer from Regular Queue. Customer number: %d\n\n", dequeue(Q[0]));
                } 
                else printf("There are no more customer from Queue.\n\n");
                break;
                
            case 4: 
                printf("\n-- Current Queue Status --\n");
                printf("Regular Queue: ");
                display(Q[0]);
                printf("Priority Queue: ");
                display(Q[1]);
                printf("\n");
                break;
                
            case 5:
                printf("Exiting program. Goodbye!");
                break;
                
            default:
                printf("The number you input is invalid\n\n");
                break;
        }
    }

    return 0;
}
