#ifndef statement_hpp
#define statement_hpp

#include <string>
#include <iostream>
#include <map>
#include"program.hpp"

#include <memory>

class Statement
	:public Program
{
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{}
};

class Assignment
	:public Statement
{
private:
	int assignmentType;
	ProgramPtr RHSExpr;
	std::string identifier;
	ProgramPtr subscript;
public:
    Assignment(std::string _identifier, ProgramPtr _RHSExpr)
	:RHSExpr(_RHSExpr), identifier(_identifier)
	{assignmentType  = 1;
	std::cerr << "constructing with identifier " << identifier << "\n";}

	Assignment(ExpressionPtr _subscript, ExpressionPtr _RHSExpr)
	:RHSExpr(_RHSExpr), subscript(_subscript)
	{assignmentType = 2;}

 	virtual void print(std::ostream &dst) {
		//dst << identifier;
	};
	virtual int getType() {
		return assignment;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		if(assignmentType == 1){
			ret.push_back(RHSExpr);
		}else{
			//std::cerr << "pushing the operands of a type 2 assignment\n";
			ret.push_back(subscript);
			ret.push_back(RHSExpr);
		}
		return ret;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		if(assignmentType == 1){
			//std::cerr << "getting identifier as " << identifier << "\n";
			ret.push_back(identifier);
		}
		return ret;
	}
	virtual std::vector<int> getInts() {
			std::vector<int> ret;
			ret.push_back(assignmentType);
			return ret;
	}
	virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
		//makeindt(outFile, indt);
		outFile<<identifier<<" = ";
		RHSExpr->translate(outFile, indt, sc, gvars);
	}
};

class IfStatement
	:public Statement
{
	private:
		ExpressionPtr expr;
		ProgramPtr firstStatementList;
		ProgramPtr secondStatementList;
		int type;
		std::string ifScopeName;
		std::string elseScopeName;
	public:
		IfStatement(ExpressionPtr _expr, ProgramPtr _statementList)
			:expr(_expr), firstStatementList(_statementList)
			{type = 1;}

		IfStatement(ExpressionPtr _expr, ProgramPtr _firstStatementList, ProgramPtr _secondStatementList)
			:expr(_expr), firstStatementList(_firstStatementList), secondStatementList(_secondStatementList)
			{type = 2;}

		virtual int getType() {
			return ifStatement;
		}
		virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			if(type == 1){
				ret.push_back(expr);
				ret.push_back(firstStatementList);
			}else{
				ret.push_back(expr);
				ret.push_back(firstStatementList);
				ret.push_back(secondStatementList);
			}
			return ret;
		}
		virtual std::vector<int> getInts() {
			std::vector<int> ret;
			ret.push_back(type);
			return ret;
		}
		virtual void setIfScopeName(std::string name) {
			ifScopeName = name;
		}
	  virtual void setElseScopeName(std::string name) {
			elseScopeName = name;
		}
	  virtual std::string getIfName() {
			return ifScopeName;
		}
	  virtual std::string getElseName() {
			return elseScopeName;
		}
		virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
			//makeindt(outFile, indt);
			std::string temp = sc;
			sc = "if";
			outFile<<"if (";
			expr->translate(outFile, indt, sc, gvars);
			outFile<<"):\n";
			indt++;
			//makeindt(outFile, indt);
			firstStatementList->translate(outFile, indt, sc, gvars);
			if(type==2){
				makeindt(outFile, indt-1);
				outFile<<"else:\n";
				secondStatementList->translate(outFile, indt, sc, gvars);
			}
			indt--;
			sc = temp;

		}

};

class ReturnStatement
	:public Statement
{
	private:
		ExpressionPtr exprReturned;
	public:
		ReturnStatement(ExpressionPtr _exprReturned)
			:exprReturned(_exprReturned)
			{}


		virtual int getType() {
			return returnStatement;
		}
		virtual std::vector<ProgramPtr> getPointers() {
			std::vector<ProgramPtr> ret;
			ret.push_back(exprReturned);
			return ret;
		}
		virtual std::vector<int> getInts() {
		}
		virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const {
			//std::cerr<<"return stat translate"<<std::endl;
			//makeindt(outFile, indt);
			outFile<<"return ";
			exprReturned->translate(outFile, indt, sc, gvars);
		}

};

class BreakStatement
	:public Statement
{
	public:
		BreakStatement(){}


		virtual int getType() {
			return breakStatement;
		}

};
class ContinueStatement
	:public Statement
{
	public:
		ContinueStatement(){}


		virtual int getType() {
			return continueStatement;
		}

};

#endif
