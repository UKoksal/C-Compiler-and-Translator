#ifndef variableDeclaration_hpp
#define variableDeclaration_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class VariableDeclaration
	: public Program
{
private:
	std::string varName;
	ExpressionPtr expressionAssigned;
	type variableType;
	double valueToAssign;
	int decType;
public:
    VariableDeclaration(std::string _identifier)
	:varName(_identifier), Program()
	{decType = 1;/*enumerator declaration i.e. an int*/
	std::cerr << varName << " is the identifier \n";}
	VariableDeclaration(std::string typeName ,std::string _identifier)
:varName(_identifier), Program()
{
	std::cerr << typeName << " is the type name and " << varName << " is the identifier \n";
	decType = 2;/*declaration with no initialisation*/
	if(typeName == "int"){
		variableType = intt;
		std::cerr << "int declaration\n";
	}else if(typeName == "double"){
		variableType = doublet;
		std::cerr << "double declaration\n";
	}else if(typeName == "float"){
		std::cerr << "float declaration\n";
		variableType = floatt;
	}else if(typeName == "char"){
		variableType = chart;
	}else if(typeName == "unsigned"){
		variableType = unsignedt;
	}else if(typeName == "struct"){
		variableType = structt;
	}
}
VariableDeclaration(std::string typeName ,std::string _identifier, ExpressionPtr _expressionAssigned)
:varName(_identifier), expressionAssigned(_expressionAssigned), Program()
{
		valueToAssign = expressionAssigned->evaluate();
		std::cerr << "value to assign evaluated as " << valueToAssign << "\n";
		std::cerr << typeName << " is the type name and " << varName << " is the identifier \n";
	decType = 3;/*declaration and initialisation*/
	if(typeName == "int"){
		std::cerr << "int declaration\n";
		variableType = intt;
	}else if(typeName == "double"){
		std::cerr << "double declaration\n";
		variableType = doublet;
	}else if(typeName == "float"){
		variableType = floatt;
	}else if(typeName == "char"){
		variableType = chart;
	}else if(typeName == "unsigned"){
		variableType = unsignedt;
	}else if(typeName == "struct"){
		variableType = structt;
	}
}
virtual int getInt(){
	std::cerr << "returning int as " << (int)valueToAssign << "\n";
	return (int)valueToAssign;
}
virtual float getFloat(){
	return (float)valueToAssign;
}
    virtual void print(std::ostream &dst) const{
	};
	virtual int getType() {
		return variableDeclaration;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		if (decType == 3){
			ret.push_back(expressionAssigned);
		}
		return ret;
	}
	virtual type getDataType(){
		return variableType;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(varName);
		return ret;
	}

	virtual std::vector<int> getInts() {
		std::vector<int> ret;
		ret.push_back(decType);
		return ret;
	}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		//makeindt(outFile, indt);
		if(sc=="global"){
			gvars.push_back(varName);
		}
		outFile<<varName<<" = ";
		if(decType==2){
			outFile<<"0";
		}
		else if(decType==3){
			expressionAssigned->translate(outFile, indt, sc, gvars);
		}
		if(sc=="global"){outFile<<"\n";}

	}

};


#endif
