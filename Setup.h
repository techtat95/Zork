#ifndef SETUP_H_
#define SETUP_H_

#include <vector>

#include "./libraries/tinyxml2.h"
#include "Map.h"

bool createMap(Map * map, tinyxml2::XMLElement * pRoot);

bool createRooms(Map * map, tinyxml2::XMLElement * pRoot);

bool addBorders(Map * map, tinyxml2::XMLElement * pRoot);

bool fillRooms(Map * map, tinyxml2::XMLElement * pRoot);

bool createItems(Map * map, tinyxml2::XMLElement * pRoot);

bool createContainers(Map * map, tinyxml2::XMLElement * pRoot);

bool createCreatures(Map * map, tinyxml2::XMLElement * pRoot);

Trigger * createTrigger(Map * map, tinyxml2::XMLElement * pTriggerElement);

#endif /* SETUP_H_ */
