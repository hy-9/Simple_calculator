#include "key_fun.h"

/*******************************************************************************
* �� �� ��       : key_scan
* ��������		 : �����������Ƿ��£������򷵻ض�Ӧ��ֵ
* ��    ��       : mode=0������ɨ�谴��
				   mode=1������ɨ�谴��
* ��    ��    	 : KEY_RESET_PRESS��K1����
				   KEY_DELETE_PRESS��K2����
				   KEY_LEFT_BRACKET_PRESS��K3����
				   KEY_RIGHT_BRACKET_PRESS��K4����
				   KEY_UNPRESS��δ�а�������
*******************************************************************************/
u8 key_scan(u8 mode)
{
	static u8 key = 1;

	if (mode)
		key = 1;														// ����ɨ�谴��
	if (key == 1 && (KEY_RESET == 0 || KEY_DELETE == 0 || KEY_LEFT_BRACKET == 0 || KEY_RIGHT_BRACKET == 0)) // ���ⰴ������
	{
		delay_10us(1000); // ����
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
	else if (KEY_RESET == 1 && KEY_DELETE == 1 && KEY_LEFT_BRACKET == 1 && KEY_RIGHT_BRACKET == 1) // �ް�������
	{
		key = 1;
	}
	return KEY_UNPRESS;
}