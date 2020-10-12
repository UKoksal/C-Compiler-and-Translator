#ifndef caseNode_hpp
#define caseNode_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class CaseNode
	: public Program
{
private:
	ProgramPtr constExpr;
 	ProgramPtr statementList;
	bool firstTime;
 	int type;
	std::string label;
public:
    CaseNode(ProgramPtr _constExpr, ProgramPtr _statementList)
	:constExpr(_constExpr), statementList(_statementList),Program()
	{
		firstTime = true;
		type = 1;
	}
	CaseNode(ProgramPtr _statementList)
	:statementList(_statementList),Program()
	{
		firstTime = true;
		type = 2;
	}

	virtual int getType() {
		return caseNode;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		if(type == 1){
			ret.push_back(constExpr);
			ret.push_back(statementList);
		}else if(type == 2){
			ret.push_back(statementList);
		}

		return ret;
	}
	virtual void setLabel(std::string _label){
		label = _label;
	}
	virtual std::string getLabel() {
		return label;
	}
	virtual std::vector<std::string> getStrings() {
	}
	virtual void setFirstTime(bool _firstTime) {
		firstTime = _firstTime;
	}
	virtual bool isFirstTime() {
		return firstTime;
	}
	virtual std::vector<int> getInts() {
		std::vector<int> ret;
		ret.push_back(type);
		return ret;
	}
};


#endif
