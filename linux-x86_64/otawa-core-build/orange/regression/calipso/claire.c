
int main() {
	int x = 0, y=10;

	while ((y*1000)>(x*1000)) {
		x++;y--;
	}
	x = 1;
	y = 10;
	while ((y*1000)>(x*1000)) {
		x++;y--;
	}
	return x;
}



