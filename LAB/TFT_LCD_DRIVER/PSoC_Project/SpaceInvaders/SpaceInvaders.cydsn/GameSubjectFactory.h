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
#ifndef SUBJECTFACTORY_H_
#define SUBJECTFACTORY_H_

#include "project.h"
#include "GameSubject.h"
    

struct GameSubjectFactory;
/** Denne funktion bruges til at initialiser GameSubjectFactory */
void GameSubjectFactory_init(struct GameSubjectFactory * this, const uint8 ** graph_texs, const uint16 * sizeXs, const uint16 * sizeYs, const char ** names, struct GFXColor * colors, struct GFXColor * Bgcolors, const size_t length);

/**
 * Denne klasse(struct) har ansvaret for at allokere hukommelse til de gameSubjects der skal bruges. den står også for at fjerne dem igen når de ikke skal bruges mere. 
 */
struct GameSubjectFactory
{
    const uint8 ** graph_texs_;
    const uint16 * sizeXs_; 
    const uint16 * sizeYs_; 
    const char ** names_;
    struct GFXColor * colors_; 
    struct GFXColor * Bgcolors_;
    size_t length_;
	/** Det denne metode der skal bruges for at tilføje et subjekt. Vil returner en ikke NULL pointer hvis der er nok hukommelse ellers returner den en NULL pointer */
    struct GameSubject * (*creat)(struct GameSubjectFactory * this, char * name, int16 X, int16 Y, int8 lives, int killpoints, int ID, int8 teamID);
    /** denne metode bruges til at fjerne Subjekt igen */
	void (*delete)(struct GameSubjectFactory * this, struct GameSubject * object);
};


#endif
/* [] END OF FILE */
