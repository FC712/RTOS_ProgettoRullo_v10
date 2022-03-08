/** ****************************************************************************************
* @file Mot.h
* @brief 
* 
* @author Crippa
* @date 11/02/22
* @version 1.0 - 11/02/22 - Versione iniziale. 
* 
* @section LICENSE
* Open Source Licensing 
* This program is free software: you can redistribute it and/or modify it under the terms 
* of the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or (at your option) any later version.
* This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
* withouteven the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* You should have received a copy of the GNU General Public License along with this
* program. If not, see(http://www.gnu.org/licenses/).
*/

#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

void vTask_Motore(void * pvParameters);
void vTaskMotPA0(void * pvParameters);
void vTaskMotPA2(void * pvParameters);
void motInit(void);
void motStop(void);
void motStart(void);

