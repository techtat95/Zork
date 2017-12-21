#include <string>
#include <iostream>

#include "Room.h"

Room::Room(std::string n, std::string d, std::string t) : north(nullptr), south(nullptr), east(nullptr), west(nullptr) {
	name = n;
	description = d;
	type = t;
}

Room::~Room() {}

std::string Room::getName() {
	return name;
}

std::string Room::getDescription() {
	return description;
}

std::string Room::getType() {
	return type;
}

std::string Room::getStatus() {
	return status;
}

void Room::setStatus(std::string s) {
	status = s;
}

std::vector<Container*> Room::getContainers() {
	return containers;
}

Container * Room::getContainer(std::string cName) {
	std::vector<Container*>::iterator iter;
	for (iter = containers.begin(); iter != containers.end(); iter++) {
		if (cName == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Room::addContainer(Container * container) {
	std::string cName = container->getName();
	std::vector<Container*>::iterator iter;
	for (iter = containers.begin(); iter != containers.end(); iter++) {
		if (cName == (*iter)->getName()) return;
	}
	containers.push_back(container);
}

void Room::removeContainer(std::string cName) {
	std::vector<Container*>::iterator iter;
	for (iter = containers.begin(); iter != containers.end(); iter++) {
		if (cName == (*iter)->getName()) {
			containers.erase(iter);
			return;
		}
	}
	return;
}

std::vector<Creature*> Room::getCreatures() {
	return creatures;
}

Creature * Room::getCreature(std::string cName) {
	std::vector<Creature*>::iterator iter;
	for (iter = creatures.begin(); iter != creatures.end(); iter++) {
		if (cName == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Room::addCreature(Creature * creature) {
	std::string cName = creature->getName();
	std::vector<Creature*>::iterator iter;
	for (iter = creatures.begin(); iter != creatures.end(); iter++) {
		if (cName == (*iter)->getName()) return;
	}
	creatures.push_back(creature);
}

void Room::removeCreature(std::string cName) {
	std::vector<Creature*>::iterator iter;
	for (iter = creatures.begin(); iter != creatures.end(); iter++) {
		if (cName == (*iter)->getName()) {
			creatures.erase(iter);
			return;
		}
	}
	return;
}

std::vector<Item*> Room::getItems() {
	return items;
}

Item * Room::getItem(std::string iName) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iName == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Room::addItem(Item * item) {
	std::string iName = item->getName();
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iName == (*iter)->getName()) return;
	}
	items.push_back(item);
}

void Room::removeItem(std::string iName) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iName == (*iter)->getName()) {
			items.erase(iter);
			return;
		}
	}
	return;
}

std::vector<Trigger*> Room::getTriggers() {
	return triggers;
}

void Room::addTrigger(Trigger * trigger) {
	triggers.push_back(trigger);
}

bool Room::removeTrigger(Trigger * trigger) {
	for (std::vector<Trigger*>::iterator iter = triggers.begin(); iter != triggers.end(); iter++) {
		if (trigger == (*iter)) {
			triggers.erase(iter);
			return true;
		}
	}
	return false;
}

Room * Room::getNorth() {
	return north;
}

void Room::setNorth(Room * room) {
	north = room;
}

Room * Room::getSouth() {
	return south;
}

void Room::setSouth(Room * room) {
	south = room;
}

Room * Room::getEast() {
	return east;
}

void Room::setEast(Room * room) {
	east = room;
}

Room * Room::getWest() {
	return west;
}

void Room::setWest(Room * room) {
	west = room;
}

void Room::setBorder(Room * n, Room * s, Room * e, Room * w) {
	north = n;
	south = s;
	east = e;
	west = w;
}
