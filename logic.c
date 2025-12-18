#include "logic.h"
#include "models.h"
#include <stdio.h>


//the modular system which allows the user to purchase materials if they are in "photographer mode" for example
int materialPurchase(int purchaseChoice)
{
    switch (purchaseChoice)
    {
    case 1:
        if (*currentRevPntr >= *paperCostPntr)
        {
            *pntPaperAmount += 5;
            *currentRevPntr -= *paperCostPntr;
            *materialSpendingCostPntr += *paperCostPntr;
        }
        else
        {
            printf("Insufficient Balance!\n");
        }
        break;
    case 2:
        if (currentRevenue >= developerCost)
        {
            *pntDeveloperAmount += 5;
            *currentRevPntr -= *developerCostPntr;
            *materialSpendingCostPntr += *developerCostPntr;
        }
        else
        {
            printf("Insufficient Balance!\n");
        }
        break;
    case 3:
        if (currentRevenue >= inkCost)
        {
            *pntInkAmount += 5;
            *currentRevPntr -= *inkCostPntr;
            *materialSpendingCostPntr += *inkCostPntr;
        }
        else
        {
            printf("Insufficient Balance!\n");
        }
        break;
    case 9:
        printf("Exiting.\n");
        break;
    default:
        printf("Invalid choice\n");
        break;
    }

    return 0;
}

// Photographer functions

//Photo development function
bool developPhoto(int clientIndex)
{
    if (*pntPaperAmount == 0 || *pntDeveloperAmount == 0) 
    {
        printf("Insufficient materials!\n");
        return false;
    }
    
    if (clientArray[clientIndex].photosToDevelop > 0)
    {
        printf("Developing photos.\n");
        --clientArray[clientIndex].photosToDevelop;
        (*pntDeveloperAmount)--;
        (*pntPaperAmount)--;
        ++clientArray[clientIndex].photosDeveloped;
        ++(*pntDeveloperSpent);
        ++(*pntPaperSpent);
        
        // Apply rush order pricing
        double cost = *developCostPntr;
        if (clientArray[clientIndex].rushOrder) {
            cost *= 1.3;
        }
        (*totalRevPntr) += cost;
        (*currentRevPntr) += cost;
        return true;
    }
    else 
    {
        printf("You dont need to develop any more photos\n");
        return false;
    }
}


//Photo printing function
bool printPhoto(int clientIndex)
{
    if (*pntInkAmount == 0 || *pntPaperAmount == 0) 
    {
        printf("Insufficient materials!\n");
        return false;
    }
    
    if (clientArray[clientIndex].photosToPrint > 0) 
    {         
        printf("Printing photos.\n");
        --clientArray[clientIndex].photosToPrint;
        (*pntInkAmount)--;
        (*pntPaperAmount)--;
        ++clientArray[clientIndex].photosPrinted;
        ++(*pntInkSpent);
        ++(*pntPaperSpent);
        
        // Apply rush order pricing
        double cost = *printCostPntr;
        if (clientArray[clientIndex].rushOrder) {
            cost *= 1.3;
        }
        (*totalRevPntr) += cost;
        (*currentRevPntr) += cost;
        return true;
    }
    else 
    {
        printf("You dont need to print any more photos\n");
        return false;
    }
}


//checks if the order needs to complete more pictures or not. if not, the order can be considered complete.
bool canCompleteOrder(int clientIndex)
{
    return (clientArray[clientIndex].photosToPrint == 0 && 
            clientArray[clientIndex].photosToDevelop == 0);
}

void completeOrder(int clientIndex)
{
    if (canCompleteOrder(clientIndex)) {
        clientArray[clientIndex].isCompleted = true;
        clientArray[clientIndex].isForwarded = false;
        printf("Order Completed!\n");
    }
    else {
        printf("Cannot complete order! Order still has photos to print/develop\n");
    }
}

// Receptionist functions


void forwardOrderToPhotographer(int clientIndex)
{
    clientArray[clientIndex].isNew = false;
    clientArray[clientIndex].isForwarded = true;
}

int countNewOrders()
{
    int count = 0;
    for (int i = 0; i < clientCapacity; i++)
    {
        if (clientArray[i].isNew) {
            count++;
        }
    }
    return count;
}

int countOngoingOrders()
{
    int count = 0;
    for (int i = 0; i < clientCapacity; i++)
    {
        if (clientArray[i].isForwarded) {
            count++;
        }
    }
    return count;
}

int countCompletedOrders()
{
    int count = 0;
    for (int i = 0; i < clientCapacity; i++)
    {
        if (clientArray[i].isCompleted) {
            count++;
        }
    }
    return count;
}

double calculateProfit()
{
    return totalRevenue - materialSpendingCost;
}