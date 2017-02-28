#include "project.h"

struct Color
{
    uint8 R;
    uint8 G;
    uint8 B;
};

struct GFX_Pos
{
	uint16 pos_X_;
    uint16 pos_Y_;
    uint16 size_X_;
	uint16 size_Y_;
};
    
struct graph_object
{
    struct Color color_;
    struct GFX_Pos pos_;
	uint8 * graph_tex_;
	
	//void (*init)(struct graph_object * this, struct GFX_Pos pos, struct Color color, uint8 * graph_tex);
	void (*setPos)(struct graph_object * this, uint16 pos_X, uint16 pos_Y);
	
	struct GFX_Pos (*getPos)(struct graph_object * this);
};

void GFX_init(struct graph_object * this, struct GFX_Pos pos, struct Color color, uint8 * graph_tex)
{
	
}

void GFX_setPos(struct graph_object * this, uint16 pos_X, uint16 pos_Y)
{
	
}

void GFX_printer(struct graph_object * this)
{
    
}


