// 97.46
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "conv_bi.h" 
#include "perfCounter.h"
using namespace std;
#include"cnpy.h"
#define NF 128
int DataOfAnImage = H*W;
int arr_NF_1_3_3[] = {NF,1,3,3};
int arr_NF[] = {NF};
int arr_NF_NF_3_3[] = {NF,NF,3,3};
int arr_NF_H_W[] = {NF,H,W};
vector<int> vec_NF_1_3_3 = vector<int>(arr_NF_1_3_3,arr_NF_1_3_3+4);
vector<int> vec_NF = vector<int>(arr_NF,arr_NF+1);
vector<int> vec_NF_NF_3_3 = vector<int>(arr_NF_NF_3_3,arr_NF_NF_3_3+4);
vector<int> vec_NF_H_W = vector<int>(arr_NF_H_W,arr_NF_H_W+3);
string path = "";
string labelFileName = "t10k-labels-idx1-ubyte";
string imageFileName = "t10k-images-idx3-ubyte";
int numberOfImages = 10000;
string intto_string(int i){
    stringstream ss;
    ss << i;
    return ss.str();
}
void checkEQ(int a, int b){
    if (a!=b) {
        cout << a << "!=" << b << endl;
        exit(1);
    }
    return;
}
int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1=i&255;
    ch2=(i>>8)&255;
    ch3=(i>>16)&255;
    ch4=(i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}
