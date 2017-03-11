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
#ifndef EEPROM_H
    #define EEPROM_H
#include <project.h>

    #define EEPROM_MAXSIZE 2
    
char EEPROM_read(uint8 id, uint8 * data);
char EEPROM_write(uint8 id, const uint8 * data);
char EEPROM_init(const size_t * types, uint8 count);

#endif
/* [] END OF FILE */
