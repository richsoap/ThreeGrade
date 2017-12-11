#include "conv_bi.h"
// global variable
float mul_buf[K*RN], add_buf[K*RN];
void load_mul_buf(float mul[K*RN],float mul_buf[K*RN], int len){
	#pragma HLS INLINE
	#ifdef __SDSCC__
	assert(len<=K*RN);
	#endif
	for(int i=0;i<len;++i){
		#pragma HLS PIPELINE
		mul_buf[i] = mul[i];
	}
}
void load_add_buf(float add[K*RN],float add_buf[K*RN],int len){
	#pragma HLS INLINE
	#ifdef __SDSCC__
	assert(len<=K*RN);
	#endif
	for(int i=0;i<len;++i){
		#pragma HLS PIPELINE
		add_buf[i] = add[i];
	}
}


template<int NN>
ap_int<16> pop_count(ap_uint<NN> &a){
	#pragma HLS INLINE
	ap_int<16> tmp = 0;
	for(int i=0;i<NN;++i){
		tmp += (ap_uint<1>)a[i];
	}
	return tmp;
}
template<int NN>
ap_int<16> mul_bi(ap_uint<NN> &a, ap_uint<NN> &b){
	#pragma HLS INLINE
	ap_uint<NN> tmp = a^b;
	// popcount
	ap_int<16> result = pop_count(tmp);
	// *2-1
	result = NN - 2*result;
	return result;
}

void load_input_bi(bi_type input[C][W], bi_type buf_line[C][W]){
	#pragma HLS INLINE off
	for(int i=0;i<C;++i)
		for(int j=0;j<W;++j){
			#pragma HLS PIPELINE
			buf_line[i][j] = input[i][j];
		}
}


void kernel_bi(bi_type buf_line[C][W], bi_type f_buf[K*RN][C][FS], 
	ap_int<16> out_buf[K*RN][W],bool init){
	#pragma HLS INLINE off
	ap_int<16> sum;
	#define PARA 16
	for(int i=0;i<W;++i)
		for(int j=0;j<FS;++j){
			for(int k=0;k<K*RN/PARA;++k){
				#pragma HLS PIPELINE II=1
				for(int l=0;l<PARA;++l){
					int ker_num = k*PARA + l;
					if(init&&j==0){
						sum = 0;
					} else {
						sum = out_buf[ker_num][i];
					}
					for(int m=0;m<C;++m){
						if(i+j-PAD >=0&&i+j-PAD<W){
							sum += mul_bi(buf_line[m][i+j-PAD],f_buf[ker_num][m][j]);
						}
					}
					out_buf[ker_num][i] = sum;
				}
			}
		}
}



void convolver_bi(int row, bi_type buf_line_1[C][W], bi_type buf_line_2[C][W], 
	bi_type buf_line_3[C][W], bi_type f_buf[FS][K*RN][C][FS], 
	ap_int<16> out_buf[K*RN][W]){
 	#pragma HLS INLINE
 	if(row!=0){
    	kernel_bi(buf_line_1, f_buf[0], out_buf,true);
 	}
	kernel_bi(buf_line_2, f_buf[1], out_buf,row==0);
	if(row!=H-1){
		kernel_bi(buf_line_3, f_buf[2], out_buf,false);
	}
}

ap_uint<1> compute(float in, float mul, float add){
	float tmp = in*mul+add;
	return tmp > 0? 1:0;
}

void store_output_bi(ap_int<16> out_buf[K*RN][W], bi_type output[K][W],
	float mul_buf[K*RN], float add_buf[K*RN]){
	#pragma HLS INLINE off
	bi_type tmp;
    for(int i=0;i<K;++i)
    	for(int j=0;j<W;++j){
    		#pragma HLS PIPELINE
    		for(int k=0;k<RN;++k){
    			tmp[k] = compute((float)out_buf[i*RN+k][j],mul_buf[i*RN+k],add_buf[i*RN+k]);
    		}
    		output[i][j] = tmp;
    	}
}

