/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "heaven",              /* Team name */
    "cjj",     /* First member full name */
    "2871843852@qq.com",  /* First member email address */

    "666",                   /* Second member full name (leave blank if none) */
    "666@qq.com"                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/*rotate : 顺时针旋转*/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    // printf("Begin %d naive_rotate!\n",dim);
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];

    // printf("Finish naive_rorate!\n");
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: 8 x 1 loop expand";
void rotate(int dim, pixel *src, pixel *dst) 
{
    // printf("Begin %d rotate!\n",dim);
    int i,j;

    /*8 x 1*/
    for (i = 0; i < dim; i++){
        for (j = 0; j + 7 < dim; j += 8){
            dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
            dst[RIDX(dim-1-j-1, i, dim)] = src[RIDX(i, j + 1, dim)];
            dst[RIDX(dim-1-j-2, i, dim)] = src[RIDX(i, j + 2, dim)];
            dst[RIDX(dim-1-j-3, i, dim)] = src[RIDX(i, j + 3, dim)];
            dst[RIDX(dim-1-j-4, i, dim)] = src[RIDX(i, j + 4, dim)];
            dst[RIDX(dim-1-j-5, i, dim)] = src[RIDX(i, j + 5, dim)];
            dst[RIDX(dim-1-j-6, i, dim)] = src[RIDX(i, j + 6, dim)];
            dst[RIDX(dim-1-j-7, i, dim)] = src[RIDX(i, j + 7, dim)];
        }
        for (; j < dim; j++) dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
    }

    // printf("Finish rotate!\n");
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
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

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    // printf("Begin %d naive_smooth!\n",dim);
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);

}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: 8 x 1 loop expand";

static pixel optim_avg(int dim, int i, int j, pixel *src){
    int ii_down = i - 1 > 0 ? i - 1 : 0; 
    int jj_down = j - 1 > 0 ? j - 1 : 0;
    int ii,jj;
    pixel_sum sum;
    pixel current_pixel;

    // initialize_pixel_sum(&sum);
    sum.red = sum.green = sum.blue = 0;
    sum.num = 0;
    int ii_up = min(i + 1,dim - 1);
    int jj_up = min(j + 1,dim - 1);
    for(ii = ii_down; ii <= ii_up; ii++){
        for (jj = jj_down; jj <= jj_up; jj++){
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

void smooth(int dim, pixel *src, pixel *dst) 
{
    // printf("Begin %d smooth!\n",dim);
    int i,j;
    for (i = 0; i < dim; i++){
        for (j = 0; j + 7 < dim; j += 8){
            // dst[RIDX(i, j, dim)] = optim_avg(dim, i, j, src);
            dst[RIDX(i, j, dim)] = optim_avg(dim, i, j, src);
            dst[RIDX(i, j + 1, dim)] = optim_avg(dim, i, j + 1, src);
            dst[RIDX(i, j + 2, dim)] = optim_avg(dim, i, j + 2, src);
            dst[RIDX(i, j + 3, dim)] = optim_avg(dim, i, j + 3, src);
            dst[RIDX(i, j + 4, dim)] = optim_avg(dim, i, j + 4, src);
            dst[RIDX(i, j + 5, dim)] = optim_avg(dim, i, j + 5, src);
            dst[RIDX(i, j + 6, dim)] = optim_avg(dim, i, j + 6, src);
            dst[RIDX(i, j + 7, dim)] = optim_avg(dim, i, j + 7, src);
        }
        for (; j < dim; j++) dst[RIDX(i, j, dim)] = optim_avg(dim, i, j, src);
    }
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

