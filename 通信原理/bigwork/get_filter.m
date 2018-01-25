function out = get_filter(para)
x = linspace(-160,160,321);
if para == -1
    out = sinc(x*pi/12);
else
    out = rcosfir(para, [-5 5], 16, 1/8E4, 'sqrt');
end;

