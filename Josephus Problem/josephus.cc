/* 	Cesar Caballero
	z1944013	
	CS340 - 2
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include "josephus.h"

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <getopt.h>


void print_underlined_string(const std::string &message);
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols);


/**
* Print a 'Usage' message and exit(1).
*
* @param a0 The name of the command to include in the usage message.
*****************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-n number of people] [-m modulus] [-p print frequency] [-c print columns]" << std::endl;
    exit(1);
}


/**
* Create a std::list of prople with generated ID/names and reduce the
* list as per the Josephus problem algorithm.
*****************************************************************************/
int main(int argc, char **argv)
{
    unsigned num_people = 41;       // The number of people to start with
    unsigned modulus = 3;           // The count used to determine the elimination
    unsigned print_frequency = 13;  // How often to print the state of the system
    unsigned num_cols = 12;         // Number of colums to print per line

    int opt;
    while ((opt = getopt(argc, argv, "n:m:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            std::istringstream(optarg) >> num_people;
            break;
        case 'm':
            std::istringstream(optarg) >> modulus;
            break;
        case 'p':
            std::istringstream(optarg) >> print_frequency;
            break;
        case 'c':
            std::istringstream(optarg) >> num_cols;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind < argc)
        usage(argv[0]); // If we get here, there was extra junk on command line
    
    
    std::list<std::string> names; //list that stores names of people in game
    std::generate_n (std::back_inserter(names),num_people,SEQ(num_people)); //inserting names by using generate function 
    
    int eliminations = 0; //counter to know how many people have been eliminated throughout program
    print_list(names,eliminations,num_cols); //print first function showing intitialized list
    
    auto it = names.begin(); //iterator that starts at beginning of list

    //loop to eliminate people from the group
    while(names.size()>1)
    {
        if(it == names.end())
        {
            it = names.begin();// making it a circular linked list by setting it to begin when it gets to end of list
        } 

        //for loop to eliminate the third person in list
        for(unsigned int i=1; i<modulus; i++)
        {
            ++it;
            if(it == names.end())
            {
                it = names.begin();
            }
        }

        it = names.erase(it);
        eliminations++; // keep track of how many elements have been deleted through each loop
        //so the program doesn't delete elemements by one. Prints in a loop until there is one remainding person
        if(eliminations % print_frequency == 0 )
        {
        print_list(names,eliminations,num_cols);
        }
    }

    //print out the remaining person along with proper header
    std::cout << "Eliminations Completed" << std::endl;
    print_list(names,eliminations,num_cols);

  return 0;
}

void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols)
{
    if(eliminations == 0) //prints this string if 0 people have been eliminated 
    {
        print_underlined_string("Initial group of people");
        std::cout << std::endl;
    }
    else //print a header to show how many people have been eliinated so far
    {
        print_underlined_string("After eliminating " + std::to_string(eliminations) + " people");
        std::cout << std::endl;    
    }
    
    int perLine = 0; //counter to keep track of how many elements have been printed out per line
    for(auto itr = collection.begin(); itr != collection.end(); ++itr)
    {
        std::cout << *itr; // iterator to print out all of contents inside the list
       ++perLine;

        //if elements equaling num_cols are printed it starts new line to print the rest along with not printing a comma for last element with std::prev
       if(perLine % num_cols == 0 || itr== std::prev(collection.end())) 
            std::cout << std::endl; 
       else
       std::cout << ", ";
    }
    std::cout << std::endl;

}

void print_underlined_string(const std::string &message)
{
    //prints out the message from print_list() function and formats a header to be the length of string
    std::cout << message << std::endl;
	
    std::cout << std::string(message.size(),'-');
}
