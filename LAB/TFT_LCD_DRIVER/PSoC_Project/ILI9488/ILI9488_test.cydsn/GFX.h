#include "project.h"

#ifndef GFX_H_
#define GFX_H_

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
    struct Color BgColor_;
    struct GFX_Pos pos_;
    struct GFX_Pos last_pos_;
	uint8 * graph_tex_;
	
	void (*setPos)(struct graph_object * this, uint16 pos_X, uint16 pos_Y);
    void (*refresh)(struct graph_object * this);
	struct GFX_Pos (*getPos)(struct graph_object * this);
    uint16 (*getX)(struct graph_object * this);
    uint16 (*getY)(struct graph_object * this);
    void (*delete)(struct graph_object * this);
    
};

void GFX_init(struct graph_object * this, struct GFX_Pos pos, struct Color color, struct Color Bgcolor, uint8 * graph_tex);
#endif

