#ifndef arrayDeclaration_hpp
#define arrayDeclaration_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class ArrayDeclaration
	: public Program
{
private:
	std::string identifier;
	ExpressionPtr sizeExpression;
	type dataType;
	int size;
public:
    ArrayDeclaration(std::string typeName ,std::string _identifier, ExpressionPtr _sizeExpression)
	:identifier(_identifier), sizeExpression(_sizeExpression), Program()
	{
		//std::cerr << "array beta\n";
		size = sizeExpression->evaluate();
		if(typeName == "int"){
			std::cerr << "int array declaration\n";
			dataType = intt;
		}else if(typeName == "double"){
			std::cerr << "double array declaration\n";
			dataType = doublet;
		}else if(typeName == "float"){
			std::cerr << "float array declaration\n";
			dataType = floatt;
		}else if(typeName == "char"){
			dataType = chart;
		}else if(typeName == "unsigned"){
			dataType = unsignedt;
		}else if(typeName == "struct"){
			dataType = structt;
		}
	}
	virtual std::vector<int> getInts() {
		std::vector<int> ret;
		ret.push_back(size);
		return ret;
	}

    virtual void print(std::ostream &dst) {
		dst << identifier;
	};
	virtual int getType() {
		return arrayDeclaration;
	}
	virtual type getDataType(){
		return dataType;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(identifier);
		return ret;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(sizeExpression);
		return ret;
	}

};


#endif
