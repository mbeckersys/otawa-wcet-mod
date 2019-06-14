int main(void) {
  int i,j , k;
  int sum;
  sum = 0;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < i; j++) {
      sum++;
    }
  }
  for (k = sum; k > 0; k--);
  for (k = 0; k < sum; k++);

}
