int main(void) {
  int i;
  int j;
  int sum = 0;
  int k;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < i; j++) {
      sum++;
    }
  }
  printf("%u\n", sum);

  for (k = 0; k < (100-sum); k++) {
    printf("%u\n", k);
  }

}
