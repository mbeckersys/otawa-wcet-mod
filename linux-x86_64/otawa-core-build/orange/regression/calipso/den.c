typedef struct {
	int a;
	int b;
} s_t;

s_t stab[5] ;
/*
void main()
{
	int i;
	s_t *s = &stab[0];

	s[0].a = 0;
	s->b = 1;
	
	for (i = s->a; i <= s->b; i++)
		;
}
*/
  
void main()
{
	int i;
	s_t *s = &stab[0];

	s[0].a = 0;
	s[0].b = 1;
	
	for (i = s[0].a; i <=s[0].b; i++)
		;
}
