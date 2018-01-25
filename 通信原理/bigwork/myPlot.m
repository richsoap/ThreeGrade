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
%遍历了一下元胞数组data里的数据，并都以0到1作为横坐标作图