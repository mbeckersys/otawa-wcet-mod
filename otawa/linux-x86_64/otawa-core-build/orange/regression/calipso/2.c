
/* two loop including in one other the first inclused loop depend on a variable assigned in the second one anti-dependency */

int main(void) {
  int i,j = 3,k;

  for (i = 0; i < 7; i++) {
    for (k = 0; k < j; k++);
    for (j = 0; j < 10; j++);
  }
}
