/*

  3���� �κ��� ���� �� �ʱ� ��ǥ�� �����ϴ� ������ ���� ���α׷��Դϴ�. 


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
	  distances[0] = P1�� P2 ������ �Ÿ�
	  distances[1] = P2�� P3 ������ �Ÿ�
	  distances[2] = P3�� P1 ������ �Ÿ� 
	  
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
	
	
	
	printf("ù ��° �κ��� �� ��° �κ� ������ �Ÿ��� �˷��ּ���.: ");
	scanf("%lf", distances);
	robots[1].x = distances[0];
	
	printf("�� ��° �κ��� �� ��° �κ� ������ �Ÿ��� �˷��ּ���.: ");
	scanf("%lf", distances + 1);
	
	printf("�� ��° �κ��� ù ��° �κ� ������ �Ÿ��� �˷��ּ���.: ");
	scanf("%lf", distances + 2);
	
	double temp = (distances[0] * distances[0] + distances[2]*distances[2] - distances[1] * distances[1]);
	temp = (temp) / (2 * distances[0] * distances[2]);
	double theta = acos(temp);
	
	robots[2].x = distances[2] * cos(theta);
	robots[2].y = distances[2] * sin(theta);
	
	
	printf("%lf, %lf", robots[2].x, robots[2].y);

	return 0;	
}



