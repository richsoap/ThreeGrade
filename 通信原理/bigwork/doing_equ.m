function out_data = doing_equ(input_data,equ)
mid_loc = ceil(length(equ)/2);
out_data = zeros(1,length(input_data));
for i=0:mid_loc-1
    out_data = out_data + [zeros(1,i) input_data(1:length(input_data)-i)*equ(mid_loc+i)];
end
    