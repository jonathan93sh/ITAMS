#include <project.h>

#ifndef GRAPH_OBJECTS_H_
#define GRAPH_OBJECTS_H_
#define space_invader_SIZE 113
#define space_invader_X 27
#define space_invader_Y 33

static const char CYCODE space_invader_GRAPH_NAME[] = "space_invader";

static const uint8 CYCODE space_invader_GRAPH[113] = {
192, 1, 0, 7, 128, 3, 0, 14, 0, 7, 0, 28, 0, 112, 0, 7, 0, 224, 0, 14, 0, 192, 1, 28, 0, 240, 255, 255, 1, 224, 255, 255, 3, 192, 255, 255, 7, 240, 227, 63, 126, 224, 199, 127, 252, 192, 143, 255, 248, 241, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 31, 255, 255, 31, 63, 254, 255, 63, 126, 252, 255, 127, 252, 56, 0, 224, 248, 113, 0, 192, 241, 227, 0, 128, 227, 0, 126, 252, 0, 0, 252, 248, 1, 0, 248, 241, 3, 0, 0
};

#define shoot_SIZE 5
#define shoot_X 9
#define shoot_Y 3

static const char CYCODE shoot_GRAPH_NAME[] = "shoot";

static const uint8 CYCODE shoot_GRAPH[5] = {
255, 255, 255, 7, 0
};

#define invader_shoot_SIZE 18
#define invader_shoot_X 15
#define invader_shoot_Y 9

static const char CYCODE invader_shoot_GRAPH_NAME[] = "invader_shoot";

static const uint8 CYCODE invader_shoot_GRAPH[18] = {
56, 112, 224, 0, 14, 28, 56, 14, 28, 56, 14, 28, 56, 128, 3, 7, 14, 0
};

#define Hero_SIZE 120
#define Hero_X 21
#define Hero_Y 45

static const char CYCODE Hero_GRAPH_NAME[] = "Hero";

static const uint8 CYCODE Hero_GRAPH[120] = {
0, 0, 224, 0, 0, 0, 0, 0, 28, 0, 0, 0, 0, 128, 3, 0, 0, 0, 192, 255, 31, 0, 0, 0, 248, 255, 3, 0, 0, 0, 255, 127, 0, 0, 254, 255, 255, 255, 255, 192, 255, 255, 255, 255, 31, 248, 255, 255, 255, 255, 227, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 1, 0
};

#define explode_SIZE 133
#define explode_X 27
#define explode_Y 39

static const char CYCODE explode_GRAPH_NAME[] = "explode";

static const uint8 CYCODE explode_GRAPH[133] = {
0, 112, 0, 7, 0, 0, 56, 128, 3, 0, 0, 28, 192, 1, 0, 7, 112, 28, 192, 129, 3, 56, 14, 224, 192, 1, 28, 7, 112, 0, 7, 0, 0, 7, 128, 3, 0, 128, 3, 192, 1, 0, 192, 1, 0, 7, 0, 28, 0, 128, 3, 0, 14, 0, 192, 1, 0, 7, 240, 3, 0, 0, 224, 255, 1, 0, 0, 240, 255, 0, 0, 0, 248, 1, 28, 0, 112, 0, 0, 14, 0, 56, 0, 0, 7, 0, 28, 0, 112, 0, 0, 112, 0, 56, 0, 0, 56, 0, 28, 0, 0, 28, 192, 1, 28, 7, 112, 224, 0, 142, 3, 56, 112, 0, 199, 1, 28, 0, 112, 0, 7, 0, 0, 56, 128, 3, 0, 0, 28, 192, 1, 0, 0
};

static const uint8 CYCODE graph_objects_GRAPH_length = 5;

static const uint8 CYCODE * graph_objects_GRAPHS[] = {
space_invader_GRAPH,shoot_GRAPH,invader_shoot_GRAPH,Hero_GRAPH,explode_GRAPH
};

static const char CYCODE * graph_objects_GRAPH_NAMES[] = {
space_invader_GRAPH_NAME,shoot_GRAPH_NAME,invader_shoot_GRAPH_NAME,Hero_GRAPH_NAME,explode_GRAPH_NAME
};

static const uint16 CYCODE graph_objects_GRAPH_SIZEXS[] = {
space_invader_X,shoot_X,invader_shoot_X,Hero_X,explode_X
};

static const uint16 CYCODE graph_objects_GRAPH_SIZEYS[] = {
space_invader_Y,shoot_Y,invader_shoot_Y,Hero_Y,explode_Y
};

#endif
