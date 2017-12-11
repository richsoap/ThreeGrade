function Red = BPSK(dataLength,snr,kind)
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
f = 1;%�ز�Ƶ��
xMod = 8;%��������
%������
'BPSK'
inputData = get0and1(dataLength,2); %��������
%inputData = [1 1 0 1 1 0 1 0 0 0]; %testData
time = linspace(0.1,dataLength,dataLength*500); %����ʱ��
BPSKData = cos(2*pi*f*time+pi*inputData(ceil(time))); % BPSK����
upSamData = upsample(BPSKData,xMod); %������
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
refData = cos(2*pi*f*temptime); %��׼����
outData = refData.*downSamData;%�����������г˷�����
outData = outData(1:length(outData)-20);%��ֹ��Ϊ���˲�����������³��Ȳ��ܱ����ݳ�������
filterData = mean(reshape(outData',length(outData)/dataLength,dataLength)); 
%������reshapeΪ������dataLength��ͬ�ľ�������mean�����Ը���������ƽ��
filterData = filterData<0;%��0�Ƚϣ��õ��������
cmpOut = inputData == filterData;%�Ƚ���������
Red =1- vpa(sum(cmpOut) / dataLength);%����������
if kind == 2
    myPlot({BPSKData,upSamData,shiftData,noisyData,downData,downSamData});
    inputData
    filterData
end;