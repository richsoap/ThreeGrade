function Red = QPSK(trueDataLength,snr,kind)
%dataLength��Ϊ���ݳ���
%snrΪ������ǿ��
%kind��ʾ��������
%0��û�в���ͼ��Ƶ��ͼ��û�в������к�������У�ֻ����������
%2���в���ͼ��Ƶ��ͼ���������к�������У�������������
%˳�㻭һ��ͼ
%|��������ʱ����|��������Ƶ��ͼ
%|���������ʱ����|���������Ƶ��ͼ
%|�˲���Ĳ���|�˲����Ƶ��ͼ
%|����������Ĳ���|�����������Ƶ��ͼ
%|ƥ���˲���Ĳ���|ƥ���˲����Ƶ��ͼ
%|�²�����Ĳ���|�²������Ƶ��ͼ
%important!!!!1e4���ϵ����ݾͲ�Ҫ��kind2�ˣ��ᱬ�ڴ�
%���峣��
'QPSK'
f = 1;%�ز�Ƶ��
xMod = 8;%��������
%������
dataLength = trueDataLength/2;
rawData = get0and1(trueDataLength,2) %��������
%rawData = [0 1 1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 0 1 1];
inputData = rawData((1:dataLength)*2-1)*2+rawData((1:dataLength)*2);%����ת����
%inputData = [0,1,2,3,3,2,1,0];
%dataLength = 8;
time = linspace(0.1,dataLength,dataLength*500); %����ʱ��
QPSKData = cos(2*pi*f*time+(2*inputData(ceil(time))-1)*pi/4); % QPSK����
upSamData = upsample(QPSKData,xMod); %������
filter = rcosfir(0.5, [-5 5], xMod, 1, 'sqrt'); %�������˲���
shiftData = conv(filter,upSamData); %�������˲�
noisyData = awgn(shiftData,snr,'measured'); %��˹����
if kind == 0
    'Shifted'
end;
downData = conv(filter,noisyData); %�����˲�
downSamData = downsample(downData,xMod); % ������
temptime = linspace(0.1,dataLength,length(downSamData)); %�������ʱ����
if kind == 0
    'Downloaded'
end;
refCos = cos(2*pi*f*temptime); %��׼����
refSin = sin(2*pi*f*temptime); %��׼����
outCos = downSamData.*refCos; 
outSin = downSamData.*refSin;%����ʱ��˷�
outCos = outCos(1:length(outCos)-20);
outSin = outSin(1:length(outSin)-20);%��ֹ��Ϊ���˲�����������³��Ȳ��ܱ����ݳ�������
filCos = sum(reshape(outCos',length(outCos)/dataLength,dataLength));
filSin = sum(reshape(outSin',length(outSin)/dataLength,dataLength));%������λ���ֵ
filSin = filSin.*filCos;
filCos = filCos < 0;
filSin = filSin < 0;%�ж����ݵ�ľ���
outData = reshape([filCos;filSin],1,trueDataLength);
cmpOut = outData == rawData;
Red = 1 - vpa(sum(cmpOut)/trueDataLength);
if kind == 2
    myPlot({QPSKData,upSamData,shiftData,noisyData,downData,downSamData});
    rawData
    outData
end;