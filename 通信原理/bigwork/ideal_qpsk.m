function ber = ideal_qpsk(inputdata,snr)
f=80000;
inputlength = length(inputdata);
datalength = inputlength/2;
N=datalength*8;

input_data_cos = get_data(datalength);
input_data_sin = get_data(datalength);
time = linspace(datalength/f/1000000,datalength/f,N);
qpsk_data=cos(2*pi*f*time+pi*(input_data_cos(ceil(time*f))))+sin(2*pi*f*time+pi*(input_data_sin(ceil(time*f))));%qpsk modulation signal
up_data=upsample(qpsk_data,8);


%none filter
rec_data = awgn(up_data,snr,'measured');%add white noise

down_data=downsample(rec_data,8);
down_data=down_data(ceil((length(down_data)-N+1)/2):ceil((length(down_data)+N-1)/2));%cut filter delay
time_data_cos=down_data.*(cos(2*pi*f*time));
time_data_sin=down_data.*(sin(2*pi*f*time));
out_data_cos=mean(reshape(time_data_cos,N/datalength,datalength));%caculate R cos
out_data_sin=mean(reshape(time_data_sin,N/datalength,datalength));

out_data_cos=out_data_cos<0;%different phase means bit "1"
out_data_sin=out_data_sin<0;
cmp_data_cos=input_data_cos ~= out_data_cos;
cmp_data_sin=input_data_sin ~= out_data_sin;
ber=vpa((sum(cmp_data_cos)+sum(cmp_data_sin))/datalength/2);