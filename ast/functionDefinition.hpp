#ifndef functionDefinition_hpp
#define functionDefinition_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class FunctionDefinition
	: public Program
{
private:
	std::string functionName;
	ProgramPtr declarationList;
	ProgramPtr statementList;
	type dataType;
	bool isEmpty;
public:
    FunctionDefinition(std::string returnType,std::string _functionName, ProgramPtr _declarationList, ProgramPtr _statementList)
	:functionName(_functionName), declarationList(_declarationList), statementList(_statementList), Program()
	{
		isEmpty = false;
		std::cerr << returnType << " is the return type \n";
		if(returnType == "int"){
			std::cerr << "int declaration\n";
			dataType = intt;
		}else if(returnType == "double"){
			std::cerr << "double declaration\n";
			dataType = doublet;
		}else if(returnType == "float"){
			dataType = floatt;
		}else if(returnType == "char"){
			dataType = chart;
		}else if(returnType == "unsigned"){
			dataType = unsignedt;
		}else if(returnType == "struct"){
			dataType = structt;
		}
	}

	FunctionDefinition(std::string returnType,std::string _functionName, ProgramPtr _declarationList)
:functionName(_functionName), declarationList(_declarationList), Program()
{
	isEmpty = true;
	std::cerr << returnType << " is the return type \n";
	if(returnType == "int"){
		std::cerr << "int declaration\n";
		dataType = intt;
	}else if(returnType == "double"){
		std::cerr << "double declaration\n";
		dataType = doublet;
	}else if(returnType == "float"){
		dataType = floatt;
	}else if(returnType == "char"){
		dataType = chart;
	}else if(returnType == "unsigned"){
		dataType = unsignedt;
	}else if(returnType == "struct"){
		dataType = structt;
	}
}

    virtual void print(std::ostream &dst) const{
		dst << functionName << " parameter list: ";
		for (int i = 0; i < declarationList->getStrings().size(); i++){
			dst << declarationList->getStrings()[i] << ", ";
		}
		dst << "statement list: ";
		for (int i = 0; i < statementList->getPointers().size(); i++){
			dst << statementList->getPointers()[i]->getStrings()[0] << " = ";
			statementList->getPointers()[i]->getPointers()[0]->print(dst);
			dst << "\n";
		}
		dst << "\n";
	};
	virtual int getType() {
		return functionDefinition;
	}
	virtual type getDataType(){
		return dataType;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(declarationList);
			if(!isEmpty){
					ret.push_back(statementList);
			}
			return ret;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(functionName);
		return ret;
	}
	virtual std::vector<int> getInts() {}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		sc = "funcdef";
		std::cerr<<"funcdef translate"<<std::endl;
		makeindt(outFile, indt);
		outFile<<"def "<<functionName<<"(";
		std::cerr<<"decllist";
		//std::cerr<<declarationList->getType()<<std::endl;
		declarationList->translate(outFile, indt, sc, gvars);
		outFile<<"):\n";
		indt++;
		std::cerr<<gvars.size()<<std::endl;
		int gsize = gvars.size();
		if(gsize!=0){
			std::cerr<<"   "<<std::endl;
			for(int j=0; j<gvars.size(); j++){
				makeindt(outFile, indt);
				outFile<<"global "<<gvars[j]<<"\n";
			}
		}
		//makeindt(outFile, indt);
		statementList->translate(outFile, indt, sc, gvars);
		indt--;
		sc = "global";
	}
};


#endif
