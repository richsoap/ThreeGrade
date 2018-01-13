data = get_data(1E5);
N = 30;
ber = zeros(1,N);
noise = linspace(-15,0,N);
for i = 1:N
    i
    ber(i)=BPSK(data,noise(i),-1);
end
ber = log(ber);
plot(noise,ber,'r');
hold on
for i = 1:N
    i
    ber(i)=QPSK(data,noise(i),-1);
end
ber = log(ber);
plot(noise,ber,'b');