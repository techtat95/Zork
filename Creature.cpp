#include <string>
#include <iostream>

#include "Creature.h"

Creature::Creature(std::string n) : attack(nullptr) {
	name = n;
}

Creature::~Creature() {}


std::string Creature::getName() {
	return name;
}

std::vector<Item*> Creature::getVulns() {
	return vuln;
}

Item * Creature::getVuln(std::string iName) {
	std::vector<Item*>::iterator iter;
	for (iter = vuln.begin(); iter != vuln.end(); iter++) {
		if (iName == (*iter)->getName()) return (*iter);
	}
	return nullptr;
}

void Creature::addVuln(Item * item) {
	std::string iName = item->getName();
	std::vector<Item*>::iterator iter;
	for (iter = vuln.begin(); iter != vuln.end(); iter++) {
		if (iName == (*iter)->getName()) return;
	}
	vuln.push_back(item);
}

bool Creature::checkVuln(Item * item) {
	for (std::vector<Item*>::iterator iter = vuln.begin(); iter != vuln.end(); iter++) {
		if ((*iter) == item) return true;
	}
	return false;
}

Trigger * Creature::getAttack() {
	return attack;
}

void Creature::setAttack(Trigger * trigger) {
	attack = trigger;
}

std::vector<Trigger*> Creature::getTriggers() {
	return triggers;
}

void Creature::addTrigger(Trigger * trigger) {
	triggers.push_back(trigger);
}

bool Creature::removeTrigger(Trigger * trigger) {
	for (std::vector<Trigger*>::iterator iter = triggers.begin(); iter != triggers.end(); iter++) {
		if (trigger == (*iter)) {
			triggers.erase(iter);
			return true;
		}
	}
	return false;
}
