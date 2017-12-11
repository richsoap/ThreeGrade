#include "conv_bi.h"
#ifndef conv_bi_file
#define conv_bf_file
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
	#define PARA 16
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
	#pragma HLS ARRAY_PARTITION variable=f_buf cyclic factor=16 dim=2

	#pragma HLS ARRAY_PARTITION variable=out_buf_1 cyclic factor=16 dim=1
	#pragma HLS ARRAY_PARTITION variable=out_buf_2 cyclic factor=16 dim=1
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