void load_filter_bi(bi_type filter[K*RN][C][FS][FS], bi_type f_buf[FS][K*RN][C][FS]){
	#pragma HLS INLINE
	for(int i=0;i<K*RN;++i)
		for(int j=0;j<C;++j)
			for(int k=0;k<FS;++k)
				for(int l=0;l<FS;++l){
					#pragma HLS PIPELINE
					f_buf[k][i][j][l] = filter[i][j][k][l];
				}
}
#pragma SDS data access_pattern(input:SEQUENTIAL, filter:SEQUENTIAL, output:SEQUENTIAL,mul:SEQUENTIAL,add:SEQUENTIAL)
void conv_bi(bi_type input[H][C][W], 
	bi_type filter[K*RN][C][FS][FS], bi_type output[H][K][W],
	float mul[K*RN],float add[K*RN]){
// #pragma HLS DATA_PACK variable=input
// #pragma HLS DATA_PACK variable=filter
// #pragma HLS DATA_PACK variable=output


	bi_type in_buf_1[C][W], in_buf_2[C][W], in_buf_3[C][W], in_buf_4[C][W];
 	bi_type f_buf[FS][K*RN][C][FS];
	ap_int<16> out_buf_1[K*RN][W], out_buf_2[K*RN][W];
	float add_buf[K*RN], mul_buf[K*RN];
	#pragma HLS ARRAY_PARTITION variable=in_buf_1 complete dim=1
	#pragma HLS ARRAY_PARTITION variable=in_buf_2 complete dim=1
	#pragma HLS ARRAY_PARTITION variable=in_buf_3 complete dim=1
	#pragma HLS ARRAY_PARTITION variable=in_buf_4 complete dim=1

	#pragma HLS ARRAY_PARTITION variable=f_buf cyclic factor=16 dim=2
	#pragma HLS ARRAY_PARTITION variable=f_buf complete dim=3

	#pragma HLS ARRAY_PARTITION variable=out_buf_1 cyclic factor=16 dim=1
	#pragma HLS ARRAY_PARTITION variable=out_buf_2 cyclic factor=16 dim=1
	load_mul_buf(mul,mul_buf,K*RN);
	load_add_buf(add,add_buf,K*RN);
	load_filter_bi(filter,f_buf);
	calculate_lp:
	for(int row = -2; row <= H; ++row) {
	#pragma AP dependence variable=input intra false
	#pragma AP dependence variable=output intra false
	#pragma AP dependence variable=in_buf_1 intra false
	#pragma AP dependence variable=out_buf_1 intra false
	switch ((row+4) % 4) {
		case 1:
//				#pragma SDS async(1)
			if(row+FS-1 <H){
				load_input_bi(input[row + FS-1], in_buf_1);
			}
//				#pragma SDS async(2)
			if(row >=0 &&row<H){
				convolver_bi(row,in_buf_2, in_buf_3, in_buf_4, f_buf, out_buf_2);
			}
//				#pragma SDS async(3)
			if(row-1>=0){
				store_output_bi(out_buf_1, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		case 2:
			if(row+FS-1 <H){
				load_input_bi(input[row + FS-1], in_buf_2);
			}
			if(row >=0 &&row<H){
				convolver_bi(row,in_buf_3, in_buf_4, in_buf_1, f_buf, out_buf_1);
			}			
			if(row-1>=0){
				store_output_bi(out_buf_2, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		case 3:
//				#pragma SDS async(1)
			if(row+FS-1 <H){
				load_input_bi(input[row + FS-1], in_buf_3);
			}
//				#pragma SDS async(2)
			if(row >=0 &&row<H){
		    	convolver_bi(row,in_buf_4, in_buf_1, in_buf_2, f_buf, out_buf_2);
		    }
//				#pragma SDS async(3)
			if(row-1>=0){
				store_output_bi(out_buf_1, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		default:
//				#pragma SDS async(1)
			if(row+FS-1 <H){
				load_input_bi(input[row + FS-1], in_buf_4);
			}
//				#pragma SDS async(2)
			if(row >=0 &&row<H){
				convolver_bi(row,in_buf_1, in_buf_2, in_buf_3, f_buf, out_buf_1);
			}
//				#pragma SDS async(3)
			if(row-1>=0){
				store_output_bi(out_buf_2, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		}
	}
}







// --------------------------------------------------
void conv_bf_cpu(float input[H][W],int w[K*RN][FS][FS],
	bi_type output[H][K][W],float mul[K*RN],float add[K*RN]){
	for(int j=0;j<K*RN;++j)
		for(int i=0;i<H;++i){
			for(int k=0;k<W;++k){
				float sum = 0;
				for(int l=0;l<FS;++l){
					for(int m=0;m<FS;++m){
						if(i+l-PAD<0||i+l-PAD>=H||k+m-PAD<0||k+m-PAD>=W)
							continue;
						if(w[j][l][m]==1){
							sum += input[i+l-PAD][k+m-PAD];
						} else if(w[j][l][m]==-1){
							sum -= input[i+l-PAD][k+m-PAD];
						} else {
							cout << "error:not binary" << endl;
							exit(1);
						}
					}
				}
				output[i][j/RN][k][j%RN] = compute((float)sum,mul[j],add[j]);
			}
		}
}

void gemm_bi(bi_type a[H*K*W],bi_type w[H*W*K][NC],float output[NC],
	float mul[NC],float add[NC]){
	load_mul_buf(mul,mul_buf,NC);
	load_add_buf(add,add_buf,NC);
	for(int i=0;i<NC;++i){
		int sum = 0;
		for(int j=0;j<H*W*K;++j){
			sum += (int)mul_bi(a[j],w[j][i]);
		}
		output[i] = sum*mul_buf[i]+add_buf[i];
	}
}
/*
#include "conv_bi.h"
#ifndef conv_bf_file
#define conv_bi_file

void load_input_bf(float input[W], float buf_line[W]){
		#pragma HLS INLINE off
		for(int j=0;j<W;++j){
			#pragma HLS PIPELINE
			buf_line[j] = input[j];
		}
}

void kernel_bf(float buf_line[W], int f_buf[K*RN][FS], 
	float out_buf[K*RN][W],bool init){
	#pragma HLS INLINE off
	float sum;
	#define PARA 4
	for(int i=0;i<W;++i)
		for(int j=0;j<FS;++j){
			for(int k=0;k<K*RN/PARA;++k){
				#pragma HLS PIPELINE
				for(int l=0;l<PARA;++l){
					int ker_num = k*PARA + l;
					if(init&&j==0){
						sum = 0;
					} else {
						sum = out_buf[ker_num][i];
					}
					if(i+j-PAD >=0&&i+j-PAD<W){
						// cout << mul_bi(buf_line[m][i+j-PAD],f_buf[ker_num][m][j]) << endl;
						// sum += mul_bi(buf_line[i+j-PAD],f_buf[ker_num][j]);
						if(f_buf[ker_num][j]==1)
							sum += buf_line[i+j-PAD];
						else
							sum -= buf_line[i+j-PAD];
					}
					out_buf[ker_num][i] = sum;
				}
			}
		}
}



void convolver_bf(int row, float buf_line_1[W], float buf_line_2[W], 
	float buf_line_3[W], int f_buf[FS][K*RN][FS], 
	float out_buf[K*RN][W]){
 	#pragma HLS INLINE
 	if(row!=0){
    	kernel_bf(buf_line_1, f_buf[0], out_buf,true);
 	}
	kernel_bf(buf_line_2, f_buf[1], out_buf,row==0);
	if(row!=H-1){
		kernel_bf(buf_line_3, f_buf[2], out_buf,false);
	}
}

void store_output_bf(float out_buf[K*RN][W], bi_type output[K][W],
	float mul_buf[K*RN], float add_buf[K*RN]){
	#pragma HLS INLINE off
	bi_type tmp;
    for(int i=0;i<K;++i)
    	for(int j=0;j<W;++j){
    		#pragma HLS PIPELINE
    		for(int k=0;k<RN;++k){
    			tmp[k] = compute(out_buf[i*RN+k][j],mul_buf[i*RN+k],add_buf[i*RN+k]);
    		}
    		output[i][j] = tmp;
    	}
}

void load_filter_bf(int filter[K*RN][FS][FS], int f_buf[FS][K*RN][FS]){
	#pragma HLS INLINE
	for(int i=0;i<K*RN;++i)
		for(int k=0;k<FS;++k)
			for(int l=0;l<FS;++l){
				#pragma HLS PIPELINE
				f_buf[k][i][l] = filter[i][k][l];
			}
}
#pragma SDS data access_pattern(input:SEQUENTIAL, filter:SEQUENTIAL, output:SEQUENTIAL,mul:SEQUENTIAL,add:SEQUENTIAL)
void conv_bf(float input[H][W], 
	int filter[K*RN][FS][FS], bi_type output[H][K][W],
	float mul[K*RN],float add[K*RN]){
// #pragma HLS DATA_PACK variable=input
// #pragma HLS DATA_PACK variable=filter
// #pragma HLS DATA_PACK variable=output


	float in_buf_1[W], in_buf_2[W], in_buf_3[W], in_buf_4[W];
 	int f_buf[FS][K*RN][FS];
	float out_buf_1[K*RN][W], out_buf_2[K*RN][W];
	float add_buf[K*RN], mul_buf[K*RN];
	#pragma HLS ARRAY_PARTITION variable=f_buf cyclic factor=4 dim=2

	#pragma HLS ARRAY_PARTITION variable=out_buf_1 cyclic factor=4 dim=1
	#pragma HLS ARRAY_PARTITION variable=out_buf_2 cyclic factor=4 dim=1
	load_mul_buf(mul,mul_buf,K*RN);
	load_add_buf(add,add_buf,K*RN);
	load_filter_bf(filter,f_buf);
	calculate_lp:
	for(int row = -2; row <= H; ++row) {
	#pragma AP dependence variable=input intra false
	#pragma AP dependence variable=output intra false
	#pragma AP dependence variable=in_buf_1 intra false
	#pragma AP dependence variable=out_buf_1 intra false
	switch ((row+4) % 4) {
		case 1:
//				#pragma SDS async(1)
			if(row+FS-1 <H){
				load_input_bf(input[row + FS-1], in_buf_1);
			}
//				#pragma SDS async(2)
			if(row >=0 &&row<H){
				convolver_bf(row,in_buf_2, in_buf_3, in_buf_4, f_buf, out_buf_2);
			}
//				#pragma SDS async(3)
			if(row-1>=0){
				store_output_bf(out_buf_1, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		case 2:
			if(row+FS-1 <H){
				load_input_bf(input[row + FS-1], in_buf_2);
			}
			if(row >=0 &&row<H){
				convolver_bf(row,in_buf_3, in_buf_4, in_buf_1, f_buf, out_buf_1);
			}			
			if(row-1>=0){
				store_output_bf(out_buf_2, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		case 3:
//				#pragma SDS async(1)
			if(row+FS-1 <H){
				load_input_bf(input[row + FS-1], in_buf_3);
			}
//				#pragma SDS async(2)
			if(row >=0 &&row<H){
		    	convolver_bf(row,in_buf_4, in_buf_1, in_buf_2, f_buf, out_buf_2);
		    }
//				#pragma SDS async(3)
			if(row-1>=0){
				store_output_bf(out_buf_1, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		default:
//				#pragma SDS async(1)
			if(row+FS-1 <H){
				load_input_bf(input[row + FS-1], in_buf_4);
			}
//				#pragma SDS async(2)
			if(row >=0 &&row<H){
				convolver_bf(row,in_buf_1, in_buf_2, in_buf_3, f_buf, out_buf_1);
			}
//				#pragma SDS async(3)
			if(row-1>=0){
				store_output_bf(out_buf_2, output[row - 1],mul_buf,add_buf);
			}
//				#pragma SDS wait(1)
//				#pragma SDS wait(2)
//				#pragma SDS wait(3)
			break;
		}
	}
}

#endif
*/
