/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <project.h>
#include "GameSubjectFactory.h"
#include "GFXNumber.h"    

#define subjectLimit 40
#define shootsInAirLimit 20
enum teamID{Player, Enemies};
enum Gdir{UP, DOWN, LEFT, RIGTH};
struct GameEngine;

/**
 * Denne funktion bruges til at initialiser GameEngine.
 */
void GameEngine_init(struct GameEngine * this, struct GameSubjectFactory * factory, char nextLevel);

struct coord
{
    int16 X;
    int16 Y;
};

/**
 * Denne klasse(struct) er en simpel lille gameEngine der indeholder de mest basle funktioner der skal bruges til at få et lille spil til at køre, f.eks. SpaceInvader. 
 */
struct GameEngine
{
    uint32 points_;
    struct GameSubject * subjects_[subjectLimit];
    struct GameSubject * shoots_[shootsInAirLimit];
    uint8 shootSpeed_[shootsInAirLimit];
    uint8 shootDir_[shootsInAirLimit];
    
    struct GameSubjectFactory * factory_;
    struct GFXNumber finalScore_;
    struct GFXNumber HighScore_;
    
    /** Denne metode bruges til at spawne nye Subjekter i spillet, hvor det er muligt at initialiser en række forskellige parameter. Metoden vil returner Subjektets ID */
    int16 (*spawn)(struct GameEngine * this, char * name, int8 teamID, int16 killpoints, int16 X, int16 Y, int8 lives); //return subject ID if -1 wrong name, -2 subject limit.
	/** Denne metode kan bruges til at ændre positionen på et allerede spawnet og ikke dødt Subjekt. for at bruge metoden skal man kende ID på det Subjekt man ønsker at flytte. */
    int8 (*move)(struct GameEngine * this, uint8 ID, int16 X, int16 Y, char relativ);
	/** Anskaffer positionen på subjektet til ID'et */
    struct coord (*getPos)(struct GameEngine * this, uint8 ID);
	/** Denne metode lader et ønsket subjekt affyre et skud */
    int8 (*shoot)(struct GameEngine * this, uint8 ID, int8 dir, char * type, uint8 speed);
	/** returner 1 hvis subjektet til det angivet ID er dødt */
    int8 (*isDead)(struct GameEngine * this, uint8 ID);
	/** Denne metode er nok den vigtigste metode i klassen, det er denne metode der behandler alle kommandoerne, hver gang denne metode bliver kaldt */
    void (*tick)(struct GameEngine * this);
	/** Returner antallet af liv et Subjekt har */
    int8 (*lifeLeft)(struct GameEngine * this, uint8 ID);
	/** Viser HighScore når et spil er færdigt */
    void (*endGame)(struct GameEngine * this);
	/** Viser brugerens nuværende score */ 
    void (*nextLevel)(struct GameEngine * this);
};

#endif
/* [] END OF FILE */
