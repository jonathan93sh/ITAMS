function [ ] = GFXencoder( FILE_NAME, nameList, prefix, postfix, scale )
%GFXENCODER Summary of this function goes here
%   Detailed explanation goes here

%FILE_NAME = 'graph_startScreen';
%nameList = {'invader_front_big', 'space', 'tap_to_play', 'invaders'};


fileID=fopen(strcat(FILE_NAME, '.h'),'w');

fprintf(fileID,'#include <project.h>\n\n');
fprintf(fileID,'#ifndef %s_H_\n',upper(FILE_NAME));
fprintf(fileID,'#define %s_H_\n',upper(FILE_NAME));
for name=nameList

    image = imread(char(strcat(name, '.tif')));
    image = image(:,:,1);
    
    image = flip(image,2);
    
    image(image~=0) = 1; 
    image = ~image;

    image = nneighbor(image, scale);

    %imshow(double(image))
    
    %
    [x_length, y_length] = size(image);

    bitArray = uint8(zeros(1,ceil(x_length*y_length/8) + 1));

    for x=1:x_length
        for y=1:y_length
            bitPos = (y-1)+((x-1)*y_length);
            byte_index = floor(bitPos/8);
            bit_index = mod(bitPos,8);
            bitArray(byte_index+1) = bitor(bitArray(byte_index+1), image(x,y)*2^bit_index);

        end
    end


    charName = char(name);
    % LUT to header file

    fprintf(fileID,'#define %s_SIZE %d\n#define %s_X %d\n#define %s_Y %d\n\n', charName,length(bitArray), charName, x_length, charName, y_length);

    %fprintf(fileID,'#define LUT_SIZE %d\n#define LUT_LSB %d\n#define LUT_SHIFT %d\n\n'); %,round(array_size), round(array_size_RPM),round(array_size_RPM_shift));
    
    fprintf(fileID,'%s char %s %s_GRAPH_NAME[] = "%s";\n\n',prefix, postfix, charName, charName); 
    
    fprintf(fileID,'%s uint8 %s %s_GRAPH[%d] = {\n',prefix,postfix, charName, length(bitArray));

    fprintf(fileID,'%d', uint8(bitArray(1)));
    for i=2:length(bitArray)
        fprintf(fileID,', %d', uint8(bitArray(i)));
    end

    fprintf(fileID,'\n};\n\n');

end

length_ = length(nameList);




fprintf(fileID,'%s uint8 %s %s_GRAPH_length = %d;\n\n',prefix,postfix, FILE_NAME, length_);


fprintf(fileID,'%s uint8 %s * %s_GRAPHS[] = {\n',prefix, postfix, FILE_NAME);
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


fprintf(fileID,'%s char %s * %s_GRAPH_NAMES[] = {\n', prefix, postfix, FILE_NAME);
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

fprintf(fileID,'%s uint16 %s %s_GRAPH_SIZEXS[] = {\n', prefix, postfix, FILE_NAME);
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

fprintf(fileID,'%s uint16 %s %s_GRAPH_SIZEYS[] = {\n', prefix, postfix, FILE_NAME);
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
fprintf(fileID,'#endif\n');
fclose(fileID);


end

