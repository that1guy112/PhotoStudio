
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "models.h"
#include "logic.h"
#include "file.h"

#define SAVE_FILE "studio_save.txt"

int roleChosen = 0;
bool exitChosen = false;
bool fullExitChosen = false;

int photographerChoice = 0;
int receptionistChoice = 0;
int customerChoice = 0;
int materialPurchaseChoice = 0;

int currentClient;

void receptionist();
void customer();
void photographer();

int userChoice(int Choice)
{
    if(Choice == 9)
    {
        exitChosen = true;
        return 0;
    }
    else
    {
        return Choice;
    }
}

void receptionist()
{
    printf("Receptionist chosen\n");
    while (!exitChosen) {
        printf("What would you like to do? (Enter only number)\n");
        printf("1. View new orders\n2. View ongoing orders\n3. View completed orders\n4. View today's revenue\n5. View today's spent materials\n6. Order materials\n7. Exit\n");

        scanf("%d", &receptionistChoice);

        switch (userChoice(receptionistChoice))
        {
        case 1:
            printf("Viewing new orders\n--------------\n");
            for (int i = 0; i < clientCapacity; i++)
            {
                if (clientArray[i].isNew){
                    printf("\n");
                    printf("%s has made an order!\nWould you like to forward the order to the photographer?\n 1. Yes\n 2. No\n", clientArray[i].name);

                    scanf("%d", &receptionistChoice);
                    if (receptionistChoice == 1)
                    {
                        forwardOrderToPhotographer(i);
                    }
                }
            }
            printf("No more new orders found\n");
            break;

        case 2:
            printf("Viewing ongoing orders\n--------------\n");
            for (int i = 0; i < clientCapacity; i++)
            {
                if (clientArray[i].isForwarded)
                {
                    printf("\n");
                    printf("\n Customer id: %d\n Customer name: %s\n %d Photos to print\n %d Photos to develop\n %d Photos printed\n %d Photos developed\n Deadline:\n %d/%d/%d\n\n", i, clientArray[i].name, clientArray[i].photosToPrint, clientArray[i].photosToDevelop, clientArray[i].photosPrinted, clientArray[i].photosDeveloped, clientArray[i].day, clientArray[i].month, clientArray[i].year);
                }
            }
            break;
            
        case 3:
        printf("\n");
            printf("Viewing completed orders\n---------------\n");
            for (int i = 0; i < clientCapacity; i++)
            {
                if (clientArray[i].isCompleted){
                    printf("\n");
                    printf("Order for %s is completed!\n", clientArray[i].name);
                }
            }
            break;

        case 4:
            printf("\n");
            printf("Viewing today's revenue\n--------------\n");
            printf("Amount gained from work = %.2lf\n", totalRevenue);
            printf("Amount spent on materials = %.2lf\n", materialSpendingCost);
            printf("Total profit = %.2lf\n", calculateProfit());
            break;

        case 5:
            printf("Viewing today's spent materials\n---------------\n");
            printf("Ink spent = %d\nPaper spent = %d\nDeveloper spent = %d\n", inkSpent, paperSpent, developerSpent);
            printf("Amount of money spent on materials = %.2lf\n", materialSpendingCost);
            printf("Viewing today's available materials.\n---------------\n");
            printf("Ink = %d\nPaper = %d\nDeveloper = %d\n", inkAmount, paperAmount, developerAmount);
            break;

        case 6:
            while (!exitChosen)
            {
                printf("What materials would you like to order?\n--------------\n");
                printf("Current Balance: %0.2f\n", currentRevenue);
                printf("Price List:\n1. 5x Paper = 2.5\n2. 5x Developer = 3\n3. 5x Ink = 3\n9. Exit\n");
                scanf("%d", &materialPurchaseChoice);
                materialPurchase(userChoice(materialPurchaseChoice));
            }
            break;

        case 7:
            exitChosen = true;
            break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
}

void customer()
{
    printf("Customer chosen\n");

    printf("What would you like to do?\n 1. Print and/or develop photos\n 2. View order status\n 3. Exit\n");
    
    scanf("%d", &customerChoice);
    if (customerChoice == 3) return;

    else if (customerChoice == 1)
    {
        int slot = findAvailableSlot();
        if (slot == -1) {
            printf("Sorry, we cannot take more orders at the moment.\n");
            return;
        }
        
        currentClient = slot;
        clientArray[currentClient].isOccupied = true;
        clientArray[currentClient].isNew = true;
        clientCurrentCount++;

        printf("Input your name:\n");
        scanf(" %[^\n]", clientArray[currentClient].name);
        
        printf("%s.\n", clientArray[currentClient].name);

        printf("How many photos would you like to print? 1 photo print costs %0.2f eur.\n", printCost);
        scanf("%d", &clientArray[currentClient].photosToPrint);

        printf("How many photos would you like to develop? 1 developed photo costs %0.2f eur.\n", developCost);
        scanf("%d", &clientArray[currentClient].photosToDevelop);

        printf("When would you like to collect the photos? (dd mm yyyy)\n");
        scanf("%d %d %d", &clientArray[currentClient].day, &clientArray[currentClient].month, &clientArray[currentClient].year);
        
        printf("Would you like a rush order or regular order?\n 0. Regular\n 1. Rush: Order costs 30 percent more.\n");
        scanf("%d", &clientArray[currentClient].rushOrderInt);
        
        switch (clientArray[currentClient].rushOrderInt)
        {
        case 0:
            printf("Regular order selected\n");
            clientArray[currentClient].rushOrder = false;
            break;
        case 1:
            printf("Rush order selected\n");
            clientArray[currentClient].rushOrder = true;
            break;
        default:
            printf("Invalid choice\n");
        }
    }
    else if (customerChoice == 2)
    {
        printf("Enter your Customer ID\n");
        scanf("%d", &currentClient);
        printf("Current progress:\n %d Photos to print\n %d Photos to develop\n %d Photos printed\n %d Photos developed\n Deadline: %d/%d/%d\n", clientArray[currentClient].photosToPrint, clientArray[currentClient].photosToDevelop, clientArray[currentClient].photosPrinted, clientArray[currentClient].photosDeveloped, clientArray[currentClient].day, clientArray[currentClient].month, clientArray[currentClient].year);
    }
}

void photographer()
{
    int photographerCustomerChoice;
    printf("Photographer chosen\n");
    printf("You currently have: %d paper, %d developer and %d ink\n", paperAmount, developerAmount, inkAmount);
    printf("Orders to complete:\n\n");
    for (int i = 0; i < clientCapacity; i++)
    {
        if (clientArray[i].isForwarded){
            printf("Customer %d has an incomplete order!\n", i);
        }
    }

    printf("Select your customer. (Enter only number)\n");
    scanf("%d", &photographerCustomerChoice);
    
    while (!exitChosen)
    {
        printf("You have %d photos printed and %d photos developed\n", clientArray[photographerCustomerChoice].photosPrinted, clientArray[photographerCustomerChoice].photosDeveloped);
        printf("You have %d photos to print and %d photos to develop.\n\n", clientArray[photographerCustomerChoice].photosToPrint, clientArray[photographerCustomerChoice].photosToDevelop);
        printf("What would you like to do? (Enter only number)\n");
        printf("1. Develop photos\n2. Print photos\n3. Finish order.\n4. Purchase materials\n5. Exit\n");
    
        scanf("%d", &photographerChoice);
    
        switch (userChoice(photographerChoice))
        {
            case 1:
                developPhoto(photographerCustomerChoice);
                break;
                
            case 2:
                printPhoto(photographerCustomerChoice);
                break;

            case 3:
                completeOrder(photographerCustomerChoice);
                if (canCompleteOrder(photographerCustomerChoice)) {
                    exitChosen = true;
                }
                break;

            case 4:
                printf("What materials would you like to purchase?\n1. 5x Paper (%0.2f eur)\n2. 5x Developer (%0.2f eur)\n3. 5x Ink (%0.2f eur)\n", paperCost, developerCost, inkCost);
                printf("Current balance: %0.2f\n", *currentRevPntr);
                scanf("%d", &materialPurchaseChoice);
                materialPurchase(materialPurchaseChoice);
                break;
                
            case 5:
                exitChosen = true;
                break;

            default:
                printf("Invalid choice\n");
                break;
        }
    }
}

int main()
{
    materialPurchaseChoice = 0;
    
    initGlobalState();
    
    if (!clientArray) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Load saved state if exists
    if (fileExists(SAVE_FILE)) {
        printf("Found saved data. Load it? (1=Yes, 0=No): ");
        int loadChoice;
        scanf("%d", &loadChoice);
        if (loadChoice == 1) {
            loadStudioState(SAVE_FILE);
        }
    }
    
    while(!fullExitChosen)
    {
        exitChosen = false;
        
        printf("Choose your role: (Enter only number)\n");
        printf("1. Receptionist\n2. Customer\n3. Photographer\n4. Save and Quit Program\n5. Quit without Saving\n");

        scanf("%d", &roleChosen);
    
        switch (userChoice(roleChosen))
        {
        case 1: 
            receptionist();
            break;

        case 2:
            customer();
            break;
            
        case 3: 
            photographer();
            break;
        
        case 4:
            saveStudioState(SAVE_FILE);
            printf("Quitting program\n");
            fullExitChosen = true;
            break;
            
        case 5:
            printf("Quitting program without saving\n");
            fullExitChosen = true;
            break;
        
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    if (clientArray) {
        free(clientArray);
    }
    
    return 0;
}