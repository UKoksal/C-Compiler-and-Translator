#ifndef program_hpp
#define program_hpp

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <memory>


enum type
  {
    intt,
    doublet,
    floatt,
    chart,
    unsignedt,
    structt
  };

enum nodeType
  {
	program = 1,
	variableDeclaration = 258,
	functionDeclaration = 259,
	declarationList = 260,
	statementList = 261,
	statement = 262,
	functionDefinition = 263,
	whileLoop = 264,
	assignment = 265,
	addition = 267,
	num = 268,
	ifStatement = 269,
	subtraction = 271,
	multiplication = 272,
	division = 273,
	ltOp = 274,
	gtOp = 275,
	lteOp = 276,
	gteOp = 277,
	lShiftOp = 278,
	rShiftOp = 279,
	moduloOp = 280,
	returnStatement = 281,
	variable = 282,
	parameterList = 283,
	functionCall = 284,
	concreteParameterList = 285,
	equals = 286,
	arrayDeclaration = 287,
	subscript = 289,
	forLoop = 290,
	caseList = 291,
	caseNode = 292,
	switchStatement = 293,
  breakStatement = 294,
  continueStatement = 295,
  enumerationSpecifier = 296,
  enumeratorList = 297,
  enumerator = 298,
  postIncrement,
  preIncrement,
  postDecrement,
  preDecrement,
  notEqual,
  bitWiseAnd,
  bitWiseEor,
  bitWiseIor,
  logicalAnd,
  logicalOr,
  scope,
  neg,
  plusEq,
  minusEq,
  timesEq,
  divEq,
  modEq,
  andEq,
  orEq,
  xorEq,
  lShiftEq,
  rShiftEq,
  notOp

  };

class Program;

typedef  Program *ProgramPtr;

class Program
{
private:

public:
    Program (ProgramPtr _left, ProgramPtr _right): left(_left), right(_right){}
    Program(){}
    ~Program()
    {}
    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) {}
	ProgramPtr left;
	ProgramPtr right;
    virtual int getType() {
	return program;
	}
	virtual void setLabel(std::string _label) {}
	virtual std::string getLabel() {}
  virtual std::vector<ProgramPtr> getPointers() {
    std::vector<ProgramPtr> ret;
    ret.push_back(left);
    ret.push_back(right);
		return ret;
	}
  virtual void setScopeName(std::string name) {
	}
  virtual std::string getScopeName() {
	}
  virtual void setIfScopeName(std::string name) {
	}
  virtual void setElseScopeName(std::string name) {
	}
  virtual std::string getIfName() {
	}
  virtual std::string getElseName() {
	}
  virtual type getDataType(){};
	virtual std::vector<std::string> getStrings() {	}
	virtual std::vector<int> getInts() {}
	virtual bool isFirstTime() {};
	virtual void setFirstTime(bool _firstTime) {}
  virtual int getInt(){
  }
  virtual double getDouble(){
  }
  virtual float getFloat(){
  }
	virtual type getConditionType(ProgramPtr condition, std::map<std::string, std::map<std::string, type> > variableTypeMap, std::map<std::string, std::map<std::string, uint32_t> > memMap, std::string scopeName, std::string funcName, bool& typeFound)
  {}
    virtual std::vector<type> getDataTypes(){};


  virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
    std::cerr<<"left type "<<left->getType()<<std::endl;
    std::cerr<<"right type "<<right->getType()<<std::endl;

    left->translate(outFile, indt, sc, gvars);
    right->translate(outFile, indt, sc, gvars);

  }
    //! Evaluate the tree using the given mapping of variables to numbers
};

inline void makeindt(std::ostream& outFile, int indt){
  for(int i=0; i<indt; i++){
    outFile<<"\t";
  }
}


#endif
