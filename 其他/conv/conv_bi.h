#ifdef __SDSCC__
#include <cstdlib>
#include "sds_lib.h"
#define malloc(x) (sds_alloc(x))
#define free(x) (sds_free(x))
#endif

#ifndef SRC_CONV_H_
#define SRC_CONV_H_

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
//#include"hls_math.h"
#include "ap_fixed.h"

#include "sds_lib.h"
// #include "test_ap_fixed.h"
#include "hls_half.h"
#include <cassert>


using namespace std;

//128*128*3*3
#define C    2     //num of channels
#define H    28    //input image height
#define W    28    //input image width
#define FS   3    //filter height
#define K    2    //num of filters
#define PAD		1
#define NC	10

#define RN 64
typedef ap_uint<RN> bi_type;

typedef bi_type in_3d[C][W];

typedef bi_type out_3d[K][W];

typedef bi_type f_4d[C][FS][FS];

void conv_bi(bi_type input[H][C][W], 
	bi_type filter[K*RN][C][FS][FS], bi_type output[H][K][W],
	float add[K*RN],float mul[K*RN]);
void gemm_bi(bi_type input[H*K*W],bi_type w[H*W*K][10],
	float output[NC],float mul[NC],float add[NC]);
void conv_bf_cpu(float input[H][W],int w[K*RN][FS][FS],
	bi_type output[H][K][W],float mul[K*RN],float add[K*RN]);
void conv_bf(float input[H][W], 
	int filter[K*RN][FS][FS], bi_type output[H][K][W],
	float mul[K*RN],float add[K*RN]);
extern float  mul_buf[K*RN], add_buf[K*RN];
void load_mul_buf(float mul[K*RN],float mul_buf[K*RN], int len);
void load_add_buf(float add[K*RN],float add_buf[K*RN],int len);
template<int NN>
ap_int<16> pop_count(ap_uint<NN> &a);
template<int NN>
ap_int<16> mul_bi(ap_uint<NN> &a, ap_uint<NN> &b);
ap_uint<1> compute(float in, float mul, float add);
#endif /* SRC_CONV_H_ */
