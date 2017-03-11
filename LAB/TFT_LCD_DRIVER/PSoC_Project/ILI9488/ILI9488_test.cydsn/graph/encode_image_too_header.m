prefix = 'static const';
postfix = 'CYCODE';

%% build header for graphs objects

FILE_NAME = 'graph_objects';
nameList = {'space_invader', 'shoot', 'invader_shoot', 'Hero', 'explode'};

GFXencoder(FILE_NAME, nameList, prefix, postfix, 3);

%% build header for number fonts

FILE_NAME = 'graph_num_fonts';
nameList = {'number_0', 'number_1', 'number_2', 'number_3', 'number_4', 'number_5', 'number_6', 'number_7', 'number_8', 'number_9'};

GFXencoder(FILE_NAME, nameList, prefix, postfix,2);

%% build header for start screen

FILE_NAME = 'graph_startScreen';
nameList = {'invader_front_big', 'space', 'tap_to_play', 'invaders'};

GFXencoder(FILE_NAME, nameList, prefix, postfix,3);