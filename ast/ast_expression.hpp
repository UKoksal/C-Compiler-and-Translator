#ifndef ast_expression_hpp
#define ast_expression_hpp
#include "program.hpp"
#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

typedef Expression *ExpressionPtr;

class Expression
	:public Program
{
public:
    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const{};

    //! Evaluate the tree using the given mapping of variables to numbers
    virtual double evaluate(
    ) 
    { throw std::runtime_error("Not implemented."); }

	virtual int getType() {
	}
	virtual std::vector<ProgramPtr> getPointers() {
	}
	virtual std::vector<std::string> getStrings() {
	}
	virtual std::vector<int> getInts() {}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{}

};

class FunctionCall
	: public Expression
{
private:
	std::string functionName;
	ProgramPtr parameterList;
public:
    FunctionCall(std::string _functionName, ProgramPtr _parameterList)
	:functionName(_functionName), parameterList(_parameterList)
	{}

	virtual int getType() {
		return functionCall;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(parameterList);
			return ret;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(functionName);
		return ret;
	}
	virtual std::vector<int> getInts() {}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const {
		std::cerr<<"funccall translate"<<std::endl;
		outFile<<functionName<<"(";
		std::cerr<<functionName<<std::endl;
		std::cerr<<parameterList<<std::endl;
		std::cerr<<parameterList->getType()<<std::endl;
		if(parameterList==NULL){std::cerr<<"parnull"<<std::endl;}
		if(parameterList!=0x0){
			std::cerr<<"parms"<<std::endl;
			parameterList->translate(outFile, indt, sc, gvars);
		}
		outFile<<")";
	}
};


#endif
