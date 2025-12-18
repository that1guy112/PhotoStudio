#include "models.h"
#include <stdlib.h>
#include <string.h>

// Global variables (matching original)
int paperAmount = 5;
int* pntPaperAmount = &paperAmount;
int developerAmount = 5;
int* pntDeveloperAmount = &developerAmount;
int inkAmount = 5;
int* pntInkAmount = &inkAmount;

int paperSpent = 0;
int* pntPaperSpent = &paperSpent;
int developerSpent = 0;
int* pntDeveloperSpent = &developerSpent;
int inkSpent = 0;
int* pntInkSpent = &inkSpent;

double totalRevenue = 0;
double* totalRevPntr = &totalRevenue;
double currentRevenue = 100;
double* currentRevPntr = &currentRevenue;

double paperCost = 2.5;
double* paperCostPntr = &paperCost;
double developerCost = 3;
double* developerCostPntr = &developerCost;
double inkCost = 3;
double* inkCostPntr = &inkCost;
double materialSpendingCost = 0;
double* materialSpendingCostPntr = &materialSpendingCost;

double printCost = 0.8;
double* printCostPntr = &printCost;
double developCost = 1.2;
double* developCostPntr = &developCost;

int clientCapacity = 10;
int clientCurrentCount = 0;
client* clientArray = NULL;


//this exists so that the clients that are first initialized aren't filled with garbage values
void initClient(client* c) {
    c->isOccupied = false;
    c->rushOrder = false;
    c->rushOrderInt = 0;
    memset(c->name, 0, sizeof(c->name));
    c->day = c->month = c->year = 0;
    c->photosToPrint = c->photosToDevelop = c->photosPrinted = c->photosDeveloped = 0;
    c->isNew = false;
    c->isForwarded = false;
    c->isCompleted = false;
}


void initGlobalState() {
    clientArray = (client*)malloc(clientCapacity * sizeof(client));
    if (clientArray) {
        for (int i = 0; i < clientCapacity; i++) {
            initClient(&clientArray[i]);
        }
    }
}


//reallocates more memory to the array if it gets full.
bool resizeClientArray(int newCapacity) {
    client* newArray = (client*)realloc(clientArray, newCapacity * sizeof(client));

    // if memory alloc fails, keep the original
    if (!newArray) {
        return false;
    }
    
    // if memory alloc is successful, the array will instead use the new array
    clientArray = newArray;
    

    //initialize clients in the newly allocated room so that they arent filled with garbage values.
    for (int i = clientCapacity; i < newCapacity; i++) {
        initClient(&clientArray[i]);
    }
    
    clientCapacity = newCapacity;
    return true;
}

int findAvailableSlot() {

     // Search for an unoccupied client slot
    for (int i = 0; i < clientCapacity; i++) {
        if (!clientArray[i].isOccupied) {
            return i;
        }
    }
    
    // if no free slot found, attempt to grow the array by 5 clients
    if (resizeClientArray(clientCapacity + 5)) {
        // Return the index of the first newly added slot
        return clientCapacity - 5;
    }
    
    // Failed to find or create an available slot
    return -1;
}