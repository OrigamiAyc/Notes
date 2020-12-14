#include <stdio.h>
#include <math.h>

#define DEPOSIT 1000
#define YEAR 5

// These statistics are actually under a percent
const double current_interest = 0.35;
const double annual_interest = 1.5;
const double dual_interest = 2.1;
const double triple_interest = 2.75;
const double five_interest = 3;

double current(double deposit, int times);
double annual(double deposit, int times);
double dual(double deposit, int times);
double triple(double deposit);
double five(double deposit);

int main(int argc, char const *argv[])
{
	double deposit = (double)DEPOSIT;
	double income;
	// 5 years in one go
	printf("5 years\n");
	income = five(deposit);
	printf("total = %lf\n", income);
	// 2 years + 3 years
	printf("2 years + 3 years\n");
	income = dual(deposit, 1);
	income = triple(income);
	printf("total = %lf\n", income);
	// 3 years + 2 years
	printf("3 years + 2 years\n");
	income = triple(deposit);
	income = dual(income, 1);
	printf("total = %lf\n", income);
	// 1 year 5 times
	printf("1 year\n");
	income = annual(deposit, 5);
	printf("total = %lf\n", income);
	// current deposit
	printf("current deposit\n");
	income = current(deposit, 5);
	printf("total = %lf\n", income);
	return 0;
}

double current(double deposit, int times)
{
	double base = 1 + current_interest / 400;
	times *= 4;
	double final = deposit * pow(base, times);
	return final;
}

double annual(double deposit, int times)
{
	double base = 1 + annual_interest / 100;
	double final = deposit * pow(base, times);
	return final;
}

double dual(double deposit, int times)
{
	double base = 1 + dual_interest / 100;
	double final = deposit * pow(base, times);
	return final;
}

double triple(double deposit)
{
	double final = deposit * (1 + triple_interest / 100);
	return final;
}

double five(double deposit)
{
	double final = deposit * (1 + five_interest / 100);
	return final;
}
