times = 40;
snrs = linspace(-60,0,times);
reds = zeros(1,times);
for i = 1:times
    i
    reds(i) = qam16(3e4,snrs(i),0);
    if mod(i,20) == 0
        outdata = [snrs' reds'];
        save QAM_Snr_Red.txt outdata -ascii
    end;
end;
plot(snrs,reds);
outdata = [snrs' reds']
save Q_Snr_Red.txt outdata -ascii