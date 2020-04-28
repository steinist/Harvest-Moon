# Harvest-Moon Game using C++
## HKUST Fall2020 - COMP2012: Object-Oriented Programming and Data Structure
## Assignment 2

### Introduction
This programming assignment aims to familiarize yoursef with the concepts of `inheritance` and `polymorphism`. At the same time, you will have the opportunity to work with the `ncurse` library.


### Task
The task is to complete all the missing function implementations in all `Todo*.cpp` and `Todo*.h` according to the description below.


### Description
#### About the Game
Harvest Moon is a turn-based game that you act as a manager to run a farm. With a smart investment strategy, you may buy properties and employ staff to make money. You may have a risk of bankruptcy due to bad management. Various employees are capable of making money in different types of properties, which may give you different rewards at the end of each turn. Both properties and employees are modeled by an abstract base class Object.

At each turn, the player can buy and build some properties ( Farmland, Cattlefarm ) on the screen. Different types of properties cost different amount of money to build. He can buy as many properties as he wishes at each turn as long as he has enough money. The properties have to be built on the screen without overlapping with each other. The player can also employ staff (Farmer, Feeder, even Cow) to make money in properties for him. Please note that he can assign an employee to a target property only if the property is suitable for that kind of employee. He may also upgrade properties he owns to make more money or to accommodate more employees.


#### Types of Properties
1. Property: This is an abstract base class of property.

2. Farmland: This models a farmland in the game (represented with 'R' on the screen; 'R' for Rice). It accommodates Employee and Farmer, and returns a random reward in the range [0, number of employees in work x 2 + number of farmers in work x 6 + level x 3) at the end of each turn. In this formula, number of employees counts only the number of Employee objects. For instance, if the 1-level farmland owns 2 Employee objects in WORK and 1 Farmer object in WORK, the formula should be [0, 2 x 2 + 1 x 6 + 1 x 3).

3. Cattlefarm: This models a cattle farm in the game (represented with 'C' on the screen; 'C' for Cow). It accommodates Feeder and Cow. At the end of each turn, it returns a reward equal to min(number of cows, number of feeders in work) x level x 10. It also checks the state of each cow, and removes those cows that have died.

void Cattlefarm::removeDiedCow(): It completely removes all the cows it owned if they are not alive.


#### Types of Employees
1. Employee: This is a basic type of employees (represented with "e" on the screen; 'e' for employee). He can handle only jobs from Farmland. He costs $5 and has a daily salary of $1 with the employment terms of 1-day work and 1-day rest.

2. Farmer: This models a farmer (represented with "r" on the screen; 'r' for rice). He can handle only jobs from Farmland. He costs $10 and has a daily salary of $2 with the employment terms of 3-day work and 1-day rest.

3. Feeder: This models a feeder (represented with "d" on the screen; 'd' for dairy). He can handle only jobs from Cattlefarm. He costs $20 and has a daily salary of $5 with the employment terms of 6-day work and 1-day rest.

4. Cow: This models a cow (represented with "c" on the screen; 'c' for cow). It can handle only jobs from Cattlefarm. It costs $15, has no salary but works everyday. It also has an attribute m_lifespan and will die after working for more days than its m_lifespan.

Each employee occupies a 1x1 space on the map. After being assigned to a property, Employees state will be changed between WORK (first) and REST. All kinds of employees get salaries in both WORK and REST states. Its position is set once he is assigned.


#### Scene
Scene is the object managing the basic game operations. It logs all the Object (both Property and Employee) on the screen. You may find the members and their details in Scene.h before implementing the member functions of Scene.
