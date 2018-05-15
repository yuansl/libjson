CC=gcc
CFLAGS=-g -Wall
CXX=g++
CXXFLAGS=-std=c++14 $(CFLAGS)
YACC=yacc
YACCFLAGS =-d
LEX=flex
CPP=cpp
CPPFLAGS =-I$(HOME)/lib
LDFLAGS = -L$(HOME)/lib
LDLIBS = -lutil -lfl

OBJS = json.o

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

clean:
	$(RM) $(OBJS)
