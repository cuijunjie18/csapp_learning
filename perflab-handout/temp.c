/*******************************************************************
 * 
 * driver.c - Driver program for CS:APP Performance Lab
 * 
 * In kernels.c, students generate an arbitrary number of rotate and
 * smooth test functions, which they then register with the driver
 * program using the add_rotate_function() and add_smooth_function()
 * functions.
 * 
 * The driver program runs and measures the registered test functions
 * and reports their performance.
 * 
 * Copyright (c) 2002, R. Bryant and D. O'Hallaron, All rights
 * reserved.  May not be used, modified, or copied without permission.
 *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define RIDX(i,j,n) ((i)*(n)+(j))
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

typedef struct {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

static pixel optim_avg(int dim, int i, int j, pixel *src){
    int ii = i - 1 > 0 ? i - 1 : 0; 
    int jj = j - 1 > 0 ? j - 1 : 0;
    pixel_sum sum;
    pixel current_pixel;

    // initialize_pixel_sum(&sum);
    sum.red = sum.green = sum.blue = 0;
    sum.num = 0;
    int ii_up = min(i + 1,dim - 1);
    for(; ii <= ii_up; ii++){
        int jj_up = min(j + 1,dim - 1);
        for (; jj <= jj_up; jj++){
            pixel p = src[RIDX(ii, jj, dim)];
            sum.red += (int) p.red;
            sum.green += (int) p.green;
            sum.blue += (int) p.blue;
            sum.num++;
        }
    }
    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

void printf_pixel(pixel x){
    printf("%d %d %d\n",x.red,x.green,x.blue);
}

int main()
{
    pixel a = {100,200,300};
    pixel b = {100,200,300};
    pixel a_ans = avg(1, 0, 0, &a);
    pixel b_ans = optim_avg(1, 0, 0, &b);
    printf_pixel(a);
    printf_pixel(b);
    return 0;
}
  