#ifndef MODELS_H
#define MODELS_H

#include <stdbool.h>

// Client structure
typedef struct client {
    bool isOccupied;
    bool rushOrder;
    int rushOrderInt;
    char name[20];
    int day, month, year;
    int photosToPrint, photosToDevelop, photosPrinted, photosDeveloped;
    bool isNew;
    bool isForwarded;
    bool isCompleted;
} client;

extern int paperAmount;
extern int* pntPaperAmount;
extern int developerAmount;
extern int* pntDeveloperAmount;
extern int inkAmount;
extern int* pntInkAmount;

extern int paperSpent;
extern int* pntPaperSpent;
extern int developerSpent;
extern int* pntDeveloperSpent;
extern int inkSpent;
extern int* pntInkSpent;

extern double totalRevenue;
extern double* totalRevPntr;
extern double currentRevenue;
extern double* currentRevPntr;

extern double paperCost;
extern double* paperCostPntr;
extern double developerCost;
extern double* developerCostPntr;
extern double inkCost;
extern double* inkCostPntr;
extern double materialSpendingCost;
extern double* materialSpendingCostPntr;

extern double printCost;
extern double* printCostPntr;
extern double developCost;
extern double* developCostPntr;

extern int clientCapacity;
extern int clientCurrentCount;
extern client* clientArray;

void initClient(client* c);
void initGlobalState();
bool resizeClientArray(int newCapacity);
int findAvailableSlot();

#endif // MODELS_H
