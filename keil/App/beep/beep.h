#ifndef _BEEP_H
#define _BEEP_H

#include "public.h"

sbit BEEP=P2^5;	//��P2.5�ܽŶ���ΪBEEP



void beep_work(u16 beep_time);

#endif