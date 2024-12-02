// Eyasu Berehanu
// Zuul
// This is an explorer game where you have to collected all 5 items to win
//Resoruces/Help From:
//
// Code from Classes, Student List, and Zuul from Java was used
// Copied an intrator example from https://www.geeksforgeeks.org/introduction-iterators-c/# for my drop function
// Ideas for storing inventory https://cplusplus.com/forum/beginner/52523/
//How to do a map came from https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
//Genral idea of exits and other ideas for came from https://courses.cs.vt.edu/~cs1114/api/student/adventure/Room.html
//map help https://stackoverflow.com/questions/4157687/using-char-as-a-key-in-stdmap
//nullptr help https://www.youtube.com/watch?v=yKT_Rwx4lsQ&ab_channel=BroCode
//help with auto again https://www.geeksforgeeks.org/range-based-loop-c/

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include "room.h"

using namespace std;

vector<char*> inventory;
int amountCollected = 0; 
void add(vector<char*>& inventory);
void moveRooms();
void drop(vector<char*>& inventory);
void win();

room* currentRoom = nullptr;

void menu() { //displays messages based on the actions of the player
  currentRoom->displayInfo();
currentRoom->displayExits();
    
    cout << "Inventory: ";
    for (auto& item : inventory) {
            cout << item << " ";  // Print the item in the inventory
        }
        cout << endl;
	win();
    }

void createRooms() { //creates all the 15 rooms for Zuul 
    room* frontentrence = new room("front entrance", "Computer", "outside the main entrance of the university");
    room* nurseroom = new room("nurse room", "na", "in a nurse room");
    room* supplycloset = new room("supply closet", "Mouse", "in a suplly closet (smells funky)");
    room* mainhall = new room("main hallway", "na", "in the main hallway");
    room* labroom = new room("laboratory room", "na", "in the labratory room (nerd.)");
    room* bathroom = new room("bathroom", "VR", "in the bathroom (did you flush...)");
    room* onehall = new room("1-hall", "na", "in 1-hall");
    room* computerroom = new room("computer room", "na", "in the computing room");
    room* studyroom = new room("study hall", "na", "in the study hall");
    room* gym = new room("gym", "Headphones", "in the gym");
    room* supplyroom = new room("equipment room", "Keyboard", "in a room with equipment (so much stuff...)");
    room* field = new room("track field", "na", "in the track field.");
 room* cafetria = new room("cafeteria", "na", "in the cafetria (yum!)");
    room* dinningroom = new room("dining room", "na", "in the dinning room (its time to grub!)");
    room* kitchen = new room("kitchen", "na", "in the kitchen (you cooking bro?)");

    frontentrence->setExit("west", mainhall);
    frontentrence->setExit("south", nurseroom);

    nurseroom->setExit("north", frontentrence);
    nurseroom->setExit("south", supplycloset);

    supplycloset->setExit("north", nurseroom);

    mainhall->setExit("north", labroom);
    mainhall->setExit("south", bathroom);
    mainhall->setExit("east", frontentrence);
    mainhall->setExit("west", onehall);

    bathroom->setExit("north", mainhall);

    labroom->setExit("west", computerroom);
    labroom->setExit("south", mainhall);

    onehall->setExit("north", computerroom);
    onehall->setExit("south", studyroom);
    onehall->setExit("east", mainhall);
    onehall->setExit("west", gym);

    computerroom->setExit("east", labroom);
    computerroom->setExit("south", onehall);

    gym->setExit("west", field);
    gym->setExit("north", supplyroom);
    gym->setExit("east", onehall);

    field->setExit("east", gym);


supplyroom->setExit("south", gym);

    studyroom->setExit("north", onehall);
    studyroom->setExit("south", cafetria);

    cafetria->setExit("north", studyroom);
    cafetria->setExit("south", dinningroom);
    cafetria->setExit("west", kitchen);

    kitchen->setExit("east", cafetria);

    dinningroom->setExit("north", cafetria);
    
    frontentrence->setItem("Computer");
    bathroom->setItem("VR");
    supplycloset->setItem("Mouse");
    supplyroom->setItem("Keyboard");
    gym->setItem("Headphones");
    
    currentRoom = frontentrence;
}

int main() { //prompts the player with options like move add drop or quit allowing the player to play the game
    vector<room*> rooms;

createRooms();

    char choice[80];
    bool start = true;

    while (start) {

      menu();
      cout << "Enter a command move add drop or quit: " << endl;
        cin.getline(choice, 80);

        if (strcmp(choice, "move") == 0) {
            moveRooms();
        } else if (strcmp(choice, "add") == 0) {
	  add(inventory);
	  
        } else if (strcmp(choice, "drop") == 0) {
	  drop(inventory);
	  
	} else if (strcmp(choice, "quit") == 0) {
            start = false; 
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    for (room* r : rooms) {
        delete r;
    }

    return 0;
}

void add(vector<char*>& inventory) { //adds the items in the room to players inventory staying with the player unless he drops it
   char* item = currentRoom->getStoredItems();
    if (item != nullptr) {

      char* items = new char[strlen(item) + 1];
      strcpy(items, item);
      inventory.push_back(items);
      amountCollected++;
      
      cout << "You added a " << item << endl;
      currentRoom->setItem(""); 

    } else {
        cout << "There is no item in this room." << endl;
    }
 }

void moveRooms() { //allows the player to choose a room and change rooms depending on direction and avaliblity
   char direction[80];
   cout << "Enter direction north, south, east, west" << endl;
    cin.getline(direction, 80);

    room* nextRoom = currentRoom->getExit(direction);

    if (nextRoom != nullptr) {
        currentRoom = nextRoom;
        cout << "You have moved to " << currentRoom->getCurrentRoom() << endl;
	// currentRoom->displayInfo();
    } else {
        cout << "No exit in that way" << endl;
    }
}

void drop(vector<char*>& inventory){ //drops the item in a room depending on the inputed item from the persons inventory
    char droppedItem[80];
    cout << "Enter item name:" << endl;
    cin.getline(droppedItem, 80);
   
     for (auto i = inventory.begin(); i != inventory.end(); ++i) {
        if (strcmp(*i, droppedItem) == 0) {
            char* itemDropped = *i;
            inventory.erase(i);

            currentRoom->setItem(itemDropped);

            cout << "You dropped the " << itemDropped << endl;
            return;
    }
}
}
void win() { //checks if all 5 items have been collected and inreturn ends the game and congraulats the player
    if (amountCollected == 5) {
        cout << "You have collected all the items. You Win!" << endl;
        exit(0);
    }
}
