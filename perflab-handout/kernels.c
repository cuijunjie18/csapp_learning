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
    for (int i = 0; i < dim; i += 32){
        for (int j = 0; j < dim; j += 32){
            for (int k = i; k < i+32; k++){
                dst[RIDX(dim-1-j, k, dim)] = src[RIDX(k, j+0, dim)];
                dst[RIDX(dim-2-j, k, dim)] = src[RIDX(k, j+1, dim)];
                dst[RIDX(dim-3-j, k, dim)] = src[RIDX(k, j+2, dim)];
                dst[RIDX(dim-4-j, k, dim)] = src[RIDX(k, j+3, dim)];
                dst[RIDX(dim-5-j, k, dim)] = src[RIDX(k, j+4, dim)];
                dst[RIDX(dim-6-j, k, dim)] = src[RIDX(k, j+5, dim)];
                dst[RIDX(dim-7-j, k, dim)] = src[RIDX(k, j+6, dim)];
                dst[RIDX(dim-8-j, k, dim)] = src[RIDX(k, j+7, dim)];
                dst[RIDX(dim-9-j, k, dim)] = src[RIDX(k, j+8, dim)];
                dst[RIDX(dim-10-j, k, dim)] = src[RIDX(k, j+9, dim)];
                dst[RIDX(dim-11-j, k, dim)] = src[RIDX(k, j+10, dim)];
                dst[RIDX(dim-12-j, k, dim)] = src[RIDX(k, j+11, dim)];
                dst[RIDX(dim-13-j, k, dim)] = src[RIDX(k, j+12, dim)];
                dst[RIDX(dim-14-j, k, dim)] = src[RIDX(k, j+13, dim)];
                dst[RIDX(dim-15-j, k, dim)] = src[RIDX(k, j+14, dim)];
                dst[RIDX(dim-16-j, k, dim)] = src[RIDX(k, j+15, dim)];
                dst[RIDX(dim-17-j, k, dim)] = src[RIDX(k, j+16, dim)];
                dst[RIDX(dim-18-j, k, dim)] = src[RIDX(k, j+17, dim)];
                dst[RIDX(dim-19-j, k, dim)] = src[RIDX(k, j+18, dim)];
                dst[RIDX(dim-20-j, k, dim)] = src[RIDX(k, j+19, dim)];
                dst[RIDX(dim-21-j, k, dim)] = src[RIDX(k, j+20, dim)];
                dst[RIDX(dim-22-j, k, dim)] = src[RIDX(k, j+21, dim)];
                dst[RIDX(dim-23-j, k, dim)] = src[RIDX(k, j+22, dim)];
                dst[RIDX(dim-24-j, k, dim)] = src[RIDX(k, j+23, dim)];
                dst[RIDX(dim-25-j, k, dim)] = src[RIDX(k, j+24, dim)];
                dst[RIDX(dim-26-j, k, dim)] = src[RIDX(k, j+25, dim)];
                dst[RIDX(dim-27-j, k, dim)] = src[RIDX(k, j+26, dim)];
                dst[RIDX(dim-28-j, k, dim)] = src[RIDX(k, j+27, dim)];
                dst[RIDX(dim-29-j, k, dim)] = src[RIDX(k, j+28, dim)];
                dst[RIDX(dim-30-j, k, dim)] = src[RIDX(k, j+29, dim)];
                dst[RIDX(dim-31-j, k, dim)] = src[RIDX(k, j+30, dim)];
                dst[RIDX(dim-32-j, k, dim)] = src[RIDX(k, j+31, dim)];
            }
        }
    }
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

