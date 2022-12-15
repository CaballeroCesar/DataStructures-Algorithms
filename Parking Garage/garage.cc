#include "car.h"
#include "garage.h"
#include <stack>

/**
 * @brief Get the input vals object
 * 
 * @param line  input to be parsed
 * @param xact_type action: A = arriving, D = Departing
 * @param license license plate
 */
void get_input_vals(const std::string &line, char &xact_type, std::string &license)
{
	xact_type = line[0]; //store the first letter of input (A or D) from input in variable
	license = line.substr(line.find(':')+1, line.find_last_of(':')-2); //storing rest of input into license string 
}

/**
 * @brief add car to garage 
 * 
 * @param license license plate of car 
 */
void garage::arrival(const std::string &license)
{
	car newCar(next_car_id,license); //car object 
	next_car_id++; //increasing id for next car each time

    std::cout << newCar << " has arrived." << std::endl;
    if(parking_lot_limit == parking_lot.size()) //if parking lot is full print statement
    {
        std::cout << "    But the garage is full!" << std::endl << std::endl;
    }
    else
    {
        std::cout << std::endl;
        parking_lot.push_back(newCar); //if parking lot is not full add the car to deque
    }
}

/**
 * @brief remove cars from garage
 * 
 * @param license license plate of car
 */
void garage::departure(const std::string &license)
{
   	bool found = false; //bool to know if license is inside of the parking lot
	std::stack<car> x; // stack to store cars inside temporarily
	int location;
	//std::string foundLicense;

	for(size_t i =0; i<parking_lot.size(); i++) //iterate and check parking_lot
	{
		if(parking_lot[i].get_license() == license) //check to see if license is stored in parking lot
		{
			found = true;
			location = i; // keep track of where in the loop car is found 
			//foundLicense = parking_lot[i].get_license();
			break;
		}
	}

	
	if(found == false) //if car is not in parking lot print message acknowledging it
	{
		std::cout << "No car with license plate \"" << license << "\" is in the garage." << std::endl;
	}

	else //if license if found in parking lot perform action to depart it
	{
		
		for (int i= parking_lot.size()-1; i>-1; i--) //go into parking lot backwards to remove cars and temporarily store in x stack
		{
			
			if(i>location) //if there is cars located infront of the one that wants to depart 
			{
				x.push(parking_lot[i]); //storing cars temporarily
				parking_lot.pop_back();
			}

			else if(i==location) //if there are no cars located infront of one that wants to depart
			{
				parking_lot[i].move(); //increment move
				std::string t= " time"; //store "time" in case car has only moved 1 time 
				if(parking_lot[i].get_num_moves()>1) //if statement to print out "times" in case car has moved more than 1 times
				{
					t= " times";
				}
                std::cout << parking_lot[i] << " has departed," << std::endl; //print out message like in reference
				std::cout << "    car was moved " << parking_lot[i].get_num_moves() << t << " in the garage. " << std::endl << std::endl;
				parking_lot.pop_back(); //remove the car from the parking lot so it can depart 
			}
			
			else //if there is carss before car that wants to depart
			{
				parking_lot[i].move();
			}
		}

		while(!x.empty()) //add cars from top of temporary stack into deque
		{
			car newCar = x.top();
			parking_lot.push_back(newCar);
			x.pop(); //remove car from stack after it is in back in deque
		}
	}

}
