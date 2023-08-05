#include <stdio.h>
#include "structDef.h"
#include "funcPrototypes.h"
#include <string.h>

//Housing Society is an array of spaces
//A space can be a type of building such such as an apartment, a school, a park or a hospital
//Each type of building has its own struct of necessary info together
//Each instance of apartment or others are a struct with floors and other info
//Floors is an array of floor structs containing info about each floor

int main () {
    printf("\t\tWelcome to your Housing Society\n");
    for (int i = 0; i < 70; i++) {
        printf("=");
    }
    printf("\nEnter a name for your Housing Society (At most 100 characters): ");

    char name[100]; //Name of the housing society. At most 100 

    stringInputter(name); //Custom string inputting function to prevent uncertain behaviours of the program

    printf("\nName successfully saved!\n");

    int exit = 0, beginningInput, lastBlankPos = 0, caseOneExit = 0;
    struct Space hS[100]; //At most 100 spaces in our housing society. Housing Society to be called hS in short.


    while (exit == 0) {
        printf("\n");
        printf("[1] Add a Space\n");
        printf("[2] List Items\n");
        printf("[3] Get Info\n");
        printf("[4] Search for a Building\n");
        printf("[5] Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &beginningInput);
        
        if (beginningInput == 1 || beginningInput == 2 || beginningInput == 3 || beginningInput == 4 || beginningInput == 5) {
            switch (beginningInput) {
                case 1:
                    if (lastBlankPos < 100) {
                        while (caseOneExit == 0) {
                            printf("\nWhat type of space do you want to add?\n");
                            printf("[1] Add an Apartment Building\n"); //Max floors: 20
                            printf("[2] Add a School\n"); //Max Floors: 6
                            printf("[3] Add a Park\n"); //No floors
                            printf("[4] Add a Hospital\n"); //Max Floors: 10
                            printf("[5] Go Back\n");
                            printf("Enter your choice: ");
                        
                            int caseOneBegInput;
                            scanf("%d", &caseOneBegInput);

                            if (caseOneBegInput == 1 || caseOneBegInput == 2 || caseOneBegInput == 3 || caseOneBegInput == 4 || caseOneBegInput == 5) {
                                switch (caseOneBegInput) {
                                    case 1:
                                        //Initialize all floor array values as -1 and number of floors = 1
                                        hS[(lastBlankPos)].bd.ap.numberOfFloors = 0;
                                        memset(hS[(lastBlankPos)].bd.ap.floors->individualSizes, 0, sizeof(hS[(lastBlankPos)].bd.ap.floors->individualSizes));
                                        memset(hS[(lastBlankPos)].bd.ap.floors->types, -1, sizeof(hS[(lastBlankPos)].bd.ap.floors->types));
                                        
                                        addApart(hS, &lastBlankPos);
                                        break;
                                    case 2:
                                        hS[(lastBlankPos)].bd.sc.numberOfFloors = 0;
                                        memset(hS[(lastBlankPos)].bd.sc.floors, 0, sizeof(hS[(lastBlankPos)].bd.sc.floors));
                                        addSchool(hS, &lastBlankPos);
                                        break;
                                    case 3:
                                        addPark(hS, &lastBlankPos);
                                        break;
                                    case 4:
                                        hS[(lastBlankPos)].bd.hs.numberOfFloors = 0;
                                        memset(hS[(lastBlankPos)].bd.hs.floors, 0, sizeof(hS[(lastBlankPos)].bd.hs.floors));
                                        addHospital(hS, &lastBlankPos);
                                        break;
                                    case 5:
                                        caseOneExit = 1;
                                        break;
                                    default:
                                        break;
                                }
                            } else {
                                printf("Invalid input! Taking you back...\n");
                                continue;
                            }
                        }
                    } else {
                        printf("Sorry, no more space available.\n");
                    }
                    break;
                case 2:
                    listItems(hS, &lastBlankPos);
                    break;
                case 3:
                    getInfo(hS, &lastBlankPos);
                    break;
                case 4:
                    printf("Enter a name or address of a building to search for it: ");
                    char nameOrAddr[200];
                    scanf("%s", &nameOrAddr);
                    search(nameOrAddr, hS, &lastBlankPos);
                    break;
                case 5:
                    goto Exit;
                    break;
                default:
                    break;
            }

        } else {
            
            printf("Invalid input! Going back...\n");
            continue;
        }
    }

    Exit:
        printf("Successfully exited the Housing Society\n");
        return 0;
}

//Function Definitions:
void addApart(struct Space hS[], int * lastBlankPos) {
    //Required info: identifier, name, address, size, number of floors
    hS[(*lastBlankPos)].identifier = 1;
    printf("\nEnter a name for your apartment (At most 100 characters): \n");

    stringInputter(hS[(*lastBlankPos)].bd.ap.name);

    printf("\nEnter the address of your apartment (At most 200 characters): \n");

    stringInputter(hS[(*lastBlankPos)].bd.ap.address);

    
    printf("\nEnter the size of your apartment in sq. ft.: ");

    double sz;

    scanf("%lf", &sz);

    while (1) {
        if (sz <= 0) {
        //Size can't be zero or less
            printf("\nInvalid size. Enter again: ");
            scanf("%lf", &sz);
        } else {
            hS[(*lastBlankPos)].size = sz;
            break;
        }
    }

    printf("\nEnter number of floors (At most 20): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 20 && f > 0) {
        //At least one floor and not more than 20
            hS[(*lastBlankPos)].bd.ap.numberOfFloors = f;
            break;
        } else {
            printf("\nInvalid number. Enter again: ");
            scanf("%d", &f);
        }
    }

    int floorChoice, exit = 0;

    //i is the floor iterator
    //j is types and individualSizes iterator
    for (int i = 0; i < f; i++) {
        printf("\nEnter floor - %d info: \n", i+1);

        int floorChoice, floorExiter = 0;

        printf("\nHow many items do you want to have in this floor? [Max: 4]\n");
        printf("Enter: ");
        int items;
        scanf("%d", &items);

        while (1) {
            if (items > 0 && items <= 4) {
                break;
            } else {
                printf("Invalid input. Enter again: ");
                scanf("%d", &items);
            }
        }

        for (int j = 0; j < items; j++) {
            
            if (currentFloorSizeChecker(hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes, items) >= sz) {
                //If sum of the sizes of items already exceeds the original apartment size
                break;
            } else {
                printf("Add to this floor:\n");
                printf("[1] Add a Flat\n");
                printf("[2] Add a Store\n");
                printf("[3] Add an Office\n");
                printf("[4] Add a parking\n");
                printf("[5] Go to previous floor\n");
                printf("Enter your choice: ");

                scanf("%d", &floorChoice);

                while (floorExiter == 0) {
                    if (floorChoice == 1 || floorChoice == 2 || floorChoice == 3 || floorChoice == 4 || floorChoice == 5) {
                        switch (floorChoice) {
                            case 1:
                                printf("Enter size of the flat: ");
                                double sizeOfFlat;
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if (sizeOfFlat > sizeLeft(hS[(*lastBlankPos)].size, currentFloorSizeChecker(hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes, items))) {
                                        printf("Too big! Enter again: ");
                                        scanf("%lf", &sizeOfFlat);
                                    } else {
                                        break;
                                    }
                                }

                                hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                hS[(*lastBlankPos)].bd.ap.floors[i].types[j] = -100; //-100 for flat type

                                break;
                            case 2:
                                printf("Enter size of the store: ");
                                double sizeOfStore;
                                scanf("%lf", &sizeOfStore);

                                while (1) {
                                    if (sizeOfStore > sizeLeft(hS[(*lastBlankPos)].size, currentFloorSizeChecker(hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes, items))) {
                                        printf("Too big! Enter again: ");
                                        scanf("%lf", &sizeOfStore);
                                    } else {
                                        break;
                                    }
                                }

                                hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes[j] = sizeOfStore;
                                hS[(*lastBlankPos)].bd.ap.floors[i].types[j] = -200; //-100 for store type

                                break;
                            case 3:
                                printf("Enter size of the office: ");
                                double sizeOfOffice;
                                scanf("%lf", &sizeOfOffice);

                                while (1) {
                                    if (sizeOfOffice > sizeLeft(hS[(*lastBlankPos)].size, currentFloorSizeChecker(hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes, items))) {
                                        printf("Too big! Enter again: ");
                                        scanf("%lf", &sizeOfOffice);
                                    } else {
                                        break;
                                    }
                                }

                                hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes[j] = sizeOfOffice;
                                hS[(*lastBlankPos)].bd.ap.floors[i].types[j] = -300; //-300 for office type

                                break;
                            case 4:
                                printf("Enter size of the parking: ");
                                double sizeOfParking;
                                scanf("%lf", &sizeOfParking);

                                while (1) {
                                    if (sizeOfParking > sizeLeft(hS[(*lastBlankPos)].size, currentFloorSizeChecker(hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes, items))) {
                                        printf("Too big! Enter again: ");
                                        scanf("%lf", &sizeOfParking);
                                    } else {
                                        break;
                                    }
                                }

                                hS[(*lastBlankPos)].bd.ap.floors[i].individualSizes[j] = sizeOfParking;
                                hS[(*lastBlankPos)].bd.ap.floors[i].types[j] = -400; //-100 for parking type

                                break;
                            case 5:
                                goto previousFloor;
                                break;
                            default:
                                break;
                        }
                    } else {
                        printf("Invalid input. Enter again: ");
                        scanf("%d", &floorChoice);
                    }     
                }
            }
        }

        

    previousFloor:
        i -= 2; //Go back 2 floors so that when the increment occurs after the continue statement, it takes you to the previous floor
        continue;
        
    }

    (*lastBlankPos) += 1; //Set the new blank position in the housing society array to next position
}

void addSchool(struct Space hS[], int * lastBlankPos) {

}

void addPark(struct Space hS[], int * lastBlankPos) {

}

void addHospital(struct Space hS[], int * lastBlankPos) {

}

void listItems(struct Space hS[], int * lastBlankPos) {

}

void getInfo(struct Space hS[], int * lastBlankPos) {

}

void search(char string[], struct Space hS[], int * lastBlankPos) {

}

double currentFloorSizeChecker(double arr[], int limit) {
    double totalSize = 0;

    for (int i = 0; i < limit; i++) {
        totalSize += arr[i];
    }

    return totalSize;
}

double sizeLeft(double originalFloorSize, double currentFloorSize) {
    return originalFloorSize - currentFloorSize;
}

void stringInputter(char destination[]) {
    char ch;
    int it;

    for (it = 0; it < 99; it++) {
        ch = getchar();
        if (ch == '\n' && it == 0) {
            while (ch == '\n') {
                printf("This field cannot be blank! Enter again: ");
                ch = getchar();
            }
        } else if (ch == '\n') {
            break;
        } else {
            destination[it] = ch;
            destination[it+1] = '\0';
        }
    }
}



