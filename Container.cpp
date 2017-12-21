#include <string>
#include <iostream>

#include "Container.h"

Container::Container(std::string n, std::string s, Item * a) {
	name = n;
	status = s;
	accept = a;
}

Container::~Container() {}

std::string Container::getName() {
	return name;
}

std::string Container::getStatus() {
	return status;
}

void Container::setStatus(std::string s) {
	status = s;
}

Item * Container::getAccept() {
	return accept;
}

std::vector<Item*> Container::getItems() {
	return items;
}

Item * Container::getItem(std::string iName) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iName == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Container::addItem(Item * item) {
	std::string iName = item->getName();
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iName == (*iter)->getName()) return;
	}
	items.push_back(item);
}

void Container::removeItem(std::string iName) {
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iName == (*iter)->getName()) {
			items.erase(iter);
			return;
		}
	}
	return;
}

std::vector<Trigger*> Container::getTriggers() {
	return triggers;
}

void Container::addTrigger(Trigger * trigger) {
	triggers.push_back(trigger);
}

bool Container::removeTrigger(Trigger * trigger) {
	for (std::vector<Trigger*>::iterator iter = triggers.begin(); iter != triggers.end(); iter++) {
		if (trigger == (*iter)) {
			triggers.erase(iter);
			return true;
		}
	}
	return false;
}
