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

void GameSubjectFactory_init(struct GameSubjectFactory * this, const uint8 ** graph_texs, const uint16 * sizeXs, const uint16 * sizeYs, const char ** names, struct GFXColor * colors, struct GFXColor * Bgcolors, const size_t length);


struct GameSubjectFactory
{
    const uint8 ** graph_texs_;
    const uint16 * sizeXs_; 
    const uint16 * sizeYs_; 
    const char ** names_;
    struct GFXColor * colors_; 
    struct GFXColor * Bgcolors_;
    size_t length_;

    struct GameSubject * (*creat)(struct GameSubjectFactory * this, char * name, int16 X, int16 Y, int8 lives, int killpoints, int ID, int8 teamID);
    void (*delete)(struct GameSubjectFactory * this, struct GameSubject * object);
};


#endif
/* [] END OF FILE */
