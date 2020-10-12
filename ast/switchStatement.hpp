#ifndef switchStatement_hpp
#define switchStatement_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class SwitchStatement
	: public Program
{
private:
	ProgramPtr conditionExpression;
	ProgramPtr caseList;
public:
    SwitchStatement(ProgramPtr _conditionExpression, ProgramPtr _caseList)
	:conditionExpression(_conditionExpression), caseList(_caseList),Program()
	{
	}

	virtual int getType() {
		return switchStatement;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(conditionExpression);
		ret.push_back(caseList);
		return ret;
	}
};


#endif
