/*

  3대의 로봇이 있을 때 초기 좌표를 설정하는 과정을 담은 프로그램입니다. 


*/


#include <stdio.h>
#include <math.h>

typedef struct {
	double x, y;
	char *name;
} ROBOT;

int main(void) {

	double distances[3] = {0,};
	/*
	  distances[0] = P1와 P2 사이의 거리
	  distances[1] = P2와 P3 사이의 거리
	  distances[2] = P3와 P1 사이의 거리 
	  
	*/
	
	
	ROBOT robots[3];
	
	robots[0].x = 0;
	robots[0].y = 0;
	robots[0].name = "P1";
	robots[1].x = 0;
	robots[1].y = 0;
	robots[1].name = "P2";
	robots[2].x = 0;
	robots[2].y = 0;
	robots[2].name = "P3";
	
	
	
	printf("첫 번째 로봇과 두 번째 로봇 사이의 거리를 알려주세요.: ");
	scanf("%lf", distances);
	robots[1].x = distances[0];
	
	printf("두 번째 로봇과 세 번째 로봇 사이의 거리를 알려주세요.: ");
	scanf("%lf", distances + 1);
	
	printf("세 번째 로봇과 첫 번째 로봇 사이의 거리를 알려주세요.: ");
	scanf("%lf", distances + 2);
	
	double temp = (distances[0] * distances[0] + distances[2]*distances[2] - distances[1] * distances[1]);
	temp = (temp) / (2 * distances[0] * distances[2]);
	double theta = acos(temp);
	
	robots[2].x = distances[2] * cos(theta);
	robots[2].y = distances[2] * sin(theta);
	
	
	printf("%lf, %lf", robots[2].x, robots[2].y);

	return 0;	
}



