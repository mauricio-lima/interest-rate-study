

#include <stdio.h>
#include <time.h>
#include <math.h>


typedef int (runner_t)(float, float, float, float, int*);


int loop(float salaryCarlos, float salaryJoao, float rateCarlos, float rateJoao, int* iterations)
{
  float balanceCarlos;
  float balanceJoao;
  int   months;

  months = 0;
  balanceCarlos = salaryCarlos;
  balanceJoao   = salaryJoao;
  while (1)
  {
    balanceCarlos *= rateCarlos;
    balanceJoao   *= rateJoao;

    if (balanceCarlos < balanceJoao)
      break;

    months++;
  }
  *iterations = months;

  return (months + 1);
}


int algebric(float salaryCarlos, float salaryJoao, float rateCarlos, float rateJoao, int* iterations)
{
  *iterations = 0;
  return round(log(salaryCarlos/salaryJoao)/log(rateJoao/rateCarlos));
}


float inline equation(float, float, float, float, float)  __attribute__((always_inline));

float inline equation(float x, float salaryCarlos, float salaryJoao, float rateCarlos, float rateJoao)
{
  return (salaryCarlos/salaryJoao) * pow(rateCarlos/rateJoao, x);
}


int dicotomy(float salaryCarlos, float salaryJoao, float rateCarlos, float rateJoao, int* iterations)
{
  float left;
  float right;
  float middle;

  *iterations = 0;
  left = 1;
  while (1)
  {
    if ( (equation(left, salaryCarlos, salaryJoao, rateCarlos, rateJoao) > 1) && (equation(left * 2, salaryCarlos, salaryJoao, rateCarlos, rateJoao) < 1) )
      break;

    left *= 2;
    (*iterations)++;
  }
  right = left * 2;

  while (1)
  {
    middle = (left + right) / 2;
    if ( (int)(equation(middle, salaryCarlos, salaryJoao, rateCarlos, rateJoao) * 1000) == 1000 )
    {
      return round(middle + 1);
    }

    if ( (equation(right, salaryCarlos, salaryJoao, rateCarlos, rateJoao) < 1) && (equation(middle, salaryCarlos, salaryJoao, rateCarlos, rateJoao) < 1) )
    {
      right = middle; 
    }
    else
    {
      left = middle;
    }

    (*iterations)++;
  }
}


void runner(runner_t* function, char* name, int count, float salaryCarlos, float salaryJoao, float rateCarlos, float rateJoao)
{
  clock_t start;
  clock_t finish;
  int     result;
  int     iterations;
  double  time_taken;
  
  start = clock();
  for(int i = 0; i < count; i++)
  {
    result = (*function)(salaryCarlos, salaryJoao, rateCarlos, rateJoao, &iterations);
  }
  finish = clock();
  time_taken = (double)(finish - start) / CLOCKS_PER_SEC * 1000 * 1000 * 1000 / count;

  printf("\nSaldo atingido em %d meses usando '%s'\n", result, name);
  printf("O cálculo foi feito com %d iterações em %2.1lf nanosegundos medidos em %d execuções\n\n", iterations, time_taken, count);
}


int main(void) 
{
  float rateCarlos = 1.02;
  float rateJoao   = 1.05;
  float salaryCarlos;


  printf("Qual o salário de Carlos? ");
  scanf("%f", &salaryCarlos);

  int profile_count = 5000;
  runner(loop,     "loop",     profile_count, salaryCarlos, salaryCarlos / 3, rateCarlos, rateJoao);
  runner(algebric, "algebric", profile_count, salaryCarlos, salaryCarlos / 3, rateCarlos, rateJoao);
  runner(dicotomy, "dicotomy", profile_count, salaryCarlos, salaryCarlos / 3, rateCarlos, rateJoao);

  return 0;
}
