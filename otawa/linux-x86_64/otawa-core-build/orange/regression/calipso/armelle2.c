 

int main () {
	int k ;
	int i, j ;
	int res = 0 ;
	for (k = 19 ; k >= 0 ; k -= 1) {
	/*for (k = 0 ; k < 20 ; ++k)*/
		 
		for (i = 0 ; i < k ; ++i)
		for (j = 0 ; j < i ; ++j) {
			/*
			if (res % j == 2)
				res += j ;
			else
				res *= j ;
			*/
		}
	}
	return 0 ;
}

