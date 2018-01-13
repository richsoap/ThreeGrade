N=40;
data = get_data(1E5);
ber = zeros(1,N);
noise = linspace(-20,0,N);
for i = 1:N
    i
    %ber(i)=BPSK_equ(data,noise(i),[18/121,20/11,-81/121],0.9);
    ber(i)=BPSK_equ(data,noise(i),[0,0,1,-0.9,0.81],0.9);
end
ber = log(ber);
plot(noise,ber,'b');
hold on;
for i = 1:N
    i
    %ber(i)=BPSK_equ(data,noise(i),[18/121,20/11,-81/121],0.9);
    ber(i)=BPSK_equ(data,noise(i),1,0.9);
end
ber = log(ber);
plot(noise,ber,'r');
for i = 1:N
    i
    %ber(i)=BPSK_equ(data,noise(i),[18/121,20/11,-81/121],0.9);
    ber(i)=BPSK_equ(data,noise(i),[0,1,-0.9],0.9);
end
ber = log(ber);
plot(noise,ber,'k');
