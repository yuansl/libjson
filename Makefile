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
LDLIBS = -lfl

TMP_OBJS = lex.yy.cc json-grammar.tab.hh json-grammar.tab.cc
OBJS = json-grammar.tab.o lex.yy.o json-array.o json-object.o json-value.o json.o  
TMP_OBJS += $(OBJS)
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

json3: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDLIBS)

lex.yy.o: lex.yy.cc
	$(CXX) $(CXXFLAGS) -c lex.yy.cc 

lex.yy.c: json-token.cpp.l json-grammar.tab.c
	$(LEX) json-token.l

lex.yy.cc: json-grammar.tab.cc json-token.cpp.l
	$(LEXCPP) json-token.cpp.l

json-grammar.tab.o: json-grammar.tab.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

json-grammar.tab.cc: json-object.h json-grammar.yy 
	$(YACC) $(YACCFLAGS) --defines -o $@ json-grammar.yy

clean:
	$(RM) $(TMP_OBJS)
