#ifndef caseList_hpp
#define caseList_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class CaseList
	: public Program
{
private:
	std::vector<ProgramPtr> cases;
	std::string switchLabel;
public:
    CaseList(ProgramPtr subList, ProgramPtr caseP)
	:Program()
	{
		cases.push_back(caseP);
		for(int i = 0; i < subList->getPointers().size(); i++){
			cases.push_back(subList->getPointers()[i]);
		}
	}
	CaseList(ProgramPtr caseP, bool isSubList)//base case constructor
	:Program()
	{	//std::cerr << "in this constructor with sublist being " << isSubList << "\n";
		if(!isSubList){
			std::cerr << "Type: "<< caseP->getType() << "\n";
			cases.push_back(caseP);
		}else{
			for(int i = 0; i < caseP->getPointers().size(); i++){
				cases.push_back(caseP->getPointers()[i]);
			}
		}
	}
	CaseList()//empty caseList constructor
	:Program()
	{
	}
	virtual void setLabel(std::string _label){
		//std::cerr << "I'm having my label set to " << _label << "\n";
		switchLabel = _label;
	}
	virtual std::string getLabel() {
		return switchLabel;
	}
	virtual int getType() {
		return caseList;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		return cases;
	}
};


#endif
