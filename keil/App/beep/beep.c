#include "beep.h"

void beep_work(u16 beep_time){
	while(beep_time--)//ѭ��2000��
		{
			BEEP=!BEEP;//����һ��Ƶ�ʵ������ź�
			delay_10us(100);
		}
		BEEP=0;//�رշ�����
}