#include "file.h"
#include "models.h"
#include <stdio.h>
#include <string.h>

bool fileExists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

bool saveStudioState(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file for saving!\n");
        return false;
    }
    
    fprintf(file, "STUDIO_STATE\n");
    fprintf(file, "%d %d %d\n", paperAmount, developerAmount, inkAmount);
    fprintf(file, "%d %d %d\n", paperSpent, developerSpent, inkSpent);
    fprintf(file, "%.2f %.2f\n", totalRevenue, currentRevenue);
    fprintf(file, "%.2f %.2f %.2f %.2f\n", paperCost, developerCost, inkCost, materialSpendingCost);
    fprintf(file, "%.2f %.2f\n", printCost, developCost);
    fprintf(file, "%d %d\n", clientCapacity, clientCurrentCount);
    
    fprintf(file, "CLIENTS\n");
    for (int i = 0; i < clientCapacity; i++) {
        const client* c = &clientArray[i];
        
        if (c->isOccupied) {
            fprintf(file, "%d %d %d %s\n", i, c->rushOrder ? 1 : 0, c->rushOrderInt, c->name);
            fprintf(file, "%d %d %d\n", c->day, c->month, c->year);
            fprintf(file, "%d %d %d %d\n", c->photosToPrint, c->photosToDevelop, 
                    c->photosPrinted, c->photosDeveloped);
            fprintf(file, "%d %d %d\n", c->isNew ? 1 : 0, c->isForwarded ? 1 : 0, 
                    c->isCompleted ? 1 : 0);
        }
    }
    
    fprintf(file, "END\n");
    fclose(file);
    
    printf("Studio state saved successfully to %s\n", filename);
    return true;
}

bool loadStudioState(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file for loading!\n");
        return false;
    }
    
    char buffer[100];
    
    if (!fgets(buffer, sizeof(buffer), file) || strcmp(buffer, "STUDIO_STATE\n") != 0) {
        printf("Error: Invalid file format!\n");
        fclose(file);
        return false;
    }
    
    fscanf(file, "%d %d %d\n", &paperAmount, &developerAmount, &inkAmount);
    fscanf(file, "%d %d %d\n", &paperSpent, &developerSpent, &inkSpent);
    fscanf(file, "%lf %lf\n", &totalRevenue, &currentRevenue);
    fscanf(file, "%lf %lf %lf %lf\n", &paperCost, &developerCost, &inkCost, &materialSpendingCost);
    fscanf(file, "%lf %lf\n", &printCost, &developCost);
    
    int savedCapacity, savedCount;
    fscanf(file, "%d %d\n", &savedCapacity, &savedCount);
    
    if (savedCapacity > clientCapacity) {
        resizeClientArray(savedCapacity);
    }
    
    clientCurrentCount = savedCount;
    
    fgets(buffer, sizeof(buffer), file);
    
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strcmp(buffer, "END\n") == 0) {
            break;
        }
        
        int index, rushOrder, rushOrderInt;
        char name[20];
        
        sscanf(buffer, "%d %d %d %[^\n]", &index, &rushOrder, &rushOrderInt, name);
        
        if (index >= 0 && index < clientCapacity) {
            client* c = &clientArray[index];
            c->isOccupied = true;
            c->rushOrder = rushOrder;
            c->rushOrderInt = rushOrderInt;
            strncpy(c->name, name, sizeof(c->name) - 1);
            c->name[sizeof(c->name) - 1] = '\0';
            
            fscanf(file, "%d %d %d\n", &c->day, &c->month, &c->year);
            fscanf(file, "%d %d %d %d\n", &c->photosToPrint, &c->photosToDevelop,
                   &c->photosPrinted, &c->photosDeveloped);
            
            int isNew, isForwarded, isCompleted;
            fscanf(file, "%d %d %d\n", &isNew, &isForwarded, &isCompleted);
            c->isNew = isNew;
            c->isForwarded = isForwarded;
            c->isCompleted = isCompleted;
        }
    }
    
    fclose(file);
    printf("Studio state loaded successfully from %s\n", filename);
    return true;
}