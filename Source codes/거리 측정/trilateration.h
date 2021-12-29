#ifndef _trilateration_h
#define _trilateration_h

#include "location.h"
#include "error.h"

// ================================================================================

Location getLocation(Location location1, Location location2, float distance23, float distance31);
//Location getLocation(Location location1, Location location2, Location location3, float distance1, float distance2, float distance3);

// ================================================================================

Location getLocation(Location location1, Location location2, float distance23, float distance31)
{
    /*  Algorithm
        A -> location1
        B -> location2
        C -> result location

        BC -> distance2
        CA -> distance3

        코사인 2법칙 이용

    */
    Location location3;

    float distance12 = distanceF(location1, location2);
    float cos = float(distance12 * distance12 + distance31 * distance31 - distance23 * distance23) / float(2.0 * distance12 * distance31);

    location3.x = cos * distance31;
    location3.y = sqrt(1 - cos * cos) * distance31;

    return location3;
}

Location getLocation(Location location1, Location location2, Location location3, float distance1, float distance2, float distance3)
{
    /*  Algorithm
    

        삼변측량법 사용

    */
    Location locationT;

    float X01 = (-2 * location1.x + 2 * location2.x);
    float X11 = ((location1.x + location2.x) * (location1.x - location2.x) + (location1.y + location2.y) * (location1.y - location2.y) + (distance2 + distance1) * (distance2 - distance1));
    float Y1 = (-2 * location1.y + 2 * location2.y);

    float X02 = (-2 * location1.x + 2 * location3.x);
    float X12 = ((location1.x + location3.x) * (location1.x - location3.x) + (location1.y + location3.y) * (location1.y - location3.y) + (distance3 + distance1) * (distance3 - distance1));
    float Y2 = (-2 * location1.y + 2 * location3.y);

    locationT.x = (Y2 * X01 - Y1 * X02) / (X12 * Y1 - X11 * Y2);
    locationT.y = (locationT.x * X01 + X11) / (Y1);

    return locationT;
}

#endif
