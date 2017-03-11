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
    

struct SubjectFactory;

void SubjectFactory_init(struct SubjectFactory * this, const uint8 ** graph_texs, const uint16 * sizeXs, const uint16 * sizeYs, const char ** names, struct Color * colors, struct Color * Bgcolors, const size_t length);


struct SubjectFactory
{
    const uint8 ** graph_texs_;
    const uint16 * sizeXs_; 
    const uint16 * sizeYs_; 
    const char ** names_;
    struct Color * colors_; 
    struct Color * Bgcolors_;
    size_t length_;

    struct GameSubject * (*creat)(struct SubjectFactory * this, char * name, int16 X, int16 Y, int8 lives, int killpoints, int ID, int8 teamID);
    void (*delete)(struct SubjectFactory * this, struct GameSubject * object);
};


#endif
/* [] END OF FILE */
