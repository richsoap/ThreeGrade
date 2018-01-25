function ber = ideal_bpsk(input_data,snr)
f=80000;
datalength = length(input_data);
N=datalength*8;

time = linspace(datalength/f/1000000,datalength/f,N);
bpsk_data=cos(2*pi*f*time+pi*(input_data(ceil(time*f))));%bpsk modulation signal
up_data=upsample(bpsk_data,8);

rec_data = awgn(up_data,snr,'measured');%add white noise

down_data=downsample(rec_data,8);
down_data=down_data(ceil((length(down_data)-N+1)/2):ceil((length(down_data)+N-1)/2));%cut filter delay
time_data=down_data.*(cos(2*pi*f*time));
out_data=mean(reshape(time_data,N/datalength,datalength));%caculate R

out_data=out_data<0;%different phase means bit "1"
cmp_data=input_data ~= out_data;
ber=vpa(sum(cmp_data)/datalength);