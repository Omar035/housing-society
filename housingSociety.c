#include <stdio.h>
#include "structDef.h"
#include "funcPrototypes.h"
#include <string.h>
#define building hS[(*lastBlankPos)].bd

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

    stringInputter(building.ap.name);

    printf("\nEnter the address of your apartment (At most 200 characters): \n");

    stringInputter(building.ap.address);

    
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
            building.ap.numberOfFloors = f;
            break;
        } else {
            printf("\nInvalid number. Enter again: ");
            scanf("%d", &f);
        }
    }


    //i is the floor iterator
    //j is types and individualSizes iterator
    for (int i = 0; i < f; i++) {
        printf("\nEnter floor - %d info: \n", i+1);
        
        int floorChoice;

        printf("\nHow many items do you want to have in this floor? Items include flats, stores, offices and parkings. [Max: 4]\n");
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
            
            if (currentFloorSizeChecker(building.ap.floors[i].individualSizes, items) >= sz) {
                //If sum of the sizes of items already exceeds the original apartment size
                break;
            } else {
                int floorExit = 0;
                while (floorExit == 0) {
                    printf("\nAdd item - %d:\n", j+1);
                    printf("[1] Add a Flat\n");
                    printf("[2] Add a Store\n");
                    printf("[3] Add an Office\n");
                    printf("[4] Add a parking\n");
                    printf("[5] Go to previous floor\n");
                    printf("Enter your choice: ");

                    scanf("%d", &floorChoice);

                    double sizeOfFlat;

                    if (floorChoice == 1 || floorChoice == 2 || floorChoice == 3 || floorChoice == 4 || floorChoice == 5) {
                        switch (floorChoice) {
                            case 1:
                                printf("Enter size of the flat: ");
                                scanf("%lf", &sizeOfFlat);

                                //Filter for negative inputs
                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors->individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Flat size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -100; //-100 for flat type

                                break;
                            case 2:
                                printf("Enter size of the store: ");
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors->individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Store size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -200; 

                                break;
                            case 3:
                                printf("Enter size of the office: ");
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors->individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Office size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -300; 

                                break;
                            case 4:
                                printf("Enter size of the parking: ");
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors->individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Parking size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -400;
                                building.ap.floors->floorSize = currentFloorSizeChecker(building.ap.floors->individualSizes, items); //Store the floor size. It can be smaller than actual space size. Because the user can leave some floor space empty. 

                                break;
                            case 5:
                                if (j == 0) {
                                    printf("You're in the first floor now. There's no previous floor!\n");
                                    j-=1; //After this block, i increases to 1 thus skipping inputs for the 0th (1st) floor. To get the user back there, i is decreased by 1 beforehand.
                                } else {
                                    j-=2; //Go back 2 floors so that when the increment occurs after the continue statement, it takes you to the previous floor
                                    printf("Now you're back to floor - %d\n", j+1);
                                    continue;
                                }
                                break;
                            default:
                                break;
                        }

                        floorExit = 1;
                    } else {
                        printf("Invalid input. Enter again: ");
                        scanf("%d", &floorChoice);
                    }
                }
            }
        }
    }

    printf("\nSuccessfully added the apartment: %s\n", building.ap.name);
    (*lastBlankPos) += 1; //Set the new blank position in the housing society array to next position
}

void addSchool(struct Space hS[], int * lastBlankPos) {
    hS[(*lastBlankPos)].identifier = 2;
    printf("\nEnter a name for your school (At most 100 characters): \n");

    stringInputter(building.sc.name);

    printf("\nEnter the address of your school (At most 200 characters): \n");

    stringInputter(building.sc.address);

    
    printf("\nEnter the size of your school in sq. ft.: ");

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

    printf("\nEnter number of floors (At most 6): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 6 && f > 0) {
        //At least one floor and not more than 6
            building.sc.numberOfFloors = f;
            break;
        } else {
            printf("\nInvalid number. Enter again: ");
            scanf("%d", &f);
        }
    }

    printf("Successfully added a school.\n");
    (*lastBlankPos) += 1;
}

void addPark(struct Space hS[], int * lastBlankPos) {
    hS[(*lastBlankPos)].identifier = 3;
    printf("\nEnter a name for your park (At most 100 characters): \n");

    stringInputter(building.pk.name);

    printf("\nEnter the address of your park (At most 200 characters): \n");

    stringInputter(building.pk.address);

    
    printf("\nEnter the size of your park in sq. ft.: ");

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

    printf("Successfully added a park.\n");
    (*lastBlankPos) += 1;
}

void addHospital(struct Space hS[], int * lastBlankPos) {
hS[(*lastBlankPos)].identifier = 2;
    printf("\nEnter a name for your hospital (At most 100 characters): \n");

    stringInputter(building.hs.name);

    printf("\nEnter the address of your hospital (At most 200 characters): \n");

    stringInputter(building.hs.address);

    
    printf("\nEnter the size of your hospital in sq. ft.: ");

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

    printf("\nEnter number of floors (At most 6): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 10 && f > 0) {
        //At least one floor and not more than 10
            building.hs.numberOfFloors = f;
            break;
        } else {
            printf("\nInvalid number. Enter again: ");
            scanf("%d", &f);
        }
    }

    printf("Successfully added a hospital.\n");
    (*lastBlankPos) += 1;
}

void listItems(struct Space hS[], int * lastBlankPos) {

}

void getInfo(struct Space hS[], int * lastBlankPos) {

}

void search(char string[], struct Space hS[], int * lastBlankPos) {
    int searchExiter = 0, atLeastOneMatchFound = 0;

    while (searchExiter == 0) {
        printf("\nWhat do you want search by?\n");
        printf("[1] Name\n");
        printf("[2] Address\n");

        int searchChoice;
        scanf("%d", &searchChoice);

        if (searchChoice == 1 || searchChoice == 2) {
            for (int i = 0; i <= (*lastBlankPos); i++) {
                if (hS[i].identifier == 1 && (hS[i].bd.ap.name == string || hS[i].bd.ap.address)) {
                    printf("\nAn apartment named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.ap.name, hS[i].bd.ap.address, i+1);
                    atLeastOneMatchFound = 1;
                } else if (hS[i].identifier == 2 && (hS[i].bd.sc.name == string || hS[i].bd.sc.address)) {
                    printf("\nA school named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.sc.name, hS[i].bd.sc.address, i+1);
                    atLeastOneMatchFound = 1;
                } else if (hS[i].identifier == 3 && (hS[i].bd.pk.name == string || hS[i].bd.pk.address)) {
                    printf("\nA park named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.pk.name, hS[i].bd.pk.address, i+1);
                    atLeastOneMatchFound = 1;
                } else if (hS[i].identifier == 4 && (hS[i].bd.hs.name == string || hS[i].bd.hs.address)) {
                    printf("\nA hospital named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.hs.name, hS[i].bd.hs.address, i+1);
                    atLeastOneMatchFound = 1;
                }
            }

            //If the program finishes the for loop with atLeastOneMatchFound = 0, that means no results were found.
            if (atLeastOneMatchFound == 0) {
                printf("\nNo results found!\n");
            } 

            searchExiter = 1; //Done with searching. Break the while loop and exit this function.
        } else {
            printf("Invalid choice. Enter agaain: ");
            scanf("%d", &searchChoice);
        }
    }
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

