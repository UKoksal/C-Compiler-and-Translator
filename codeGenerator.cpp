#include "parser.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<stdint.h>
#include<bitset>
#include<algorithm>
#include<fstream>

std::map<std::string, std::map<std::string, type> > variableTypeMap;
std::map<std::string, type> functionTypeMap;
std::map<std::string, int> variableCount;
void compile(Program* progAST, std::map<std::string, std::map<std::string, uint32_t> >& memMap, int retReg, int& stackOffset, std::ofstream& outFile, int& paramCount, bool stackAlloc = false, std::string funcName = "", std::string scopeName = "global", std::string continueLabel = "", type opType = intt, type returnType = intt);


static int makeNameUnq=0;

static std::string genUniqueLabel(std::string base)
{
    return "_"+base+"_"+std::to_string(makeNameUnq++);
}

int main(int argc, char *argv[]){
    if(argc != 5){
			std::cerr << "Invalid input arguments, required: bin/c_compiler -S [source-file.c] -o [dest-file.s]\n";
		}
    else{
			char* sourceFile = argv[2];
			char* destFile = argv[4];

			std::ofstream outFile;
			outFile.open(destFile);
			Program* ast=parseAST(sourceFile);//telling the parser to parse the input file
			std::cout << "Syntax tree successfully built \n";
      std::string translate = argv[1];
      if(translate=="--translate"){
        //freopen (argv[2],"r",stdin);
        //std::cout<< std::endl;

          //freopen (argv[4],"w",stdout);
        std::cerr<<"translating"<<std::endl;
        int indstart = 0;
        std::vector<std::string> globalvars;
        ast->translate(outFile, indstart, "global", globalvars);
        std::cout<<std::endl;

        outFile<<std::endl;
        outFile<<"# Boilerplate"<<std::endl;
        outFile<<"if __name__ == \"__main__\":"<<std::endl;
        outFile<<"\timport sys"<<std::endl;
        outFile<<"\tret=main()"<<std::endl;
        outFile<<"\tsys.exit(ret)"<<std::endl;
      }
      else{
			     int stackOffset = 0;
           int paramCount = 0;
			        std::map<std::string, std::map<std::string, uint32_t> > memMap;/*
				stores names of variables in memory and the offsets relative to their frame
				in which they are stored the first key is the scope name and the second is the variable name
			*/
      outFile << ".data\n";
//      outFile << ".set noat\n";
      compile(ast, memMap, 2, stackOffset, outFile, paramCount);
      outFile << ".set macro\n";
      outFile << ".set reorder\n";
			outFile.close();
			std::cerr << "Compilation successful \n";
		}
  }
}

