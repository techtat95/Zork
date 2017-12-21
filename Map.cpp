#include <iostream>
#include <string>

#include "Map.h"

Map::~Map() { }

Room * Map::getEntrance() {
	return entrance;
}

void Map::setEntrance(Room * room) {
	entrance = room;
}

std::vector<Room*> Map::getExits() {
	return exits;
}

void Map::addExit(Room * room) {
	std::string name = room->getName();
	std::vector<Room*>::iterator iter;
	for (iter = exits.begin(); iter != exits.end(); iter++) {
		if (name == (*iter)->getName()) return;
	}
	exits.push_back(room);
}

std::vector<Room*> Map::getRooms() {
	return rooms;
}

Room * Map::getRoom(std::string name) {
	std::vector<Room*>::iterator iter;
	for (iter = rooms.begin(); iter != rooms.end(); iter++) {
		if (name == (*iter)->getName()) return (*iter);
	}

	return nullptr;
}

void Map::addRoom(Room * room) {
	std::string name = room->getName();
	std::vector<Room*>::iterator iter;
	for (iter = rooms.begin(); iter != rooms.end(); iter++) {
		if (name == (*iter)->getName()) return;
	}
	rooms.push_back(room);
}

std::vector<Container*> Map::getContainers() {
	return containers;
}

Container * Map::getContainer(std::string name) {
	std::vector<Container*>::iterator iter;
	for (iter = containers.begin(); iter != containers.end(); iter++) {
		if (name == (*iter)->getName()) return (*iter);
	}

	return nullptr;
}

void Map::addContainer(Container * container) {
	std::string name = container->getName();
	std::vector<Container*>::iterator iter;
	for (iter = containers.begin(); iter != containers.end(); iter++) {
		if (name == (*iter)->getName()) return;
	}
	containers.push_back(container);
}

std::vector<Creature*> Map::getCreatures() {
	return creatures;
}

Creature * Map::getCreature(std::string cName) {
	std::vector<Creature*>::iterator iter;
	for (iter = creatures.begin(); iter != creatures.end(); iter++) {
		if (cName == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Map::addCreature(Creature * creature) {
	std::string cName = creature->getName();
	std::vector<Creature*>::iterator iter;
	for (iter = creatures.begin(); iter != creatures.end(); iter++) {
		if (cName == (*iter)->getName()) return;
	}
	creatures.push_back(creature);
}


std::vector<Item*> Map::getItems() {
	return items;
}

Item * Map::getItem(std::string name) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (name == (*iter)->getName()) return (*iter);
	}

	return nullptr;
}

void Map::addItem(Item * item) {
	std::string name = item->getName();
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (name == (*iter)->getName()) return;
	}
	items.push_back(item);
}

void Map::removeItem(std::string name) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (name == (*iter)->getName()) {
			items.erase(iter);
			return;
		}
	}
	return;
}

void Map::addTrigger(Trigger * trigger) {
	triggers.push_back(trigger);
}

void Map::resetTriggers() {
	for (std::vector<Trigger*>::iterator iter = triggers.begin(); iter != triggers.end(); iter++) {
		if ((*iter)->getType() == "permanent") (*iter)->setUsed(false);
	}
}
