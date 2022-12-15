/* 	Cesar Caballero

	z1944013	

	CS340 - 2

	

	I certify that this is my own work and where appropriate an extension 

	of the starter code provided for the assignment.

*/

#include "matrix.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

using std::cout;
using std::endl;
using std::istream;
using std::string;
using std::setw;

matrix::matrix(unsigned int rows, unsigned int cols)
{
	resize(rows,cols); // allows to reset rows and cols
}

void matrix::resize(unsigned int rows, unsigned int cols)
{
	mat.resize(rows);
	for (unsigned int i = 0; i < rows; i++) //vector gets resized to hold the correct amount of elements 
	{
		mat[i].resize(cols);
	}
}

void matrix::load(istream &is)
{
	unsigned int rows, cols;

	is >> rows;
	is >> cols;

	resize(rows, cols); //resizes the matrices

        for(unsigned int i = 0; i < getRows(); i ++) //allows to insert rows 
        {
                for(unsigned int j = 0; j < getCols(); j++) //allows to insert cols
                {
                        is >> at(i, j); //fills the elements for rows and cols
                }
        }

        return;
}	

void matrix::print(int colWidth) const
{ 
	cout << getRows() << "x" << getCols() << endl; //show what matrices will be multiplied

	if(getCols()==8) // if else loop to set the header depending on cols size
		cout << string(colWidth*11-9,'-') << endl;

	else
		cout << string(colWidth*8-5,'-') << endl;


	for(unsigned int j=0; j<getRows(); j++) // print out matrix elements separated by line
	{ 
		for(unsigned int k=0; k<getCols(); k++)
		{
			cout << "|" << setw(colWidth) <<  at(j,k);
			if(k == getCols()-1)
				cout << "|" << endl; // adds extra | after last element and stars new line
		}
	}
	

	if(getCols()==8) // if else loop to set footer depending on cols size
		cout << string (colWidth*11-9, '-') <<endl;

	else
		cout << string(colWidth*8-5,'-') << endl;
}


matrix matrix::operator*(const matrix &rhs) const
{
	matrix product(getRows(),rhs.getCols()); // object of matrix to hold product 
	unsigned int rows, cols;

	rows = rhs.getRows();
	cols = rhs.getCols();

	assert(rows*cols !=0); // allows program to exit if product equals to 0 
	
	for(unsigned int i=0; i<getRows(); i++) // nested for loop to multiply rows with cols and store values into product object
	{
		for(unsigned int j=0; j<rhs.getCols(); j++)
		{
			for(unsigned int k=0; k<getCols() ;k++)
			{
				product.at(i,j) += at(i,k) * rhs.at(k,j);
			}
		}
	}
	

	return product;	//return the multiplied values :)
}		

	
