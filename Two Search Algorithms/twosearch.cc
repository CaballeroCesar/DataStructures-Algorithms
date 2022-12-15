/* 	Cesar Caballero

	z1944013	

	CS340 - 2

	

	I certify that this is my own work and where appropriate an extension 

	of the starter code provided for the assignment.

*/

#include "twosearch.h"

#include <getopt.h>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>


/**
* see: 
* https://en.wikipedia.org/wiki/Usage_message
* https://www.ibm.com/docs/en/aix/7.2?topic=commands-usage-statements
*
* @param a0 The value of argv[0] (the name of the command) so that it 
*   can be printed.
*
* @note This function will terminate the application via exit(1).
******************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-l rand_low] [-h rand_high] [-a a_size] [-b b_size] [-x a_seed] [-y b_seed] [-c print_cols] [-w col_width]" << std::endl;
    std::cerr << "    rand_low   = rand() low bound (default=1)" << std::endl;
    std::cerr << "    rand_high  = rand() high bound (default=1000)" << std::endl;
    std::cerr << "    a_size     = size of vector A (default=200)" << std::endl;
    std::cerr << "    b_size     = size of vector B (default=100)" << std::endl;
    std::cerr << "    a_seed     = random seed for vector A (default=1)" << std::endl;
    std::cerr << "    b_seed     = random seed for vector B (default=3)" << std::endl;
    std::cerr << "    print_cols = number of colums per line (default=16)" << std::endl;
    std::cerr << "    col_width  = printed column value width (default=4)" << std::endl;
    exit(1);
} // End of usage()

/**
* Parse the command-line args, create and sort vector A, create vector B,
* search vector A for those elements appearing in vector B using both
* a linear and binary search, and print the hit-rate (the percentage of 
* items in B that have been located in A.)
*
* If an invalid command-line arg is encountered, print a Usage statement 
* and terminte with an exit-status of 1.
*
* @return zero
******************************************************************************/
int main(int argc, char **argv)
{
    // Demonstrate the use of getopt() to override default config parameter
    int rand_low = 1;
    int rand_high = 1000;
    int a_size = 200;
    int b_size = 100;
    int a_seed = 1;
    int b_seed = 3;
    int print_cols = 16;
    int col_width = 4;

    std::vector <int> a(a_size); //initializing a and b vectors
    std::vector <int> b(b_size);

    int opt;
    // see: http://faculty.cs.niu.edu/~winans/CS340/2022-sp/#getopt
    while ((opt = getopt(argc, argv, "a:b:c:h:l:w:x:y:")) != -1)
    {
        switch(opt)
        {
        case 'a':
            // see https://en.cppreference.com/w/cpp/string/basic_string/stol
            a_size = std::stoi(optarg); // override the default for a_size
            break;

        case 'b':
            b_size = std::stoi(optarg);
            break;
        case 'c':
            print_cols = std::stoi(optarg);
            break;
        case 'h':
            rand_high = std::stoi(optarg);
            break;
        case 'l':
            rand_low = std::stoi(optarg);
            break;
        case 'w':
            col_width = std::stoi(optarg);
            break;
        case 'x':
            a_seed = std::stoi(optarg);
            break;
        case 'y':
            b_seed = std::stoi(optarg);
            break;
            
        default:
            // got an arg that is not recognized...
            usage(argv[0]);     // pass the name of the program so it can print it
        }
    }

    // Make sure there are not any more arguments (after the optional ones)
    if (optind < argc)
        usage(argv[0]);

    // Add application logic here.

	init_vector(a, a_seed, rand_low, rand_high); // initialize vector a
	init_vector(b, b_seed, rand_low, rand_high); // initialize vector b

	std::cout << "A vector: " << std::endl;
	print_vector(a, print_cols, col_width); //print contents of vector A before being sorted

	std::cout << "A vector sorted: " << std::endl; 
	sort_vector(a); // sorts vector A
	print_vector(a, print_cols, col_width);// prints vector A sorted

	std::cout << "B vector: " << std::endl;
	print_vector(b, print_cols, col_width); // prints contents of vector B

	search_vector(a, b, linear_search); // performs a linear search for all of values of vector B in vector A
	int found = search_vector(a, b, linear_search); // search_vector function with linear search inside a variable for later use
	std::cout << "Linear Search: ";
	print_stat(found, b.size()); // print the statistics of success using linear search

	search_vector(a, b, binary_search); // performs a binary search for all of values of vector B in vector A
	found = search_vector(a, b, binary_search); // search_vector function with binary search inside a variable for later use
	std::cout << "Binary Search: ";
	print_stat(found, b.size()); //print statistics of success using binary search

    return 0;

} // End of main()

void init_vector(std::vector<int> &vec, int seed, int lo, int hi)
{
        srand(seed); // initializing random number generator
        
        for(unsigned int i=0; i<vec.size(); i++) // for loop that stores random numbers into vector
	{
		vec[i] = rand()%(hi-lo+1)+lo; // store random numbers into vector
	}
}

void print_vector(const std::vector<int> &v, int print_cols, int col_width)
{
	int rows; // counter to add "|" after if needed

	// for loop prints header depending on column size
	for(int i=0; i<print_cols; i++)
	{
		std::cout << std::string(col_width+2,'-');
	}

	std::cout<< "-" << std::endl;

	for(size_t i=0; i<v.size(); i++)
	{
		std::cout << "| " << std::setw(col_width) <<v[i]; // puting | before every number along with a space
		rows++; // keeping track of counter to know if | is needed

		if((i+1) % print_cols == 0)
		{
			std::cout << "|" << std::endl; // if loop allows for new line to keep printing elements
			rows=0;
		}
	}

	while((rows>0) & (rows != print_cols)) // prints space after very last element
	{
		std::cout<< "|" << std::setw(col_width+1) << " ";
		rows++;
	}

	if (rows == print_cols)
	{
		std::cout << "|" ;
	}
	std::cout << std::endl;


	//for loop prints header depending on column size
	for(int i=0; i<print_cols; i++)
	{
		std::cout << std::string(col_width+2,'-');
	}
	std::cout<< "-" << std::endl;
}

void sort_vector(std::vector<int> &v)
{
	sort(v.begin(),v.end()); // using sort() to rearrange elements from vector into ascending order
}

int search_vector(const std::vector<int> &v1, const std::vector<int> &v2, bool (*p)(const std::vector<int> &, int))
{
	//for loop searches each element from v2 in v1 to find a match, for each matching number the counter increments
	int total=0;

	for(size_t i=0; i<v2.size();i++)
	{
		if(p(v1,v2[i]))
		{
			total++;
		}
	}	
	return total;
}

void print_stat(int found, int total)
{
	std::cout << "Percent of Succesful Searches = " << std::fixed << std::setprecision(2) << ((float)found / (float)total * 100.00) << "%" << std::endl; // formula to get percentage then typecasted from int to float with 2 decimal places
}

bool linear_search(const std::vector<int> &v, int x)
{
	if(std::find(v.begin(),v.end(),x) != v.end()) // use find() to search from beginning til the end of vec until x is found
		return true;
	else
		return false;
}

bool binary_search(const std::vector<int> &v, int x)
{
	if(std::binary_search(v.begin(),v.end(),x)) // binary_search() searches from beginning til end of vec until x is found
		return true;
	else
		return false;
}




