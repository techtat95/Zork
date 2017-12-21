#include <string>
#include <iostream>

#include "Trigger.h"

Trigger::Trigger() : used(false) {}

Trigger::~Trigger() {}

std::string Trigger::getType() {
	return type;
}

void Trigger::setType(std::string t) {
	type = t;
}

std::string Trigger::getCommand() {
	return command;
}

void Trigger::setCommand(std::string c) {
	command =  c;
}

std::string Trigger::getObject() {
	return object;
}

void Trigger::setObject(std::string o) {
	object = o;
}

std::string Trigger::getHas() {
	return has;
}

void Trigger::setHas(std::string h) {
	has = h;
}

std::string Trigger::getOwner() {
	return owner;
}

void Trigger::setOwner(std::string o) {
	owner  = o;
}

std::string Trigger::getStatus() {
	return status;
}

void Trigger::setStatus(std::string s) {
	status = s;
}

std::vector<std::string> Trigger::getPrints() {
	return prints;
}

void Trigger::addPrint(std::string p) {
	prints.push_back(p);
}

std::vector<std::string> Trigger::getActions() {
	return actions;
}

void Trigger::addAction(std::string a) {
	actions.push_back(a);
}

bool Trigger::getUsed() {
	return used;
}

void Trigger::setUsed(bool u) {
	used = u;
}
