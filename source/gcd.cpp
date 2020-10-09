// a > b여야한다. 
int gcd (int a, int b){
	int c; 
	//b==0이라면 a를 출력하고 종료한다. 
	while(b){
		c = a % b; 
		a = b; 
		b = c; 
	}
	return a; 
}