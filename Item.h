#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <vector>

#include "Trigger.h"

class Item {
private:
	std::string name;
	std::string writing;
	std::string status;
	Trigger * turnon;
	std::vector<Trigger*> triggers;

protected:

public:
	Item(std::string n, std::string w, std::string s);
	virtual ~Item();
	std::string getName();
	std::string getWriting();
	std::string getStatus();
	void setStatus(std::string s);
	Trigger * getTurnon();
	void setTurnon(Trigger * trigger);
	std::vector<Trigger*> getTriggers();
	void addTrigger(Trigger * trigger);
	bool removeTrigger(Trigger * trigger);
};

#endif
