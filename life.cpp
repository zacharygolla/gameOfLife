/****************************************************
Name:
Date:
Problem Number:
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This file provides the implementation of the life.h header file.


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <iomanip>

#include "life.h"

using namespace std;

//GLOBAL VARIABLES

int ROWS = 0;
int COLUMNS = 0;

char **brdptr;
int **neighborptr;

//This function reads input file for subsequent prosessing (add high level 
//description of your implementation logic) 
void populateWorld (const char * FILE_NAME)
{
    ifstream fin;
    fin.open(FILE_NAME);
    
    //measure from the file the number of rows and columns in intital board
    while(!fin.eof())
    {
        char board_count = '0';
        fin.get(board_count);
        if (board_count == '1' || board_count == '0')
        {
            COLUMNS++;
        }
        else if(board_count == '\n')
        {
            ROWS++;
            COLUMNS = 0;
        }
    }

    //set the proper number of rows and columns
    COLUMNS += 1;
    ROWS += 4;
    
    fin.close();

    fin.open(FILE_NAME);
    
    ofstream fout;
    fout.open("temp_file.txt");
    
    //read in data to build initial board
    brdptr = new char *[ROWS];
    for(int i = 0; i < ROWS; i++)
        brdptr[i] = new char [COLUMNS];
    
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
        {
            brdptr[i][j] = '0';
        }
    
    for(int i = 1; i < ROWS - 1; i++)
    {
        for(int k = 1; k < COLUMNS - 1; k++)
        {
            fin >> brdptr[i][k];
        }
    }
    
    fout.close();
    fin.close();
}

//This function outputs the grid for current generation (add high level
//description of your implementation logic) 
void showWorld ()
{
    //print out the current generation of cells
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
        {
            cout << brdptr[i][j];
        }
}

//This function creats new geneneration grid from the old generation grid
//(add high level description of your implementation logic)
void iterateGeneration()
{
    //count the number of cells that are adjacent to current cell and alive
    countNeighbors();
    
    //apply the rules for the game of life and build new board
    rules();
}

//counts the number of neighbors each cell has
void countNeighbors()
{
    //build an integer pointer for a 2D array and put the number of neighbors
    //into each element
    neighborptr = new int *[ROWS];
    for(int i = 0; i < ROWS; i++)
        neighborptr[i] = new int [COLUMNS];
    
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
        {
            neighborptr[i][j] = 0;
        }
    
    for(int i = 1; i < ROWS - 1; ++i)
        for(int k = 1; k < COLUMNS - 1; ++k)
        {
            //count the number of neighbors
            neighborptr[i][k] = count(i, k);
        }
}

//counts how many cells are alive surrounding each cell
int count(int i, int k)
{
    
    int count = 0;
    for(int j = i - 1; j < i + 2; j++)
    {
        for(int n = k - 1; n < k + 2; n++)
        {
            if(brdptr[j][n] == '1')
            {
                count++;
            }
        }
    }
    if(brdptr[i][k] == '1')
        count -= 1;
    
    return count;
}

void rules()
{
    
    ofstream fout;
    fout.open("temp_file.txt");
    
    char ** tempptr;
    
    //create a temp pointer for 2d array so board point can be deleted and then reset
    tempptr = new char *[ROWS];
    for(int i = 0; i < ROWS; i++)
        tempptr[i] = new char [COLUMNS];
    
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
        {
            tempptr[i][j] = '0';
        }

    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
        {
            tempptr[i][j] = brdptr[i][j];
        }
    
    for(int i = 0; i < ROWS; ++i)
        delete [] brdptr[i];
    delete [] brdptr;
    
    brdptr = new char *[ROWS];
    for(int i = 0; i < ROWS; i++)
        brdptr[i] = new char [COLUMNS];
    
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
        {
            brdptr[i][j] = '0';
        }
    
    //fill the new board according to rules
    for(int i = 1; i < ROWS - 1; i++)
        for(int k = 1; k < COLUMNS - 1; k++)
        {
            if(tempptr[i][k] == '1' && (neighborptr[i][k] == 2 || neighborptr[i][k] == 3))
            {
                brdptr[i][k] = '1';
            }
            else if(tempptr[i][k] == '1' && (neighborptr[i][k] <= 1 || (neighborptr[i][k] >= 4)))
            {
                brdptr[i][k] = '0';
            }
            else if(tempptr[i][k] == '0' && neighborptr[i][k] == 3)
            {
                brdptr[i][k] = '1';
                
            }
            else
            {
                brdptr[i][k] = '0';
            }
            fout << brdptr[i][k];

        }

    
    fout.close();
    
}


