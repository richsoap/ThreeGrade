function myPlot(data)
dataLength = size(data);
dataLength = max(dataLength);
for i = 1:dataLength
    figure(i);
    subplot(1,2,1);
    plot(linspace(0,1,length(data{i})),data{i});
    axis off
    subplot(1,2,2);
    plot(linspace(0,1,length(data{i})),fft(data{i}));
    axis off
    print(i,'-dpng',num2str(i));
end;
%������һ��Ԫ������data������ݣ�������0��1��Ϊ��������ͼ