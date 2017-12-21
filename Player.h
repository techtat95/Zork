#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <vector>

#include "Item.h"
#include "Room.h"

class Player {
private:
	Room * location;
	std::vector<Item*> items;
	std::vector<Trigger*> triggers;

protected:
	void updateTriggers();

public:
	virtual ~Player();
	Room * getLocation();
	void setLocation(Room * room);
	std::vector<Item*> getItems();
	Item * getItem(std::string name);
	void addItem(Item * item);
	void removeItem(std::string name);
	std::vector<Trigger*> getTriggers();
	void removeTrigger(Trigger * trigger);
};

#endif /* PLAYER_H_ */
