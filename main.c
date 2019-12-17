

#include <stdio.h>


void loop(float salaryCarlos, float rateCarlos, float rateJoao)
{
  float balanceCarlos;
  float balanceJoao;
  int   months;

  months = 0;
  balanceCarlos = salaryCarlos;
  balanceJoao   = salaryCarlos / 3;
  while (1)
  {
    balanceCarlos *= rateCarlos;
    balanceJoao   *= rateJoao;

    if (balanceCarlos < balanceJoao)
      break;

    months++;
  }

  printf("\nSaldo atingido em %d meses\n\n", months+1);
}


int main(void) 
{
  float rateCarlos = 1.02;
  float rateJoao   = 1.05;
  float salaryCarlos;

  printf("Qual o salário de Carlos? ");
  scanf("%f", &salaryCarlos);

  loop(salaryCarlos, rateCarlos, rateJoao);

  return 0;
}
