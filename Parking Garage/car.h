#ifndef CAR_H
#define CAR_H
#include <iostream> //ostream
#include <string>


class car
{
public:
    car(int id, const std::string &license) : id(id), license(license) {}

    /// Call this to increment the number of times the car has been moved.
    void move();

    /// @return the number of times that the car has been moved.
    int get_num_moves() const;
	
    /// @return A reference to the license for this car.
    const std::string &get_license() const;

    /**
    * Overload the << so this can print itself as:
    *    Car X with license plate "Y"
    ******************************************************************/
    friend std::ostream& operator<<(std::ostream& lhs, const car& rhs);

private:
    int id;                 ///< The ID number for this car (assigned by the garage)
    std::string license;    ///< license plate of this car.
    int num_moves = {0};    ///< how many times the car was moved within the garage.
};
#endif