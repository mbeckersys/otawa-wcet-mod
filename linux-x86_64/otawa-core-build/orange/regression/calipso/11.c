void pakonpozan(int x) {
  int i = 0;

  for (i = 0; i < x; i++) {
  }

  for (i = 0; i < Y; i++) {
  }
  Y = 1;
}
int Y;


int main(void) {
  int k;
  int v;
  int i;
  int x;
  for (v = 0; v < 5; v++) {
    k = 0;
    for (k = 0; k < 10; k++) {
      Y = k*2;
      pakonpozan(k+5);
    }
  }
}
