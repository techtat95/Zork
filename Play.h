#ifndef PLAY_H_
#define PLAY_H_

#include "Map.h"
#include "Player.h"

bool playGame(Map * map, Player * player, bool debug);

bool doMove(Map * map, Player * player, Room * room, std::string input, bool trigger);

bool doAction(Map * map, Player * player, Room * room, std::string input, bool trigger);

bool doTrigger(Map * map, Player * player, Room * room, Trigger * trigger);

/***
 * return: -1, 0, 1
 * -1: Do not run original command
 *  0: Game over command
 *  1: Run original command
 */
int checkTriggers(Map * map, Player * player, Room * room, std::string input);

bool checkCondition(Map * map, Player * player, Room * room, Trigger * trigger);

bool startGame();

void printHelp();

void openInventory(Player * player);

bool checkExit(Room * room);

void openContainer(Room * room, std::string name);

void takeItem(Player * player, Room * room, std::string name, bool trigger);

void readItem(Player * player, std::string name, bool trigger);

void dropItem(Player * player, Room * room, std::string name, bool trigger);

void putItem(Player * player, Room * room, std::string input, bool trigger);

bool turnonItem(Map * map, Player * player, Room * room, std::string input, bool trigger);

bool attackCreature(Map * map, Player * player, Room * room, std::string input, bool trigger);

void triggerAdd(Map * map, std::string input);

void triggerDelete(Map * map, std::string input);

void triggerUpdate(Map * map, std::string input);

#endif /* PLAY_H_ */
