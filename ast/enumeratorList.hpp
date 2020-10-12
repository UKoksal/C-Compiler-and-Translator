#ifndef enumeratorList_hpp
#define enumeratorList_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class EnumeratorList
	: public Program
{
private:
	std::vector<ProgramPtr> enumerators;
public:
	EnumeratorList(ProgramPtr enumerator, ProgramPtr subList)
	:Program()
	{
		enumerators.push_back(enumerator);
		for(int i = 0; i < subList->getPointers().size(); i++){
			enumerators.push_back(subList->getPointers()[i]);
		}
	}
	EnumeratorList(ProgramPtr enumerator)//base case constructor
	:Program()
	{
		enumerators.push_back(enumerator);
	}
	virtual int getType() {
		return enumeratorList;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			return enumerators;
	}
};


#endif
