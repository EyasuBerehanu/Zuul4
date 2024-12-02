#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <cstring>
 #include <map>

using namespace std;

class room { //defins of the DigitalMedia
protected:
  char* currentRoom; //pointer to char array storing current room
  map<char*, room*> exits; //allows the game to map out diffrent driections
  char* storedItems; //pointer to char array storing the stored items
  char* description; //pointed to char array storing the description
   
public:
    room(); 
    room(char* cr, char* si, char* d); //constructor that takes char pointer
    virtual ~room();
  
    char* getCurrentRoom();
    char* getStoredItems();
    char* getDescription();

  void setExit(char* direction, room* availibleRooms);
  room* getExit(char* direction);
  void setItem(char* items);
  
  virtual void displayInfo(); 
virtual void displayExits();

  
};

#endif
