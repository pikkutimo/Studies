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
    double arrival_rate, departure_rate;
    bool takeoffsBanned = false;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;
    // Two separate runways for both landing and takeoff
    Runway landingStrip(queue_limit);
    Runway takeoffStrip(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) {
        // loop over time intervals

        
        int number_arrivals = variable.poisson(arrival_rate);
        // current arrival requests
        for (int i = 0; i < number_arrivals; i++) {
    
            Plane landing_plane(flight_number++, current_time, arriving);
            if (landingStrip.can_land(landing_plane) != success)
            {   
                takeoffsBanned = true;
                //If the landing queue is full, check if the other runways takeoff queue is empty
                //-> if it is landing can be done through that runway
                if (takeoffStrip.takeoff_queue_empty())
                {
                    takeoffStrip.can_land(landing_plane);
                }
                else
                    landing_plane.refuse();
            }
            else
                takeoffsBanned = false;
        }
    
        int number_departures = variable.poisson(departure_rate);
        // current departure requests

        if (takeoffsBanned == false)
        {
            for (int j = 0; j < number_departures; j++) {
                
            Plane takeoff_plane(flight_number++, current_time, departing);
            if (takeoffStrip.can_depart(takeoff_plane) != success)
            {
                //If the takeoff queue is full, check if the other runways landing queue is empty
                //-> if it is takeoff can be done through that runway
                if (landingStrip.landing_queue_empty())
                {
                    landingStrip.can_depart(takeoff_plane);
                }
                else
                    takeoff_plane.refuse();
            }    
                
        }
        }§
        
        Plane first_moving_plane;
        Plane second_moving_plane;

        // For moving planes if the landing queue is full, the runway for takeoffs 
        // stops all takeoffs and is used for landings only until the receiving
        // queue can handle all moving planes
        switch (landingStrip.landing_activity(current_time, first_moving_plane)) {
        
            case land:
                first_moving_plane.land(current_time);
                break;
            case idle: //If idle can handle the other queue
                run_idle(current_time);
        }

        switch (takeoffStrip.takeoff_activity(current_time, second_moving_plane)) {

            case take_off:
                second_moving_plane.fly(current_time);
                break;
            case idle: //If idle can handle the other queue
                run_idle(current_time);
        }
    }

    std::cout << std::endl;
    takeoffStrip.shut_down_takeoffs(end_time);
    landingStrip.shut_down_landings(end_time);

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