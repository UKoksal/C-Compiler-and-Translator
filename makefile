CPPFLAGS += -W -Wall -g

# This avoids error: ‘fileno’ was not declared in this scope
CPPFLAGS += -std=c++0x

# Avoid warnings about yyunput not used
CPPFLAGS += -Wno-unused-function

all : bin/c_compiler

bin/c_compiler: parser.o lexer.o codeGenerator.o
	g++ -o bin/c_compiler $^

lexer.cpp: lexer.flex
	flex  -o lexer.cpp lexer.flex

lexer.o : lexer.cpp
	g++ -c lexer.cpp

parser.cpp: parser.y
	bison -v -d parser.y -o parser.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

codeGenerator.o : codeGenerator.cpp parser.hpp
	g++ -c codeGenerator.cpp

compile: inputCode.c
	./bin/c_compiler  -S inputCode.c -o assemb.s
	mips-linux-gnu-gcc -mfp32 -static -o assembexec assemb.s
test: inputCode.c driver.c
	./bin/c_compiler  -S inputCode.c -o assemb.s
	mips-linux-gnu-gcc -mfp32 -static -o test_program.o -c assemb.s
	mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o driver.c
		


clean :
	-rm -f parseTester
	-rm -f parser.cpp
	-rm -f lexer.cpp
	-rm -f parser.h
	-rm -f *.o
	-rm -f ./bin/c_compiler
