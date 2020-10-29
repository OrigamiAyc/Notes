#include <stdio.h>
#include <math.h>

#define PI 3.14

int main(int argc, char const *argv[])
{
	double r = 1.5, h = 3;
	printf("Please input radius and height, seperating with blankspace\n");
	scanf("%lf%lf", &r, &h);
	double circumference = 2 * PI * r;
	printf("The circumference of the circle is %.2lf\n",circumference);
	double area = PI * r * r;
	printf("The area of the circle is %.2lf\n", area);
	double ball_superficial_area = 4 * PI * r * r;
	printf("The superficial area of the ball is %.2lf\n", ball_superficial_area);
	double ball_volume = (4 / 3) * PI * r * r * r;
	printf("The volume of the ball is %.2lf\n", ball_volume);
	double cylinder_volume = h * PI * r * r;
	printf("The volume of the cylinder is %.2lf\n", cylinder_volume);
	return 0;
}
