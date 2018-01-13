times = 40;
snrs = linspace(-100,0,times);
BPSK_reds = zeros(1,times);
QPSK_reds = zeros(1,times);
for i = 1:times
    i
    BPSK_reds(1,i) = BPSK(1e4,snrs(i),0);
    QPSK_reds(1,i) = QPSK(1e4,snrs(i),0);
    if mod(i,20) == 0
        outdata = [snrs' BPSK_reds'];
        save B_Snr_Red.txt outdata -ascii
        outdata = [snrs' QPSK_reds'];
        save Q_Snr_Red.txt outdata -ascii
    end;
end;
subplot(2,1,1);
plot(snrs,reds());
subplot(2,1,2);
plot(snrs,reds(1,:));
BPSK_reds
outdata = [snrs' BPSK_reds']
save B_Snr_Red.txt outdata -ascii
QPSK_reds
outdata = [snrs' QPSK_reds']
save Q_Snr_Red.txt outdata -ascii