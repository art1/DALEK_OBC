

/*********************************************************** Copyright 
 **
 ** Copyright (c) 2008, German Aerospace Center (DLR)
 ** All rights reserved.
 ** 
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 ** 
 ** 1 Redistributions of source code must retain the above copyright
 **   notice, this list of conditions and the following disclaimer.
 ** 
 ** 2 Redistributions in binary form must reproduce the above copyright
 **   notice, this list of conditions and the following disclaimer in the
 **   documentation and/or other materials provided with the
 **   distribution.
 ** 
 ** 3 Neither the name of the German Aerospace Center nor the names of
 **   its contributors may be used to endorse or promote products derived
 **   from this software without specific prior written permission.
 ** 
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **  
 ****************************************************************************/

/**
 * @file hw_uart.cc
 */


#include "thread.h"
#include <string.h>
#include "hw_uart.h"

//#include "rodos.h"


#ifndef NO_RODOS_NAMESPACE
namespace RODOS {
#endif

//HAL_UART* uarts[3] = {&uart1,&uart2,&uart3};


UART::UART(int uart_num):
		hal_uart((UART_IDX)uart_num)
{


}

UART::~UART() 
{
}


//put character on UART-line
void UART::writechar(const char c)  // SergioM
{
	while(hal_uart.isWriteFinished() == false) {}  // TW+ ED
	hal_uart.putcharNoWait(c);
}

//check for incoming message
bool UART::isCharReady() 
{

	return false;
}

//read a char. from UART-RxFiFo
bool UART::getcharNoWait(char &c) 
{

	return false;
}

//compatibility purpose to putter
bool UART::putGeneric(const unsigned int len, const void* msg) 
{

	return false;
}

#ifndef NO_RODOS_NAMESPACE
}
#endif

