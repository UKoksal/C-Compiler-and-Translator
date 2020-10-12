#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual int getType() {
	return variable;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(id);
		return ret;
	}

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual double evaluate()
    {

    }
    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		//outFile<<"\t"<<id<<"";
      //makeindt(outFile, indt);
      outFile<<id<<"";
  	}
};

class Number
    : public Expression
{
private:
    double valueD;
    float valueF;
    int valueI;
public:
    Number(std::string value){
      valueD = std::stod(value);
      valueF = std::stof(value);
      valueI = std::stoi(value);
    }
	virtual int getType() {
	return num;
	}
    virtual int getInt(){
      return valueI;
    }
    virtual double getDouble(){
      return valueD;
    }
    virtual float getFloat(){
      return valueF;
    }
    virtual std::vector<ProgramPtr> getPointers() {
      //std::cerr << "using the top-level getPointers\n";
  		std::vector<ProgramPtr> ret;
  		return ret;
  	}
    virtual double evaluate()
    {
      return valueD;
    }

	virtual std::vector<int> getInts() {
		 std::vector<int> ret;
		 ret.push_back((int)valueI);
		return 	ret;
	}
  virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const {
    //std::cerr<<"translate num"<<std::endl;
    //makeindt(outFile, indt);
    outFile<<valueI<<"";
  }
};


#endif
