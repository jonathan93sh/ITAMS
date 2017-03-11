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

#include "SubjectFactory.h"
#include <stdio.h>
#include <stdlib.h>


struct GameSubject * SF_creat(struct SubjectFactory * this, char * name, int16 X, int16 Y, int8 lives, int killpoints, int ID, int8 teamID);
void SF_delete(struct SubjectFactory * this, struct GameSubject * object);

void SubjectFactory_init(struct SubjectFactory * this, const uint8 ** graph_texs, const uint16 * sizeXs, const uint16 * sizeYs, const char ** names, struct Color * colors, struct Color * Bgcolors, const size_t length)
{
    this->graph_texs_ = graph_texs;
    this->sizeXs_ = sizeXs;
    this->sizeYs_ = sizeYs;
    this->names_ = names;
    this->colors_ = colors;
    this->Bgcolors_ = Bgcolors;
    this->length_ = length;
    
    this->creat = SF_creat;
    this->delete = SF_delete;
}


struct GameSubject * SF_creat(struct SubjectFactory * this, char * name, int16 X, int16 Y, int8 lives, int killpoints, int ID, int8 teamID)
{
    uint8 i;
    struct GameSubject * newSubject = NULL;
    
    for(i = 0; i < this->length_; i++)
    {
        if(strcmp(name, this->names_[i]) == 0)
        {
            newSubject = (struct GameSubject *)malloc(sizeof(struct GameSubject));
            
            if(newSubject == NULL)
                return NULL;
            
            GameSubject_init(newSubject, this->graph_texs_[i], this->sizeXs_[i], this->sizeYs_[i], this->colors_[i], this->Bgcolors_[i], X, Y, lives, killpoints, ID, teamID);
            break;   
        }
    }
    
    
    return newSubject;
}

void SF_delete(struct SubjectFactory * this, struct GameSubject * object)
{
    if(object == NULL)
        return;
    
    object->graph_.delete(&object->graph_);
    
    free(object);
}

/* [] END OF FILE */
