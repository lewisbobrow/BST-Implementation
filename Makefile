#
# Makefile for Binary Search Tree
#
# Homework 4 (spring 2019)
#
# Author: Lewis Bobrow
# 
# Due Date: 02/27/19
#
# Not using -Wextra

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3

hw4: main.o BinarySearchTree.o pretty_print.o
	${CXX} ${LDFLAGS} -o hw4 main.o BinarySearchTree.o pretty_print.o

main.o:              main.cpp BinarySearchTree.h 
BinarySearchTree.o:  BinarySearchTree.cpp BinarySearchTree.h
pretty_print.o:      pretty_print.cpp BinarySearchTree.h

clean:
	rm -rf hw4 *.o *.dSYM

provide:
	provide comp15 hw4 main.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        pretty_print.cpp README Makefile