void ReadMNISTImage(vector<vector<float> > &arr)
{
    arr.resize(numberOfImages,vector<float>(DataOfAnImage));
    ifstream file ((path+imageFileName).c_str(),ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= ReverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= ReverseInt(n_cols);
        for(int i=0;i<number_of_images;++i)
        {
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
                    arr[i][(n_rows*r)+c]= 2*((float)temp/256.0)-1;
                }
            }
        }
    } else{
        cout << "Can't open" << path + imageFileName << endl;
    }
}
void ReadMNISTLabel(vector<int> &arr){
    arr.resize(numberOfImages);
    ifstream file ((path+labelFileName).c_str(), ios::binary);
    if (file.is_open()){
        int magic_number=0;
        int number_of_images=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        for(int i=0;i<number_of_images;++i){
            unsigned char temp=0;
            file.read((char*)&temp,sizeof(temp));
            arr[i]= temp;
        }
    } else{
        cout << "Can't open" << path + labelFileName << endl;
    }
}
void printOne(float i){
    if(i>0){
        cout << "\u25A0";
    } else {
        cout << "  ";
    }
    return;
}
void printImage(vector<float> arr){
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j){
            printOne(arr[i*W+j]);
        }
        cout << endl;
    }
}
cnpy::NpyArray load_npz(cnpy::npz_t &my_npz,
    int i, int size_,vector<int> vec){
    // cout << string("arr_") + to_string(i);
    cnpy::NpyArray arr = my_npz[string("arr_"+intto_string(i))];
    checkEQ(arr.word_size,size_);
    checkEQ(arr.shape.size(),vec.size());
    for(int i=0;i<vec.size();++i){
        checkEQ(arr.shape[i],vec[i]);
    }
    return arr;
}
void check_point(bi_type output[H][K][W],int i){
    cout << "check_point" << i << endl;
    string file_name = "output" + to_string(i)+".npz";
    cnpy::npz_t my_npz = cnpy::npz_load(file_name);
    cnpy::NpyArray out_npy = load_npz(my_npz,0,sizeof(float),vec_NF_H_W);
    typedef float out_float[H][W];
    out_float* out_float_p = (out_float*)out_npy.data;
    int wrong_number = 0;
    for(int i=0;i<K*RN;++i)
        for(int j=0;j<H;++j)
            for(int k=0;k<W;++k){
                if((2*(int)output[j][i/RN][k][i%RN]-1)!=
                    out_float_p[i][j][k]){
                    wrong_number++;
                }
            }
    cout << "error rate:" << wrong_number*1.0/(K*RN*H*W) << endl;
    out_npy.destruct();
}
void load_mul_add(cnpy::npz_t &my_npz,int i,int len,
    float *mul, float *add){
    vector<int> aa;
    aa.push_back(len);
    // float *mul = (float*)malloc(len*sizeof(float));
    // float *add = (float*)malloc(len*sizeof(float));
    cnpy::NpyArray b_npy = load_npz(my_npz,i,sizeof(float),aa);
    cnpy::NpyArray beta_npy = load_npz(my_npz,i+1,sizeof(float),aa);
    cnpy::NpyArray g_npy = load_npz(my_npz,i+2,sizeof(float),aa);
    cnpy::NpyArray m_npy = load_npz(my_npz,i+3,sizeof(float),aa);
    cnpy::NpyArray inv_npy = load_npz(my_npz,i+4,sizeof(float),aa);
    float *b_npy_float = (float*)b_npy.data;
    float *beta_npy_float = (float*)beta_npy.data;
    float *g_npy_float = (float*)g_npy.data;
    float *m_npy_float = (float*)m_npy.data;
    float *inv_npy_float = (float*)inv_npy.data;
    for(int i=0;i<len;++i){
        mul[i] = g_npy_float[i]*inv_npy_float[i];
        add[i] = beta_npy_float[i] + (b_npy_float[i]-m_npy_float[i])*mul[i];
    }
    b_npy.destruct();
    beta_npy.destruct();
    g_npy.destruct();
    m_npy.destruct();
    inv_npy.destruct();
    return;
    // return make_pair(mul,add);
}
void convert(bi_type input[H][K][W], bi_type a[H*W*K]){
    for(int i=0;i<K;++i)
        for(int j=0;j<H;++j)
            for(int k=0;k<W;++k)
                a[(i*H+j)*W+k] = input[j][i][k];
}
void conv_bi_caller(bi_type input[H][C][W], 
    bi_type filter[K*RN][C][FS][FS], bi_type output[H][K][W],
    float add[K*RN],float mul[K*RN]){
    conv_bi(input,filter,output,add,mul);
}
int main(){
    checkEQ(sizeof(bi_type),8);
    int num_cor = 0;
    vector<vector<float> > image_tst;
    vector<int> label_tst;
    ReadMNISTImage(image_tst);
    ReadMNISTLabel(label_tst);
    checkEQ(image_tst.size(),label_tst.size());
    // Load npz file
    cnpy::npz_t my_npz = cnpy::npz_load("mnist_parameters.npz");
    // weight of first layer
    cnpy::NpyArray w1_npy = load_npz(my_npz,0,sizeof(float),vec_NF_1_3_3);
    typedef float w1_type_npy[FS][FS];
    typedef int w1_type[FS][FS];
    w1_type_npy *w1_npy_p = (w1_type_npy*)w1_npy.data;
    int w1[K*RN][FS][FS];
    // w1_type *w1 = (w1_type*)malloc(NF*FS*FS*sizeof(int));
    for(int i=0;i<K*RN;++i){
        for(int j=0;j<FS;++j)
            for(int k=0;k<FS;++k){
                w1[i][j][k] = ((w1_npy_p[i][FS-1-j][FS-1-k]>0)?1:-1);
            }
    }
    w1_npy.destruct();
    float mul1[K*RN], add1[K*RN];
    load_mul_add(my_npz,1,K*RN,mul1,add1);
    // float *mul1 = mul_add1.first;
    // float *add1 = mul_add1.second;


    cnpy::NpyArray w2_npy = load_npz(my_npz,6,sizeof(float),vec_NF_NF_3_3);
    typedef bi_type w2_type[C][FS][FS];
    typedef float w2_type_npy[K*RN][FS][FS];
    w2_type_npy *w2_npy_p = (w2_type_npy*)w2_npy.data;
    bi_type w2[K*RN][C][FS][FS];
    // w2_type *w2 = (w2_type*)malloc(K*RN*C*FS*FS*sizeof(sizeof(bi_type)));
    for(int i=0;i<K*RN;++i)
        for(int j=0;j<K*RN;++j)
            for(int k=0;k<FS;++k)
                for(int l=0;l<FS;++l)
                    w2[i][j/RN][k][l][j%RN] = 
                        (w2_npy_p[i][j][FS-1-k][FS-1-l]>0?1:0);
    w2_npy.destruct();
    float mul2[K*RN], add2[K*RN];
    load_mul_add(my_npz,7,K*RN,mul2,add2);
    // float *mul2 = mul_add2.first;
    // float *add2 = mul_add2.second;

    cnpy::NpyArray w3_npy = load_npz(my_npz,12,sizeof(float),vec_NF_NF_3_3);
    typedef bi_type w3_type[C][FS][FS];
    typedef float w3_type_npy[K*RN][FS][FS];
    w3_type_npy *w3_npy_p = (w3_type_npy*)w3_npy.data;
    bi_type w3[K*RN][C][FS][FS];
    // w3_type *w3 = (w3_type*)malloc(K*RN*C*FS*FS*sizeof(sizeof(bi_type)));
    for(int i=0;i<K*RN;++i)
        for(int j=0;j<K*RN;++j)
            for(int k=0;k<FS;++k)
                for(int l=0;l<FS;++l)
                    w3[i][j/RN][k][l][j%RN] = 
                        (w3_npy_p[i][j][FS-1-k][FS-1-l]>0?1:0);
    w3_npy.destruct();
    float mul3[K*RN], add3[K*RN];
    load_mul_add(my_npz,13,K*RN,mul3,add3);
    // float *mul3 = mul_add3.first;
    // float *add3 = mul_add3.second;

    vector<int> tmp;
    tmp.push_back(K*RN*H*W);
    tmp.push_back(NC);
    cnpy::NpyArray w4_npy = load_npz(my_npz,18,sizeof(float),tmp);
    typedef float w4_type_npy[NC];
    typedef bi_type w4_type[NC];
    w4_type_npy *w4_npy_p = (w4_type_npy*)w4_npy.data;
    bi_type w4[K*H*W][NC];
    // w4_type *w4 = (w4_type*)malloc(K*H*W*NC*sizeof(bi_type));
    for(int i=0;i<NC;++i)
        for(int j=0;j<K;++j)
           for(int k=0;k<RN;++k)
                for(int l=0;l<H;++l)
                    for(int m=0;m<W;++m)
                        w4[(j*H+l)*W+m][i][k] = 
                            (w4_npy_p[((j*RN+k)*H+l)*W+m][i] > 0?1:0);
    w4_npy.destruct();
    float mul4[NC], add4[NC];
    load_mul_add(my_npz,19,NC,mul4,add4);
    // float *mul4 = mul_add4.first;
    // float *add4 = mul_add4.second;

    bi_type output1[H][K][W];
    // out_3d *output1 = (out_3d *)malloc(H*W*K*sizeof(bi_type));
    bi_type output2[H][K][W];
    // out_3d *output2 = (out_3d *)malloc(H*W*K*sizeof(bi_type));
    bi_type output3[H][K][W];
    // out_3d *output3 = (out_3d *)malloc(H*W*K*sizeof(bi_type));
    float output4[NC];
    // float *output4 = (float*)malloc(NC*sizeof(float));
    perf_counter ctr;
    for(int i=0;i<10000;++i){
        vector<float> arr = image_tst[i];
        cout << "------------------" << endl;
        // printImage(image_tst[i]);
        float input1[H][W];
        for(int j=0;j<H;++j){
            for(int k=0;k<W;++k){
                input1[j][k] = arr[j*H+k];
                if(i%10==0)
                    printOne(input1[j][k]);
            }
            if(i%10 == 0)
                cout << endl;
        }
        if(i!=0)
            ctr.start();
        conv_bf(input1,w1,output1,mul1,add1);
        if(i==0){
            check_point(output1,1);
        }
        // check(output1,"arr")
        conv_bi_caller(output1,w2,output2,mul2,add2);
        if(i==0){
            check_point(output2,2);
        }
        conv_bi_caller(output2,w3,output3,mul3,add3);
        if(i==0){
            check_point(output3,3);
        }
        bi_type a[H*W*K];
        convert(output3,a);
        gemm_bi(a,w4,output4,mul4,add4);
        int argmax = 0;
        float maxOut = -INT_MIN;
        for(int j=0;j<NC;++j){
            // cout << j << ":" << output4[j] << " ";
            if(output4[j]>maxOut){
                argmax = j;
                maxOut = output4[j];
            }
        }
        if(i!=0)
            ctr.stop();
        cout << "label:"<< label_tst[i] << endl;
        cout << "result:" << argmax << endl;
        if(argmax==label_tst[i])
            num_cor++;
    }
    cout << "------------------" << endl;
    cout << "time per image:" << ctr.avg_cpu_cycles()/667/(10E6) << "s" << endl;
    cout << "precision:" << 100.0*num_cor/numberOfImages << endl;
    cout << "total precision:" << 97.46 << endl;
    return 0;
}
