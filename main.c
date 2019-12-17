

#include <stdio.h>
#include <time.h>


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


void runner(char* name, int count, float salaryCarlos, float salaryJoao, float rateCarlos, float rateJoao)
{
  clock_t start;
  clock_t finish;
  int     result;
  int     iterations;


  start = clock();
  for(int i = 0; i < count; i++)
  {
    result = loop(salaryCarlos, salaryJoao, rateCarlos, rateJoao, &iterations);
  }
  finish = clock();

  printf("\nSaldo atingido em %d meses usando '%s'\n", result, name);
  printf("O cálculo foi feito com %d iterações em %2.1lf microsegundos medidos em %d execuções\n\n", iterations, (double)(finish - start) / CLOCKS_PER_SEC * 1000 * 1000 * 1000 / count, count);
}


int main(void) 
{
  float rateCarlos = 1.02;
  float rateJoao   = 1.05;
  float salaryCarlos;


  printf("Qual o salário de Carlos? ");
  scanf("%f", &salaryCarlos);

  runner("loop", 300, salaryCarlos, salaryCarlos / 3, rateCarlos, rateJoao);

  return 0;
}
