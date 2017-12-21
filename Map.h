#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "Room.h"

class Map {
private:
	Room * entrance;
	std::vector<Room*> exits;
	std::vector<Room*> rooms;
	std::vector<Container*> containers;
	std::vector<Creature*> creatures;
	std::vector<Item*> items;
	std::vector<Trigger*> triggers;

protected:

public:
	virtual ~Map();
	Room * getEntrance();
	void setEntrance(Room * room);
	std::vector<Room*> getExits();
	void addExit(Room * room);
	std::vector<Room*> getRooms();
	Room * getRoom(std::string name);
	void addRoom(Room * room);
	std::vector<Container*> getContainers();
	Container * getContainer(std::string name);
	void addContainer(Container * container);
	std::vector<Creature*> getCreatures();
	Creature * getCreature(std::string cName);
	void addCreature(Creature * creature);
	std::vector<Item*> getItems();
	Item * getItem(std::string name);
	void addItem(Item * item);
	void removeItem(std::string name);
	void addTrigger(Trigger * trigger);
	void resetTriggers();
};



#endif
