/*CPE = 9*/
void psum1(){
    for (int i = 0; i < n; i++){
        p[i] = p[i - 1] + a[i];
    }
}

/*revise CPE =  3,only add restrict*/ 
void psum2(){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum = sum + a[i];
        p[i] = sum;
    }
}