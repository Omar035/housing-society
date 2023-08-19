# housing-society
This project was originally created for my level-1 term-2 lab work as a revision of the C programming language. 

Let's dive deeper into the functionality of this program. This program has three major parts that you can focus to understand the workflow.
A. The definitions of structures and unions,
B. The driver function (main function),
C. Function definitions.

A. Structures and Unions:
The Housing Society is considered as an array of 'Spaces'. Each Space can be a building or a park. A building can be of a certain type which a user must choose. A building can be an apartment, a school, a hospital. Each building is a container of some info (identifier that idetifies a building as an apartment, school or hospital type) and an array of floors. Each floor is a struct that has some necessary info about each floor. Floors can have a overall size that has to be lower or equal to the space size. Because, the user can leave some room of the floor to be empty. But it can never be greater than the allocated space size.

Programatically, There is a 'Building' union declared inside a 'Space' struct. And there are 'Apartment', 'School', 'Park' and 'Hosptal' structs inside the 'Building' union. How does this construction help? Let's understand:

As we know about the functionality of unions, any ONE of its existing members can be occupied and accessed. Thus, to save space, we created a union named 'Building' so that it can either populate 'Apartment' or 'School' and so on. Additionally, to keep track of which of the members of our 'Building' union is being used, we added an 'identifier' variable as a member of the 'Space' struct. 

//More to write
