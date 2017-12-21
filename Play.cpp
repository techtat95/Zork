#include <vector>

#include "Play.h"

bool playGame(Map * map, Player * player, bool debug) {
	if (debug) {
		if (!startGame()) return true;
	}
	else {
		std::cout << "\n\n----------------------\n" << "   Welcome to ZORK!\n" << "----------------------" << std::endl;
		std::cout << "Type 'help' to get a list of game commands.\n" << std::endl;
	}

	std::string userInput;
	std::string firstWord;
	Room * room = map->getRoom("Entrance");
	player->setLocation(room);
	std::cout << room->getDescription() << std::endl;

	std::cout << "\n> ";
	std::getline(std::cin, userInput);
	int check;
	while (userInput != "quit") {
		room = player->getLocation();

		check = checkTriggers(map, player, room, userInput);
		if (check == 0) return true;

		else if (check == 1) {
			if (!doMove(map, player, room, userInput, false)) {
				if (room == player->getLocation()) {
					if (doAction(map, player, room, userInput, false)) return true;
				}
			}
		}

		if (checkTriggers(map, player, room, "") == 0) return true;

		map->resetTriggers();

		std::cout << "\n> ";
		std::getline(std::cin, userInput);
	}

	return true;
}

bool doMove(Map * map, Player * player, Room * room, std::string input, bool trigger) {
	Room * next;
	bool move = false;
	if ((input == "n") || (input == "north")) {
		next = room->getNorth();
		move = true;
	}
	else if ((input == "s") || (input == "south")) {
		next = room->getSouth();
		move = true;
	}
	else if ((input == "e") || (input == "east")) {
		next = room->getEast();
		move = true;
	}
	else if ((input == "w") || (input == "west")) {
		next = room->getWest();
		move = true;
	}
	if (move) {
		if (next == nullptr) {
			if (!trigger) std::cout << "You can't go that way." << std::endl;
			return true;
		}
		if (next->getStatus() == "hidden") {
			if (!trigger) std::cout << "You can't go that way." << std::endl;
			return true;
		}
		else {
			player->setLocation(next);
			std::cout << next->getDescription() << std::endl;
			return true;
		}
	}

	return false;
}

bool doAction(Map * map, Player * player, Room * room, std::string input, bool trigger) {
	std::string action = input.substr(0, input.find(' '));
	std::string end = input.substr(input.find(' ')+1);
	std::string action2 = input.substr(0, input.find(' ')) + " " + end.substr(0, end.find(' '));

	if (input == "help") printHelp();
	else if (input == "i") openInventory(player);
	else if (input == "open exit") {
		if (checkExit(room)) return true;
	}
	else if (action == "open") openContainer(room, end);
	else if (action == "take") takeItem(player, room, end, trigger);
	else if (action == "read") readItem(player, end, trigger);
	else if (action == "drop") dropItem(player, room, end, trigger);
	else if (action == "put") putItem(player, room, end, trigger);
	else if (action == "attack") {
		if (attackCreature(map, player, room, end, trigger)) return true;
	}
	else if (action2 == "turn on") {
		if (turnonItem(map, player, room, end, trigger)) return true;
	}
	else if (trigger) {
		if (action == "Add") triggerAdd(map, end);
		else if (action == "Delete") triggerDelete(map, end);
		else if (action == "Update") triggerUpdate(map, end);
		else if (input == "Game Over") {
			std::cout << "GAME OVER" << std::endl;
			return true;
		}
	}

	else std::cout << "That is not a valid command." << std::endl;
	return false;
}

