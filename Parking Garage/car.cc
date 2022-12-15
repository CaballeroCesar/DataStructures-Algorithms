#include "car.h"

/// Call this to increment the number of times the car has been moved.
void car::move()
{
    num_moves++;
}

/// @return the number of times that the car has been moved.
int car::get_num_moves() const
{
    return num_moves;
}

/// @return A reference to the license for this car.
const std::string &car::get_license() const
{
    return license;
}

std::ostream& operator<<(std::ostream& lhs, const car& rhs) //overloading "<<" to be able to print for the car class
{
	lhs << "Car " << rhs.id << " with license plate \"" << rhs.license << "\"";
	return lhs;
}

