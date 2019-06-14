int main(void) {
  int i;
  int b = 10;
  int d;
  int *c = &b;
  c=c+0;
  *c = 3;
  for (i = 0; i < b; i++) {
    printf("la\n");
  }
  
}
