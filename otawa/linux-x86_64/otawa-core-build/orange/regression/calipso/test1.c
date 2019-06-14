#include "stdio.h"

int main (void) 
{
  volatile int p, q, r, s, t;
  int i, j, k;
  int init;
  int l,m,n;
printf("avec borne a 10\n");
          l=0;n=0;
          for (i = 0; i < 10; i++)
            {
              printf("i = %d, l=%d \n",i,l);
              m=0;
              for (k = i; k < 10; k++)
                {
                  printf("k=%d, m=%d, n=%d \n",k,m,n);
                  if (s && t)
                    {
                      for (j = 0; j < 4; j++);
                        
                    }
                  else
                    {
                      
                    }
                  n++;
                  m++;
                }
                l++;
            }


printf("avec borne a 20\n");

          l=0;n=0;
          for (i = 0; i < 20; i++)
            {
              printf("i = %d, l=%d \n",i,l);
              m=0;
              for (k = i; k < 10; k++)
                {
                  printf("k=%d, m=%d, n=%d \n",k,m,n);
                  if (s && t)
                    {
                      for (j = 0; j < 4; j++);
                      
                    }
                  else
                    {
                      
                    }
                  n++;
                  m++;
                }
                l++;
            }



  return 0;
}
