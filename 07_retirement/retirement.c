#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0

typedef struct _retire_info {
  int months;
  double contribution, rate_of_return;
} retire_info;


void retirement (int startAge,   //in months
		 double initial, //initial savings in dollars
		 retire_info working, //info about working
		 retire_info retired) //info about being retired
{
  double balance = initial;
  int month = startAge % 12;
  int age = startAge / 12;

  for(int m = 0; m < working.months; m++) {
    if (month > 11)
      {
	age ++;
	month = 0;
      }
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    balance = balance + balance * working.rate_of_return + working.contribution;
    month++;
  }
  for(int m = 0; m < retired.months; m++) {
    if (month > 11)
      {
	age ++;
	month = 0;
      }
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    balance = balance + balance * retired.rate_of_return + retired.contribution;
    month++;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}

                 
