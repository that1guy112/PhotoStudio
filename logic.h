#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>


int materialPurchase(int purchaseChoice);

// Photographer functions
bool developPhoto(int clientIndex);
bool printPhoto(int clientIndex);
bool canCompleteOrder(int clientIndex);
void completeOrder(int clientIndex);

// Receptionist functions
void forwardOrderToPhotographer(int clientIndex);
int countNewOrders();
int countOngoingOrders();
int countCompletedOrders();
double calculateProfit();

#endif // LOGIC_H
