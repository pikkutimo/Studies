# Airport simulator - Project assignment

Exercise pertaining to the use and modification of Queue and Extended_queue classes from 
the book "Data Structures and Program Design in C++" by Robert L. Kruse and Alexander J. Ryba.

The assignment is divided into stages with spesified goals that you must pass to gain points.

## One point

Create the basic simulator from the book without any modification. 

Aim for such traffic density that the airport runs at its peak capacity. Run the simulation and 
create text document of the results.

## Two points

Create version where there are separate runways for both landings and takeoffs. Compare the 
performance with the previous version.

## Three points

First enable landing on the takeoff runway while the takeoff queue is empty and vice versa.

Secondly alter the functioning so that the moving planes have priority over planes that are
taking off. While the landing strips queue is full, the takeoff strips is used only for landings.

## Four points

Add third runway. One runway is used for landings only, the second for takeoffs only and the third
is mainly landings but when the landing queue is empty, takeoffs from the third are possible.

## Five points

Airport has only one runway. Every arriving plane has random amount of fuel left nut always enough
that it could land immediately.

If plane in the landing queue is running out of fuel, it is granted emergency access to the runway.
However this leads to longer wait times for the planes in the landing queue and they could drop 
from the sky when their fuel runs out. This can be handled during landing by checking the fuel
situation, if it has run out, the plane will be registered as crash.

The planes turned away suffer from the same problem. There should be a certain, predefined amount
of fuel in their tanks in order that they can safely reach the alternative airport or -field.