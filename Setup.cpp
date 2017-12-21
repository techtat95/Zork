#include "Setup.h"
#include "Room.h"

bool createMap(Map * map, tinyxml2::XMLElement * pRoot) {
	if (!createRooms(map, pRoot)) return false;

	if (!addBorders(map, pRoot)) return false;

	createItems(map, pRoot);

	createContainers(map, pRoot);

	createCreatures(map, pRoot);

	if (!fillRooms(map, pRoot)) return false;

	return true;
}

bool createRooms(Map * map, tinyxml2::XMLElement * pRoot) {
	tinyxml2::XMLElement * pRoomElement = pRoot->FirstChildElement("room");
	if (pRoomElement == nullptr) return false;

	tinyxml2::XMLElement * pElement = nullptr;
	Room * room;
	const char * name = nullptr;
	const char * description = nullptr;
	const char * type = nullptr;

	while (pRoomElement != nullptr) {
		pElement = pRoomElement->FirstChildElement("name");
		name = pElement->GetText();
		pElement = pRoomElement->FirstChildElement("description");
		description = pElement->GetText();
		pElement = pRoomElement->FirstChildElement("type");
		if (pElement == nullptr) type = "";
		else type = pElement->GetText();

		room = new Room(name, description, type);
		map->addRoom(room);
		if (!strcmp("Entrance", name)) map->setEntrance(room);
		else if (!strcmp("exit", type)) map->addExit(room);

		pRoomElement = pRoomElement->NextSiblingElement("room");
	}

	return true;
}

bool addBorders(Map * map, tinyxml2::XMLElement * pRoot) {
	tinyxml2::XMLElement * pRoomElement = pRoot->FirstChildElement("room");
	if (pRoomElement == nullptr) return false;
	std::vector<Room*> rooms = map->getRooms();

	tinyxml2::XMLElement * pBorderElement;
	tinyxml2::XMLElement * pDirectionElement;
	Room * room = nullptr;
	Room * borderRoom = nullptr;
	const char * direction = nullptr;

	while (pRoomElement != nullptr) {
		room = map->getRoom(pRoomElement->FirstChildElement("name")->GetText());
		pBorderElement = pRoomElement->FirstChildElement("border");
		while (pBorderElement != nullptr) {
			borderRoom = map->getRoom(pBorderElement->FirstChildElement("name")->GetText());
			pDirectionElement = pBorderElement->FirstChildElement("direction");
			direction = pDirectionElement->GetText();

			if (!strcmp(direction, "north")) room->setNorth(borderRoom);
			else if (!strcmp(direction, "south")) room->setSouth(borderRoom);
			else if (!strcmp(direction, "east")) room->setEast(borderRoom);
			else if (!strcmp(direction, "west")) room->setWest(borderRoom);

			pBorderElement = pBorderElement->NextSiblingElement("border");
		}

		pRoomElement = pRoomElement->NextSiblingElement("room");
	}

	return true;
}

bool fillRooms(Map * map, tinyxml2::XMLElement * pRoot) {
	tinyxml2::XMLElement * pRoomElement = pRoot->FirstChildElement("room");
	if (pRoomElement == nullptr) return false;
	std::vector<Room*> rooms = map->getRooms();

	tinyxml2::XMLElement * pElement;
	tinyxml2::XMLElement * pTriggerElement = nullptr;
	Room * room = nullptr;
	Trigger * trigger = nullptr;

	while (pRoomElement != nullptr) {
		room = map->getRoom(pRoomElement->FirstChildElement("name")->GetText());

		pElement = pRoomElement->FirstChildElement("item");
		while (pElement != nullptr) {
			room->addItem(map->getItem(pElement->GetText()));
			pElement = pElement->NextSiblingElement("item");
		}

		pElement = pRoomElement->FirstChildElement("container");
		while (pElement != nullptr) {
			room->addContainer(map->getContainer(pElement->GetText()));
			pElement = pElement->NextSiblingElement("container");
		}

		pElement = pRoomElement->FirstChildElement("creature");
		while (pElement != nullptr) {
			room->addCreature(map->getCreature(pElement->GetText()));
			pElement = pElement->NextSiblingElement("creature");
		}

		pTriggerElement = pRoomElement->FirstChildElement("trigger");
		while (pTriggerElement != nullptr) {
			trigger = createTrigger(map, pTriggerElement);
			room->addTrigger(trigger);
			map->addTrigger(trigger);
			pTriggerElement = pTriggerElement->NextSiblingElement("trigger");
		}

		pRoomElement = pRoomElement->NextSiblingElement("room");
	}

	return true;
}

bool createItems(Map * map, tinyxml2::XMLElement * pRoot) {
	tinyxml2::XMLElement * pItemElement = pRoot->FirstChildElement("item");
	if (pItemElement == nullptr) return false;

	tinyxml2::XMLElement * pElement = nullptr;
	tinyxml2::XMLElement * pTurnonElement = nullptr;
	tinyxml2::XMLElement * pTriggerElement = nullptr;
	Item * item = nullptr;
	const char * name = nullptr;
	const char * writing = nullptr;
	const char * status = nullptr;
	Trigger * trigger = nullptr;

	while (pItemElement != nullptr) {
		pElement = pItemElement->FirstChildElement("name");
		name = pElement->GetText();
		pElement = pItemElement->FirstChildElement("writing");
		if (pElement == nullptr) writing = "";
		else writing = pElement->GetText();
		pElement = pItemElement->FirstChildElement("status");
		if (pElement == nullptr) status = "";
		else status = pElement->GetText();

		item = new Item(name, writing, status);

		pTurnonElement = pItemElement->FirstChildElement("turnon");
		if (pTurnonElement != nullptr) {
			item->setTurnon(createTrigger(map, pTurnonElement));
		}

		pTriggerElement = pItemElement->FirstChildElement("trigger");
		while (pTriggerElement != nullptr) {
			trigger = createTrigger(map, pTriggerElement);
			item->addTrigger(trigger);
			map->addTrigger(trigger);
			pTriggerElement = pTriggerElement->NextSiblingElement("trigger");
		}

		map->addItem(item);

		pItemElement = pItemElement->NextSiblingElement("item");
	}

	return true;
}

