int main(void) {
  int i;
  int j;
  int sum = 0;
  int borne;
  int k;

  borne = 0;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < i; j++) {
      borne++;
    }
  }
  /* borne = 45  mais surestimmee a 90 */

  /* boucle non executee */
  for (i = 0; i < (borne-44); i++) {
    for (j = 0; j < i; j++) {
      sum++;
    }
  }
  for (k = 0; k < (1000-sum); k++);
}
