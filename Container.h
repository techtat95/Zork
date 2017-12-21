#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <string>
#include <vector>

#include "Item.h"
#include "Trigger.h"

class Container {
private:
	std::string name;
	std::string status;
	Item * accept;
	std::vector<Item*> items;
	std::vector<Trigger*> triggers;

protected:

public:
	Container(std::string n, std::string s, Item * a);
	virtual ~Container();
	std::string getName();
	std::string getStatus();
	void setStatus(std::string s);
	Item * getAccept();
	std::vector<Item*> getItems();
	Item * getItem(std::string iName);
	void addItem(Item * item);
	void removeItem(std::string name);
	std::vector<Trigger*> getTriggers();
	void addTrigger(Trigger * trigger);
	bool removeTrigger(Trigger * trigger);
};

#endif
