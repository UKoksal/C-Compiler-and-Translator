#ifndef concreteParameterList_hpp
#define concreteParameterList_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class ConcreteParameterList
	: public Program
{
private:
	std::vector<ProgramPtr> parameters;
public:
    ConcreteParameterList(ProgramPtr _parameter, ProgramPtr subList)
	:Program()
	{
		parameters.push_back(_parameter);
		for(int i = 0; i < subList->getPointers().size(); i++){
			parameters.push_back(subList->getPointers()[i]);
		}
	}
	ConcreteParameterList(ProgramPtr _parameter)//base case constructor
	:Program()
	{
		parameters.push_back(_parameter);
	}
	ConcreteParameterList()//base case constructor
	:Program()
	{
	}

    virtual void print(std::ostream &dst) const{
		//dst << identifier;
	};
	virtual int getType() {
		return concreteParameterList;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		return parameters;
	}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		std::cerr<<"print conc params"<<std::endl;
		if(parameters.size()==1){
			parameters[0]->translate(outFile, indt, sc, gvars);
			//outFile<<parameters[0];
		}
		else{
			for(int i=0; i<parameters.size(); i++){
				parameters[i]->translate(outFile, indt, sc, gvars);
				//outFile<<parameters[i];
				if(i!=parameters.size()-1){
					outFile<<",";
				}
			}

		}
	}
};


#endif
