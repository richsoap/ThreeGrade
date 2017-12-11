function Red = QPSK(trueDataLength,snr,kind)
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
'QPSK'
f = 1;%载波频率
xMod = 8;%过采样率
%主进程
dataLength = trueDataLength/2;
rawData = get0and1(trueDataLength,2) %生成数据
%rawData = [0 1 1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 0 1 1];
inputData = rawData((1:dataLength)*2-1)*2+rawData((1:dataLength)*2);%串行转并行
%inputData = [0,1,2,3,3,2,1,0];
%dataLength = 8;
time = linspace(0.1,dataLength,dataLength*500); %生成时间
QPSKData = cos(2*pi*f*time+(2*inputData(ceil(time))-1)*pi/4); % QPSK调制
upSamData = upsample(QPSKData,xMod); %过采样
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
refCos = cos(2*pi*f*temptime); %标准余弦
refSin = sin(2*pi*f*temptime); %标准正弦
outCos = downSamData.*refCos; 
outSin = downSamData.*refSin;%进行时域乘法
outCos = outCos(1:length(outCos)-20);
outSin = outSin(1:length(outSin)-20);%防止因为与滤波器卷积而导致长度不能被数据长度整除
filCos = sum(reshape(outCos',length(outCos)/dataLength,dataLength));
filSin = sum(reshape(outSin',length(outSin)/dataLength,dataLength));%求出各段积分值
filSin = filSin.*filCos;
filCos = filCos < 0;
filSin = filSin < 0;%判断数据点的距离
outData = reshape([filCos;filSin],1,trueDataLength);
cmpOut = outData == rawData;
Red = 1 - vpa(sum(cmpOut)/trueDataLength);
if kind == 2
    myPlot({QPSKData,upSamData,shiftData,noisyData,downData,downSamData});
    rawData
    outData
end;