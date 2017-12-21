#include <iostream>
#include <vector>

#include "./libraries/tinyxml2.h"
#include "Map.h"
#include "Room.h"
#include "Play.h"
#include "Player.h"
#include "Setup.h"

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { printf("XML Error: %i\n", a_eResult); return a_eResult; }
#endif

void printMap(Map * map);

void printBorders(Room * room);

void printItems(Room * room);

void printContainers(Room * room);

void printCreatures(Room * room);

int main(int argc, char ** argv) {
	if (argc < 2) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./main <xml file>\n");
		return EXIT_FAILURE;
	}
	bool debug = false;
	if (argc > 2 && !strcmp(argv[2], "-d")) debug = true;

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(argv[1]);
	XMLCheckResult(eResult);

	tinyxml2::XMLElement * pRoot = xmlDoc.FirstChildElement();
	if (pRoot == nullptr) return tinyxml2::XML_ERROR_FILE_READ_ERROR;

	Map * pMap = new Map();
	Player * pPlayer = new Player();
	if (!createMap(pMap, pRoot)) return EXIT_FAILURE;

	if (debug) printMap(pMap);

	playGame(pMap, pPlayer, debug);

	return EXIT_SUCCESS;
}

void printMap(Map * map) {
	std::vector<Room*> rooms = map->getRooms();
	std::vector<Room*>::iterator iter;
	std::string border;
	for (iter = rooms.begin(); iter != rooms.end(); iter++) {
		std::cout << std::endl;
		std::cout << "-----" << (*iter)->getName() << "-----" << std::endl;
		printBorders(*iter);
		printItems(*iter);
		std::cout << std::endl;
		printContainers(*iter);
		std::cout << std::endl;
		printCreatures(*iter);
	}

	std::vector<Item*> items;
	std::vector<Item*>::iterator iterI;
	std::vector<Container*> containers = map->getContainers();
	std::vector<Container*>::iterator iter1;
	std::cout << "\n---------------\n\nContainers: " << std::endl;
	for (iter1 = containers.begin(); iter1 != containers.end(); iter1++) {
		std::cout << " - " << (*iter1)->getName() << std::endl;
		items = (*iter1)->getItems();
		for (iterI = items.begin(); iterI != items.end(); iterI++) {
			std::cout << "   - " << (*iterI)->getName() << std::endl;
		}
	}

	std::cout << std::endl;

	std::vector<Creature*> creatures = map->getCreatures();
	std::vector<Creature*>::iterator iter2;
	std::cout << "Creatures: " << std::endl;
	for (iter2 = creatures.begin(); iter2 != creatures.end(); iter2++) {
		std::cout << " - " << (*iter2)->getName() << std::endl;
		items = (*iter2)->getVulns();
		for (iterI = items.begin(); iterI != items.end(); iterI++) {
			std::cout << "   - " << (*iterI)->getName() << std::endl;
		}
	}
 }

void printBorders(Room * room) {
	Room * border;
	std::string name;

	border = room->getNorth();
	if (border == nullptr) std::cout << "North: " << std::endl;
	else std::cout << "North: " << border->getName() << std::endl;
	border = room->getSouth();
	if (border == nullptr) std::cout << "South: " << std::endl;
	else std::cout << "South: " << border->getName() << std::endl;
	border = room->getEast();
	if (border == nullptr) std::cout << "East: " << std::endl;
	else std::cout << "East: " << border->getName() << std::endl;
	border = room->getWest();
	if (border == nullptr) std::cout << "West: " << std::endl;
	else std::cout << "West: " << border->getName() << std::endl;

	return;
}

void printItems(Room * room) {
	std::cout << "Items: ";
	std::string item;
	std::vector<Item*> items = room->getItems();
	std::vector<Item*>::iterator iter;
	for (iter = items.begin(); iter != items.end(); iter++) {
		if (iter != items.begin()) std::cout << ", ";
		std::cout << (*iter)->getName();
	}

	return;
}

void printContainers(Room * room) {
	std::cout << "Containers: ";
	std::string container;
	std::vector<Container*> containers = room->getContainers();
	std::vector<Container*>::iterator iter;
	for (iter = containers.begin(); iter != containers.end(); iter++) {
		if (iter != containers.begin()) std::cout << ", ";
		std::cout << (*iter)->getName();
	}

	return;
}

void printCreatures(Room * room) {
	std::cout << "Creatures: ";
	std::string creature;
	std::vector<Creature*> creatures = room->getCreatures();
	std::vector<Creature*>::iterator iter;
	for (iter = creatures.begin(); iter != creatures.end(); iter++) {
		if (iter != creatures.begin()) std::cout << ", ";
		std::cout << (*iter)->getName();
	}

	return;
}
