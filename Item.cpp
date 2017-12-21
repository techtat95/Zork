#include <string>
#include <iostream>

#include "Item.h"

Item::Item(std::string n, std::string w, std::string s) : turnon(nullptr) {
	name = n;
	writing = w;
	status = s;
}

Item::~Item() {}

std::string Item::getName() {
	return name;
}

std::string Item::getWriting() {
	return writing;
}

std::string Item::getStatus() {
	return status;
}

void Item::setStatus(std::string s) {
	status = s;
}

Trigger * Item::getTurnon() {
	return turnon;
}

void Item::setTurnon(Trigger * trigger) {
	turnon = trigger;
}

std::vector<Trigger*> Item::getTriggers() {
	return triggers;
}

void Item::addTrigger(Trigger * trigger) {
	triggers.push_back(trigger);
}

bool Item::removeTrigger(Trigger * trigger) {
	for (std::vector<Trigger*>::iterator iter = triggers.begin(); iter != triggers.end(); iter++) {
		if (trigger == (*iter)) {
			triggers.erase(iter);
			return true;
		}
	}
	return false;
}
