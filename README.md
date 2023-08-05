# housing-society
This project was originally created for my level-1 term-2 lab work as a revision of the C programming language. 

Let's dive deeper into the functionality of this program. This program has three major parts that you can focus to understand the workflow.
1. The definitions of structures and unions
2. The driver function (main function)
3. Function definitions


1. Structures and Unions:
The Housing Society is considered as an array of 'Spaces'. Each Space can be a building or a park. A building can be of a certain type which a user must choose. A building can be an apartment, a school, a hospital. Each building is a container of some info (identifier that idetifies a building as an apartment, school or hospital type) and an array of floors. Each floor is a struct that has some necessary info about each floor. Floors can have a overall size that has to be lower or equal to the space size. Because, the user can leave some room of the floor to be empty. But it can never be greater than the allocated space size.
