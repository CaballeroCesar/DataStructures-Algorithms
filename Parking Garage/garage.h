#ifndef GARAGE_H
#define GARAGE_H

#include <deque>
#include <string>
#include <ostream>

void get_input_vals(const std::string &line, char &xact_type, std::string &license);



class garage
{
public:
        garage(size_t limit = 10) : parking_lot_limit(limit) {}

        /// @param license The license of the car that has arrived.                                                           
        void arrival(const std::string &license);

        /// @param license The license of the car that has departed.                                                          
        void departure(const std::string &license);

private:
        int next_car_id = { 1 };
        std::deque<car> parking_lot;
        size_t parking_lot_limit;
};
#endif