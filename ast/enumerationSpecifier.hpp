#ifndef enumerationSpecifier_hpp
#define enumerationSpecifier_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class EnumerationSpecifier
	: public Program
{
private:
	std::string name;
	ProgramPtr enumeratorList;
public:
    EnumerationSpecifier(std::string _name, ProgramPtr _enumeratorList)
	:name(_name), enumeratorList(_enumeratorList), Program()
	{}
	virtual int getType() {
		return enumerationSpecifier;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(enumeratorList);
			return ret;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(name);
		return ret;
	}
};


#endif
