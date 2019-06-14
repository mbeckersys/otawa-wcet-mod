main()
{
	int L7 ;
	int i, j;
 
	for(i = 0, j = 10; i <= j; i += 2, j--) ;

    for(i = 1, j = 10; i <= j; i *= 2, j--) ;

	for(i = 1, j = 10; i <= j; i *= 2, j /= 2) ;

	for(i = 1, j = 10; i <= j;) 
	{
		 if (L7) i *= 2; else j /= 2;
	}
	for(i = 0, j = 10; i <= j;) 
	{
		 if (L7) i *= 2; else j /= 2;
	}

}

