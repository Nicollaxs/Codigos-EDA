#include <stdio.h>

long int armazena[1000];
long int fibonacci(int n) {
  if (n == 1 || n == 2)
    return 1;
  if (armazena[n] != 0)
    return armazena[n];
   armazena[n] = fibonacci(n - 1) + fibonacci(n - 2);
  return armazena [n];
}