bool doTrigger(Map * map, Player * player, Room * room, Trigger * trigger) {
	std::vector<std::string>::iterator iter;
	std::vector<std::string> prints = trigger->getPrints();
	std::vector<std::string> actions = trigger->getActions();

	for (iter = prints.begin(); iter != prints.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	for (iter = actions.begin(); iter != actions.end(); iter++) {
		if (doMove(map, player, room, (*iter), true)) return true;

		if (room == player->getLocation()) {
			if (doAction(map, player, room, (*iter), true)) return true;
		}
	}

	return false;
}

int checkTriggers(Map * map, Player * player, Room * room, std::string input) {
	std::vector<Trigger*> triggers = player->getTriggers();
	std::vector<Trigger*>::iterator iter;
	std::string command;
	for (iter = triggers.begin(); iter != triggers.end(); iter++) {
		command = (*iter)->getCommand();
		if (!command.empty()) {
			if (command == input) {
				if (checkCondition(map, player, room, (*iter))) {
					if ((*iter)->getType() == "permanent") {
						if ((*iter)->getUsed()) continue;
						else (*iter)->setUsed(true);
					}
					else if ((*iter)->getType() == "single") player->removeTrigger(*iter);
					if (doTrigger(map, player, room, (*iter))) return 0;
					return -1;
				}
				else continue;
			}
			else continue;
		}
		else if (checkCondition(map, player, room, (*iter))) {
			if ((*iter)->getType() == "permanent") {
				if ((*iter)->getUsed()) continue;
			}
			if ((*iter)->getType() == "single") player->removeTrigger(*iter);
			if (doTrigger(map, player, room, *iter)) return 0;
			return 1;
		}
	}

	return 1;
}

bool checkCondition(Map * map, Player * player, Room * room, Trigger * trigger) {
	Item * item = nullptr;
	Container * container = nullptr;
	std::vector<Container*> containers = room->getContainers();
	std::string iOwner;
	std::string cOwner;
	std::string object = trigger->getObject();
	std::string has = trigger->getHas();
	std::string owner = trigger->getOwner();
	std::string status = trigger->getStatus();

	if (object.empty()) return true;

	container = room->getContainer(object);
	if (container != nullptr) {
		if (container->getStatus() == status) return true;
		return false;
	}

	item = player->getItem(object);
	if (item != nullptr) iOwner = "inventory";
	else {
		item = room->getItem(object);
		if (item != nullptr) iOwner = room->getName();
		else {
			for (std::vector<Container*>::iterator iter = containers.begin(); iter != containers.end(); iter++) {
				item = (*iter)->getItem(object);
				if (item != nullptr) {
					iOwner = (*iter)->getName();
					break;
				}
			}
		}
	}

	if (container != nullptr) {
		if (status == container->getStatus()) return true;
	}
	else if (item != nullptr) {
		if (has == "yes") {
			if (owner == iOwner) return true;
		}
		else if (has == "no") {
			if (owner != iOwner) return true;
		}
		else if (status == item->getStatus()) return true;
	}
	else if (has == "no") return true;

	return false;
}

bool startGame() {
	std::cout << "\n\n----------------------\n" << "   Welcome to ZORK!\n" << "----------------------" << std::endl;
	std::cout << "Debugging mode is active. When you are ready, type 'start' to begin the game." << std::endl;
	std::cout << "Type 'help' to get a list of game commands.\n" << std::endl;

	std::string userInput;
	std::cout << "\n> ";
	std::getline(std::cin, userInput);
	while (userInput != "start") {
		if (userInput == "help") printHelp();
		else if (userInput == "quit") return false;
		else std::cout << "That is not a valid command." << std::endl;

		std::cout << "\n> ";
		std::getline(std::cin, userInput);
	}

	return true;
}

void printHelp() {
	std::cout << "\n\nPlayer Commands\n--------------------" << std::endl;
	std::cout << "     n: Go north" << std::endl;
	std::cout << "     s: Go south" << std::endl;
	std::cout << "     e: Go east" << std::endl;
	std::cout << "     w: Go west" << std::endl;
	std::cout << "     i: Open your inventory" << std::endl;
	std::cout << "     open <container>: Open container in the room" << std::endl;
	std::cout << "     open exit: Try to open the exit" << std::endl;
	std::cout << "     take <item>: Take item from the room" << std::endl;
	std::cout << "     read <item>: Read item in your inventory" << std::endl;
	std::cout << "     drop <item>: Drop item from your inventory" << std::endl;
	std::cout << "     put <item> in <container>: Put item from your inventory into a container" << std::endl;
	std::cout << "     attack <creature> with <item>: Attack a creature in the room with an item" << std::endl;
	std::cout << "     turn on <item>: Turn on item in your inventory" << std::endl;
	std::cout << "     quit: Quit the game" << std::endl;
	std::cout << "--------------------\n" << std::endl;

	return;
}

void openInventory(Player * player) {
	std::vector<Item*> items = player->getItems();
	if (items.empty()) std::cout << "Inventory: empty" << std::endl;
	else {
		std::cout << "Inventory: ";
		std::vector<Item*>::iterator iter;
		for (iter = items.begin(); iter != items.end(); iter++) {
			if (iter != items.begin()) std::cout << ", ";
			std::cout << (*iter)->getName();
		}
		std::cout << std::endl;
	}

	return;
}

bool checkExit(Room * room) {
	if (room->getType() == "exit") {
		std::cout << "GAME OVER" << std::endl;
		return true;
	}
	else std::cout << "There is no exit." << std::endl;
	return false;
}

void openContainer(Room * room, std::string name) {
	bool found = false;
	std::vector<Container*> containers = room->getContainers();
	for (std::vector<Container*>::iterator iterC = containers.begin(); iterC != containers.end(); iterC++) {
		if ((*iterC)->getName() == name) {
			found = true;
			if ((*iterC)->getStatus() == "locked") {
				std::cout << "The " << name << " is locked." << std::endl;
				return;
			}
			std::vector<Item*> items = (*iterC)->getItems();
			if (items.empty()) {
				std::cout << "There is nothing in the " << name << "."<< std::endl;
				return;
			}
			std::cout << (*iterC)->getName() << " contains ";
			for (std::vector<Item*>::iterator iterI = items.begin(); iterI != items.end(); iterI++) {
				if (iterI != items.begin()) std::cout << ", ";
				std::cout << (*iterI)->getName();
			}
			std::cout << "." << std::endl;
		}
	}

	if (!found) std::cout << "There is no " << name << " in this room." << std::endl;
	return;
}

void takeItem(Player * player, Room * room, std::string name, bool trigger) {
	Item * item = room->getItem(name);
	Container * container = nullptr;
	if (item == nullptr) {
		std::vector<Container*> containers = room->getContainers();
		for (std::vector<Container*>::iterator iter = containers.begin(); iter != containers.end(); iter++) {
			item = (*iter)->getItem(name);
			if (item != nullptr) {
				container = (*iter);
				break;
			}
		}
	}
	if (item == nullptr || (container != nullptr && container->getStatus() == "locked")) {
		if (!trigger) std::cout << "There is no such item here." << std::endl;
	}
	else {
		player->addItem(item);
		room->removeItem(name);
		if (container != nullptr) container->removeItem(name);
		std::cout << "Item " << name << " added to inventory." << std::endl;
	}
	return;
}

void readItem(Player * player, std::string name, bool trigger) {
	Item * item = player->getItem(name);
	if (item == nullptr) {
		if (!trigger) std::cout << "Item " << name << " is not in your inventory" << std::endl;
	}
	else {
		std::string writing = item->getWriting();
		if (writing.empty()) std::cout << "Nothing written." << std::endl;
		else std::cout << writing << std::endl;
	}
	return;
}

void dropItem(Player * player, Room * room, std::string name, bool trigger) {
	Item * item = player->getItem(name);
	if (item == nullptr) {
		if (!trigger) std::cout << "Item " << name << " is not in your inventory." << std::endl;
	}
	else {
		player->removeItem(name);
		room->addItem(item);
		std::cout << "Item " << name << " dropped." << std::endl;
	}
	return;
}

void putItem(Player * player, Room * room, std::string input, bool trigger) {
	std::string object = input.substr(0, input.find(' '));
	std::string dest = input.substr(input.find(' ')+1);
	if (dest.substr(0, dest.find(' ')) != "in") {
		std::cout << "That is not a valid command." << std::endl;
		return;
	}
	dest = dest.substr(dest.find(' ')+1);

	Item * item = player->getItem(object);
	Container * container = room->getContainer(dest);

	if (item == nullptr) {
		std::cout << "Item " << object << " is not in your inventory." << std::endl;
		return;
	}
	if (container == nullptr) {
		std::cout << "There is no " << dest << " in this room." << std::endl;
		return;
	}

	if (container->getStatus() == "locked") {
		if (item != container->getAccept()) {
			std::cout << "You cannot put the " << object << " in the " << dest << "." << std::endl;
			return;
		}
	}

	player->removeItem(object);
	container->addItem(item);
	std::cout << "Item " << object << " added to " << dest << "." << std::endl;

	return;
}

bool turnonItem(Map * map, Player * player, Room * room, std::string input, bool trigger) {
	std::string name = input.substr(input.find(' ')+1);

	Item * item = player->getItem(name);
	if (item == nullptr) {
		std::cout << "Item " << name << " is not in your inventory." << std::endl;
		return false;
	}
	else {
		std::cout << "You activate the " << item->getName() << "." << std::endl;
		Trigger * trig = item->getTurnon();
		if (trig == nullptr) {
			std::cout << "Nothing happened." << std::endl;
			return false;
		}
		if (checkCondition(map, player, room, trig)) return doTrigger(map, player, room, trig);
		else {
			if (!trigger) std::cout << "Nothing happened." << std::endl;
			return false;
		}
	}
}

bool attackCreature(Map * map, Player * player, Room * room, std::string input, bool trigger) {
	std::string name = input.substr(0, input.find(' '));
	std::string object = input.substr(input.find(' ')+1);
	if (object.substr(0, object.find(' ')) != "with") {
		std::cout << "That is not a valid command." << std::endl;
		return false;
	}
	object = object.substr(object.find(' ')+1);
	Trigger * attack;

	Creature * creature = room->getCreature(name);
	if (creature != nullptr) {
		Item * item = player->getItem(object);
		if (item == nullptr) {
			std::cout << "The item " << object << " is not in your inventory." << std::endl;
			return false;
		}
		if (!creature->checkVuln(item)) {
			std::cout << "Creature " << name << " is not vulnerable to item " << object << "." << std::endl;
			return false;
		}

		attack = creature->getAttack();
		if (attack == nullptr) {
			std::cout << "You attack the " << name << " with the " << object << "." << std::endl;
			if (!trigger) std::cout << "Nothing happened." << std::endl;
			return false;
		}

		if (checkCondition(map, player, room, creature->getAttack())) {
			std::cout << "You attack the " << name << " with the " << object << "." << std::endl;
			return doTrigger(map, player, room, creature->getAttack());
		}
		else {
			std::cout << "You attack the " << name << " with the " << object << "." << std::endl;
			if (!trigger) std::cout << "Nothing happened." << std::endl;
			return false;
		}
	}
	else {
		std::cout << "There is no creature " << name << " here to attack." << std::endl;
		return false;
	}
}

void triggerAdd(Map * map, std::string input) {
	std::string object = input.substr(0, input.find(' '));
	std::string dest = input.substr(input.find(' ')+1);
	if (dest.substr(0, dest.find(' ')) != "to") return;
	dest = dest.substr(dest.find(' ')+1);
	std::string type;

	Item * item = map->getItem(object);
	Container * container = map->getContainer(object);
	Creature * creature = map->getCreature(object);

	if (item != nullptr) type = "item";
	else if (container != nullptr) type = "container";
	else if (creature != nullptr) type = "creature";

	Room * room = map->getRoom(dest);
	Container * containerIn = map->getContainer(dest);
	if (room != nullptr) {
		if (type == "item") room->addItem(item);
		else if (type == "container") room->addContainer(container);
		else if (type == "creature") room->addCreature(creature);
	}
	else if (containerIn != nullptr) {
		if (type == "item") containerIn->addItem(item);
	}

	return;
}

void triggerDelete(Map * map, std::string input) {
	Item * item = map->getItem(input);
	Container * container = map->getContainer(input);
	Creature * creature = map->getCreature(input);
	Room * room = map->getRoom(input);

	std::vector<Room*> rooms = map->getRooms();
	std::vector<Container*> containers = map->getContainers();

	if (item != nullptr) {
		for (std::vector<Room*>::iterator iter = rooms.begin(); iter != rooms.end(); iter++) {
			(*iter)->removeItem(item->getName());
		}
		for (std::vector<Container*>::iterator iter = containers.begin(); iter != containers.end(); iter++) {
			(*iter)->removeItem(item->getName());
		}
	}
	else if (container != nullptr) {
		for (std::vector<Room*>::iterator iter = rooms.begin(); iter != rooms.end(); iter++) {
			(*iter)->removeContainer(container->getName());
		}
	}
	else if (creature != nullptr) {
		for (std::vector<Room*>::iterator iter = rooms.begin(); iter != rooms.end(); iter++) {
			(*iter)->removeCreature(creature->getName());
		}
	}
	else if (room != nullptr) {
		room->setStatus("hidden");
	}

	return;
}

void triggerUpdate(Map * map, std::string input) {
	std::string object = input.substr(0, input.find(' '));
	std::string status = input.substr(input.find(' ')+1);
	if (status.substr(0, status.find(' ')) != "to") return;
	status = status.substr(status.find(' ')+1);
	std::string type;

	Item * item = map->getItem(object);
	if (item != nullptr) {
		item->setStatus(status);
		return;
	}

	Container * container = map->getContainer(object);
	if (container != nullptr) container->setStatus(status);

	return;
}
