void phase_6(char* rdi){
	char *r13 = rsp - 0x50
	char *rsi = rsp
	read_six_numbers(rsi);
	// rsp[0] ~ rsp[5] = number1 ~ number5
	int numbers[6] = rsp;
	int x = numbers[0] - 1;
	int y = 0;
	if (x > 5) explode_bomb();
	y++;
	if (y == 6){

	}else{
		int z = y;
		do{
		if (numbers[z] == numbers[0]) explode_bomb();
		z++;
		}while(z <= 5);
	}
	int *r13 = &numbers[1];
}
