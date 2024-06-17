#include "key_fun.h"

/*******************************************************************************
* 函 数 名       : key_scan
* 函数功能		 : 检测独立按键是否按下，按下则返回对应键值
* 输    入       : mode=0：单次扫描按键
				   mode=1：连续扫描按键
* 输    出    	 : KEY_RESET_PRESS：K1按下
				   KEY_DELETE_PRESS：K2按下
				   KEY_LEFT_BRACKET_PRESS：K3按下
				   KEY_RIGHT_BRACKET_PRESS：K4按下
				   KEY_UNPRESS：未有按键按下
*******************************************************************************/
u8 key_scan(u8 mode)
{
	static u8 key = 1;

	if (mode)
		key = 1;														// 连续扫描按键
	if (key == 1 && (KEY_RESET == 0 || KEY_DELETE == 0 || KEY_LEFT_BRACKET == 0 || KEY_RIGHT_BRACKET == 0)) // 任意按键按下
	{
		delay_10us(1000); // 消抖
		key = 0;
		if (KEY_RESET == 0)
			return KEY_RESET_PRESS;
		else if (KEY_DELETE == 0)
			return KEY_DELETE_PRESS;
		else if (KEY_LEFT_BRACKET == 0)
			return KEY_LEFT_BRACKET_PRESS;
		else if (KEY_RIGHT_BRACKET == 0)
			return KEY_RIGHT_BRACKET_PRESS;
	}
	else if (KEY_RESET == 1 && KEY_DELETE == 1 && KEY_LEFT_BRACKET == 1 && KEY_RIGHT_BRACKET == 1) // 无按键按下
	{
		key = 1;
	}
	return KEY_UNPRESS;
}