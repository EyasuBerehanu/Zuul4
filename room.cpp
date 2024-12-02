#include "room.h"
#include <iostream>
#include <cstring>
using namespace std;

room::room() { //I had to add these because if i didnt define it as empty or a nullptr the game wouldnt load and function properally
  currentRoom = nullptr;
  storedItems = nullptr;
  description = nullptr;
}
room::room(char* cr, char* si, char* d) { //constructor for the aspects of a or the room

    currentRoom = new char[80];
    strcpy(currentRoom, cr);
  
    storedItems = new char[80];
    strcpy(storedItems, si);

    description = new char[80];
    strcpy(description, d); 
}
room::~room() { //destructor for the aspects of the room
    delete[] currentRoom;
    delete[] description;
    delete[] storedItems;
}

char* room::getCurrentRoom(){ //getter for the current Room;
  return currentRoom;
}
char* room::getDescription(){ //getter for description
  return description;
}
char* room::getStoredItems(){ //getter for storedItems
    return storedItems;
}

void room::setExit(char* direction, room* avalibleRooms){ //allows rooms to be connect by giving a direction for the possible exits or the avalibles rooms that you alound to go to 
  char* avaliableExits = new char[80];
  strcpy(avaliableExits, direction);
  exits[avaliableExits] = avalibleRooms;
}

room* room::getExit(char* direction){ //lets the player get theexit that want to go to and the returns a pointer fot that exit if it exisit leting them move
  for (auto& exit : exits) {
        if (strcmp(exit.first, direction) == 0) {
            return exit.second;
        }
}
}
void room::setItem(char* items) { //assigns items to each room if there is and if there isint I put an "na" in it
   if (storedItems != nullptr) {
        delete[] storedItems;
    }
   
    storedItems = new char[strlen(items) + 1];
    strcpy(storedItems, items);
}


void room::displayInfo(){ //just displays the info
    cout << "You are in: " << currentRoom << endl;
    cout << "Description: " << description << endl;
    cout << "Item in this room: " << storedItems << endl;
}

void room::displayExits() { //displays the exits based on the map used and the given exits for each room
  cout << "Exits: " << endl;
        for (auto& exit : exits) {
            cout << exit.first << " ";
        }
        cout << endl;
    }

