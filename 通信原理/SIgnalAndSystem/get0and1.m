function out = get0and1(length,kind)
out = mod(ceil(rand(1,length)*255),kind);
%随机出整数，再将其对kind取模得到相应的数据列
