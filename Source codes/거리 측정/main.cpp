#include <stdio.h>
#include <math.h>
#include "location.h"
#include "trilateration.h"

int main(void)
{

    Location o;
    o.x = 0;
    o.y = 0;
    
    Location n;
    n.x = 30;
    n.y = 00;
    
    Location m;
    m.x = 30;
    m.y = 40;
    
    
    
	Location target = getLocation(o, n, m, 25, 25, 25.495097567963924150);
	
	printf("(%f, %f)\n", target.x, target.y);

    return 0;
}
