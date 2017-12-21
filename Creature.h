#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <vector>

#include "Item.h"
#include "Trigger.h"

class Creature {
private:
	std::string name;
	std::string status;
	std::vector<Item*> vuln;
	Trigger * attack;
	std::vector<Trigger*> triggers;

protected:

public:
	Creature(std::string n);
	virtual ~Creature();
	std::string getName();
	std::vector<Item*> getVulns();
	Item * getVuln(std::string iName);
	void addVuln(Item * item);
	bool checkVuln(Item * item);
	Trigger * getAttack();
	void setAttack(Trigger * trigger);
	std::vector<Trigger*> getTriggers();
	void addTrigger(Trigger * trigger);
	bool removeTrigger(Trigger * trigger);
};

#endif
