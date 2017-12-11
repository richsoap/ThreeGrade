function Red = BPSK(dataLength,snr,kind)
%dataLength即为数据长度
%snr为白噪声强度
%kind表示运行类型
%0：没有波形图和频谱图，没有测试序列和输出序列，只返回误码率
%2：有波形图和频谱图，测试序列和输出序列，并返回误码率
%顺便画一堆图
%|发送序列时域波形|发送序列频谱图
%|过采样后的时域波形|过采样后的频谱图
%|滤波后的波形|滤波后的频谱图
%|加入噪声后的波形|加入噪声后的频谱图
%|匹配滤波后的波形|匹配滤波后的频谱图
%|下采样后的波形|下采样后的频谱图
%important!!!!1e4以上的数据就不要用kind2了，会爆内存
%定义常数
f = 1;%载波频率
xMod = 8;%过采样率
%主进程
'BPSK'
inputData = get0and1(dataLength,2); %生成数据
%inputData = [1 1 0 1 1 0 1 0 0 0]; %testData
time = linspace(0.1,dataLength,dataLength*500); %生成时间
BPSKData = cos(2*pi*f*time+pi*inputData(ceil(time))); % BPSK调制
upSamData = upsample(BPSKData,xMod); %过采样
filter = rcosfir(0.5, [-5 5], xMod, 1, 'sqrt'); %升余弦滤波器
shiftData = conv(filter,upSamData); %升余弦滤波
noisyData = awgn(shiftData,snr,'measured'); %高斯加噪
if kind == 0
    'Shifted'
end;
downData = conv(filter,noisyData); %二次滤波
downSamData = downsample(downData,xMod); % 降采样
temptime = linspace(0.1,dataLength,length(downSamData)); %生成输出时间轴
if kind == 0
    'Downloaded'
end;
refData = cos(2*pi*f*temptime); %标准余弦
outData = refData.*downSamData;%两个函数进行乘法运算
outData = outData(1:length(outData)-20);%防止因为与滤波器卷积而导致长度不能被数据长度整除
filterData = mean(reshape(outData',length(outData)/dataLength,dataLength)); 
%将数据reshape为列数与dataLength相同的矩阵，再用mean函数对各列向量求平均
filterData = filterData<0;%和0比较，得到最终输出
cmpOut = inputData == filterData;%比较输入和输出
Red =1- vpa(sum(cmpOut) / dataLength);%计算误码率
if kind == 2
    myPlot({BPSKData,upSamData,shiftData,noisyData,downData,downSamData});
    inputData
    filterData
end;