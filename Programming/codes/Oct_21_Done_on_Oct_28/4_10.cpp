#include <stdio.h>
#include <math.h>

const int LEVEL_1 = 100000;
const int LEVEL_2 = 200000;
const int LEVEL_3 = 400000;
const int LEVEL_4 = 600000;
const int LEVEL_5 = 1000000;

const float RATE_1 = 0.1;
const float RATE_2 = 0.075;
const float RATE_3 = 0.05;
const float RATE_4 = 0.03;
const float RATE_5 = 0.015;
const float RATE_6 = 0.01;

int main(int argc, char const *argv[])
{
	int I = 0;
	float bonus;
	printf("Please input your benefit\n");
	scanf("%d", &I);
	if (I <= LEVEL_1)
	{
		bonus = I * RATE_1;
		printf("bonus = %f\n", bonus);
	}
	else if ((I > LEVEL_1) && (I <= LEVEL_2))
	{
		bonus += LEVEL_1 * RATE_1;
		bonus += (I - LEVEL_1) * RATE_2;
		printf("bonus = %f\n", bonus);
	}
	else if ((I > LEVEL_2) && (I <= LEVEL_3))
	{
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += (I - LEVEL_2) * RATE_3;
		printf("bonus = %f\n", bonus);
	}
	else if ((I > LEVEL_3) && (I <= LEVEL_4))
	{
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += LEVEL_3 * RATE_3;
		bonus += (I - LEVEL_3) * RATE_4;
		printf("bonus = %f\n", bonus);
	}
	else if ((I > LEVEL_4) && (I <= LEVEL_5))
	{
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += LEVEL_3 * RATE_3;
		bonus += LEVEL_4 * RATE_4;
		bonus += (I - LEVEL_4) * RATE_5;
		printf("bonus = %f\n", bonus);
	}
	else
	{
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += LEVEL_3 * RATE_3;
		bonus += LEVEL_4 * RATE_4;
		bonus += LEVEL_5 * RATE_5;
		bonus += (I - LEVEL_5) * RATE_6;
		printf("bonus = %f\n", bonus);
	}
	int level = 0;
	if (I <= LEVEL_1)
	{
		level = 0;
	}
	else if ((I > LEVEL_1) && (I <= LEVEL_2))
	{
		level = 1;
	}
	else if ((I > LEVEL_2) && (I <= LEVEL_3))
	{
		level = 2;
	}
	else if ((I > LEVEL_3) && (I <= LEVEL_4))
	{
		level = 3;
	}
	else if ((I > LEVEL_4) && (I <= LEVEL_5))
	{
		level = 4;
	}
	else
	{
		level = 5;
	}
	switch (level)
	{
	case 0:
		bonus = I * RATE_1;
		printf("bonus = %f\n", bonus);
		break;
	case 1:
		bonus += LEVEL_1 * RATE_1;
		bonus += (I - LEVEL_1) * RATE_2;
		printf("bonus = %f\n", bonus);
		break;
	case 2:
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += (I - LEVEL_2) * RATE_3;
		printf("bonus = %f\n", bonus);
		break;
	case 3:
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += LEVEL_3 * RATE_3;
		bonus += (I - LEVEL_3) * RATE_4;
		printf("bonus = %f\n", bonus);
		break;
	case 4:
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += LEVEL_3 * RATE_3;
		bonus += LEVEL_4 * RATE_4;
		bonus += (I - LEVEL_4) * RATE_5;
		printf("bonus = %f\n", bonus);
		break;
	case 5:
		bonus += LEVEL_1 * RATE_1;
		bonus += LEVEL_2 * RATE_2;
		bonus += LEVEL_3 * RATE_3;
		bonus += LEVEL_4 * RATE_4;
		bonus += LEVEL_5 * RATE_5;
		bonus += (I - LEVEL_5) * RATE_6;
		printf("bonus = %f\n", bonus);
		break;
	default:
		break;
	}

	return 0;
}
