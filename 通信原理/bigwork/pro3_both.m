input_data = get_data(1E3);
f=40e3;
datalength = length(input_data)/2;
N=datalength*8;

input_data_cos = input_data(1:datalength);
input_data_sin = input_data(datalength+1:2*datalength);
time = linspace(datalength/f/1000000,datalength/f,N);
bpsk_data=cos(2*pi*f*time+pi*(input_data_cos(ceil(time*f))))+sin(2*pi*f*time+pi*(input_data_sin(ceil(time*f))));%qpsk modulation signal
up_data=upsample(bpsk_data,8);
rec_data = awgn(up_data,10,'measured');%add white noise
down_data = downsample(rec_data,8);
down_data=down_data(ceil((length(down_data)-N+1)/2):ceil((length(down_data)+N-1)/2));
time_data_cos=down_data.*(cos(2*pi*f*time));
time_data_sin=down_data.*(sin(2*pi*f*time));
out_data_cos=mean(reshape(time_data_cos,N/datalength,datalength))/mean(abs(time_data_cos));%caculate R cos
out_data_sin=mean(reshape(time_data_sin,N/datalength,datalength))/mean(abs(time_data_sin));

plot(out_data_cos,out_data_sin,'. k');
hold on;

input_data_cos = input_data(1:datalength);
input_data_sin = input_data(datalength+1:2*datalength);
time = linspace(datalength/f/1000000,datalength/f,N);
bpsk_data=cos(2*pi*f*time+pi*(input_data_cos(ceil(time*f))))+sin(2*pi*f*time+pi*(input_data_sin(ceil(time*f))));%qpsk modulation signal
up_data=upsample(bpsk_data,8);
filter = get_filter(-1);%low-band pass
filt_data = conv(up_data,filter);
filter = get_filter(0.5);
filt_data = conv(filt_data,filter);
%none filter
rec_data = awgn(filt_data,10,'measured');%add white noise
rec_data = conv(rec_data,filter);
down_data=downsample(rec_data,8);
down_data=down_data(ceil((length(down_data)-N+1)/2):ceil((length(down_data)+N-1)/2));%cut filter delay
time_data_cos=down_data.*(cos(2*pi*f*time));
time_data_sin=down_data.*(sin(2*pi*f*time));
out_data_cos=mean(reshape(time_data_cos,N/datalength,datalength))/mean(abs(time_data_cos));%caculate R cos
out_data_sin=mean(reshape(time_data_sin,N/datalength,datalength))/mean(abs(time_data_sin));

plot(out_data_cos,out_data_sin,'. r');