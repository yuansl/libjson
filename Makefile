CC=gcc
CFLAGS=-g -Wall
CXX=g++
CXXFLAGS=-std=c++14 $(CFLAGS)
YACC=bison
YACCFLAGS =-d
LEX=flex
LEXCPP=flex++
CPP=cpp
CPPFLAGS =-I$(HOME)/lib
LDFLAGS = -L$(HOME)/lib
LDLIBS = -lutil -lfl

OBJS = json.o lex.yy.o lex.yy.cc json-grammar.tab.cc json-grammar.tab.o

.PHONY: all clean
all: json

test-json: test-json.o
	$(CXX) $(LDFLAGS) -o $@ $<

json: json-token.o json-grammar.o
	$(CC) $(LDFLAGS) -o $@ json-token.o json-grammar.o $(LDLIBS)

json-token.c: json-token.l json-grammar.c
	$(LEX) -o $@ json-token.l

json-grammar.c: json-grammar.y
	$(YACC) $(YACCFLAGS) -o $@ json-grammar.y

json2: lex.yy.o json-grammar.tab.o
	$(CXX) -o $@ lex.yy.o json-grammar.tab.o -lfl

json3: lex.yy.o json-grammar.tab.o json3.o 
	$(CXX) -o $@ lex.yy.o json-grammar.tab.o json3.o -lfl

lex.yy.o: lex.yy.cc
	$(CXX) $(CXXFLAGS) -c lex.yy.cc 

lex.yy.c: json-token.cpp.l json-grammar.tab.cc
	$(LEX) json-token.cpp.l

lex.yy.cc: json-grammar.tab.cc
	flex++ json-token.cpp.l

json-grammar.tab.cc: json-grammar.yy
	$(YACC) --defines -o $@ json-grammar.yy

clean:
	$(RM) $(OBJS)
