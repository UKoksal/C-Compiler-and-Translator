#ifndef functionDeclaration_hpp
#define functionDeclaration_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class FunctionDeclaration
	: public Program
{
private:
	std::string functionName;
	ProgramPtr declarationList;
public:
    FunctionDeclaration(std::string _functionName, ProgramPtr _declarationList)
	:functionName(_functionName), declarationList(_declarationList), Program()
	{}

	virtual int getType() {
		return functionDeclaration;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(declarationList);
			return ret;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(functionName);
		return ret;
	}
	virtual std::vector<int> getInts() {}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		std::cerr<<"funcdecl"<<std::endl;
	}

};


#endif
