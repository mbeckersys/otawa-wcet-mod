#include <stdint.h>
#include <stdio.h>
uint32_t align(uint32_t i) {static int cpt=0;
  if(i != 0) {
    while( 0x0000110 & i)
     {printf ("dans boucle %d\n",i) ; i >>= 1; cpt++;}
  }printf ("%d %d   %d\n", cpt,0x00000100,i);
  return i;
}

void main()
{
	 
	 return align( 511);

}
