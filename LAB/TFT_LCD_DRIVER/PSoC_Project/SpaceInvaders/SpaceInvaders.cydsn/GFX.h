
#ifndef GFX_H_
#define GFX_H_
    
#include "project.h"    
#include "TFT_LCD.h"

/**
 * Denne struct indeholder information om en bestemt farve i RGB format.
 */
    
struct GFXColor
{
    uint8 R;
    uint8 G;
    uint8 B;
};

/**
 * Denne stuct indeholder informationer omkring position og størrelse af et Objekt.
 */
struct GFXPos
{
	uint16 pos_X;
    uint16 pos_Y;
    uint16 size_X;
	uint16 size_Y;
};

/**
 * Denne klasse(struct) bruges til håndtering af grafiske elementer.
 */
struct GFXObject
{
    struct GFXColor color_;
    struct GFXColor BgColor_;
    struct GFXPos pos_;
    struct GFXPos last_pos_;
	const uint8 * graph_tex_;
	
	void (*setPos)(struct GFXObject * this, uint16 pos_X, uint16 pos_Y); /** brug denne metode til at ændre positionen for et grafisk objekt. */
    void (*refresh)(struct GFXObject * this); /** bruges til at opdatere et grafisk objekt. f.eks. hvis noget af det grafiske objekt er blevet slette kan denne metode bruges til at gendanne objektet. */
	struct GFXPos (*getPos)(struct GFXObject * this); /** Returner position og størrelse af det grafiske objekt. */
    uint16 (*getX)(struct GFXObject * this); /** Returner X positionen. */
    uint16 (*getY)(struct GFXObject * this); /** Returner Y positionen. */
    void (*delete)(struct GFXObject * this); /** Bruges til at sikre fjerne det grafiske objekt. */
    
};

/** Denne funktion bruges til at initialisere et GFXObject, hvor det er muligt at angive dens farve, og hvilket grafisk billede den skal have. */
void GFXObject_init(struct GFXObject * this, struct GFXPos pos, struct GFXColor color, struct GFXColor Bgcolor, const uint8 * graph_tex);
#endif

