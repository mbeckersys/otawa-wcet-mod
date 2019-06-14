int f (int x) {
	int i, j ;
	int res = 0 ;
	for (i = 0 ; i < x ; ++i)
		for (j = 0 ; j < i ; ++j) {
			/*
			if (res % j == 2)
				res += j ;
			else
				res *= j ;
			*/
		}
	return res ;
}

int main () {
	int k ;
	for (k = 19 ; k >= 0 ; k -= 1) {
	/*for (k = 0 ; k < 20 ; ++k)*/
		f (k) ;
	}
	return 0 ;
}

