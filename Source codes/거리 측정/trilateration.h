/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265359

double dist1, dist2, dist3;

typedef struct {
    double x, y;
} Location;

void initLocation(Location* p);
void setLocation(Location* p, double x, double y);
void showLocation(Location* p);
double getDistance(Location* p1, Location* p2);
Location rotation2(Location* p, double radian);
void rotation(Location* p, double radian);
double getRadian(Location* p);
Location get3rdStandardLocation(double dist1, double dist2, double dist3);
Location getMyLocation(const Location *p[3], double dist[3]);

int main()
{
    dist1 = 3.0;
    dist2 = 4.0;
    dist3 = 5.0;

    Location p1, p2, p3;
    initLocation(&p1);
    initLocation(&p2);
    initLocation(&p3);
    
    setLocation(&p1, 0, 0);
    setLocation(&p2, dist2, 0);

    double COS = (dist1 * dist1 + dist3 * dist3 - dist2 * dist2) / (2.0 * dist1 * dist3);
    setLocation(&p3, COS * dist3, sqrt(1.0 - COS * COS) * dist3);

    printf("Standard position:\n\t");
    showLocation(&p1);
    showLocation(&p2);
    showLocation(&p3);
    printf("\n");





    Location current;
    double pd1, pd2, pd3;
    pd1 = 6.7082039325;
    pd2 = 3.6055512755;
    pd3 = 7.6157731059;

    initLocation(&current);
    
    dist1 = getDistance(&p1, &p2);
    double COS_THETA = -(pd2 * pd2 - pd1 * pd1 - dist1 * dist1) / (2 * pd1 * dist1);
    double SIN_THETA = sqrt(1 - COS_THETA * COS_THETA);
    Location predL1, predL2;
    setLocation(&predL1, COS_THETA * pd1, SIN_THETA * pd1);
    setLocation(&predL1, COS_THETA * pd1, -SIN_THETA * pd1);

    double dist_1 = abs(getDistance(&predL1, &p3) - pd3);
    printf("Node #4 position:\n\t");
    if (dist_1 > abs(getDistance(&predL2, &p3) - pd3)) {
        showLocation(&predL2);
    } else {
        showLocation(&predL1);
    }










    Location t;
    setLocation(&t, 1, 1);
    printf("\n");
    printf("%.10f", getRadian(&t));



    return 0;
}

Location get3rdStandardLocation(double dist1, double dist2, double dist3) {
    Location p3;
    
    double COS = (dist1 * dist1 + dist3 * dist3 - dist2 * dist2) / (2.0 * dist1 * dist3);
    setLocation(&p3, COS * dist3, sqrt(1.0 - COS * COS) * dist3);

    return p3;
};

Location getMyLocation(const Location *p[3], double dist[3]) {
    
    Location rotatedP[3];
    rotatedP[2].x = &p[2] -> x - &p[0] -> x;
    rotatedP[2].y = &p[2] -> y - &p[0] -> y;
    rotatedP[1].x = &p[1] -> x - &p[0] -> x;
    rotatedP[1].y = &p[1] -> y - &p[0] -> y;
    rotatedP[0].x = 0;
    rotatedP[0].y = 0;
    
    double theta = getRadian(&rotatedP[1]);
    rotation(&rotatedP[1], theta);
    rotation(&rotatedP[2], theta);
    
    
    double distB = getDistance(&rotatedP[0], &rotatedP[1]);       //  Distance between 2 Standard nodes
    double COS_THETA = -(dist[1] * dist[1] - dist[0] * dist[0] - distB * distB) / (2 * dist[0] * distB);
    double SIN_THETA = sqrt(1 - COS_THETA * COS_THETA);
    Location predL1, predL2;            //  Predicted locations
    setLocation(&predL1, COS_THETA * dist[0], SIN_THETA * dist[0]);
    setLocation(&predL1, COS_THETA * dist[0], -SIN_THETA * dist[0]);

    double dist_1 = abs(getDistance(&predL1, &rotatedP[2]) - dist3);
    if (dist_1 > abs(getDistance(&predL2, &rotatedP[2]) - dist3)) {
        return rotation(&predL2, -theta);
    }
    return rotation(&predL1, -theta);
}




void initLocation(Location* p) {
    p -> x = 0;
    p -> y = 0;
};

void setLocation(Location* p, double x, double y) {
    p -> x = x;
    p -> y = y;
};

void showLocation(Location* p) {
    printf("(%.3f, %.3f)\t", p -> x, p -> y);
};

double getDistance(Location* p1, Location* p2) {
    double dx = (p1 -> x) - (p2 -> x);
    double dy = (p1 -> y) - (p2 -> y);
    
    return sqrt((dx * dx) + (dy * dy));
};

Location rotation2(Location* p, double radian) {
    double COS = cos(radian);
    double SIN = sin(radian);
    double x = p -> x;
    double y = p -> y;

    Location result;
    result.x = x * COS - y * SIN;
    result.y = x * SIN + y * COS;
    
    return result;
};

void rotation(Location* p, double radian) {
    double COS = cos(radian);
    double SIN = sin(radian);
    double x = p -> x;
    double y = p -> y;

    p -> x = p -> x * COS - p -> y * SIN;
    p -> y = p -> x * SIN + p -> y * COS;
};

double getRadian(Location* p) {
    double x = p -> x;
    double y = p -> y;
    
    if (x == 0) {
        if (y == 0) {
            return 0;
        } else if (y > 0) {
            return PI;
        }
        return -PI;
    }
    
    double theta = atan(y / x);
    if (x < 0) {
        return theta + 2.0 * PI;
    }
    return theta;
}