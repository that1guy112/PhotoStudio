#include <cstring>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int roleChosen = 0;

//case 1
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
double materialSpendingCost;
double* materialSpendingCostPntr = &materialSpendingCost;

double printCost = 0.8;
double* printCostPntr = &printCost;
double developCost = 1.2;
double* developCostPntr = &developCost;

bool exitChosen = false;
bool fullExitChosen = false;

int photographerChoice = 0;
int receptionistChoice = 0;
int customerChoice = 0;
int materialPurchaseChoice = 0;

int currentClient;

int clientCapacity = 10;
int clientCurrentCount;

struct client
{
    bool isOccupied; //checks if index number in use
    bool rushOrder; //defines if the client order is to be rushed or not.
    int rushOrderInt; //a workaround so that the user can make the choice (0 = regular order; 1 = rush order)
    char name[20];
    int day, month, year;
    int photosToPrint, photosToDevelop, photosPrinted, photosDeveloped;
    bool isNew = false; // newly added order, waiting to be forwarded
    bool isForwarded = false; // forwarded to the photographer
    bool isCompleted = false; // order complete, photos printed and/or developed.
};

<<<<<<< HEAD
    int photosToPrint = 5;
    int photosToDevelop = 5;
    int photosPrinted = 0;
    int photosDeveloped = 0;
    
    bool exitChosen = false;
    bool fullExitChosen = false;
    int photographerChoice = 0;
    
    //THIS IS A TEST
    while(!fullExitChosen)// lisa ka functioni mis laseb kasutajal kontrollida mis materjalid alles on + mitu fotod oli valmis tehtud.
    {
        exitChosen = false; //used to make sure that the role selection while loop works correctly. 
        

      
        printf_s("Choose your role: (Enter only number)\n");
        printf_s("1. Receptionist (IN DEVELOPMENT)\n2. Customer (IN DEVELOPMENT)\n3. Photographer\n4. Quit Program\n");
=======



client* clientArray = NULL;

// initialize a client with default values so that the starting client isnt filled with garbage values.
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

// resize the client array when the dynamic array is filled up
bool resizeClientArray(int newCapacity) {
    client* newArray = (client*)realloc(clientArray, newCapacity * sizeof(client));
    if (!newArray) {
        return false;
    }
    
    clientArray = newArray;
    
    // Initialize new slots
    for (int i = clientCapacity; i < newCapacity; i++) {
        initClient(&clientArray[i]);
    }
    
    clientCapacity = newCapacity;
    return true;
}

// find next available client slot
int findAvailableSlot() {
    for (int i = 0; i < clientCapacity; i++) {
        if (!clientArray[i].isOccupied) {
            return i;
        }
    }
    
    // no available slots, resize array
    if (resizeClientArray(clientCapacity + 5)) {
        return clientCapacity - 5; // Return first new slot
    }
    
    return -1; // failed to resize
}


int userChoice(int Choice)
{
    //system("cls"); //clears the terminal after each input, only works in windows machines, (for some reason my vs code terminal bugs out if this is included but works in the .exe, uncomment before finishing project)
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
>>>>>>> 6c31958f916a2822bccc0a30e28a9475de2db7d6

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
            materialSpendingCost += *developerCostPntr;
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
        printf_s("Exiting.\n");
    default:
        printf_s("Invalid choice\n");
        break;
    }

    return 0;
}

