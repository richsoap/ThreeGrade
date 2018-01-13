function ber = BPSK_equ(input_data,snr,equ,int)
ber=0;
f=80000;
datalength = length(input_data);
N=datalength*8;

time = linspace(datalength/f/1000000,datalength/f,N);
bpsk_data=cos(2*pi*f*time+pi*(input_data(ceil(time*f))));%bpsk modulation signal
up_data=upsample(bpsk_data,8);

filter = get_filter(-1);%low-band pass
filt_data = conv(up_data,filter);

rec_data = awgn(filt_data,snr-10*log10(4),'measured');%add white noise

down_data=downsample(rec_data,8);
down_data=down_data(ceil((length(down_data)-N+1)/2):ceil((length(down_data)+N-1)/2));%cut filter delay
time_data=down_data.*(cos(2*pi*f*time));
out_data=mean(reshape(time_data,N/datalength,datalength));%caculate R
out_data=out_data/mean(abs(out_data));
out_data=(out_data+1)/2;

out_data=[out_data(1) (int*out_data(1:length(out_data)-1)+out_data(2:length(out_data)))];

out_data=doing_equ(out_data,equ);

out_data=round(out_data);
out_data=-out_data+1;
cmp_data=input_data ~= out_data;
ber=vpa(sum(cmp_data)/datalength,10);