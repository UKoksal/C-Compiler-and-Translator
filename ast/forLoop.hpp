#ifndef ForLoop_hpp
#define ForLoop_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class ForLoop
	: public Program
{
private:
	ProgramPtr initialisation;
	ProgramPtr condition;
	ProgramPtr update;
	ProgramPtr statementList;
	std::string scopeName;
	bool isEmpty;
public:
    ForLoop(ProgramPtr _initialisation, ProgramPtr _condition, ProgramPtr _update, ProgramPtr _statementList)
	:initialisation(_initialisation), condition(_condition), update(_update), statementList(_statementList)
	{isEmpty = false;}
		ForLoop(ProgramPtr _initialisation, ProgramPtr _condition, ProgramPtr _update)
	:initialisation(_initialisation), condition(_condition), update(_update)
	{isEmpty = true;}

    virtual void print(std::ostream &dst) const{
	};
	virtual int getType() {
		return forLoop;
	}
	virtual void setScopeName(std::string name) {
		scopeName = name;
	}
	virtual std::string getScopeName() {
		return scopeName;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(initialisation);
			ret.push_back(condition);
			ret.push_back(update);
			if(!isEmpty){
				ret.push_back(statementList);
			}
			return ret;
	}
};


#endif
