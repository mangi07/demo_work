#############################
#makefile for CS 162 Project 4
#Author: Benjamin R. Olson
#Date: May 24, 2014
#############################

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

SRC1 = combat_modified.cpp
SRC2 = 
SRCS = ${SRC1} ${SRC2}

#include reflection here
FILE1 = cs162project4reflection_olsonbe.pdf
FILE2 = 
FILES = ${FILE1} ${FILE2}

TAR = cs162project4_olsonbe.tar.bz2

default:
	${CXX} ${CXXFLAGS} ${SRCS} -o combat2
		
compress:
	tar cvjf ${TAR} ${SRCS} ${FILES} makefile ${FILE1}
	
decompress:
	tar xvjf ${TAR}
