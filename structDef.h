struct Space {
    //Apartment = 1, School = 2, Park = 3, Hospital = 4
    int identifier; 
    double size;

    struct Floor {
            int id; //which floor
            int items; //How many types in a particular floor; At most 4 [Store, Parking, Flat, Office]
            double size;
            int types[4];
            double individualSizes[4]; //Size of individual type
        };

    union Building {
        //Internal structures' definitions of the housing society:
        struct Apartment {
            char name[100]; //Prompt and prevent user from inputting more than 100 characters
            char address[200]; //Prompt and prevent user from inputting more than 200 chars
            int numberOfFloors;
            struct Floor floors[20];
        } ap;

        struct School {
            char name[100];
            char address[200];
            int numberOfFloors;
            struct Floor floors[6]; //At most 6 floors 
        } sc;

        struct Park {
            char name[100];
            char address[200];
            int hasKidsPlayground; //1 if yes, 0 if no
            //No floors input for a park
        } pk;

        struct Hospital {
            char name[100];
            char address[200];
            char type[50]; //Cardiac, Orthopedic, General, Diagnostic etc.
            int numberOfFloors;
            struct Floor floors[10]; //At most 10 floors
        } hs;
    } bd;
};
