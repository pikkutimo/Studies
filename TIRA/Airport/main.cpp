#include "random.h"
#include "runway.h"
#include "utilities.h"
#include "queue.h"
#include "plane.h"
#include <iostream>

void initialize(int &, int &, double &, double &);
void run_idle(int);

int main()
/* Pre: The user must supply the number of time intervals the simulation is to run,
        the expected number of planes arriving, the expected number of planes
        departing per time interval, and the maximum allowed size for runway
        queues.
Post:   The program performs a random simulation of the airport, showing the
        status of the runway at each time interval, and prints out a summary of
        airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize. */
{
    int end_time; // time to run simulation
    int queue_limit; // size of Runway queues
    int flight_number = 0;
    // The amount fuel to reach alternative airport
    int emergency_reserve = 3;
    double arrival_rate, departure_rate;
    bool emergency_landing_possible;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    Runway small_airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) {
        // loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);
        std::cout << number_arrivals << std::endl;
        bool emergency_landing_possible = true;
        // current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
    
            Plane current_plane(flight_number++, current_time, arriving);

            // If the current plane can be added onto the landing queue
            if (small_airport.can_land(current_plane) == success)
            {
                if (current_plane.checkFuel() == 1 && emergency_landing_possible)
                {
                    // In emergency, any plane can be allowed to land instantly once per time unit
                    std::cout << "Emergency landing!" << std::endl;
                    current_plane.land(current_time);
                    emergency_landing_possible = false;
                }   
            }
            else
            {
                if (current_plane.checkFuel() < emergency_reserve)
                {
                    small_airport.add_enroute_crashes();
                    current_plane.hailmary();
                }
                else
                    current_plane.refuse();
            }
            
        }
    
        int number_departures = variable.poisson(departure_rate);
        // current departure requests

        for (int j = 0; j < number_departures; j++) {
                
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }
        
        Plane moving_plane;

        // If there hasn't been any emergency landings
        // one plane is stil allowed to land.
        if (emergency_landing_possible)
        {
            switch (small_airport.activity(current_time, moving_plane)) {
                
                case land:
                    if (moving_plane.land(current_time))
                        small_airport.add_crashes();
                    break;
                case take_off:
                    moving_plane.fly(current_time);
                    break;
                case idle:
                    run_idle(current_time);
            }
        }
        
    }
    small_airport.shut_down(end_time);

    return 0;
}

void initialize(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate)
/* Pre: The user specifies the number of time units in the simulation, the maximal
        queue sizes permitted, and the expected arrival and departure rates for
        the airport.
Post:   The program prints instructions and initializes the parameters end_time,
        queue_limit, arrival_rate, and departure_rate to the specified values.
Uses:   utility function user_says_yes */
{
    std::cout << "This program simulates an airport with two runways." << std::endl
        << "One plane can land and depart in each unit of time." << std::endl;
    std::cout << "Up to what number of planes can be waiting to land "
            << "or take off at any time? " << std::flush;
    std::cin >> queue_limit;
    std::cout << "How many units of time will the simulation run?" << std::flush;
    std::cin >> end_time;
    bool acceptable;
    
    do {
        std::cout << "Expected number of arrivals per unit time?" << std::flush;
        std::cin >> arrival_rate;
        std::cout << "Expected number of departures per unit time?" << std::flush;
        std::cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            std::cerr << "These rates must be nonnegative." << std::endl;
        else
            acceptable = true;
        if (acceptable && arrival_rate + departure_rate > 2.0)
            std::cerr << "Safety Warning: This airport will become saturated. " << std::endl;
    } while (!acceptable);
}

void run_idle(int time)
/* Post: The specified time is printed with a message that the runway is idle. */
{
    std::cout << time << ": Runway is idle." << std::endl;
}