static void set_corner(int cc, pixel *src, pixel *dst, int a1, int a2, int a3){
    dst[cc].blue = (src[cc].blue+src[a1].blue+src[a2].blue+src[a3].blue) >> 2;
    dst[cc].green = (src[cc].green+src[a1].green+src[a2].green+src[a3].green) >> 2;
    dst[cc].red = (src[cc].red+src[a1].red+src[a2].red+src[a3].red) >> 2;
}
static void set_top(int dim, pixel *src, pixel *dst, int j){
    dst[j].blue = (src[j].blue+src[j+dim].blue+src[j-1].blue+src[j+1].blue+src[j+dim-1].blue+src[j+dim+1].blue)/6;
    dst[j].green = (src[j].green+src[j+dim].green+src[j-1].green+src[j+1].green+src[j+dim-1].green+src[j+dim+1].green)/6;
    dst[j].red = (src[j].red+src[j+dim].red+src[j-1].red+src[j+1].red+src[j+dim-1].red+src[j+dim+1].red)/6;
}
static void set_bottom(int dim, pixel *src, pixel *dst, int j){
    dst[j].blue = (src[j].blue+src[j-dim].blue+src[j-1].blue+src[j+1].blue+src[j-dim-1].blue+src[j-dim+1].blue)/6;
    dst[j].green = (src[j].green+src[j-dim].green+src[j-1].green+src[j+1].green+src[j-dim-1].green+src[j-dim+1].green)/6;
    dst[j].red = (src[j].red+src[j-dim].red+src[j-1].red+src[j+1].red+src[j-dim-1].red+src[j-dim+1].red)/6;
}
static void set_left(int dim, pixel *src, pixel *dst, int i){
    dst[i].blue = (src[i].blue+src[i-dim].blue+src[i-dim+1].blue+src[i+1].blue+src[i+dim].blue+src[i+dim+1].blue)/6;
    dst[i].green = (src[i].green+src[i-dim].green+src[i-dim+1].green+src[i+1].green+src[i+dim].green+src[i+dim+1].green)/6;
    dst[i].red = (src[i].red+src[i-dim].red+src[i-dim+1].red+src[i+1].red+src[i+dim].red+src[i+dim+1].red)/6;
}
static void set_right(int dim, pixel *src, pixel *dst, int i){
    dst[i].blue = (src[i].blue+src[i-dim].blue+src[i-dim-1].blue+src[i-1].blue+src[i+dim].blue+src[i+dim-1].blue)/6;
    dst[i].green = (src[i].green+src[i-dim].green+src[i-dim-1].green+src[i-1].green+src[i+dim].green+src[i+dim-1].green)/6;
    dst[i].red = (src[i].red+src[i-dim].red+src[i-dim-1].red+src[i-1].red+src[i+dim].red+src[i+dim-1].red)/6;
}
static void set_in(int dim, pixel *src, pixel *dst, int k){
    dst[k].blue = (src[k].blue+src[k-1].blue+src[k+1].blue+src[k+dim-1].blue+src[k+dim].blue+src[k+dim+1].blue+src[k-dim-1].blue+src[k-dim].blue+src[k-dim+1].blue)/9;
    dst[k].green = (src[k].green+src[k-1].green+src[k+1].green+src[k+dim-1].green+src[k+dim].green+src[k+dim+1].green+src[k-dim-1].green+src[k-dim].green+src[k-dim+1].green)/9;
    dst[k].red = (src[k].red+src[k-1].red+src[k+1].red+src[k+dim-1].red+src[k+dim].red+src[k+dim+1].red+src[k-dim-1].red+src[k-dim].red+src[k-dim+1].red)/9;
}
void smooth(int dim, pixel *src, pixel *dst) 
{
    // 处理四个角
    set_corner(0, src, dst, 1, dim, dim+1);
    set_corner(dim-1, src, dst, dim-2, dim+dim-2, dim+dim-1);
    set_corner(RIDX(dim-1, 0, dim), src, dst, RIDX(dim-1, 1, dim), RIDX(dim-2, 0, dim), RIDX(dim-2, 1, dim));
    set_corner(RIDX(dim-1, dim-1, dim), src, dst, RIDX(dim-1, dim-2, dim), RIDX(dim-2, dim-2, dim), RIDX(dim-2, dim-1, dim));
    // 处理四个边
    for(int j = 1; j <= dim-2; j++){
        set_top(dim, src, dst, j);
        set_bottom(dim, src, dst, dim*dim-dim+j);
        set_left(dim, src, dst, j*dim);
        set_right(dim, src, dst, j*dim+dim-1);
    }
    // 中间部分
    for(int i = 1; i <= dim-2; i++){
        for(int j = 1; j <= dim-2; j++){
            set_in(dim, src, dst, i*dim+j);
        }
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

