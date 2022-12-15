/* 	Cesar Caballero
	z1944013	
	CS340 - 2
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/
#include "car.h"
#include "garage.h"
#include <iostream>

int main()
{
	std::string input; //variable with input line
	char arrival_departure; //variable with A or D stored
	std::string license; // License stored from input
	garage g;

	while(std::getline (std::cin, input)) //while loop to read and store all of input in variable
	{
		get_input_vals(input,arrival_departure,license); //calling function
	
		if(arrival_departure == 'A') //apply arrival method to car with A
		{
			g.arrival(license);
		}

		else if(arrival_departure == 'D') //apply departure method to car with D
		{
			g.departure(license);
		}

		else
		 std::cout << "'" << arrival_departure << "': invalid action!" << std::endl << std::endl; //print out incase of invalid input
	}
	
	std::cout << std::endl; // to match refout
    return 0;
}