void compile(Program* progAST, std::map<std::string, std::map<std::string, uint32_t>>& memMap, int retReg, int& stackOffset, std::ofstream& outFile, int& paramCount, bool stackAlloc, std::string funcName, std::string scopeName, std::string continueLabel, type opType, type returnType){
  if(progAST->getType() == program){
		std::cerr << "found a program with  " << progAST->getPointers().size() << " children \n";
		stackOffset = 0;
    compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile, paramCount);
    compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile, paramCount);
  }else if(progAST->getType() == variableDeclaration){//allocating variable to either register or memory
		//std::cerr << "allocated space for variable " << progAST->getStrings()[0] << " at location " << 0x7FFFFFFF + 4*memMap.size();
    if(scopeName != "global"){
      if(stackAlloc){
        std::cout << "scope of " << progAST->getStrings()[0] << " is " << scopeName << "\n";
        variableTypeMap[scopeName][progAST->getStrings()[0]] = progAST->getDataType();
        std::cerr << "setting data type for " << progAST->getStrings()[0] << " as " << variableTypeMap[scopeName][progAST->getStrings()[0]] << "\n";
        //std::cerr << "Here\n";
        stackOffset = stackOffset + 4;
        //std::cerr << "stack alloc step for variable\n";
        if(progAST->getInts()[0] == 3){
          compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, progAST->getDataType());//evaluating the constExpr that assigns the enumerator
          }
      }else{
          std::cerr << "\n";
          std::cerr << "\n";
          std::cerr << "\n";
        std::cerr << "scopename " << scopeName << "\n";
        std::cerr << "stackOffset " << stackOffset << "\n";
        std::cerr << "paramCount " << paramCount << "\n";
        std::cerr << "funcName " << funcName << "\n";
        std::cerr << "\n";
        std::cerr << "\n";
        std::cerr << "\n";
        memMap[scopeName][progAST->getStrings()[0]] = (stackOffset - 8) - (variableCount[funcName])*4 - 4;
        variableCount[funcName]++;
        std::cerr << "variable count for  " << funcName << " is " << variableCount[funcName] << "\n";
        std::cerr << "allocating " <<progAST->getStrings()[0] << " to " << memMap[scopeName][progAST->getStrings()[0]] <<" \n";
          outFile << "#start of assignment\n";
        if(progAST->getInts()[0] == 3){
          compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, progAST->getDataType());//evaluating the constExpr that assigns the enumerator
          if(progAST->getDataType() == intt){
            outFile << "sw $2, " << memMap[scopeName][progAST->getStrings()[0]] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
            outFile << "nop\n";
            outFile << "#end of assignment\n";
          }else if(progAST->getDataType() == floatt){
            std::cerr << "loading a float into the float declared\n";
            outFile << "swc1 $f0, " << memMap[scopeName][progAST->getStrings()[0]] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
            outFile << "nop\n";
          }
          }
      }
    }else{//global variablelogicalNotOp
      //std::cerr << "global variable declared " << progAST->getStrings()[0] << "\n";
      variableTypeMap[scopeName][progAST->getStrings()[0]] = progAST->getDataType();
      std::cerr << "setting data type for " << progAST->getStrings()[0] << " as " << variableTypeMap[scopeName][progAST->getStrings()[0]] << "\n";
      if(progAST->getInts()[0] == 3){//again allowing for definition upon declaration but now for global variables
        if(progAST->getDataType() == intt){
          std::cerr << "initialising int global variable\n";
          outFile << progAST->getStrings()[0] << ": .word " <<std::to_string(progAST->getInt())<< " \n";//assuming that the RHS of the assignment is a number
        }else if(progAST->getDataType() == floatt){
          std::cerr << "initialising float global variable with " << progAST->getFloat() << "\n";
          float valF = progAST->getFloat();
          float* valP = &valF;
          int* intP = (int*)valP;
          int val = *intP;
          outFile << progAST->getStrings()[0] << ": .word " <<  std::to_string(val)<< " \n";
        }

      }else{
        outFile << progAST->getStrings()[0] << ": \n";
      }
      memMap["global"][progAST->getStrings()[0]] = 4;
    }
  }else if(progAST->getType() == functionDeclaration){
		//do nothing for now, will look at ABI
	}else if (progAST->getType() == parameterList){//assuming that this will always be run once so no need to worry about stackAlloc
      int stackOffsetLocal = stackOffset;
      paramCount = progAST->getStrings().size();//types: parameter type dependent storing
      bool intEncountered = false;
      for(int i = 0; i < progAST->getStrings().size() && i < 4; i++){
          if(progAST->getDataTypes()[i] == intt){
            intEncountered = true;
          }
          if(intEncountered){
            variableTypeMap[scopeName][progAST->getStrings()[i]] = progAST->getDataTypes()[i];
  					memMap[scopeName][progAST->getStrings()[i]] = stackOffsetLocal;
  					outFile << "sw $" << std::to_string(4 + i) << ", " << std::to_string(stackOffsetLocal) << "($fp)\n";
            stackOffsetLocal = stackOffsetLocal + 4;
          }else{
            if(i == 0){
              variableTypeMap[scopeName][progAST->getStrings()[i]] = progAST->getDataTypes()[i];
    					memMap[scopeName][progAST->getStrings()[i]] = stackOffsetLocal;
    					outFile << "swc1 $f12, " << std::to_string(stackOffsetLocal) << "($fp)\n";
              stackOffsetLocal = stackOffsetLocal + 4;
            }else if(i == 1){
              variableTypeMap[scopeName][progAST->getStrings()[i]] = progAST->getDataTypes()[i];
    					memMap[scopeName][progAST->getStrings()[i]] = stackOffsetLocal;
    					outFile << "swc1 $f14, " << std::to_string(stackOffsetLocal) << "($fp)\n";
              stackOffsetLocal = stackOffsetLocal + 4;
            }else{
              variableTypeMap[scopeName][progAST->getStrings()[i]] = progAST->getDataTypes()[i];
    					memMap[scopeName][progAST->getStrings()[i]] = stackOffsetLocal;
    					outFile << "sw $" << std::to_string(4 + i) << ", " << std::to_string(stackOffsetLocal) << "($fp)\n";
              stackOffsetLocal = stackOffsetLocal + 4;
            }
          }
			}
      outFile << "nop\n";
      if(progAST->getStrings().size() > 4){
        //std::cerr << "allocating extra parameters\n";
        for(int i = 4; i < progAST->getStrings().size(); i++){
            std::cerr << "saving offset for " << progAST->getStrings()[i] << " at " << stackOffsetLocal << "\n";
            variableTypeMap[scopeName][progAST->getStrings()[i]] = progAST->getDataTypes()[i];
            memMap[scopeName][progAST->getStrings()[i]] = stackOffsetLocal;
            stackOffsetLocal = stackOffsetLocal + 4;
  			}
      }
	}else if(progAST->getType() == functionDefinition){
    std::cerr << "defining a function\n" << progAST->getStrings()[0];
    //std::cerr << progAST->getStrings()[0] << "'s' function definition\n";
    functionTypeMap[progAST->getStrings()[0]] = progAST->getDataType();
    paramCount = 0;
    stackOffset = 8;//3 words, one for the frame pointer one for the 31 and one as a scratch location for three address operations
    compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile, paramCount, true, progAST->getStrings()[0], progAST->getStrings()[0], "", intt, progAST->getDataType());//run the statement list with stackAlloc mode to determine the stackOffset
    outFile << ".text\n";
    outFile << ".globl " << progAST->getStrings()[0] << "\n";
    outFile << progAST->getStrings()[0] << ":\n";//creating a label for a function's name
    outFile << ".set noreorder\n";
    outFile << ".set nomacro\n";
    outFile << "addiu $sp, $sp, -" << stackOffset <<"\n";
		outFile << "sw $31, " <<(stackOffset - 4) << "($sp)\n";//saving the return address needed if we make a function call within this functionDefinition
		outFile << "sw $fp, " << (stackOffset - 8) << "($sp)\n";
		outFile << "move $fp, $sp\n";
    outFile << "addiu $sp, $sp, -4\n";
    compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, progAST->getStrings()[0], progAST->getStrings()[0], "", intt, progAST->getDataType());
    compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, progAST->getStrings()[0], progAST->getStrings()[0], "", intt, progAST->getDataType());//run the sta
    //note that we compile the statementlist first to determine the stackOffset which then informs what offsets to use in the function header
    //what if we don't have a return statement so nothing moves into $2 the result, we default to 0 for the main but what about other functions?
    outFile << "li $2, 0\n";
    outFile << progAST->getStrings()[0] << "End:\n";
    outFile << "addiu $sp, $sp, 4\n";
    outFile << "move $sp, $fp\n";
		outFile << "lw $31, " <<(stackOffset - 4) << "($sp)\n";
		outFile << "lw $fp, " << (stackOffset - 8) << "($sp)\n";//the idea is that the sp must have been reset to the
		outFile << "addiu $sp, $sp, " << stackOffset <<"\n";
		outFile << "j $31\n";
    stackOffset = 0;
    paramCount = 0;
	}else if(progAST->getType() == statementList){
		for(int i = 0; i < progAST->getPointers().size(); i++){
			compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
		}
	}else if(progAST->getType() == scope){
  		compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
  }else if(progAST->getType() == assignment){
		//std::cout << "here \n";
    if(!stackAlloc){
      //std::cerr << "assignment\n";
      if(progAST->getInts()[0] == 1){//this refers to assignment type
        std::string variableAssigned = progAST->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
        //std::cerr << "assignmentl\n";ranger
        std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
        std::map<std::string, uint32_t>::iterator it = scopeMap.find(progAST->getStrings()[0]);
        if(it != scopeMap.end())
        {//need to store based on operation type
          type operationType = variableTypeMap[scopeName][variableAssigned];
          std::cerr << "operation type " << operationType << " for variable " << variableAssigned << "\n";
          compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, operationType, returnType);
          if(operationType == 0){
            outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
            outFile << "nop\n";
          }else if(operationType == 2){
            outFile << "swc1 $f0, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
            outFile << "nop\n";
          }
        }else{
          std::map<std::string, uint32_t> funcMap = memMap[funcName];
          std::map<std::string, uint32_t>::iterator itt = funcMap.find(progAST->getStrings()[0]);
          if(itt != funcMap.end()){
            type operationType = variableTypeMap[funcName][variableAssigned];
            std::cerr << "operation type " << operationType << " for variable " << variableAssigned << "\n";
            compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, operationType, returnType);
            if(operationType == 0){
              outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
              outFile << "nop\n";
            }else if(operationType == 2){
              outFile << "swc1 $f0, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
              outFile << "nop\n";
            }
          }else{// If we haven't found the variable in the function scope, look for it in the global scope
          std::map<std::string, uint32_t> globalMap = memMap["global"];
          std::map<std::string, uint32_t>::iterator ittt = globalMap.find(progAST->getStrings()[0]);
          if(ittt != globalMap.end()){
            type operationType = variableTypeMap["global"][variableAssigned];
            std::cerr << "operation type " << operationType << " for variable " << variableAssigned << "\n";
            compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, operationType, returnType);
              outFile << "sw $2, " << variableAssigned << "\n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
              outFile << "nop\n";
          }else{
            std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
          }
          }
        }
        outFile << "move $" << std::to_string(retReg) << ", $2 \n";// returning in the requested register
      }else{
        std::cerr << "TYPE 2 ASSIGNMENT\n";
        compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, intt, returnType);//compiling the index as the first pointer of a type 2 assignment is a subscript
        //outFile << "type 2 assignment start\n";
        outFile << "sw $2, 0($sp)\n";//now the offset is calculated, we push it onto the stack to preserve it while we evaluate the expression to assign to the array element
        outFile << "addiu $sp, $sp, -4\n";
        std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
        std::map<std::string, uint32_t>::iterator it = scopeMap.find(progAST->getPointers()[0]->getStrings()[0]);
        std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
        if(it != scopeMap.end())
        {
          type operationType = variableTypeMap[scopeName][variableAssigned];
          compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, operationType, returnType);
          std::cerr << "finished evaluating lhs for array assignment\n";
          if(operationType == intt){
            outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
            outFile << "lw $3, 0($sp)\n";
            outFile << "nop\n";
            outFile << "addiu $sp, $sp, 4\n";
            outFile << "lw $2, 0($sp)\n";
            outFile << "nop\n";
            outFile << "sll $2, $2, 2\n";
            outFile << "li $1, " << memMap[scopeName][progAST->getPointers()[0]->getStrings()[0]] << "\n";
            outFile << "add  $2, $1, $2\n";
            outFile << "add  $2, $2, $fp\n";
            outFile << "sw $3,0($2)\n";
            outFile << "nop\n";
          }else if(operationType == floatt){
            std::cerr << "FLOAT TYPE 2 ASSIGNMENT\n";
            outFile << "addiu $sp, $sp, 4\n";
            outFile << "lw $2, 0($sp)\n";
            outFile << "nop\n";
            outFile << "sll $2, $2, 2\n";
            std::cerr << "offset for array is " << memMap[scopeName][progAST->getPointers()[0]->getStrings()[0]] << "\n";
            outFile << "li $1, " << memMap[scopeName][progAST->getPointers()[0]->getStrings()[0]] << "\n";
            outFile << "add  $2, $1, $2\n";
            outFile << "add  $2, $2, $fp\n";
            outFile << "swc1 $f0,0($2)\n";
            outFile << "nop\n";
          }

        }else{
          std::map<std::string, uint32_t> funcMap = memMap[funcName];
          std::map<std::string, uint32_t>::iterator itt = funcMap.find(progAST->getPointers()[0]->getStrings()[0]);
          if(itt != funcMap.end()){
            type operationType = variableTypeMap[funcName][variableAssigned];
            std::cerr << "FLOATTHEBOATS\n";
            compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, operationType, returnType);
            if(operationType == intt){
              outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
              outFile << "lw $3, 0($sp)\n";
              outFile << "nop\n";
              outFile << "addiu $sp, $sp, 4\n";
              outFile << "lw $2, 0($sp)\n";
              outFile << "nop\n";
              outFile << "sll $2, $2, 2\n";
              outFile << "li $1, " << memMap[funcName][progAST->getPointers()[0]->getStrings()[0]] << "\n";
              outFile << "add  $2, $1, $2\n";
              outFile << "add  $2, $2, $fp\n";
              outFile << "sw $3,0($2)\n";
              outFile << "nop\n";
            }else if(operationType == floatt){
              std::cerr << "FLOATTHEBOATE\n";
              outFile << "addiu $sp, $sp, 4\n";
              outFile << "lw $2, 0($sp)\n";
              outFile << "nop\n";
              outFile << "sll $2, $2, 2\n";
              outFile << "li $1, " << memMap[funcName][progAST->getPointers()[0]->getStrings()[0]] << "\n";
              outFile << "add  $2, $1, $2\n";
              outFile << "add  $2, $2, $fp\n";
              outFile << "swc1 $f0,0($2)\n";
              outFile << "nop\n";
            }
          }else{
            std::cerr << "here beta\n";
            std::map<std::string, uint32_t> globalMap = memMap["global"];
            std::map<std::string, uint32_t>::iterator ittt = globalMap.find(progAST->getPointers()[0]->getStrings()[0]);
            if(ittt != globalMap.end()){
              type operationType = variableTypeMap["global"][variableAssigned];
              std::cerr << "Operation type is " << operationType << "\n";
              compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, operationType, returnType);
              if(operationType == intt){
                outFile << "move $3, $2\n";
                outFile << "addiu $sp, $sp, 4\n";
                outFile << "lw $2, 0($sp)\n";
                outFile << "nop\n";
                outFile << "sll $2, $2, 2\n";
                outFile << "la $1, arr0" << progAST->getPointers()[0]->getStrings()[0] << "\n";
                outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
                outFile << "sw $3, 0($2)\n";
                outFile << "nop\n";
              }else if(operationType == floatt){
                  outFile << "addiu $sp, $sp, 4\n";
                  outFile << "lw $2, 0($sp)\n";
                  outFile << "nop\n";
                  outFile << "sll $2, $2, 2\n";
                  outFile << "la $1, arr0" << progAST->getPointers()[0]->getStrings()[0] << "\n";
                  outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
                  outFile << "mfc1 $3, $f0\n";
                  outFile << "sw $3,0($2)\n";
                  outFile << "nop\n";
              }
            }
          }
        }

      }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);
    }
	}else if(progAST->getType() == postIncrement){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       std::cerr << "getting single operand\n";
       outFile << "addiu $2, $2, 1 \n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "sw $2, 0($3)\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         outFile << "sw $2, 0($sp)\n";
         outFile << "addiu $sp, $sp, -4\n";//Pushing the value to write into the array element to stack while we figure out the index
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "sw $3, 0($2)\n";
             }
           }
         }
       }
       outFile << "addiu $sp, $sp, 4\n";
       outFile << "lw $" << std::to_string(retReg) << ", 0($sp)\n";
       outFile << "nop\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == postDecrement){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       std::cerr << "getting single operand\n";
       outFile << "addiu $2, $2, -1 \n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "sw $2, 0($3)\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         outFile << "sw $2, 0($sp)\n";
         outFile << "addiu $sp, $sp, -4\n";//Pushing the value to write into the array element to stack while we figure out the index
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "sw $3, 0($2)\n";
             }
           }
         }
       }
       outFile << "addiu $sp, $sp, 4\n";
       outFile << "lw $" << std::to_string(retReg) << ", 0($sp)\n";
       outFile << "nop\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == preIncrement){
         if(!stackAlloc){
           compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
           outFile << "addiu $2, $2, 1 \n";
            outFile << "sw $2, 0($sp)\n";//saving return value onto stack
            outFile << "addiu $sp, $sp, -4\n";
            if(progAST->getPointers()[0]->getType() == variable){
              std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
              //std::cerr << "assignmentl\n";ranger
              std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
              std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
              if(it != scopeMap.end())
              {
                outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
                outFile << "nop\n";
              }else{
                std::map<std::string, uint32_t> funcMap = memMap[funcName];
                std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
                if(itt != funcMap.end()){
                  outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
                  outFile << "nop\n";
                }else{// If we haven't found the variable in the function scope, look for it in the global scope
                std::map<std::string, uint32_t> globalMap = memMap["global"];
                std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
                if(ittt != globalMap.end()){
                  outFile << "la $3, " << variableAssigned << "\n";
                  outFile << "sw $2, 0($3)\n";
                }else{
                  std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
                }
                }
              }
            }else if(progAST->getPointers()[0]->getType() == subscript){
              std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
              outFile << "sw $2, 0($sp)\n";
              outFile << "addiu $sp, $sp, -4\n";//Pushing the value to write into the array element to stack while we figure out the index
              compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
              outFile << "sll $2, $2, 2\n";
              outFile << "addiu $sp, $sp, 4\n";
              outFile << "lw $3, 0($sp)\n";
              std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
              std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
              if(it != scopeMap.end())
              {
                outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
                outFile << "add  $2, $1, $2\n";
                outFile << "add  $2, $2, $fp\n";
                outFile << "sw $3,0($2)\n";
                outFile << "nop\n";
              }else{
                std::map<std::string, uint32_t> funcMap = memMap[funcName];
                std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
                if(itt != funcMap.end()){
                  outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
                  outFile << "add  $2, $1, $2\n";
                  outFile << "add  $2, $2, $fp\n";
                  outFile << "sw $3,0($2)\n";
                  outFile << "nop\n";
                }else{
                  std::cerr << "here beta\n";
                  std::map<std::string, uint32_t> globalMap = memMap["global"];
                  std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
                  if(ittt != globalMap.end()){
                    outFile << "la $1, arr0" << variableAssigned << "\n";
                    outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
                    outFile << "sw $3, 0($2)\n";
                  }
                }
              }
            }
            outFile << "addiu $sp, $sp, 4\n";
            outFile << "lw $" << std::to_string(retReg) << ", 0($sp)\n";
            outFile << "nop\n";
         }else{
           compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
         }
       }else if(progAST->getType() == preDecrement){
         if(!stackAlloc){
           compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
           outFile << "addiu $2, $2, -1 \n";
            outFile << "sw $2, 0($sp)\n";//saving return value onto stack
            outFile << "addiu $sp, $sp, -4\n";
            if(progAST->getPointers()[0]->getType() == variable){
              std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
              //std::cerr << "assignmentl\n";ranger
              std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
              std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
              if(it != scopeMap.end())
              {
                outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
                outFile << "nop\n";
              }else{
                std::map<std::string, uint32_t> funcMap = memMap[funcName];
                std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
                if(itt != funcMap.end()){
                  outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
                  outFile << "nop\n";
                }else{// If we haven't found the variable in the function scope, look for it in the global scope
                std::map<std::string, uint32_t> globalMap = memMap["global"];
                std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
                if(ittt != globalMap.end()){
                  outFile << "la $3, " << variableAssigned << "\n";
                  outFile << "sw $2, 0($3)\n";
                }else{
                  std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
                }
                }
              }
            }else if(progAST->getPointers()[0]->getType() == subscript){
              std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
              outFile << "sw $2, 0($sp)\n";
              outFile << "addiu $sp, $sp, -4\n";//Pushing the value to write into the array element to stack while we figure out the index
              compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
              outFile << "sll $2, $2, 2\n";
              outFile << "addiu $sp, $sp, 4\n";
              outFile << "lw $3, 0($sp)\n";
              std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
              std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
              if(it != scopeMap.end())
              {
                outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
                outFile << "add  $2, $1, $2\n";
                outFile << "add  $2, $2, $fp\n";
                outFile << "sw $3,0($2)\n";
                outFile << "nop\n";
              }else{
                std::map<std::string, uint32_t> funcMap = memMap[funcName];
                std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
                if(itt != funcMap.end()){
                  outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
                  outFile << "add  $2, $1, $2\n";
                  outFile << "add  $2, $2, $fp\n";
                  outFile << "sw $3,0($2)\n";
                  outFile << "nop\n";
                }else{
                  std::cerr << "here beta\n";
                  std::map<std::string, uint32_t> globalMap = memMap["global"];
                  std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
                  if(ittt != globalMap.end()){
                    outFile << "la $1, arr0" << variableAssigned << "\n";
                    outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
                    outFile << "sw $3, 0($2)\n";
                  }
                }
              }
            }
            outFile << "addiu $sp, $sp, 4\n";
            outFile << "lw $" << std::to_string(retReg) << ", 0($sp)\n";
            outFile << "nop\n";
         }else{
           compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
         }
  }else if(progAST->getType() == plusEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "addu $2, $2, $3\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "addu $2, $2, $3\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "addu $2, $2, $1\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "addu $3, $3, $4\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $3\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "addu $3, $3, $4\n";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $3\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "addu $3, $3, $4\n";
                outFile << "sw $3, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $3\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == minusEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "subu $2, $2, $3\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "subu $2, $2, $3\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "subu $2, $2, $1\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "subu $3, $4, $3\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $3\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "subu $3, $4, $3";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $3\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "subu $3, $4, $3\n";
                outFile << "sw $3, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $3\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == timesEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "mult $2, $3 \n";
           outFile << "mflo $2\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "mult $2, $3 \n";
             outFile << "mflo $2\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "mult $2, $1 \n";
             outFile << "mflo $2\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "mult $4, $3 \n";
           outFile << "mflo $4\n";
           outFile << "sw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $4\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "mult $4, $3 \n";
             outFile << "mflo $4\n";
             outFile << "sw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $4\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "mult $4, $3 \n";
               outFile << "mflo $4\n";
                outFile << "sw $4, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $4\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == divEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "div $2, $3 \n";
           outFile << "mflo $2\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "div $2, $3 \n";
             outFile << "mflo $2\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "div $2, $1 \n";
             outFile << "mflo $2\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "div $4, $3 \n";
           outFile << "mflo $4\n";
           outFile << "sw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $4\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "div $4, $3 \n";
             outFile << "mflo $4\n";
             outFile << "sw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $4\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "div $4, $3 \n";
               outFile << "mflo $4\n";
                outFile << "sw $4, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $4\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == modEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "div $2, $3 \n";
           outFile << "mfhi $2\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "div $2, $3 \n";
             outFile << "mfhi $2\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "div $2, $1 \n";
             outFile << "mfhi $2\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "div $4, $3 \n";
           outFile << "mfhi $4\n";
           outFile << "sw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $4\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "div $4, $3 \n";
             outFile << "mfhi $4\n";
             outFile << "sw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $4\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "div $4, $3 \n";
               outFile << "mfhi $4\n";
                outFile << "sw $4, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $4\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == andEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "and $2, $2, $3\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "and $2, $2, $3\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "and $2, $2, $1\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "and $3, $3, $4\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $3\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "and $3, $3, $4\n";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $3\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "and $3, $3, $4\n";
                outFile << "sw $3, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $3\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == orEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "or $2, $2, $3\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "or $2, $2, $3\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "or $2, $2, $1\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "or $3, $3, $4\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $3\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "or $3, $3, $4\n";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $3\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "or $3, $3, $4\n";
                outFile << "sw $3, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $3\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == xorEq){
    if(!stackAlloc){
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//getting the value of the variable/array element
       outFile << "sw $2, 0($sp)\n";//saving return value onto stack
       outFile << "addiu $sp, $sp, -4\n";
       if(progAST->getPointers()[0]->getType() == variable){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];//need to overwrite the variable in memory once the expression is evaluated
         //std::cerr << "assignmentl\n";ranger
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "lw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
           outFile << "addiu $sp, $sp, 4\n";
           outFile << "lw $3, 0($sp) \n";
           outFile << "nop\n";
           outFile << "xor $2, $2, $3\n";
           outFile << "sw $2, " << memMap[scopeName][variableAssigned] << "($fp) \n";
           outFile << "nop\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "lw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $3, 0($sp) \n";
             outFile << "nop\n";
             outFile << "xor $2, $2, $3\n";
             outFile << "sw $2, " << memMap[funcName][variableAssigned] << "($fp) \n";
             outFile << "nop\n";
           }else{// If we haven't found the variable in the function scope, look for it in the global scope
           std::map<std::string, uint32_t> globalMap = memMap["global"];
           std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
           if(ittt != globalMap.end()){
             outFile << "la $3, " << variableAssigned << "\n";
             outFile << "lw $2, 0($3)\n";
             outFile << "addiu $sp, $sp, 4\n";
             outFile << "lw $1, 0($sp) \n";
             outFile << "nop\n";
             outFile << "xor $2, $2, $1\n";
             outFile << "sw $2, 0($3)\n";
             outFile << "nop\n";
           }else{
             std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
           }
           }
         }
       }else if(progAST->getPointers()[0]->getType() == subscript){
         std::string variableAssigned = progAST->getPointers()[0]->getStrings()[0];
         compile(progAST->getPointers()[0]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//compiling the index as the operand is a subscript
         outFile << "sll $2, $2, 2\n";
         outFile << "addiu $sp, $sp, 4\n";
         outFile << "lw $3, 0($sp)\n";
         std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
         std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableAssigned);
         if(it != scopeMap.end())
         {
           outFile << "li $1, " << memMap[scopeName][variableAssigned] << "\n";
           outFile << "add  $2, $1, $2\n";
           outFile << "add  $2, $2, $fp\n";
           outFile << "lw $4,0($2)\n";
           outFile << "nop\n";
           outFile << "xor $3, $3, $4\n";
           outFile << "sw $3,0($2)\n";
           outFile << "nop\n";
           outFile << "move $2, $3\n";
         }else{
           std::map<std::string, uint32_t> funcMap = memMap[funcName];
           std::map<std::string, uint32_t>::iterator itt = funcMap.find(variableAssigned);
           if(itt != funcMap.end()){
             outFile << "li $1, " << memMap[funcName][variableAssigned] << "\n";
             outFile << "add  $2, $1, $2\n";
             outFile << "add  $2, $2, $fp\n";
             outFile << "lw $4,0($2)\n";
             outFile << "nop\n";
             outFile << "xor $3, $3, $4\n";
             outFile << "sw $3,0($2)\n";
             outFile << "nop\n";
             outFile << "move $2, $3\n";
           }else{
             std::cerr << "here beta\n";
             std::map<std::string, uint32_t> globalMap = memMap["global"];
             std::map<std::string, uint32_t>::iterator ittt = globalMap.find(variableAssigned);
             if(ittt != globalMap.end()){
               outFile << "la $1, arr0" << variableAssigned << "\n";
               outFile << "add  $2, $1, $2\n";//$2 contains the offset from the line after compile
               outFile << "lw $4, 0($2)\n";
               outFile << "nop\n";
               outFile << "xor $3, $3, $4\n";
                outFile << "sw $3, 0($2)\n";
                outFile << "nop\n";
                outFile << "move $2, $3\n";
             }
           }
         }
       }
    }else{
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
    }
  }else if(progAST->getType() == lShiftEq){

  }else if(progAST->getType() == rShiftEq){

  }else if(progAST->getType() == addition){
    if(!stackAlloc){
      if(opType == intt){
        std::cerr << "Doing an int addition\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "nop\n";
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "add $" << std::to_string(retReg) << ", $1, $2 \n";
      }else if(opType == floatt){
        std::cerr << "doing a FLOATFLOATFLOAT addition\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "add.s $f0, $f1, $f0 \n";
        outFile << "mfc1 $" << std::to_string(retReg) <<", $f0\n";
      }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
	}else if(progAST->getType() == subtraction){
    if(!stackAlloc){
      if(opType == intt){
        std::cerr << "Doing an int subtraction\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "nop\n";
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "sub $" << std::to_string(retReg) << ", $1, $2 \n";
      }else if(opType == floatt){
        std::cerr << "doing a float subtraction\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "sub.s $f0, $f1, $f0 \n";
        outFile << "mfc1 $" << std::to_string(retReg) <<", $f0\n";
      }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);//the idea is that the left and right hand sides might have some memory to allocate in the frame
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == multiplication){
    if(!stackAlloc){
        if(opType == intt){
          compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
            std::cerr << "getting lhs\n";
           outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
           outFile << "addiu $sp, $sp, -4\n";
          compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
          outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
          outFile << "lw $2, 0($sp)\n";
          outFile << "nop\n";
          outFile << "addiu $sp, $sp, 4\n";
          outFile << "lw $1, 0($sp)\n";
          outFile << "nop\n";
           outFile << "mult $1, $2 \n";
           outFile << "mflo $" << std::to_string(retReg) << "\n";
        }else if(opType == floatt){
          std::cerr << "doing a float multiplication\n";
          compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
            std::cerr << "getting lhs\n";
           outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
           outFile << "addiu $sp, $sp, -4\n";
          compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          outFile << "addiu $sp, $sp, 4\n";
          outFile << "lwc1 $f1, 0($sp)\n";
          outFile << "nop\n";
          outFile << "mul.s $f0, $f1, $f0 \n";
          outFile << "mfc1 $" << std::to_string(retReg) <<", $f0\n";
        }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == division){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "div $1, $2 \n";
         outFile << "mflo $" << std::to_string(retReg) << "\n";
      }else if(opType == floatt){
        std::cerr << "doing a float division\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "div.s $f0, $f1, $f0 \n";
        outFile << "mfc1 $" << std::to_string(retReg) <<", $f0\n";
      }

    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == num){
    if(!stackAlloc){
      std::cerr << "returning a number\n";
      if(opType == intt){
        std::cerr << "integer number\n";
        int val = progAST->getInt();
        std::cerr << "number got is " << val << "\n";
    		outFile << "li $2, " << std::to_string(val)  << "\n";
      }else if(opType == floatt){
        std::cerr << "float number\n";
        float valF = progAST->getFloat();
        std::cerr << "number is " << progAST->getFloat() << "\n";
        float* valP = &valF;
        int* intP = (int*)valP;
        int val = *intP;
        outFile << "li $2," << std::to_string(val) << "\n";
        outFile << "mtc1 $2,$f0\n";
        //std::cerr << "float representation " << val << "\n";
      }
    }
	}else if(progAST->getType() == variable){
    std::cerr << "returning a variable\n";
    std::string variableReturned = progAST->getStrings()[0];
    if(!stackAlloc){
      std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
      std::map<std::string, uint32_t>::iterator it = scopeMap.find(variableReturned);
      if(it != scopeMap.end())
      {
        if(variableTypeMap[scopeName][variableReturned] == intt){
          if(opType == intt){
            std::cerr << "variable is int to int and is named " << variableReturned <<" in scope: " << scopeName << " with offset " << memMap[scopeName][progAST->getStrings()[0]]<<"\n";
            outFile << "lw $" << std::to_string(retReg) << ", " << memMap[scopeName][variableReturned] << "($fp)\n";
            outFile << "nop\n";
          }
        }else if(variableTypeMap[scopeName][variableReturned] == floatt){
          if(opType == intt){
            std::cerr << "variable is float to int and is named " << variableReturned <<" in scope: " << scopeName << " with offset " << memMap[scopeName][progAST->getStrings()[0]]<<"\n";
            outFile << "lwc1 $f0, "<< memMap[scopeName][variableReturned] << "($fp) \n";
            outFile << "nop\n";
            outFile << "trunc.w.s $f0,$f0,$2\n";
            outFile << "mfc1 $2,$f0\n";
          }else if(opType == floatt){
            std::cerr << "variable is float to float and is named " << variableReturned <<" in scope: " << scopeName << " with offset " << memMap[scopeName][progAST->getStrings()[0]]<<"\n";
            outFile << "lwc1 $f0, "<< memMap[scopeName][variableReturned] << "($fp) \n";
            outFile << "nop\n";
          }
        }
      }else{
        std::map<std::string, uint32_t> funcMap = memMap[funcName];
        std::map<std::string, uint32_t>::iterator itt = funcMap.find(progAST->getStrings()[0]);
        if(itt != funcMap.end()){
          if(variableTypeMap[funcName][variableReturned] == intt){
            if(opType == intt){
              std::cerr << "variable is int to int and is named " << variableReturned <<" in scope: " << funcName << " with offset " << memMap[funcName][progAST->getStrings()[0]]<<"\n";
              outFile << "lw $" << std::to_string(retReg) << ", " << memMap[funcName][variableReturned] << "($fp)\n";
              outFile << "nop\n";
            }
          }else if(variableTypeMap[funcName][variableReturned] == floatt){
            if(opType == intt){
              std::cerr << "variable is float to int and is named " << variableReturned <<" in scope: " << funcName << " with offset " << memMap[funcName][progAST->getStrings()[0]]<<"\n";
              outFile << "lwc1 $f0, "<< memMap[funcName][variableReturned] << "($fp) \n";
              outFile << "nop\n";
              outFile << "trunc.w.s $f0,$f0,$2\n";
              outFile << "mfc1 $2,$f0\n";
            }else if(opType == floatt){
              std::cerr << "variable is float to float and is named " << variableReturned <<" in scope: " << funcName << " with offset " << memMap[funcName][progAST->getStrings()[0]]<<"\n";
              outFile << "lwc1 $f0, "<< memMap[funcName][variableReturned] << "($fp) \n";
              outFile << "nop\n";
            }
          }
        }else{// If we haven't found the variable in the function scope, look for it in the global scope
      //  std::cerr << "Global variable " << progAST->getStrings()[0] << "\n";
        std::map<std::string, uint32_t> globalMap = memMap["global"];
        std::map<std::string, uint32_t>::iterator ittt = globalMap.find(progAST->getStrings()[0]);
        if(ittt != globalMap.end()){

          if(variableTypeMap["global"][variableReturned] == intt){
            if(opType == intt){
              std::cerr << "global variable is int to int and is named " << variableReturned <<" in global scope \n";
              outFile << "lw $" << std::to_string(retReg) << ", " << progAST->getStrings()[0] << "\n";
              outFile << "nop\n";
            }
          }else if(variableTypeMap["global"][variableReturned] == floatt){
            if(opType == intt){
              std::cerr << "global variable is float to int and is named " << variableReturned <<" in global scope \n";
              outFile << "lwc1 $f0, "<< progAST->getStrings()[0] << "\n";
              outFile << "nop\n";
              outFile << "trunc.w.s $f0,$f0,$2\n";
              outFile << "mfc1 $2,$f0\n";
            }else if(opType == floatt){
              std::cerr << "global variable is float to float and is named " << variableReturned <<" in global scope \n";
              outFile << "lwc1 $f0, "<< progAST->getStrings()[0] << "\n";
              outFile << "nop\n";
            }
          }

        }else{
          std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
        }
        }
      }

    }
  }else if(progAST->getType() == ifStatement){
    if(!stackAlloc){
      std::cerr << "Start of conditional\n";
  		if(progAST->getInts()[0] == 2){
        std::string ifScope = progAST->getIfName();
        std::string elseScope = progAST->getElseName();
  			std::string trueLabel = genUniqueLabel("trueLabel");
  			std::string falseLabel = genUniqueLabel("falseLabel");
  			compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, ifScope, continueLabel, intt, returnType);//evaluating condition
  			 outFile << "beq $2, $0," << falseLabel << "\n";//if false then skip the true condition
         outFile << "nop\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, ifScope, continueLabel, intt, returnType);//true condition statementList
  			 outFile <<  "b " << trueLabel << "\n";
         outFile << "nop\n";
  			 outFile << falseLabel << ":\n";
  			compile(progAST->getPointers()[2],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, elseScope, continueLabel, intt, returnType);//else condition statementList
  			 outFile << trueLabel << ":\n";
  		}else{
        std::string ifScope = progAST->getIfName();
  			std::string skipLabel = genUniqueLabel("skipLabel");
  			compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, ifScope, continueLabel, intt, returnType);//evaluating condition
  			 outFile << "beq $2, $0," << skipLabel << "\n";//if false then skip the true condition
         outFile << "nop\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, ifScope, continueLabel, intt, returnType);//true condition statementList
  			 outFile << skipLabel << ":\n";
  		}
  		std::cerr << "End of conditional\n";
    }else{
      if(progAST->getInts()[0] == 2){
        std::string ifScope = genUniqueLabel("ifScope");
        std::string elseScope = genUniqueLabel("elseScope");
        progAST->setIfScopeName(ifScope);
        progAST->setElseScopeName(elseScope);
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, ifScope, continueLabel, intt, returnType);
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, ifScope, continueLabel, intt, returnType);
        compile(progAST->getPointers()[2],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, elseScope, continueLabel, intt, returnType);
      }else{
        std::string ifScope = genUniqueLabel("ifScope");
        progAST->setIfScopeName(ifScope);
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, ifScope, continueLabel, intt, returnType);
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, ifScope, continueLabel, intt, returnType);
      }
    }
	}else if(progAST->getType() == whileLoop){
    if(!stackAlloc){
      std::string whileScope = progAST->getScopeName();
      //std::cout << "escape label is " << escapeLabel;
      bool typeFound = false;
      std::cerr << "found a while loop and determined condition type as " << progAST->getConditionType(progAST->getPointers()[0], variableTypeMap,  memMap, scopeName,funcName, typeFound) << "\n";
      type conditionType = progAST->getConditionType(progAST->getPointers()[0], variableTypeMap,  memMap, scopeName,funcName, typeFound);
      std::string beginLabel = genUniqueLabel("beginLabel");
      std::string escapeLabel = genUniqueLabel("escapeLabel");
      std::string continueLabel = genUniqueLabel("continueLabel");
       outFile << beginLabel << ":\n";
       //std::cerr << "about to evaluate condition\n";
       outFile << "#condition\n";
      compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile,paramCount, false, funcName, whileScope, continueLabel, conditionType, returnType);
      if(conditionType == floatt){
        std::cerr << "converting condition value to integer\n";
        outFile << "#truncating\n";
        outFile << "nop\n";
        outFile << "trunc.w.s $f0,$f0,$2\n";
        outFile << "mfc1 $2,$f0\n";
        outFile << "beq $2, $0," << escapeLabel << "\n";//condition evaluation in $2
        outFile << "nop\n";
      }else if(conditionType == intt){
        outFile << "beq $2, $0," << escapeLabel << "\n";//condition evaluation in $2
        outFile << "nop\n";
      }
      outFile << "#end of condition\n";
      if(progAST->getPointers().size() == 2){
        compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile,paramCount, false, funcName, whileScope, continueLabel, intt, returnType);
      }
       outFile << continueLabel << ":\n";
       outFile << "b " << beginLabel << "\n";
       outFile << "nop\n";
       outFile << escapeLabel << ":\n";
    }else{
      std::string whileScope = genUniqueLabel("whileScope");
      progAST->setScopeName(whileScope);
      compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile,paramCount, true, funcName, whileScope, continueLabel, intt, returnType);
      if(progAST->getPointers().size() == 2){
        compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile,paramCount, true, funcName, whileScope, continueLabel, intt, returnType);
      }
    }

  }else if(progAST->getType() == ltOp){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "slt  $" << std::to_string(retReg) <<  ", $1, $2 \n";
      }else if(opType == floatt){
        std::string trueLabel = genUniqueLabel("ltTrueLabel");
        std::string skipLabel = genUniqueLabel("ltSkipLabel");
        float one = 1;
        float zero = 0;
        float* oneP = &one;
        float* zeroP = &zero;
        int oneInt = * (int*)oneP;
        int zeroInt = * (int*) zeroP;
        std::cerr << "doing a float less than\n";
        outFile << "li $2," << std::to_string(oneInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "swc1 $f0, 0($sp)\n";
        outFile << "addiu $sp,$sp, -4\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "c.lt.s $f1, $f0 \n";
        outFile << "nop\n";
        outFile << "bc1t " << trueLabel << "\n";
        outFile << "nop\n";
        outFile << "li $2," << std::to_string(zeroInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "b " << skipLabel << "\n";
        outFile << "nop\n";
        outFile << trueLabel << ":\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f0, 0($sp)\n";
        outFile << skipLabel << ":\n";
      }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == gtOp){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "slt  $" << std::to_string(retReg) <<  ", $2, $1 \n";
      }else if(opType == floatt){
        std::string trueLabel = genUniqueLabel("ltTrueLabel");
        std::string skipLabel = genUniqueLabel("ltSkipLabel");
        float one = 1;
        float zero = 0;
        float* oneP = &one;
        float* zeroP = &zero;
        int oneInt = * (int*)oneP;
        int zeroInt = * (int*) zeroP;
        std::cerr << "doing a float greater than\n";
        outFile << "li $2," << std::to_string(oneInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "swc1 $f0, 0($sp)\n";
        outFile << "addiu $sp,$sp, -4\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "c.lt.s $f0, $f1 \n";
        outFile << "nop\n";
        outFile << "bc1t " << trueLabel << "\n";
        outFile << "nop\n";
        outFile << "li $2," << std::to_string(zeroInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "b " << skipLabel << "\n";
        outFile << "nop\n";
        outFile << trueLabel << ":\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f0, 0($sp)\n";
        outFile << skipLabel << ":\n";
      }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == lteOp){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "slt  $" << std::to_string(retReg) <<  ", $2, $1 \n";
         outFile << "xori $" << std::to_string(retReg) << ",$2,0x1\n";//inversion of greater than result
      }else if(opType == floatt){
        std::string trueLabel = genUniqueLabel("ltTrueLabel");
        std::string skipLabel = genUniqueLabel("ltSkipLabel");
        float one = 1;
        float zero = 0;
        float* oneP = &one;
        float* zeroP = &zero;
        int oneInt = * (int*)oneP;
        int zeroInt = * (int*) zeroP;
        std::cerr << "doing a float less than\n";
        outFile << "li $2," << std::to_string(oneInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "swc1 $f0, 0($sp)\n";
        outFile << "addiu $sp,$sp, -4\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "c.le.s $f1, $f0 \n";
        outFile << "nop\n";
        outFile << "bc1t " << trueLabel << "\n";
        outFile << "nop\n";
        outFile << "li $2," << std::to_string(zeroInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "b " << skipLabel << "\n";
        outFile << "nop\n";
        outFile << trueLabel << ":\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f0, 0($sp)\n";
        outFile << skipLabel << ":\n";
      }

    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == gteOp){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
          std::cerr << "getting lhs\n";
         outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
         outFile << "slt  $" << std::to_string(retReg) <<  ", $1, $2 \n";
         outFile << "xori $" << std::to_string(retReg) << ",$2,0x1\n";//inversion of less than result
      }else if(opType == floatt){
        std::string trueLabel = genUniqueLabel("ltTrueLabel");
        std::string skipLabel = genUniqueLabel("ltSkipLabel");
        float one = 1;
        float zero = 0;
        float* oneP = &one;
        float* zeroP = &zero;
        int oneInt = * (int*)oneP;
        int zeroInt = * (int*) zeroP;
        std::cerr << "doing a float less than\n";
        outFile << "li $2," << std::to_string(oneInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "swc1 $f0, 0($sp)\n";
        outFile << "addiu $sp,$sp, -4\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "c.le.s $f0, $f1 \n";
        outFile << "nop\n";
        outFile << "bc1t " << trueLabel << "\n";
        outFile << "nop\n";
        outFile << "li $2," << std::to_string(zeroInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "b " << skipLabel << "\n";
        outFile << "nop\n";
        outFile << trueLabel << ":\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f0, 0($sp)\n";
        outFile << skipLabel << ":\n";
      }

    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == lShiftOp){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        std::cerr << "getting lhs\n";
       outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
       outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
       outFile << "sll  $" << std::to_string(retReg) <<  ", $1, $2 \n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == rShiftOp){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        std::cerr << "getting lhs\n";
       outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
       outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
       outFile << "sra  $" << std::to_string(retReg) <<  ", $1, $2 \n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == moduloOp){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        std::cerr << "getting lhs\n";
       outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
       outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
       outFile << "div $1, $2 \n";
       outFile << "mfhi $" << std::to_string(retReg) << "\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == returnStatement){
    if(!stackAlloc){
      std::cerr << "Encountered a return statement and will pass return type " << returnType << " as operation type\n";
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile, paramCount, false, funcName, scopeName, continueLabel, returnType);
      outFile <<"b " <<funcName << "End \n";
      outFile << "nop\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == functionCall){
    std::cerr << "stackAlloc value " << stackAlloc << "\n";
    if(!stackAlloc){
      std::cerr << "functioncall\n";
      outFile << "#functioncall\n";
      outFile << "addiu $sp, $sp,-" << progAST->getPointers()[0]->getPointers().size()*4 << "\n";//this needs to get more complicated to support different types
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile, paramCount, false, funcName, scopeName, continueLabel);//putting the variables to pass into registers and memory
      outFile << "jal " << progAST->getStrings()[0] << "\n";
      outFile << "nop\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp," << progAST->getPointers()[0]->getPointers().size()*4 << "\n";
    }else{
      std::cerr << "allocating for the function call\n";
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile, paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == concreteParameterList){
    std::cerr << "conc parameter \n";
    if(!stackAlloc){
      //std::cerr << "number of concrete parameters " << progAST->getInts().size() << "\n";
      //std::cerr << "number of concrete parameters " << progAST->getInts().size() << "\n";
      std::cerr << "Size of concrete parameter list is: " << progAST->getPointers().size() << "\n";
      for(int i = 0; i < progAST->getPointers().size() && i < 4; i++){
        //std::cerr << "beginning allocation\n";
        compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile, paramCount, false, funcName, scopeName, continueLabel);
        outFile << "move $" << (4 + i) << ", $2\n";
        std::cerr << "moved a parameter into register\n";
      }
      if(progAST->getPointers().size() > 4){
        //std::cerr << "allocating extra parameters\n";
        for(int i = 4; i < progAST->getPointers().size(); i++){
            std::cerr << "writing concrete parameter to memory: " << progAST->getPointers()[i] << "\n";
            compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile, paramCount, false, funcName, scopeName, continueLabel);
            outFile << "sw $2, " << (12 + (i-3)*4) << "($sp)\n";//CHECK THIS
  			}
      }
    }else{
        if(progAST->getPointers().size() > 0){
          //std::cerr << "detected a function call with size " << progAST->getInts().size() << "\n";
          //std::cerr << "stackoffset is currently " << stackOffset << "\n";
          stackOffset = stackOffset + (progAST->getPointers().size()-1)*4;//allocating
          for(int i = 0; i < progAST->getPointers().size() && i < 4; i++){
            compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile, paramCount, true, funcName, scopeName, continueLabel);
          }
        }
    }
  }else if(progAST->getType() == neg){
    std::cerr << "neg\n";
    if(!stackAlloc){

      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "subu $2, $0, $2\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == equals){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        std::cerr << "getting lhs\n";
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "xor $2, $2, $1\n";
        outFile << "sltu $" << std::to_string(retReg)<<",$2, 1\n";
      }else if(opType == floatt){
        std::string trueLabel = genUniqueLabel("ltTrueLabel");
        std::string skipLabel = genUniqueLabel("ltSkipLabel");
        float one = 1;
        float zero = 0;
        float* oneP = &one;
        float* zeroP = &zero;
        int oneInt = * (int*)oneP;
        int zeroInt = * (int*) zeroP;
        std::cerr << "doing a float less than\n";
        outFile << "li $2," << std::to_string(oneInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "swc1 $f0, 0($sp)\n";
        outFile << "addiu $sp,$sp, -4\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "c.eq.s $f1, $f0 \n";
        outFile << "nop\n";
        outFile << "bc1t " << trueLabel << "\n";
        outFile << "nop\n";
        outFile << "li $2," << std::to_string(zeroInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "b " << skipLabel << "\n";
        outFile << "nop\n";
        outFile << trueLabel << ":\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f0, 0($sp)\n";
        outFile << skipLabel << ":\n";
      }
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == arrayDeclaration){
    if(scopeName != "global"){
      if(stackAlloc){
        variableTypeMap[scopeName][progAST->getStrings()[0]] = progAST->getDataType();
        stackOffset = stackOffset + progAST->getInts()[0]*4;
        std::cerr << "Array " <<progAST->getStrings()[0] << " of size " << progAST->getInts()[0] << " allocated \n";
      }else{
        std::cerr << "hererear\n";
          std::cerr << "Before  size of memmap is " << memMap[scopeName].size() << "\n";
          std::cerr << "paramcount " << paramCount <<"\n";

          std::cerr << "\n";
          std::cerr << "\n";
          std::cerr << "\n";
          std::cerr << "scopename " << scopeName << "\n";
          std::cerr << "stackOffset " << stackOffset << "\n";
          std::cerr << "paramCount " << paramCount << "\n";
          std::cerr << "funcName " << funcName << "\n";
          int offset = (stackOffset - 8) - (variableCount[funcName])*4 - progAST->getInts()[0]*4;
          variableCount[funcName] = variableCount[funcName] + progAST->getInts()[0]*4;
          std::cerr << "variable count for  " << funcName << " is " << variableCount[funcName] << "\n";
          std::cerr << "\n";
          std::cerr << "\n";
          std::cerr << "\n";
          memMap[scopeName][progAST->getStrings()[0]] = offset;
          for(int i = 1; i < progAST->getInts()[0]; i++){
            std::string dummyName = genUniqueLabel(progAST->getStrings()[0]);
            memMap[scopeName][progAST->getStrings()[0] + dummyName] = offset;
          }//adding dummy entries all with the same offset which will never be referred to but indicate how many bytes are taken for the (memMap[scopeName].size() - paramCount)*4 term in subsequent array/variable allocations
          std::cerr << "allocating array " <<progAST->getStrings()[0] << " to " << memMap[scopeName][progAST->getStrings()[0]] <<" \n";
          std::cerr << "current size of memmap is " << memMap[scopeName].size() << "\n";
      }
    }else{
      variableTypeMap["global"][progAST->getStrings()[0]] = progAST->getDataType();
      memMap["global"][progAST->getStrings()[0]] = 4;//only need to declare the existence of the array once in the memory map as the global one isn't used for frame allocation
      for(int i = 0; i < progAST->getInts()[0]; i++){
        outFile << "arr" << i << progAST->getStrings()[0] <<": \n";//declare using same label for all array entries, the index at the beginning makes sure it is not a valid variable name to avoid conflicts and also have unique labels
      }
    }
  }else if(progAST->getType() == subscript){
      if(!stackAlloc){
        std::cerr << "returning an array element\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sll $2, $2, 2\n";
        std::map<std::string, uint32_t> scopeMap = memMap[scopeName];
        std::map<std::string, uint32_t>::iterator it = scopeMap.find(progAST->getStrings()[0]);
        if(it != scopeMap.end()){
          outFile << "li $1, " << memMap[scopeName][progAST->getStrings()[0]] << "\n";
          outFile << "add  $2, $1, $2\n";
          outFile << "add  $2, $2, $fp\n";
          type operationType = variableTypeMap[scopeName][progAST->getStrings()[0]];
          std::cerr << "Returning a subscript of type " << operationType << " for array " << progAST->getStrings()[0] << "\n";
          if(operationType == 0){
            outFile << "lw $" << std::to_string(retReg) << ", 0($2)\n";
            outFile << "nop\n";
          }else if(operationType == 2){
            outFile << "lwc1 $f0, 0($2) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
            outFile << "nop\n";
            if(opType == 0){
                std::cerr << "array is float to int and is named " << progAST->getStrings()[0] <<" in scope: " << scopeName << " with offset " << memMap[scopeName][progAST->getStrings()[0]]<<"\n";
                outFile << "trunc.w.s $f0,$f0,$2\n";
                outFile << "mfc1 $2,$f0\n";
            }
          }

        }else{
          std::map<std::string, uint32_t> funcMap = memMap[funcName];
          std::map<std::string, uint32_t>::iterator itt = funcMap.find(progAST->getStrings()[0]);
          if(itt != funcMap.end()){
            outFile << "li $1, " << memMap[funcName][progAST->getStrings()[0]] << "\n";
            outFile << "add  $2, $1, $2\n";
            outFile << "add  $2, $2, $fp\n";
            type operationType = variableTypeMap[funcName][progAST->getStrings()[0]];
            std::cerr << "Returning a subscript of type " << operationType << " for array " << progAST->getStrings()[0] << "\n";
            if(operationType == 0){
              outFile << "lw $" << std::to_string(retReg) << ", 0($2)\n";
              outFile << "nop\n";
            }else if(operationType == 2){
              outFile << "lwc1 $f0, 0($2) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
              outFile << "nop\n";
              if(opType == 0){
                  std::cerr << "array is float to int and is named " << progAST->getStrings()[0] <<" in scope: " << funcName << " with offset " << memMap[funcName][progAST->getStrings()[0]]<<"\n";
                  outFile << "trunc.w.s $f0,$f0,$2\n";
                  outFile << "mfc1 $2,$f0\n";
              }
            }
          }else{
            std::cerr << "Got to checking global array\n";
            std::map<std::string, uint32_t> globalMap = memMap["global"];
            std::map<std::string, uint32_t>::iterator ittt = globalMap.find(progAST->getStrings()[0]);
            if(ittt != globalMap.end()){
              type operationType = variableTypeMap["global"][progAST->getStrings()[0]];
              std::cerr << "operation type for global array is " << operationType << "\n";
              if(operationType == 0){
                outFile << "la $3, arr0" << progAST->getStrings()[0] << "\n";//the agreed format for the label of the first memory location change for other types
                outFile << "add  $2, $3, $2\n";//$2 contains the offset from the line after compile
                outFile << "lw $" << std::to_string(retReg) << ", 0($2)\n";
              }else if(operationType == 2){
                outFile << "la $3, arr0" << progAST->getStrings()[0] << "\n";//the agreed format for the label of the first memory location change for other types
                outFile << "add  $2, $3, $2\n";//$2 contains the offset from the line after compile
                outFile << "lwc1 $f0, 0($2) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
                outFile << "nop\n";
                if(opType == 0){
                    std::cerr << "global array is float to int and is named " << progAST->getStrings()[0];
                    outFile << "trunc.w.s $f0,$f0,$2\n";
                    outFile << "mfc1 $2,$f0\n";
                }
              }
            }else{
              std::cerr << "Y U GIVE WRONG CODE? Ha? HA?\n";
            }
          }
        }
      }else{
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      }
  }else if(progAST->getType() == forLoop){
    if(!stackAlloc){
      std::string forScope = progAST->getScopeName();
      std::string escapeLabel = genUniqueLabel("escapeLabel");
      std::string beginLabel = genUniqueLabel("beginLabel");
      std::string continueLabel = genUniqueLabel("continueLabel");
      compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile,paramCount, false, funcName, forScope,continueLabel, intt, returnType);
       outFile << beginLabel << ":\n";
       std::cerr << "about to evaluate condition\n";
      compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile,paramCount, false, funcName, forScope,continueLabel,intt, returnType);
       outFile << "beq $2, $0," << escapeLabel << "\n";//condition evaluation in $2
       outFile << "nop\n";
       if(progAST->getPointers().size() == 4){
         compile(progAST->getPointers()[3], memMap, 2, stackOffset, outFile,paramCount, false, funcName, forScope, continueLabel, intt, returnType);//actually, continueLabel is only needed for the loop body where a continue statement might lie
       }
      outFile << continueLabel << ":\n";// the compile below is for the increment, so a continue branches just before the loop increment
      compile(progAST->getPointers()[2], memMap, 2, stackOffset, outFile,paramCount, false, funcName, forScope, continueLabel, intt, returnType);
       outFile << "b " << beginLabel << "\n";
       outFile << "nop\n";
       outFile << escapeLabel << ":\n";
    }else{
      std::string forScope = genUniqueLabel("forScope");
      progAST->setScopeName(forScope);
      compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile,paramCount, true, funcName, forScope, continueLabel, intt, returnType);
      compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile,paramCount, true, funcName, forScope, continueLabel, intt, returnType);
      compile(progAST->getPointers()[2], memMap, 2, stackOffset, outFile,paramCount, true, funcName, forScope, continueLabel, intt, returnType);
      if(progAST->getPointers().size() == 4){
        compile(progAST->getPointers()[3], memMap, 2, stackOffset, outFile,paramCount, true, funcName, forScope, continueLabel, intt, returnType);
      }

    }
  }else if(progAST->getType() == switchStatement){
    if(!stackAlloc){
      std::string switchEndLabel = genUniqueLabel("switchEnd");
      //std::cerr << "got to switchstatement\n";
      //std::cerr << "switch end label << "<< switchEndLabel << "\n";
      //outFile << "start of eval\n";
      outFile << "#evaluating controlling expr\n";
      compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile,paramCount, false, funcName, switchEndLabel, continueLabel, intt, returnType);//evaluating the controlling expression
      //outFile << "end of eval\n";
      outFile << "sw $2, 0($sp)\n";//the evaluation of the controlling expression is pushed onto the stack
      outFile << "addiu $sp, $sp, -4\n";
      progAST->getPointers()[1]->setLabel(switchEndLabel);
      compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile,paramCount, false, funcName, switchEndLabel, continueLabel, intt, returnType);
      outFile << switchEndLabel << ":\n";
    }else{
      compile(progAST->getPointers()[0], memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);//evaluating the controlling expression
      compile(progAST->getPointers()[1], memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);//evaluating the controlling expression
    }

  }else if(progAST->getType() == caseList){
    if(!stackAlloc){
      std::cerr << "got to caselist \n";
      std::cerr << "size of caselist " << progAST->getPointers().size() << "\n";
      for(int i = 0; i < progAST->getPointers().size(); i++){
        compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
  		}
      outFile << "addiu $sp, $sp, 4\n";//at this point, we no longer need the controlling expression so we pop it off the stack
      //checking for a default case to print
      bool foundDefault = false;
      for(int i = 0; i < progAST->getPointers().size(); i++){
        if(progAST->getPointers()[i]->getInts()[0] == 2){//if the caseNode is a default one
          foundDefault = true;
          outFile << "b " << progAST->getPointers()[i]->getLabel() << "\n";//label set in the previous for loop
          outFile << "nop\n";
        }
  		}
      if(!foundDefault){
        outFile << "b "<< progAST->getLabel() << "\n";
        outFile << "nop\n";
      }
      for(int i = 0; i < progAST->getPointers().size(); i++){
        compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
  		}
    }else{
      for(int i = 0; i < progAST->getPointers().size(); i++){
        compile(progAST->getPointers()[i],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);
  		}
    }
  }else if(progAST->getType() == caseNode){
    if(!stackAlloc){

        if(progAST->isFirstTime() == true){
          if(progAST->getInts()[0] == 1){
            std::string caseLabel = genUniqueLabel("case");
            progAST->setLabel(caseLabel);
            std::cerr << "first time\n";
            progAST->setFirstTime(false);
            compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
            outFile << "move $3, $2\n";
            outFile << "lw $2, 4($sp)\n";//restoring value of controlling expression into $2
            outFile << "beq $3, $2, " << caseLabel << "\n";
            outFile << "nop\n";
          }else{
            //won't do anything for a default case apart from creating a label for it
            std::string caseLabel = genUniqueLabel("case");
            progAST->setLabel(caseLabel);
            progAST->setFirstTime(false);
          }
        }else{
          std::cerr << "second time\n";
          outFile <<  progAST->getLabel() <<":\n";
          if(progAST->getInts()[0] == 1){
            compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
          }else{
            std::cerr << "printing label for default \n";
            compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, stackAlloc, funcName, scopeName, continueLabel, intt, returnType);
          }

        }
    }else{
      //std::cerr << "printing for a case node KJASK:LDJAKFDASNHFPIASFP@IAJEPFD@JAEDFP~OAJSD\n";
      if(progAST->getInts()[0] == 1){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);
      }else{
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel, intt, returnType);
      }
    }

  }else if(progAST->getType() == breakStatement){
    if(!stackAlloc){
          outFile << "b " << scopeName << "\n";
    }
  }else if(progAST->getType() == continueStatement){
    if(!stackAlloc){
      outFile << "b " << continueLabel << "\n";
    }
  }else if(progAST->getType() == enumerationSpecifier){
    if(stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
    }

  }else if(progAST->getType() == enumeratorList){
    if(!stackAlloc){
          outFile << "addiu $2, $0, -1\n";
    }
    int prevEnumVal = 0;
    for(int i = 0; i < progAST->getPointers().size(); i++){
      if(scopeName != "global"){
        if(stackAlloc){
            stackOffset = stackOffset + 4;
        }else{
          if(progAST->getPointers()[i]->getInts()[0] == 1){
            std::string enumName = progAST->getPointers()[i]->getStrings()[0];
              memMap[scopeName][enumName] = (stackOffset - 8) - (memMap[scopeName].size() - paramCount)*4 - 4;
              std::cerr << "allocating enumerator " <<enumName << " to " << memMap[scopeName][enumName] <<" \n";
              compile(progAST->getPointers()[i]->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);//evaluating the constExpr that assigns the enumerator
                outFile << "sw $2, " << memMap[scopeName][enumName] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
                outFile << "nop\n";

          }else{
            //std::cerr << "living da life " << (progAST->getPointers()[i]->getType() == enumeratorList) <<"\n";
            std::string enumName = progAST->getPointers()[i]->getStrings()[0];
          //  std::cerr << "living da life\n";
              outFile << "addiu $2, $2, 1\n";//incrementing from the previous enumerators value when we don't define one as is the case for a type 2 enumerator
              memMap[scopeName][enumName] = (stackOffset - 8) - (memMap[scopeName].size() - paramCount)*4 - 4;
              std::cerr << "allocating enumerator " <<enumName << " to " << memMap[scopeName][enumName] <<" \n";
              outFile << "sw $2, " << memMap[scopeName][enumName] << "($fp) \n";//writing the variable's new value in memory, no need to retrieve it so no lw before this
              outFile << "nop\n";
          }
        }
      }else{
        if(progAST->getPointers()[i]->getInts()[0] == 1){
          std::string enumName = progAST->getPointers()[i]->getStrings()[0];
            memMap[scopeName][enumName] = 4;
            std::cerr << "allocating enumerator " <<enumName << " to global \n";
            outFile << enumName << ": .word " <<progAST->getPointers()[i]->getInts()[1]<< " \n";
            prevEnumVal = progAST->getPointers()[i]->getInts()[1];
            std::cerr << "setting previous enumval to " << progAST->getPointers()[i]->getInts()[1] << "\n";

        }else{
            std::string enumName = progAST->getPointers()[i]->getStrings()[0];
            memMap[scopeName][enumName] = 4;
            std::cerr << "allocating enumerator " <<enumName << " to  global \n";
            outFile << enumName << ": .word " <<prevEnumVal<< " \n";
        }

      }

      prevEnumVal++;
    }
  }else if(progAST->getType() == notEqual){
    if(!stackAlloc){
      if(opType == intt){
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        std::cerr << "getting lhs\n";
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
        outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
        outFile << "lw $2, 0($sp)\n";
        outFile << "nop\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lw $1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "xor $2, $2, $1\n";
        outFile << "sltu $" << std::to_string(retReg)<<",$0, $2\n";
      }else if(opType == floatt){
        std::string trueLabel = genUniqueLabel("ltTrueLabel");
        std::string skipLabel = genUniqueLabel("ltSkipLabel");
        float one = 1;
        float zero = 0;
        float* oneP = &one;
        float* zeroP = &zero;
        int oneInt = * (int*)oneP;
        int zeroInt = * (int*) zeroP;
        std::cerr << "doing a float less than\n";
        outFile << "li $2," << std::to_string(oneInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "swc1 $f0, 0($sp)\n";
        outFile << "addiu $sp,$sp, -4\n";
        compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
          std::cerr << "getting lhs\n";
         outFile << "swc1 $f0, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
         outFile << "addiu $sp, $sp, -4\n";
        compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel, opType);
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f1, 0($sp)\n";
        outFile << "nop\n";
        outFile << "c.eq.s $f1, $f0 \n";
        outFile << "nop\n";
        outFile << "bc1f " << trueLabel << "\n";
        outFile << "nop\n";
        outFile << "li $2," << std::to_string(zeroInt) << "\n";
        outFile << "mtc1 $2,$f0\n";
        outFile << "b " << skipLabel << "\n";
        outFile << "nop\n";
        outFile << trueLabel << ":\n";
        outFile << "addiu $sp, $sp, 4\n";
        outFile << "lwc1 $f0, 0($sp)\n";
        outFile << skipLabel << ":\n";
      }

    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == bitWiseAnd){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      std::cerr << "getting lhs\n";
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
      outFile << "and $" << std::to_string(retReg)<< ", $2, $1\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == bitWiseIor){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      std::cerr << "getting lhs\n";
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
      outFile << "or $" << std::to_string(retReg)<< ", $2, $1\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == bitWiseEor){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      std::cerr << "getting lhs\n";
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
      outFile << "xor $" << std::to_string(retReg)<< ", $2, $1\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == logicalAnd){
    if(!stackAlloc){
      std::string falseLabel = genUniqueLabel("false");
      std::string endLabel = genUniqueLabel("end");
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      std::cerr << "getting lhs\n";
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
      outFile << "beq $1, $0, " << falseLabel << "\n";
      outFile << "nop\n";
      outFile << "beq $2, $0, " << falseLabel << "\n";
      outFile << "nop\n";
      outFile << "li $" << std::to_string(retReg)<< ", 1 \n";
      outFile << "b " << endLabel << "\n";
      outFile << "nop\n";
      outFile << falseLabel << ":\n";
      outFile << "move $" << std::to_string(retReg)<< ", $0 \n";
      outFile << endLabel << ":\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == notOp){
    if(!stackAlloc){
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sltu $2, $2, 1\n";
      outFile << "andi $2, $2, 0x00ff\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST->getType() == logicalOr){
    if(!stackAlloc){
      std::string falseLabel = genUniqueLabel("false");
      std::string trueLabel = genUniqueLabel("true");
      std::string endLabel = genUniqueLabel("end");
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      std::cerr << "getting lhs\n";
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "addiu $sp, $sp, -4\n";
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, false, funcName, scopeName, continueLabel);
      outFile << "sw $2, 0($sp)\n";//need to save value of lhs in memory in this fixed address since the below code will overwrite $2
      outFile << "lw $2, 0($sp)\n";
      outFile << "nop\n";
      outFile << "addiu $sp, $sp, 4\n";
      outFile << "lw $1, 0($sp)\n";
      outFile << "nop\n";
      outFile << "bne $1, $0, " << trueLabel << "\n";
      outFile << "nop\n";
      outFile << "beq $2, $0, " << falseLabel << "\n";
      outFile << "nop\n";
      outFile << trueLabel << ": \n";
      outFile << "li $" << std::to_string(retReg)<< ", 1 \n";
      outFile << "b " << endLabel << "\n";
      outFile << "nop\n";
      outFile << falseLabel << ":\n";
      outFile << "move $" << std::to_string(retReg)<< ", $0 \n";
      outFile << endLabel << ":\n";
    }else{
      compile(progAST->getPointers()[0],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
      compile(progAST->getPointers()[1],  memMap, 2, stackOffset, outFile,paramCount, true, funcName, scopeName, continueLabel);
    }
  }else if(progAST == NULL){
		std::cerr << "Error, null pointer encountered in AST \n";
	}
}
