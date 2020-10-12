#ifndef whileLoop_hpp
#define whileLoop_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class WhileLoop
	: public Program
{
private:
	ProgramPtr condition;
	ProgramPtr statementList;
	type condType;
	bool isEmpty;
	std::string scopeName;
public:
    WhileLoop(ProgramPtr _condition, ProgramPtr _statementList)
	:condition(_condition), statementList(_statementList), Program()
	{
		isEmpty = false;
	}
	WhileLoop(ProgramPtr _condition)
:condition(_condition), Program()
{
	isEmpty = true;
}

    virtual void print(std::ostream &dst) const{
	};
	virtual int getType() {
		return whileLoop;
	}
	virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(condition);
			if(!isEmpty){
				ret.push_back(statementList);
			}
			return ret;
	}
	virtual std::vector<std::string> getStrings() {
	}
	virtual void setScopeName(std::string name) {
		scopeName = name;
	}
	virtual std::string getScopeName() {
		return scopeName;
	}
	virtual std::vector<int> getInts() {}


	virtual type getConditionType(ProgramPtr condition, std::map<std::string, std::map<std::string, type> > variableTypeMap, std::map<std::string, std::map<std::string, uint32_t> > memMap, std::string scopeName, std::string funcName, bool& typeFound){
			if(condition == NULL){
				return intt;
			}else{
				//std::cerr << "non-base case with type " << condition->getType() << "\n";
				if(condition->getType() == variable){
					//std::cerr << "got to a variable\n";
					std::string variableName = condition->getStrings()[0];
					std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
		      std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableName);
		      if(it != scopeMap.end())
		      {
					 typeFound = true;
		       return variableTypeMap[scopeName][variableName];
		      }else{
		        std::map<std::string, uint32_t> funcMap = memMap[funcName];
		        std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableName);
		        if(itt != funcMap.end()){
							typeFound = true;
		          return variableTypeMap[funcName][variableName];
		        }else{// If we haven't found the variable in the function scope, look for it in the global scope
		        std::map<std::string, uint32_t> globalMap = memMap["global"];
		        std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableName);
		        if(ittt != globalMap.end()){
							typeFound = true;
		          return variableTypeMap["global"][variableName];
		        }else{
		          std::cerr << "Y U GIVE WRONG CODE? Ha? HA? in whileLoop\n";
		        }
		        }
		      }
				}else{
					type retType;
					//std::cerr << "size is " << condition->getPointers().size() << "\n";
					for(int i = 0; i < condition->getPointers().size(); i++){
						retType = getConditionType(condition->getPointers()[i], variableTypeMap,memMap, scopeName, funcName, typeFound);
						if(typeFound){
							break;
						}
					}
					return retType;
				}
			}
	}


	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		//makeindt(outFile, indt);
		std::string temp = sc;
		sc = "while";
		outFile<<"while (";
		condition->translate(outFile, indt, sc, gvars);
		outFile<<"):\n";
		indt++;
		//makeindt(outFile, indt);
		statementList->translate(outFile, indt, sc, gvars);
		indt--;
		sc = temp;

	}

};


#endif
