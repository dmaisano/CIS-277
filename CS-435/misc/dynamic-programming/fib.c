#include <stdio.h>
#include <stdlib.h>

// exponential time complexity
unsigned long fib (unsigned long n) {
  if (n <= 1) return n;

  return fib(n - 1) + fib(n - 2);
}

// linear time complexity
unsigned long dynamicFib(unsigned long n) {
  unsigned long *fib = malloc(sizeof(unsigned long) * n);

  fib[0] = 0;
  fib[1] = 1;

  for (unsigned long i = 2; i <= n; i++) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }

  return fib[n];
}


int main() {
  unsigned long n = 0;

  printf("enter n-th desired Fibonacci number: ");
  scanf("%lu", &n);

  // unsigned long fib1 = fib(n);
  unsigned long fib2 = dynamicFib(n);

  printf("Fibonacci number: %lu\n", fib2);

  return 0;
}