bool createContainers(Map * map, tinyxml2::XMLElement * pRoot) {
	tinyxml2::XMLElement * pContainerElement = pRoot->FirstChildElement("container");
	if (pContainerElement == nullptr) return false;

	tinyxml2::XMLElement * pElement = nullptr;
	tinyxml2::XMLElement * pTriggerElement = nullptr;
	Container * container = nullptr;
	const char * name = nullptr;
	const char * status = nullptr;
	Item * accept = nullptr;
	Trigger * trigger = nullptr;

	while (pContainerElement != nullptr) {
		pElement = pContainerElement->FirstChildElement("name");
		name = pElement->GetText();
		pElement = pContainerElement->FirstChildElement("status");
		if (pElement == nullptr) status = "";
		else status = pElement->GetText();
		pElement = pContainerElement->FirstChildElement("accept");
		if (pElement == nullptr) accept = nullptr;
		else accept = map->getItem(pElement->GetText());

		container = new Container(name, status, accept);

		pElement = pContainerElement->FirstChildElement("item");
		while (pElement != nullptr) {
			container->addItem(map->getItem(pElement->GetText()));
			pElement = pElement->NextSiblingElement("item");
		}

		pTriggerElement = pContainerElement->FirstChildElement("trigger");
		while (pTriggerElement != nullptr) {
			trigger = createTrigger(map, pTriggerElement);
			container->addTrigger(trigger);
			map->addTrigger(trigger);
			pTriggerElement = pTriggerElement->NextSiblingElement("trigger");
		}

		map->addContainer(container);

		pContainerElement = pContainerElement->NextSiblingElement("container");
	}

	return true;
}

bool createCreatures(Map * map, tinyxml2::XMLElement * pRoot) {
	tinyxml2::XMLElement * pCreatureElement = pRoot->FirstChildElement("creature");
	if (pCreatureElement == nullptr) return false;

	tinyxml2::XMLElement * pElement = nullptr;
	tinyxml2::XMLElement * pAttackElement = nullptr;
	tinyxml2::XMLElement * pTriggerElement = nullptr;
	Creature * creature;
	const char * name = nullptr;
	Trigger * trigger = nullptr;

	while (pCreatureElement != nullptr) {
		pElement = pCreatureElement->FirstChildElement("name");
		name = pElement->GetText();

		creature = new Creature(name);

		pElement = pCreatureElement->FirstChildElement("vulnerability");
		while (pElement != nullptr) {
			creature->addVuln(map->getItem(pElement->GetText()));
			pElement = pElement->NextSiblingElement("vulnerability");
		}

		pAttackElement = pCreatureElement->FirstChildElement("attack");
		if (pAttackElement != nullptr) {
			creature->setAttack(createTrigger(map, pAttackElement));
		}

		pTriggerElement = pCreatureElement->FirstChildElement("trigger");
		while (pTriggerElement != nullptr) {
			trigger = createTrigger(map, pTriggerElement);
			creature->addTrigger(trigger);
			map->addTrigger(trigger);
			pTriggerElement = pTriggerElement->NextSiblingElement("trigger");
		}

		map->addCreature(creature);

		pCreatureElement = pCreatureElement->NextSiblingElement("creature");
	}

	return true;
}

Trigger * createTrigger(Map * map, tinyxml2::XMLElement * pTriggerElement) {
	Trigger * trigger = new Trigger();
	tinyxml2::XMLElement * pElement = nullptr;
	tinyxml2::XMLElement * pConditionElement = nullptr;

	pElement = pTriggerElement->FirstChildElement("type");
	if (pElement != nullptr) trigger->setType(pElement->GetText());
	else trigger->setType("single");

	pElement = pTriggerElement->FirstChildElement("command");
	if (pElement != nullptr) trigger->setCommand(pElement->GetText());

	pConditionElement = pTriggerElement->FirstChildElement("condition");
	if (pConditionElement != nullptr) {
		pElement = pConditionElement->FirstChildElement("object");
		if (pElement != nullptr) trigger->setObject(pElement->GetText());

		pElement = pConditionElement->FirstChildElement("has");
		if (pElement != nullptr) trigger->setHas(pElement->GetText());

		pElement = pConditionElement->FirstChildElement("owner");
		if (pElement != nullptr) trigger->setOwner(pElement->GetText());

		pElement = pConditionElement->FirstChildElement("status");
		if (pElement != nullptr) trigger->setStatus(pElement->GetText());
	}

	pElement = pTriggerElement->FirstChildElement("print");
	while (pElement != nullptr) {
		trigger->addPrint(pElement->GetText());
		pElement = pElement->NextSiblingElement("print");
	}

	pElement = pTriggerElement->FirstChildElement("action");
	while (pElement != nullptr) {
		trigger->addAction(pElement->GetText());
		pElement = pElement->NextSiblingElement("action");
	}

	return trigger;
}
