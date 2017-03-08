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


#include "gameEngine.h"

int16 GE_spawn(struct GameEngine * this, char * name, int8 teamID, int16 killpoints, int16 X, int16 Y, int8 lives); //return subject ID if -1 wrong name, -2 subject limit.
int8 GE_move(struct GameEngine * this, uint8 ID, int16 X, int16 Y, char relativ);
struct coord GE_getPos(struct GameEngine * this, uint8 ID);
int8 GE_shoot(struct GameEngine * this, uint8 ID, int8 dir, char * type, uint8 speed);
int8 GE_tick(struct GameEngine * this);
void GE_checkHit(struct GameEngine * this);
void GE_updatePos(struct GameEngine * this);
void GE_shootMove(struct GameEngine * this);
uint8 GE_isDead(struct GameEngine * this, uint8 ID);
uint8 hitCheck(struct graph_object * p1, struct graph_object * p2);

int16 GE_spawn(struct GameEngine * this, char * name, int8 teamID, int16 killpoints, int16 X, int16 Y, int8 lives) //return subject ID if -1 wrong name, -2 subject limit.
{
    int ID, ptr;

    ID = -1;
    
    
    for(ptr = 0; ptr < subjectLimit; ptr++)
    {
        if(this->subjects_[ptr] == NULL)
        {
            ID = ptr;   
            break;
        }
    }
    
    if(ID == -1)
        return -2;
    
    
    this->subjects_[ID] = this->factory_->creat(this->factory_, name, X, Y, lives, killpoints, ID, teamID);
    
    if(this->subjects_[ID] == NULL)
        return -1;
    
    return ID;
}

int8 GE_move(struct GameEngine * this, uint8 ID, int16 X, int16 Y, char relativ)
{
    if(this->subjects_[ID] == NULL)
        return -2;
    
    //if(relativ == 1)
        //return -2;
    
    if(this->subjects_[ID]->lives_ == 0)
        return -1;
    
    //this->subjects_[ID]->move(&this->subjects_[ID], X, Y);
    if(relativ == 0)
    {
        this->subjects_[ID]->X_ = X;
        this->subjects_[ID]->Y_ = Y;
    }
    else
    {
        this->subjects_[ID]->X_ += X;
        this->subjects_[ID]->Y_ += Y;
    }
    return 1;
}


struct coord GE_getPos(struct GameEngine * this, uint8 ID)
{
    struct coord c;
    
    if(this->subjects_[ID] == NULL)
    {
        c.X = 0;
        c.Y = 0;
        return c;
    }
    c.X = this->subjects_[ID]->X_;
    c.Y = this->subjects_[ID]->Y_;
    
    return c;
    
}

uint8 GE_isDead(struct GameEngine * this, uint8 ID)
{
    if(this->subjects_[ID] == NULL)
        return 1;
    
    return 0;
}

int8 GE_shoot(struct GameEngine * this, uint8 ID, int8 dir, char * type, uint8 speed)
{
    int8 index, ptr;
    struct coord c;
    ptr = -1;
    if(this->subjects_[ID] == NULL)
        return -1;
    
    //if(this->shootSize_ >= shootsInAirLimit)
        //return -1;
    
    for(index = 0; index < shootsInAirLimit; index++)
    {
        if(this->shoots_[index] == NULL)
        {
            ptr = index;
            break;
        }
    }
    
    if(ptr == -1)
        return -1;
    
    
    
    c = GE_getPos(this, ID);
    
    c.X += this->subjects_[ID]->graph_.pos_.size_X_ / 2;
    c.Y += this->subjects_[ID]->graph_.pos_.size_Y_ / 2;
    
    switch(dir)
    {
        case UP:
        c.X -= this->subjects_[ID]->graph_.pos_.size_X_ / 2;
        break;
        case DOWN:
        c.X += this->subjects_[ID]->graph_.pos_.size_X_ / 2;
        break;
        case LEFT:
        c.Y += this->subjects_[ID]->graph_.pos_.size_Y_ / 2;
        break;
        case RIGTH:
        c.Y -= this->subjects_[ID]->graph_.pos_.size_Y_ / 2;
        break;
        default:
            return -2;
        break;
    }
    
    
    
    this->shootDir_[ptr] = dir;
    this->shootSpeed_[ptr] = speed;
    
    this->shoots_[ptr] = this->factory_->creat(this->factory_, type, c.X, c.Y, 0, 0, 0, this->subjects_[ID]->TeamID_);
    
    if(this->shoots_[ptr] == NULL){}
        //while(1);
    
    return 1;
}

