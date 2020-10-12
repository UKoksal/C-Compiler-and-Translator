#ifndef statementList_hpp
#define statementList_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class StatementList
	: public Program
{
private:
	std::vector<ProgramPtr> statements;
public:
    StatementList(ProgramPtr subList, ProgramPtr statement)
	:Program()
	{
		statements.push_back(statement);
		for(int i = 0; i < subList->getPointers().size(); i++){
			statements.push_back(subList->getPointers()[i]);
		}
	}
	StatementList(ProgramPtr statement)//base case constructor
	:Program()
	{
		statements.push_back(statement);
	}
	StatementList()//empty constructor for an empty parameterList
	:Program()
	{

	}

    virtual void print(std::ostream &dst) const{
		//dst << identifier;
	};
	virtual int getType() {
		return statementList;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		return statements;
	}
	virtual std::vector<std::string> getStrings() {
	}
	virtual std::vector<int> getInts() {}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		//std::cerr<<"print params"<<std::endl;
		int temp = indt;
		for(int i=0; i<statements.size(); i++){
			makeindt(outFile, indt);
			statements[i]->translate(outFile, indt, sc, gvars);
			outFile<<"\n";
			indt = temp;
		}
	}
};


#endif
