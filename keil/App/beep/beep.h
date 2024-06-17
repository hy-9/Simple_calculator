#ifndef _BEEP_H
#define _BEEP_H

#include "public.h"

sbit BEEP=P2^5;	//将P2.5管脚定义为BEEP



void beep_work(u16 beep_time);

#endif