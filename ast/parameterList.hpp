#ifndef parameterList_hpp
#define parameterList_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class ParameterList
	: public Program
{
private:
	std::vector<std::string> varNames;
	std::vector<type> varTypes;
public:
	ParameterList()//empty constructor for an empty parameterList
	:Program()
	{

	}
    ParameterList(std::string _varType, std::string _varName, ProgramPtr subList)
	:Program()
	{
		type variableType;
		if(_varType == "int"){
		variableType = intt;
		std::cerr << "int parameter\n";
		}else if(_varType == "double"){
			variableType = doublet;
			std::cerr << "double parameter\n";
		}else if(_varType == "float"){
			std::cerr << "float parameter\n";
			variableType = floatt;
		}

		varNames.push_back(_varName);
		varTypes.push_back(variableType);
		for(int i = 0; i < subList->getStrings().size(); i++){
			varNames.push_back(subList->getStrings()[i]);
			varTypes.push_back(subList->getDataTypes()[i]);
		}
	}
	ParameterList(std::string _varType, std::string _varName)//base case constructor
	:Program()
	{
		type variableType;
		if(_varType == "int"){
		variableType = intt;
		std::cerr << "int parameter\n";
		}else if(_varType == "double"){
			variableType = doublet;
			std::cerr << "double parameter\n";
		}else if(_varType == "float"){
			std::cerr << "float parameter\n";
			variableType = floatt;
		}
		varTypes.push_back(variableType);
		varNames.push_back(_varName);
	}


    virtual void print(std::ostream &dst) const{
		//dst << identifier;
	};
	virtual int getType() {
		return parameterList;
	}
	virtual std::vector<std::string> getStrings() {
		return varNames;
	}
	virtual std::vector<type> getDataTypes(){
		return varTypes;
	}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const {
		std::cerr<<"partrans"<<std::endl;
		std::cerr<<"parsize"<<varNames.size()<<std::endl;
		if(varNames.size()==1){
			outFile<<varNames[0];
		}
		else if(varNames.size()!=0){
			for(int i=0; i<varNames.size(); i++){
				outFile<<varNames[i];
				if(i!=varNames.size()-1){
					outFile<<",";
				}
			}
		}
	}
};


#endif