void GE_shootMove(struct GameEngine * this)
{
    uint8 i,i2;
    struct coord c;
    uint8 speed;
    
    for(i = 0; i < shootsInAirLimit; i++)
    {
        if(this->shoots_[i] != NULL)
        {
            c.X = this->shoots_[i]->X_;
            c.Y = this->shoots_[i]->Y_;
            if(c.X > SCREEN_SIZE_X || c.Y > SCREEN_SIZE_Y || c.X < 0 || c.Y < 0)
            {
                this->factory_->delete(this->factory_, this->shoots_[i]);
                this->shoots_[i] = NULL;
                
            }
            else
            {
                speed = this->shootSpeed_[i];
                switch(this->shootDir_[i])
                {
                    
                    case UP:
                    c.X -= speed;
                    break;
                    case DOWN:
                    c.X += speed;
                    break;
                    case LEFT:
                    c.Y += speed;
                    break;
                    case RIGTH:
                    c.Y -= speed;
                    break;
                    default:
                        
                    break;
                }  
                this->shoots_[i]->X_ = c.X;
                this->shoots_[i]->Y_ = c.Y;
                this->shoots_[i]->graph_.setPos(&this->shoots_[i]->graph_, c.X, c.Y);
                
                
                for(i2 = 0; i2 < subjectLimit; i2++)
                {
                    if(this->subjects_[i2] != NULL)
                    {
                        if(hitCheck(&this->shoots_[i]->graph_, &this->subjects_[i2]->graph_))
                        {
                            this->subjects_[i2]->graph_.refresh(&this->subjects_[i2]->graph_);
                            break;
                        }
                    }
                }
                
            }
        }
    }
}

void GE_updatePos(struct GameEngine * this)
{
    unsigned i;
    
    for(i = 0; i < subjectLimit; i++)
    {
        if(this->subjects_[i] != NULL)
        {
            if((this->subjects_[i]->X_ != this->subjects_[i]->graph_.getX(&this->subjects_[i]->graph_) || 
            this->subjects_[i]->Y_ != this->subjects_[i]->graph_.getY(&this->subjects_[i]->graph_)))
            {
                this->subjects_[i]->graph_.setPos(&this->subjects_[i]->graph_, this->subjects_[i]->X_, this->subjects_[i]->Y_); 
            }
        }
    }
}

uint8 hitCheck(struct graph_object * p1, struct graph_object * p2)
{
    uint16 x11, x12, y11, y12, 
    x21, x22, y21, y22;
    
    x11 = p1->pos_.pos_X_;
    x12 = p1->pos_.pos_X_ + p1->pos_.size_X_;
    y11 = p1->pos_.pos_Y_;
    y12 = p1->pos_.pos_Y_ + p1->pos_.size_Y_;
    
    x21 = p2->pos_.pos_X_;
    x22 = p2->pos_.pos_X_ + p2->pos_.size_X_;
    y21 = p2->pos_.pos_Y_;
    y22 = p2->pos_.pos_Y_ + p2->pos_.size_Y_;
    
    if(y21 <= y12 && y12 <= y22)
    {
        
        
        if((x21 <= x12 && x12 <= x22) || ((x21 <= x11 && x11 <= x22)))
        {
            return 1;
        }
    }
    else if(y21 <= y11 && y11 <= y22)
    {
        
        if((x21 <= x12 && x12 <= x22) || (x21 <= x11 && x11 <= x22))
        {
            return 1;
        }
    }
    return 0;
}

void GE_checkHit(struct GameEngine * this)
{
    
    unsigned i,i2;
    for(i = 0; i < shootsInAirLimit; i++)
    {
        if(this->shoots_[i] != NULL)
        {
            //this->shoots_[i]->graph_.getPos(&this->shoots_[i]->graph_);
            
            for(i2 = 0; i2 < subjectLimit; i2++)
            {
                if(this->subjects_[i2] != NULL)
                {
                    if(this->shoots_[i]->TeamID_ != this->subjects_[i2]->TeamID_)
                    {
                        if(hitCheck(&this->shoots_[i]->graph_, &this->subjects_[i2]->graph_))
                        {
                            if(this->subjects_[i2]->lives_ != 0)
                            {
                                this->subjects_[i2]->lives_--;
                                
                                this->factory_->delete(this->factory_, this->shoots_[i]);
                                this->shoots_[i] = NULL;
                                
                                
                                if(this->subjects_[i2]->lives_ == 0)
                                {
                                    this->points +=  this->subjects_[i2]->killPoints_;
                                    this->factory_->delete( this->factory_, this->subjects_[i2]);
                                    this->subjects_[i2] = NULL;
                                }
                                
                            }
                        }
                    }
                }
            }
        }
    }
    
    
}

int8 GE_tick(struct GameEngine * this)
{
    GE_checkHit(this);
    GE_updatePos(this);
    GE_shootMove(this);
    return 1;
}



void GameEngine_init(struct GameEngine * this, struct SubjectFactory * factory)
{
    uint8 i;
    this->factory_ = factory;
    
    this->getPos = GE_getPos;
    this->move = GE_move;
    this->shoot = GE_shoot;
    this->spawn = GE_spawn;
    this->tick = GE_tick;
    this->isDead = GE_isDead;
    
    
    
    
    for(i = 0; i < subjectLimit; i++)
    {
        this->subjects_[i] = NULL;
    }
    
    for(i = 0; i < shootsInAirLimit; i++)
    {
        this->shoots_[i] = NULL;
    }
}

/* [] END OF FILE */
