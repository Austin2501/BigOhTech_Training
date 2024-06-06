#include <iostream>
#include "System.h"
#include "User.h"
#include "Country.h"
#include "City.h"
#include "Wall.h"
#include "Brick.h"
#include "Comment.h"

int main() {
    System system;

    // Create users
    User* alice = new User("Alice");
    User* bob = new User("Bob");
    User* charlie = new User("Charlie");
    User* dave = new User("Dave");

    // Add users to the system
    system.addUser(alice);
    system.addUser(bob);
    system.addUser(charlie);
    system.addUser(dave);

    // Create a country
    Country* country = new Country("Wonderland");
    system.addCountry(country);

    // Create cities
    City* city1 = new City("Hearts");
    City* city2 = new City("Diamonds");

    // Add cities to the country
    country->addCity(city1);
    country->addCity(city2);

    // Create walls
    Wall* wall1 = new Wall();
    Wall* wall2 = new Wall();

    // Add walls to the cities
    city1->addWall(wall1);
    city2->addWall(wall2);

    // Create bricks
    Brick* brick1 = new Brick("Love", "Alice loves Bob", alice, bob);
    Brick* brick2 = new Brick("Friendship", "Charlie and Dave are best friends", charlie, dave);

    // Add bricks to the walls
    wall1->addBrick(brick1);
    wall2->addBrick(brick2);

    // Add bricks to the users
    alice->addBrick(brick1);
    charlie->addBrick(brick2);

    // Display the hottest and lonely users
    system.displayHottestUser();
    system.displayLonelyUser();

    return 0;
}
