#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "arrayStack.h"

int main() {
    // write your code here
    Stack S[3];
    Stack temp[3];
    int i, x, choice = 0, value = 0;
    bool check = false;
    
    for(i = 0; i < 3; i++) initializeStack(&S[i]);
    
    while(choice != 5) {
        printf("--- Warehouse Inventory Management System ---\n");
        printf("1. Push a container\n");
        printf("2. Pop a container\n");
        printf("3. Check if a container exists\n");
        printf("4. Display all stacks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter container ID to push: ");
                scanf("%d", &value);
                for(i = 0; isFull(&S[i]); i++);
                if(i == 3) {
                    printf("All Containers are full.\n\n");
                }
                else {
                    push(&S[i], value);
                    printf("Container %d pushed successfully.\n\n", value);
                }
                break;
                
            case 2:
                if(isEmpty(&S[0])) {
                    printf("Error: All stacks are empty. Cannot pop container.\n\n");
                }
                else {
                    for(i = 0; isFull(&S[i]); i++); 
                    if(i == 3) i = 2;
                    printf("Container %d popped successfully.\n\n",  pop(&S[i]));
                }
                break;

            case 3: 
               printf("Enter container ID to check: ");
                scanf("%d", &value);
                check = false;
                for(i = 0; i < 3; i++) temp[i] = S[i];
                
                for(i = 0; i < 3 && !isEmpty(&temp[i]) && check == false; i++) {
                    for(x = temp[i].top; x >= 0 && check == false; x--) {
                        if(pop(&temp[i]) == value) {
                            check = true;
                        }
                    }
                }
                
                if(check) printf("Container %d exists in a stack.\n\n", value);
                else printf("Container %d does not exist in any stack.\n\n", value); 
                break;
                
            case 4:
                for(i = 0; i < 3; i++) {
                    printf("\n--- Stack %d ---\n", i+1);
                    display(&S[i]);
                }
                printf("\n");
                break;
                
            case 5:
                printf("Exiting program.");
                break;
                
            default:
                printf("The number you input is invalid, Try Again.\n\n");
                break;
        }
    }

    return 0;
}
