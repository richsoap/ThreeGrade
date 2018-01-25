function ber = BPSK(input_data,snr,kind)
f=80000;
datalength = length(input_data);
N=datalength*8;

time = linspace(datalength/f/1000000,datalength/f,N);
bpsk_data=cos(2*pi*f*time+pi*(input_data(ceil(time*f))));%bpsk modulation signal
up_data=upsample(bpsk_data,8);

filter = get_filter(-1);%low-band pass
filt_data = conv(up_data,filter);
if kind ~= -1
    filter = get_filter(kind);
    filt_data = conv(filt_data,filter);
end;

rec_data = awgn(filt_data,snr,'measured');%add white noise

if kind~= -1
    rec_data = conv(rec_data,filter);
end;

down_data=downsample(rec_data,8);
down_data=down_data(ceil((length(down_data)-N+1)/2):ceil((length(down_data)+N-1)/2));%cut filter delay
time_data=down_data.*(cos(2*pi*f*time));
out_data=mean(reshape(time_data,N/datalength,datalength));%caculate R

out_data=out_data<0;%different phase means bit "1"
cmp_data=input_data ~= out_data;
ber=vpa(sum(cmp_data)/datalength,10);

