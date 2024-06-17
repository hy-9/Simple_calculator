#include "beep.h"

void beep_work(u16 beep_time){
	while(beep_time--)//循环2000次
		{
			BEEP=!BEEP;//产生一定频率的脉冲信号
			delay_10us(100);
		}
		BEEP=0;//关闭蜂鸣器
}