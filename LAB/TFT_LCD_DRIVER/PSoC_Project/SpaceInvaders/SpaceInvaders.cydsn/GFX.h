
#ifndef GFX_H_
#define GFX_H_
    
#include "project.h"    
#include "TFT_LCD.h"

    
struct GFXColor
{
    uint8 R;
    uint8 G;
    uint8 B;
};

struct GFXPos
{
	uint16 pos_X;
    uint16 pos_Y;
    uint16 size_X;
	uint16 size_Y;
};
    
struct GFXObject
{
    struct GFXColor color_;
    struct GFXColor BgColor_;
    struct GFXPos pos_;
    struct GFXPos last_pos_;
	const uint8 * graph_tex_;
	
	void (*setPos)(struct GFXObject * this, uint16 pos_X, uint16 pos_Y);
    void (*refresh)(struct GFXObject * this);
	struct GFXPos (*getPos)(struct GFXObject * this);
    uint16 (*getX)(struct GFXObject * this);
    uint16 (*getY)(struct GFXObject * this);
    void (*delete)(struct GFXObject * this);
    
};

void GFXObject_init(struct GFXObject * this, struct GFXPos pos, struct GFXColor color, struct GFXColor Bgcolor, const uint8 * graph_tex);
#endif

