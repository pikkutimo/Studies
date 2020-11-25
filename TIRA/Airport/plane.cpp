#include "plane.h"

Plane::Plane(int flt, int time, Plane_status status)
/* Post: The Plane data members flt_num, clock_start, and state are set to the
values of the parameters flt, time and status, respectively. */
{
    Random variable;

    flt_num = flt;
    clock_start = time;
    state = status;
    fuel = variable.random_integer(2, 15);
    std::cout << "Plane number " << flt << " with fuel: " << fuel << " ready to ";

    if (status == arriving)
        std::cout << "land." << std::endl;
    else
        std::cout << "take off." << std::endl;
}

Plane::Plane( )
/* Post: The Plane data members flt_num, clock_start, state are set to illegal default values. */
{
    flt_num = 0;
    clock_start = 0;
    state = null;
    fuel = 10;
}

void Plane::refuse( ) const
/* Post: Processes a Plane wanting to use Runway, when the Queue is full. */
{
    std::cout << "Plane number " << flt_num;
    if (state == arriving)
        std::cout << " directed to another airport" << std::endl;
    else
        std::cout << " told to try to takeoff again later" << std::endl;
}

void Plane::hailmary( ) const
/* Post: Processes a Plane wanting to use Runway, when the Queue is full. */
{
    std::cout << "Plane number " << flt_num;
    std::cout << " directed to another airport and suffered catastrophic failure." << std::endl;
}

bool Plane::land(int time)
/* Post: Processes a Plane that is landing at the specified time. */
{
    int wait = time-clock_start;
    if (wait > fuel)
    {
        std::cout << time << ": Plane number " << flt_num << " crashed after "
        << fuel << " time unit" << ((fuel == 1) ? "" : "s")
        << " in the landing queue." << std::endl;

        return true;
    }
    else
    {
        std::cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the landing queue." << std::endl;
    }
    
    return false;
}

void Plane::fly(int time) const
/* Post: Process a Plane that is taking off at the specified time. */
{
    int wait = time-clock_start;
    std::cout << time << ": Plane number " << flt_num << " took off after "
            << wait << " time unit" << ((wait == 1) ? "" : "s")
            << " in the takeoff queue." << std::endl;
}

int Plane::started( ) const
/* Post: Return the time that the Plane entered the airport system. */
{
    return clock_start;
}

int Plane::checkFuel( )
/* Post: Return the amount of fuel in tanks. */
{
    return fuel;
}

void Plane::setFuel()
/* Post: Randomize the amount of fuel left in tanks. */
{
    Random variable;
    fuel = variable.random_integer(2, 15);
}