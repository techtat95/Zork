#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>
#include <string>
#include <vector>

class Trigger {
private:
	std::string type;
	std::string command;
	std::string object;
	std::string has;
	std::string owner;
	std::string status;
	std::vector<std::string> prints;
	std::vector<std::string> actions;
	bool used;

protected:

public:
	Trigger();
	virtual ~Trigger();
	std::string getType();
	void setType(std::string t);
	std::string getCommand();
	void setCommand(std::string c);
	std::string getObject();
	void setObject(std::string o);
	std::string getHas();
	void setHas(std::string h);
	std::string getOwner();
	void setOwner(std::string o);
	std::string getStatus();
	void setStatus(std::string s);
	std::vector<std::string> getPrints();
	void addPrint(std::string p);
	std::vector<std::string> getActions();
	void addAction(std::string a);
	bool getUsed();
	void setUsed(bool u);
};

#endif
