#########################################################
# File: makefile
# Taken from TA resources and modified for this project
# Description: A robust makefile for CS162.
#########################################################

# CXX is a standard variable name used for the compiler. 
CXX = g++

# CXXFLAGS is a standard variable name for compile flags.
# -std=c++0x specifies to use the most recent language version.
CXXFLAGS = -std=c++0x

# -Wall turns on all warnings
CXXFLAGS += -Wall

# -pedantic-errors strictly enforces the standard
CXXFLAGS += -pedantic-errors

# -g turns on debug information 
CXXFLAGS += -g

####################
### USER SECTION ###
####################

# SRCS is a standard name for the source files.
SRC1 = main.cpp
SRC2 = generation_copy.cpp
SRCS = ${SRC1} ${SRC2}

# HEADERS is a standard name for the header files.
HEADER1 = generation_copy.hpp
HEADERS = ${HEADER1}

# Executable
PROG = gol

# This is the name of your compressed file. Edit name as needed. Keep the format.
TAR = cs162_project1_olsonbe.tar.bz2

#####################
### BUILD SECTION ###
#####################

# Typing 'make' in terminal calls the first build availible.

default:
	${CXX} ${SRCS} ${HEADERS} -o ${PROG}

# Typing 'make all' in terminal calls this build.

all:
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o ${PROG}

# Typing 'make tar' in terminal calls this build.
# This creates a compressed file for submission.

tar:
	tar cvjf ${TAR} ${SRCS} ${HEADERS} makefile

# Typing 'make clean' calls this build.
# It's designed to clean up the folder.
# Be careful with this, edit as needed.
clean: 
	rm -f ${PROGS} *.o *~