void receptionist() // the receptionist can see the orders that the customer has placed.
{
    printf_s("Receptionist chosen\n");
    while (!exitChosen) {


        printf_s("What would you like to do? (Enter only number)\n");
        printf_s("1. View new orders\n2. View ongoing orders\n3. View completed orders\n4. View today's revenue\n5. View today's spent materials\n6. Order materials\n7. Exit\n");

        scanf_s("%d", &receptionistChoice);

        switch (userChoice(receptionistChoice))
        {
        case 1:
            while (!exitChosen) {
                printf_s("Viewing new orders\n--------------\n");
                for (int i = 0; i < clientCapacity; i++)
                {
                    if (clientArray[i].isNew){
                        printf_s("%s has made an order!\nWould you like to forward the order to the photographer?\n 1. Yes\n 2. No\n", clientArray[i].name);

                        scanf_s("%d", &receptionistChoice);
                        if (receptionistChoice == 1)
                        {
                            clientArray[i].isNew = false;
                            clientArray[i].isForwarded = true;
                        }
                    }
                }
                printf_s("No ongoing orders found\n");
                break;
                
            }
            break;

        case 2:
            printf_s("Viewing ongoing orders\n--------------\n");
            for (int i = 0; i < clientCapacity; i++)
            {
                if (clientArray[i].isForwarded)
                {
                    printf_s("\n Customer id: %d\n Customer name: %s\n %d Photos to print\n %d Photos to develop\n %d Photos printed\n %d Photos developed\n Deadline:\n %d/%d/%d\n\n", i, clientArray[i].name, clientArray[i].photosToPrint, clientArray[i].photosToDevelop, clientArray[i].photosPrinted, clientArray[i].photosDeveloped, clientArray[i].day, clientArray[i].month, clientArray[i].year);
                }
                else break;
            }
            break;
            

        case 3:
            printf_s("Viewing completed orders\n---------------\n");
            for (int i = 0; i < clientCapacity; i++)
            {
                if (clientArray[i].isCompleted){
                    printf_s("Order for %s is completed!\n", clientArray[i].name);
                }
            }
            break;

        case 4:
            printf_s("Viewing today's revenue\n--------------\n");
            printf_s("Amount gained from work = %.2lf\n", totalRevenue);
            printf_s("Amount spent on materials = %.2lf\n", materialSpendingCost);
            printf_s("Total profit = %.2lf\n", totalRevenue - materialSpendingCost);
            break;

        case 5:
            printf_s("Viewing today's spent materials\n---------------\n");
            printf_s("Ink spent = %d\nPaper spent = %d\nDeveloper spent = %d\n", inkSpent, paperSpent, developerSpent);
            printf_s("Amount of money spent on materials = %.2lf\n", materialSpendingCost);
            printf_s("Viewing today's available materials.\n---------------\n");
            printf_s("Ink = %d\nPaper = %d\nDeveloper = %d\n", inkAmount, paperAmount, developerAmount);
            break;

        case 6:
            
            while (!exitChosen)
            {
                printf_s("What materials would you like to order?\n--------------\n");
                printf("Current Balance: %0.2f\n", currentRevenue);
                printf_s("Price List:\n1. 5x Paper = 2.5\n2. 5x Developer = 3\n3. 5x Ink = 3\n9. Exit\n");
                scanf_s("%d", &materialPurchaseChoice);
                materialPurchase(userChoice(materialPurchaseChoice));
            }
            break;

        case 7:
            exitChosen = true;
            break;

        default:
            printf_s("Invalid choice\n");
            break;
        }
    }
}



void customer() //Function for the customer role. allows to place orders (if there are free slots)  // tbh tundub semi done, kui keegi viitsib ss võib selle switchiks teha TODO
{
    
    printf_s("Customer chosen\n");


    printf_s("What would you like to do?\n 1. Print and/or develop photos\n 2. View order status\n 3. Exit\n");
    
    scanf_s("%d", &customerChoice);
    if (customerChoice == 3) return; //Exits customer view

    else if (customerChoice == 1) //Creates a new customer and starts to log his/her order
        while (!exitChosen)
        {
            int slot = findAvailableSlot();
            if (slot == -1) {
                printf_s("Sorry, we cannot take more orders at the moment.\n");
                return;
            }
            
            currentClient = slot;
            clientArray[currentClient].isOccupied = true;
            clientArray[currentClient].isNew = true;
            clientCurrentCount++;




            printf_s("Input your name:\n"); //name input
            scanf_s(" %[^\n]", clientArray[currentClient].name, (unsigned)sizeof(clientArray[currentClient].name));
            
            printf_s("%s.\n", clientArray[currentClient].name);

            printf_s("How many photos would you like to print? 1 photo print costs %0.2f eur.\n", printCost); //print photo input

            scanf_s("%d", &clientArray[currentClient].photosToPrint);

            printf_s("How many photos would you like to develop? 1 developed photo costs %0.2f eur.\n", developCost); //develop photo input

            scanf_s("%d", &clientArray[currentClient].photosToDevelop);

            printf_s("When would you like to collect the photos? (dd mm yyyy)\n"); //order deadline input

            scanf_s("%d %d %d", &clientArray[currentClient].day, &clientArray[currentClient].month, &clientArray[currentClient].year);
            //TODO: redo the photographer system so that the business gets the money per photo.
            printf_s("Would you like a rush order or regular order?\n 0. Regular\n 1. Rush: Order costs 30 percent more.\n"); //rush/regular order input

            scanf_s("%d", &clientArray[currentClient].rushOrderInt);
            
            switch (clientArray[currentClient].rushOrderInt)
            {
            case 0:
                printf_s("Regular order selected\n");
                clientArray[currentClient].rushOrder = false;
                exitChosen = true;
                break;
            case 1:
                printf_s("Rush order selected\n");
                clientArray[currentClient].rushOrder = true;
                exitChosen = true;
                break;
            default:
                printf_s("Invalid choice\n");
            }
        }
    else if (customerChoice == 2) //allows the customer to see progress on his/her order
    {
        printf_s("Enter your Customer ID\n");
        scanf_s("%d", &currentClient);
        printf_s("Current progress:\n %d Photos to print\n %d Photos to develop\n %d Photos printed\n %d Photos developed\n Deadline: %d/%d/%d\n", clientArray[currentClient].photosToPrint, clientArray[currentClient].photosToDevelop, clientArray[currentClient].photosPrinted, clientArray[currentClient].photosDeveloped, clientArray[currentClient].day, clientArray[currentClient].month, clientArray[currentClient].year);
    }
}

