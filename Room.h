#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>

#include "Container.h"
#include "Creature.h"
#include "Item.h"
#include "Trigger.h"

class Room {
private:
	std::string name;
	std::string status;
	std::string type;
	std::string description;
	std::vector<Container*> containers;
	std::vector<Item*> items;
	std::vector<Creature*> creatures;
	std::vector<Trigger*> triggers;
	Room * north;
	Room * south;
	Room * east;
	Room * west;

protected:

public:
	Room(std::string n, std::string d, std::string t);
	virtual ~Room();
	std::string getName();
	std::string getDescription();
	std::string getType();
	std::string getStatus();
	void setStatus(std::string s);
	std::vector<Container*> getContainers();
	Container * getContainer(std::string cName);
	void addContainer(Container * container);
	void removeContainer(std::string cName);
	std::vector<Creature*> getCreatures();
	Creature * getCreature(std::string cName);
	void addCreature(Creature * creature);
	void removeCreature(std::string cName);
	std::vector<Item*> getItems();
	Item * getItem(std::string iName);
	void addItem(Item * item);
	void removeItem(std::string iName);
	std::vector<Trigger*> getTriggers();
	void addTrigger(Trigger * trigger);
	bool removeTrigger(Trigger * trigger);
	Room * getNorth();
	void setNorth(Room * room);
	Room * getSouth();
	void setSouth(Room * room);
	Room * getEast();
	void setEast(Room * room);
	Room * getWest();
	void setWest(Room * room);
	void setBorder(Room * n, Room * s, Room * e, Room * w);
};

#endif
