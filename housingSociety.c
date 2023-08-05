#include <stdio.h>
#include <string.h>
#include "structDef.h"
#include "funcPrototypes.h"

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

    fgets(name, sizeof(name), stdin);

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
                                        memset(hS[(lastBlankPos)].bd.ap.floors, -1, sizeof(hS[(lastBlankPos)].bd.ap.floors));
                                        
                                        //addApart() will return 1 if everything goes on flow. That is the user properly inputs all floors and floor info correctly and completely.
                                        if (addApart) {

                                        } //More else if blocks and else block to come
                                        break;
                                    case 2:
                                        hS[(lastBlankPos)].bd.sc.numberOfFloors = 0;
                                        memset(hS[(lastBlankPos)].bd.sc.floors, -1, sizeof(hS[(lastBlankPos)].bd.sc.floors));
                                        addSchool(hS, &lastBlankPos);
                                        break;
                                    case 3:
                                        addPark(hS, &lastBlankPos);
                                        break;
                                    case 4:
                                        hS[(lastBlankPos)].bd.hs.numberOfFloors = 0;
                                        memset(hS[(lastBlankPos)].bd.hs.floors, -1, sizeof(hS[(lastBlankPos)].bd.hs.floors));
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
int addApart(struct Space hS[], int * lastBlankPos) {
    //Required info: identifier, name, address, floor number
    hS[(*lastBlankPos)].identifier = 1;
    printf("Enter a name for your apartment (At most 100 characters): \n");
    scanf("%s", &hS[(*lastBlankPos)].bd.ap.name);
    printf("Enter the address of your apartment (At most 200 characters): \n");
    scanf("%s", &hS[(*lastBlankPos)].bd.ap.address);
    printf("Enter the size of your apartment in sq. ft.: ");

    double sz;

    scanf("%lf", &sz);

    while (1) {
        if (sz <= 0) {
        //Size can't be zero or less
            printf("Invalid size. Enter again: ");
            scanf("%lf", &sz);
        } else {
            hS[(*lastBlankPos)].size = sz;
            break;
        }
    }

    printf("Enter number of floors (At most 20): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 20 && f > 0) {
        //At least one floor and not more than 20
            hS[(*lastBlankPos)].bd.ap.numberOfFloors = f;
            break;
        } else {
            printf("Invalid number. Enter again: ");
            scanf("%d", &f);
        }
    }

    int floorChoice, exit = 0;

    for (int i = 0; i < f; i++) {
        hS[(*lastBlankPos)].bd.ap.floors[i].id = i + 1;
        printf("Enter floor-%d info: \n", i+1);
        printf("[1] Add a Flat\n");
        printf("[2] Add a Store\n");
        printf("[3] Add a Parking\n");
        printf("[4] Add an Office\n");
        printf("[5] Go to Previous Floor\n");
        printf("[6] Go Back\n");
        printf("Ente your choice: ");

        scanf("%d", &floorChoice);

        while (exit == 0) {
            if (floorChoice == 1 || floorChoice == 2 || floorChoice == 3 || floorChoice == 4 || floorChoice == 5 || floorChoice == 6) {
                switch (floorChoice) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:

                        break;
                    default:
                        break;
                }
            } else {
                printf("Invalid input. Taking you back...\n");
                continue;
            }
        }


        
        
    }
    
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