void photographer() // the photographer. the photographer can complete the orders by using the necessary materials.
{
    int photographerCustomerChoice;
    printf_s("Photographer chosen\n");
    printf_s("You currently have: %d paper, %d developer and %d ink\n", paperAmount, developerAmount, inkAmount);
    printf_s("Orders to complete:\n\n");
    for (int i = 0; i < clientCapacity; i++)
    {
        if (clientArray[i].isForwarded){
            printf_s("Customer %d has an uncomplete order!\n", i);
        }
    }

    printf_s("Select your customer. (Enter only number)\n");

    scanf_s("%d", &photographerCustomerChoice);
    
    while (!exitChosen)
    {
        printf_s("You have %d photos printed and %d photos developed\n", clientArray[photographerCustomerChoice].photosPrinted, clientArray[photographerCustomerChoice].photosDeveloped);
        printf_s("You have %d photos to print and %d photos to develop.\n\n", clientArray[photographerCustomerChoice].photosToPrint, clientArray[photographerCustomerChoice].photosToDevelop);
        printf_s("What would you like to do? (Enter only number)\n");
        printf_s("1. Develop photos\n2. Print photos\n3. Finish order.\n4. Pray for materials\n5. Exit\n");
    
        scanf_s("%d", &photographerChoice);
    
        switch (userChoice(photographerChoice))
        {
            case 1:
            if (paperAmount == 0 || developerAmount == 0) 
            { //case 1
                printf_s("Insufficient materials!\n");
                continue;
            }
                if (clientArray[photographerCustomerChoice].photosToDevelop > 0)  // main way to develop photos.
                {
                    printf_s("Developing photos.\n");
                    --clientArray[photographerCustomerChoice].photosToDevelop;
                    (*pntDeveloperAmount)--;
                    (*pntPaperAmount)--;
                    ++clientArray[photographerCustomerChoice].photosDeveloped;
                    //TODO: redo these into pointers
                    ++(*pntDeveloperSpent);
                    ++(*pntPaperSpent);
                    (*totalRevPntr) += *developCostPntr;
                    (*currentRevPntr) += *developCostPntr;
                }
                else printf_s("You dont need to develop any more photos\n");
                break;
            case 2:  // main way to print photos.

                if (clientArray[photographerCustomerChoice].photosToPrint > 0) {         
                    printf_s("Printing photos.\n");
                    --clientArray[photographerCustomerChoice].photosToPrint;
                    (*pntInkAmount)--;
                    ++clientArray[photographerCustomerChoice].photosPrinted;
                    ++(*pntInkSpent);
                    (*totalRevPntr) += *printCostPntr;
                    (*currentRevPntr) += *printCostPntr;
                }
                else printf_s("You dont need to print any more photos\n");
                break;


            case 3: // if all of the photos are printed and/or develop, the user can select this option to mark the order as "Complete"
                if (clientArray[photographerCustomerChoice].photosToPrint == 0 && clientArray[photographerCustomerChoice].photosToDevelop == 0) {
                    clientArray[photographerCustomerChoice].isCompleted = true;
                    clientArray[photographerCustomerChoice].isForwarded = false;
                    printf_s("Order Completed!\n");
                }
                else { //if there are photos still undone, this message will appear when trying to select the 'complete' option.
                    printf_s("Cannot complete order! Order still has photos to print/develop\n");
                }
                exitChosen = true;
                break;

            case 4: //temporary method to restock materials
                
                (*pntDeveloperAmount)++;
                (*pntPaperAmount)++;
                (*pntInkAmount)++;
                printf_s("Restocked");
                break;
            case 5:
                exitChosen = true;
                break;

            default:
                printf_s("Invalid choice\n");
                break;
        }
        clientArray[photographerCustomerChoice] = clientArray[currentClient];
    }
    
    
}
int main()
{
    clientArray = (client*)malloc(clientCapacity * sizeof(client));
    if (!clientArray) {
        printf_s("Memory allocation failed!\n");
        return 1;
    }
    
    // initialize all client slots
    for (int i = 0; i < clientCapacity; i++) {
        initClient(&clientArray[i]);
    }
    
    while(!fullExitChosen) //this is the main menu loop that allows the user to go back and forth between different roles
    {
        exitChosen = false; //used to make sure that the user can properly back out of a role (e.g photographer -> menu -> receptionist).
        
        printf_s("Choose your role: (Enter only number)\n"); // currently there's a bug where the system goes crazy if a user inputs a character instead of a number. planning to fix.
        printf_s("1. Receptionist (IN DEVELOPMENT)\n2. Customer (IN DEVELOPMENT)\n3. Photographer\n4. Quit Program\n"); // the choice can be made by inputting a number

        scanf_s("%d", &roleChosen); //user makes a choice using this function.
    
        switch (userChoice(roleChosen)) // this switch holds the necessary code for everything regarding different roles and their respective systems.
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
        
            case 4: // allows the user to quit the program by not closing the program by hand.
            printf_s("Quitting program\n");
            fullExitChosen = true;
            break;
        
        default:
            printf_s("Invalid choice\n");
            break;
        }
    }

    if (clientArray) {
        free(clientArray);
    }
    
    
    return 0;
}

