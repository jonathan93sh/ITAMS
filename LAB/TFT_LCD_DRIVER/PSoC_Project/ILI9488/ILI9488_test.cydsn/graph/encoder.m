%%
clk = 48 * 10^6;

T_tick = 1/60;

count = clk*T_tick

%%
clear
close all;
clc
FILE_NAME = 'graph.h';
nameList = {'space_invader', 'shoot', 'invader_shoot', 'Hero', 'explode'};

fileID=fopen(FILE_NAME,'w');

fprintf(fileID,'#include <project.h>\n\n');

for name=nameList


    
    image = imread(char(strcat(name, '.tif')));




    image = image(:,:,1);

    image(image~=0) = 1; 
    image = ~image;

    image = nneighbor(image, 3);

    imshow(double(image))
    %
    [x_length, y_length] = size(image)

    bitArray = uint8(zeros(1,ceil(x_length*y_length/8) + 1));

    for x=1:x_length
        for y=1:y_length
            bitPos = (y-1)+((x-1)*y_length)
            byte_index = floor(bitPos/8);
            bit_index = mod(bitPos,8);
            bitArray(byte_index+1) = bitor(bitArray(byte_index+1), image(x,y)*2^bit_index);

        end
    end


    charName = char(name);
    % LUT to header file

    fprintf(fileID,'#define %s_SIZE %d\n#define %s_X %d\n#define %s_Y %d\n\n', charName,length(bitArray), charName, x_length, charName, y_length);

    %fprintf(fileID,'#define LUT_SIZE %d\n#define LUT_LSB %d\n#define LUT_SHIFT %d\n\n'); %,round(array_size), round(array_size_RPM),round(array_size_RPM_shift));
    
    fprintf(fileID,'static char %s_GRAPH_NAME[] = "%s";\n\n', charName, charName); 
    
    fprintf(fileID,'static uint8 %s_GRAPH[%d] = {\n', charName, length(bitArray));

    fprintf(fileID,'%d', uint8(bitArray(1)));
    for i=2:length(bitArray)
        fprintf(fileID,', %d', uint8(bitArray(i)));
    end

    fprintf(fileID,'\n};\n\n');

    % fprintf(fileID,'static const uint8 CONST_LUT[LUT_SIZE] = {\n');
    % 
    % fprintf(fileID,'%d', uint8(power_const_LUT(1)));
    % for i=2:length(power_const_LUT)
    %     fprintf(fileID,', %d', uint8(power_const_LUT(i)));
    % end

    %fprintf(fileID,'\n};');

end

length_ = length(nameList);




fprintf(fileID,'static uint8 GRAPH_length = %d;\n\n', length_);


fprintf(fileID,'static uint8 * GRAPHS[] = {\n');
first = 1;
for name=nameList
    charName = char(name);
    if first == 0
        fprintf(fileID,',');
    end
    first = 0;
    fprintf(fileID,'%s_GRAPH', charName);

end

fprintf(fileID,'\n};\n\n');


fprintf(fileID,'static char * GRAPH_NAMES[] = {\n');
first = 1;
for name=nameList
    charName = char(name);
    if first == 0
        fprintf(fileID,',');
    end
    first = 0;
    fprintf(fileID,'%s_GRAPH_NAME', charName);

end

fprintf(fileID,'\n};\n\n');

fprintf(fileID,'static uint16 GRAPH_SIZEXS[] = {\n');
first = 1;
for name=nameList
    charName = char(name);
    if first == 0
        fprintf(fileID,',');
    end
    first = 0;
    fprintf(fileID,'%s_X', charName);

end

fprintf(fileID,'\n};\n\n');

fprintf(fileID,'static uint16 GRAPH_SIZEYS[] = {\n');
first = 1;
for name=nameList
    charName = char(name);
    if first == 0
        fprintf(fileID,',');
    end
    first = 0;
    fprintf(fileID,'%s_Y', charName);

end

fprintf(fileID,'\n};\n\n');

fclose(fileID);


%%
% [x_length, y_length] = size(image)
% 
% count = 0;
% last=0;
% 
% bitpos = 1;
% bitArray = zeros(1,x_length*y_length );
% 
% for x=1:x_length-1
%     for y=1:y_length-1
%         if(image(x,y) == last)
%             count = count +1;
%         else
%             last = image(x,y);
%             count = count +1;
%             bitArray(bitpos) = count;
%             bitpos = bitpos + 1;
%             count = 0;
%         end
%             
%     end
% end