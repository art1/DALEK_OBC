/**
 * \file    UsbphyGS70.c
 *
 * \brief   This file contains AM335x USB Phy  related functions.
 *
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "hw_types.h"
#include "soc_AM335x.h"    
#include "hw_usbphyGS70.h"
//#include "usblib.h"
#include "hw_usb.h"
#include "debug.h"

//*****************************************************************************
//
// USB instance Object
//
//*****************************************************************************
//extern tUSBInstanceObject g_USBInstance[];


/**
 * \brief This function will switch on the USB Phy  
 *          
 *
 * \param    None
 *
 * \return   None
 *
  **/
void UsbPhyOn(unsigned int ulIndex)
{
  // No Usb Support right now
}


/**
 * \brief This function will switch off  the USB Phy  
 *          
 *
 * \param    None
 *
 * \return   None
 *
  **/
void UsbPhyOff(unsigned int ulIndex)
{
  // No Usb Support Right now
}

