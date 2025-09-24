
#include <stdio.h>
#include <stdbool.h>

int main()
{
    int roleChosen = 0;
    
    int paperAmount = 5;
    int developerAmount = 5;
    int inkAmount = 5;

    int paperSpent = 0;
    int developerSpent = 0;
    int inkSpent = 0;

    int photosToPrint = 5;
    int photosToDevelop = 5;
    int photosPrinted = 0;
    int photosDeveloped = 0;

    double totalRevenue = 0.0;
    
    bool exitChosen = false;
    bool fullExitChosen = false;

    int photographerChoice = 0;
    int receptionistChoice = 0;

    while(!fullExitChosen)// lisa ka functioni mis laseb kasutajal kontrollida mis materjalid alles on + mitu fotod oli valmis tehtud.
    {
        exitChosen = false; //used to make sure that the role selection while loop works correctly. 
        
        printf_s("Choose your role: (Enter only number)\n");
        printf_s("1. Receptionist (IN DEVELOPMENT)\n2. Customer (IN DEVELOPMENT)\n3. Photographer\n4. Quit Program\n");

        scanf_s("%d", &roleChosen); //user makes a choice using this function.
    
        switch (roleChosen) // this switch holds the necessary code for everythin
        {
        case 1:
            printf_s("Receptionist chosen\n");

            while (!exitChosen) {


                printf_s("What would you like to do? (Enter only number)\n");
                printf_s("1. View pending orders\n2. View ongoing orders\n3. View completed orders\n4. View today's revenue\n5. View today's spent materials\n6. Exit\n");

                scanf_s("%d", &receptionistChoice);

                switch (receptionistChoice) // since currently we do not have an order making system i can not create a system to arrange the orders
                {
                case 1:
                    printf_s("Viewing pending orders\n--------------\n");
                    break;

                case 2:
                    printf_s("Viewing ongoing orders\n--------------\n");
                    break;

                case 3:
                    printf_s("Viewing completed orders\n---------------\n");
                    break;

                case 4:
                    printf_s("Viewing today's revenue\n--------------\n");
                    printf_s("Today's revenue = %.2lf\n", totalRevenue);
                    break;

                case 5:
                    printf_s("Viewing today's spent materials\n---------------\n");
                    printf_s("Ink spent = %d\nPaper spent = %d\nDeveloper spent = %d\n", inkSpent, paperSpent, developerSpent);
                    break;

                case 6:
                    exitChosen = true;
                    break;

                default:
                    printf_s("Invalid choice\n");
                    break;
                }
            }
            break;
        case 2:
            printf_s("Customer chosen\n");

            printf_s("What would you like to do? (Enter only number)\n");
            printf_s("1. Develop photos\n2. Print photos\n3. Exit\n4. Submit a report. (IN DEVELOPMENT)\n");
            break;
        case 3:
            printf_s("Photographer chosen\n");
            printf_s("You currently have: %d paper, %d developer and %d ink\n", paperAmount, developerAmount, inkAmount);
            
            while (!exitChosen)
            {
                printf_s("You have %d photos printed and %d photos developed\n", photosPrinted, photosDeveloped);
                printf_s("You have %d photos to print and %d photos to develop.\n\n", photosToPrint, photosToDevelop);
                printf_s("What would you like to do? (Enter only number)\n");
                printf_s("1. Develop photos\n2. Print photos\n3. Exit\n4. Submit a report. (IN DEVELOPMENT)\n");
            
                scanf_s("%d", &photographerChoice);
            
                switch (photographerChoice)
                {
                    case 1: // lisa if checki mis annab erineva lause kui sul on materjalid otsas.
                    if (paperAmount == 0 || developerAmount == 0)
                    {
                        printf_s("Insufficient materials!\n");
                        continue;
                    }
                    
                        printf_s("Developing photos.\n");
                        --photosToDevelop;
                        --developerAmount;
                        --paperAmount;
                        ++photosDeveloped;
                        ++developerSpent;
                        ++paperSpent;
                        break;
                    case 2:
                        break;
                    case 3:
                        exitChosen = true;
                        break;
                    default:
                        printf_s("Invalid choice\n");
                        break;
                }
            }
            break;
            case 4:
            printf_s("Quitting program\n");
            fullExitChosen = true;
            break;
            default:
            printf_s("Invalid choice\n");
            break;
        }
    }
    
    
    return 0;
}

