#ifndef scope_hpp
#define scope_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class Scope
	: public Program
{
private:
	ProgramPtr statementList;
	bool isEmpty;
public:
    Scope(ProgramPtr _statementList)
	:statementList(_statementList), Program()
	{
		isEmpty = false;
	}
	Scope()
:Program()
{
	isEmpty = true;
}


	virtual int getType() {
		return scope;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			if(!isEmpty){
				ret.push_back(statementList);
			}
			return ret;
	}

};


#endif
