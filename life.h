/****************************************************
Name:
Date:
Problem Number:
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This header file provides the prototypes of the function definitions
//for the project.

#ifndef life_h
#define life_h

#include <iostream>
#include <fstream>

using namespace std;

void populateWorld(const char *);
void showWorld();
void iterateGeneration();
void countNeighbors();
int count(int , int );
void rules ();



#endif
