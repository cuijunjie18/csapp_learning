int func_a(int a,int b){
	int x = a > b ? a : b;
	return x;
}

int func_b(int a,int b){
	int x;
	if (a > b) x = a;
	else x = b;
	return x;
}

int main()
{
	int ans1 = func_a(2,1);
	int ans2 = func_b(2,1);
	printf("%d\n",ans1);
	printf("%d\n",ans2);
	return 0;
}
