              int main(void) {
  int i,j = 3,k;

  for (i = 0; i < 7; i++) {
    for (k = j; k < 10; k++);
    for (j = 0; j < 10; j++);
  }
}
