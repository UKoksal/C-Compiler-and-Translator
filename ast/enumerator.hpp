#ifndef enumerator_hpp
#define enumerator_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class Enumerator
	: public Program
{
private:
	std::string enumerationConstant;
	ExpressionPtr constExpr;
	int enumVal;
	int type;
public:
	Enumerator(std::string _enumerationConstant, ExpressionPtr _constExpr)
	:enumerationConstant (_enumerationConstant), constExpr(_constExpr), Program()
	{
		enumVal = constExpr->evaluate();
		std::cerr << "EVALUATED CONSTANT EXPRESSION AS " << enumVal << "\n";
		type = 1;
	}
	Enumerator(std::string _enumerationConstant)
	:enumerationConstant (_enumerationConstant){
		type = 2;
	}
	virtual int getType() {
		return enumerator;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		if(type == 1){
			ret.push_back(constExpr);
		}
			return ret;
	}
	virtual std::vector<int> getInts() {
			std::vector<int> ret;
			ret.push_back(type);
			if(type == 1){
				ret.push_back(enumVal);
			}
			return ret;
	}
	virtual std::vector<std::string> getStrings() {
			std::vector<std::string> ret;
			ret.push_back(enumerationConstant);
			return ret;
	}
};


#endif
