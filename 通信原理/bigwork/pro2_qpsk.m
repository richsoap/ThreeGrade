N=40;
data = get_data(1E5);
ber = zeros(1,N);
noise = linspace(-20,-5,N);
for i = 1:N
    i
    ber(i)=ideal_qpsk(data,noise(i));
end
ber = log(ber);
plot(noise,ber,'k');
hold on
for i = 1:N
    i
    ber(i)=QPSK(data,noise(i),0);
end
ber = log(ber);
plot(noise,ber,'b');
for i = 1:N
    i
    ber(i)=QPSK(data,noise(i),0.5);
end
ber = log(ber);
plot(noise,ber,'r');
for i = 1:N
    i
    ber(i)=QPSK(data,noise(i),1);
end
ber = log(ber);
plot(noise,ber,'g');
for i = 1:N
    i
    ber(i)=QPSK(data,noise(i),-1);
end
ber = log(ber);
%plot(noise,ber,'c');