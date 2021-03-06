#ifndef RUNWAY_H
#define RUNWAY_H

#include "utilities.h"
#include "queue.h"
#include "plane.h"

enum Runway_activity {idle, land, take_off};

class Runway {
    public:
        Runway(int limit);
        Error_code can_land(const Plane &current);
        Error_code can_depart(const Plane &current);
        Runway_activity activity(int time, Plane &moving);
        Runway_activity landing_activity(int time, Plane &moving);
        Runway_activity takeoff_activity(int time, Plane &moving);
        void add_enroute_crashes();
        void add_crashes();
        void shut_down(int time) const;
        void shut_down_landings(int time) const;
        void shut_down_takeoffs(int time) const;
        bool landing_queue_empty() const;
        bool takeoff_queue_empty() const;
    private:
        Extended_queue landing;
        Extended_queue takeoff;
        int queue_limit;
        int num_land_requests; // number of planes asking to land
        int num_takeoff_requests; // number of planes asking to take off
        int num_landings; // number of planes that have landed
        int num_takeoffs; // number of planes that have taken off
        int num_land_accepted; // number of planes queued to land
        int num_takeoff_accepted; // number of planes queued to take off
        int num_land_refused; // number of landing planes refused
        int num_takeoff_refused; // number of departing planes refused
        int num_crashes;   // number of crashes
        int num_enroute_crashes; // number of crashes en route to alternative strip
        int land_wait; // total time of planes waiting to land
        int takeoff_wait; // total time of planes waiting to take off
        int idle_time; // total time runway is idle
};

#endif