function [ rgb_large ] = nneighbor( rgb, M )
%NNEIGHBOR Summary of this function goes here
%   Detailed explanation goes here

[x_length, y_length] = size(rgb);
rgb_large = uint8(zeros(x_length*M, y_length*M));

for x=1:x_length
   for y=1:y_length 
       fill_value=rgb(x,y);
       for x_sub=0:M-1
           for y_sub=0:M-1
               rgb_large((x)*M - x_sub, (y)*M - y_sub) = uint8(fill_value);
           end
       end
   end
end

end

