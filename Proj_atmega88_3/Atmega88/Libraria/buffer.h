/******************************************************************************
	BUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 17112022
Comment:
	Circular Buffer
*******************************************************************************/
#ifndef _BUFFER_H_
	#define _BUFFER_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#define BUFFvar char

/*** Global Variable ***/
struct bufferposition
{
	BUFFvar* orig;
	BUFFvar* head;
	BUFFvar* end;
};

struct buffer
{
	struct bufferposition pos;
	void (*push)(struct buffer* self, BUFFvar data);
	BUFFvar* (*raw)(struct buffer* self);
	void (*flush)(struct buffer* self);
};

typedef struct buffer BUFF;

/*** Global Header ***/
BUFF BUFFenable(uint8_t size_buff, BUFFvar* buff);

#endif
/***EOF***/

