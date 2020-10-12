#include "parser.hpp"
#include<iostream>
int main(){
		const Program* ast=parseAST();
		std::cout << "done \n";
		 ast->print(std::cout);
}
/*int main(){
	while(1){
		tokenType type = (tokenType)yylex();
		std::cout << "\n token type " << type << "\n";
		if(type == None){
			break;
		}
	}

}*/
