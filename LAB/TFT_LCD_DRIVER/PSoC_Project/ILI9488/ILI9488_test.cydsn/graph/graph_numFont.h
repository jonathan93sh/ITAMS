#include <project.h>

#define number_0_SIZE 41
#define number_0_X 20
#define number_0_Y 16

static char number_0_GRAPH_NAME[] = "number_0";

static uint8 number_0_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0
};

#define number_1_SIZE 41
#define number_1_X 20
#define number_1_Y 16

static char number_1_GRAPH_NAME[] = "number_1";

static uint8 number_1_GRAPH[41] = {
0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0
};

#define number_2_SIZE 41
#define number_2_X 20
#define number_2_Y 16

static char number_2_GRAPH_NAME[] = "number_2";

static uint8 number_2_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 252, 63, 252, 63, 252, 63, 252, 63, 60, 0, 60, 0, 60, 0, 60, 0, 252, 63, 252, 63, 252, 63, 252, 63, 0
};

#define number_3_SIZE 41
#define number_3_X 20
#define number_3_Y 16

static char number_3_GRAPH_NAME[] = "number_3";

static uint8 number_3_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0
};

#define number_4_SIZE 41
#define number_4_X 20
#define number_4_Y 16

static char number_4_GRAPH_NAME[] = "number_4";

static uint8 number_4_GRAPH[41] = {
60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0
};

#define number_5_SIZE 41
#define number_5_X 20
#define number_5_Y 16

static char number_5_GRAPH_NAME[] = "number_5";

static uint8 number_5_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 60, 0, 60, 0, 60, 0, 60, 0, 252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0
};

#define number_6_SIZE 41
#define number_6_X 20
#define number_6_Y 16

static char number_6_GRAPH_NAME[] = "number_6";

static uint8 number_6_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 60, 0, 60, 0, 60, 0, 60, 0, 252, 63, 252, 63, 252, 63, 252, 63, 60, 60, 60, 60, 60, 60, 60, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0
};

#define number_7_SIZE 41
#define number_7_X 20
#define number_7_Y 16

static char number_7_GRAPH_NAME[] = "number_7";

static uint8 number_7_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0
};

#define number_8_SIZE 41
#define number_8_X 20
#define number_8_Y 16

static char number_8_GRAPH_NAME[] = "number_8";

static uint8 number_8_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 60, 60, 60, 60, 60, 60, 60, 60, 252, 63, 252, 63, 252, 63, 252, 63, 60, 60, 60, 60, 60, 60, 60, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0
};

#define number_9_SIZE 41
#define number_9_X 20
#define number_9_Y 16

static char number_9_GRAPH_NAME[] = "number_9";

static uint8 number_9_GRAPH[41] = {
252, 63, 252, 63, 252, 63, 252, 63, 60, 60, 60, 60, 60, 60, 60, 60, 252, 63, 252, 63, 252, 63, 252, 63, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0, 60, 0
};

static uint8 GRAPH_NUM_length = 10;

static uint8 * NUM_GRAPHS[] = {
number_0_GRAPH,number_1_GRAPH,number_2_GRAPH,number_3_GRAPH,number_4_GRAPH,number_5_GRAPH,number_6_GRAPH,number_7_GRAPH,number_8_GRAPH,number_9_GRAPH
};

static char * GRAPH_NUM_NAMES[] = {
number_0_GRAPH_NAME,number_1_GRAPH_NAME,number_2_GRAPH_NAME,number_3_GRAPH_NAME,number_4_GRAPH_NAME,number_5_GRAPH_NAME,number_6_GRAPH_NAME,number_7_GRAPH_NAME,number_8_GRAPH_NAME,number_9_GRAPH_NAME
};

static uint16 GRAPH_NUM_SIZEXS[] = {
number_0_X,number_1_X,number_2_X,number_3_X,number_4_X,number_5_X,number_6_X,number_7_X,number_8_X,number_9_X
};

static uint16 GRAPH_NUM_SIZEYS[] = {
number_0_Y,number_1_Y,number_2_Y,number_3_Y,number_4_Y,number_5_Y,number_6_Y,number_7_Y,number_8_Y,number_9_Y
};

