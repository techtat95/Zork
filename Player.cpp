#include <iostream>
#include <string>

#include "Player.h"

Player::~Player() { }

void Player::updateTriggers() {
	triggers.clear();

	std::vector<Trigger*> trigs = location->getTriggers();

	triggers.insert(triggers.end(), trigs.begin(), trigs.end());

	std::vector<Creature*> creatures = location->getCreatures();
	for (std::vector<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); iter++) {
		trigs = (*iter)->getTriggers();
		triggers.insert(triggers.end(), trigs.begin(), trigs.end());
	}

	std::vector<Container*> containers = location->getContainers();
	for (std::vector<Container*>::iterator iter = containers.begin(); iter != containers.end(); iter++) {
		trigs = (*iter)->getTriggers();
		triggers.insert(triggers.end(), trigs.begin(), trigs.end());
	}

	std::vector<Item*> itemsT = location->getItems();
	for (std::vector<Item*>::iterator iter = itemsT.begin(); iter != itemsT.end(); iter++) {
		trigs = (*iter)->getTriggers();
		triggers.insert(triggers.end(), trigs.begin(), trigs.end());
	}

	return;
}

Room * Player::getLocation() {
	return location;
}

void Player::setLocation(Room * room) {
	location = room;
	return;
}

std::vector<Item*> Player::getItems() {
	return items;
}

Item * Player::getItem(std::string name) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (name == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Player::addItem(Item * item) {
	std::string name = item->getName();
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (name == (*iter)->getName()) return;
	}
	items.push_back(item);
	return;
}

void Player::removeItem(std::string name) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (name == (*iter)->getName()) {
			items.erase(iter);
			return;
		}
	}
	return;
}

std::vector<Trigger*> Player::getTriggers() {
	updateTriggers();
	return triggers;
}

void Player::removeTrigger(Trigger * trigger) {
	std::vector<Trigger*> trigs;

	bool done = location->removeTrigger(trigger);

	if (!done) {
		std::vector<Creature*> creatures = location->getCreatures();
		for (std::vector<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); iter++) {
			done = (*iter)->removeTrigger(trigger);
		}
	}

	if (!done){
		std::vector<Container*> containers = location->getContainers();
		for (std::vector<Container*>::iterator iter = containers.begin(); iter != containers.end(); iter++) {
			trigs = (*iter)->getTriggers();
			for (std::vector<Trigger*>::iterator iterT = trigs.begin(); iterT != trigs.end(); iterT++) {
				done = (*iter)->removeTrigger(trigger);
			}
		}
	}

	if (!done) {
		std::vector<Item*> itemsT = location->getItems();
		for (std::vector<Item*>::iterator iter = itemsT.begin(); iter != itemsT.end(); iter++) {
			trigs = (*iter)->getTriggers();
			for (std::vector<Trigger*>::iterator iterT = trigs.begin(); iterT != trigs.end(); iterT++) {
				done = (*iter)->removeTrigger(trigger);
			}
		}
	}

	for (std::vector<Trigger*>::iterator iter = triggers.begin(); iter != triggers.end(); iter++) {
		if (trigger == (*iter)){
			triggers.erase(iter);
			return;
		}
	}
}
