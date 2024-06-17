#include "key_matrix.h"


/*******************************************************************************
* �� �� ��       : key_matrix_ranks_scan
* ��������		 : ʹ������ʽɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
* ��    ��       : ��
* ��    ��    	 : key_value��1-16����ӦS1-S16����
				   0������δ����
*******************************************************************************/
u8 key_matrix_ranks_scan(void)
{
	u8 key_value=0;

	P1=0xf7;//����һ�и�ֵ0������ȫΪ1
	if(P1!=0xf7)//�жϵ�һ�а����Ƿ���
	{
		delay_10us(1000);//����
		switch(P1)//�����һ�а������º�ļ�ֵ	
		{
			case 0x77: key_value=1;break;
			case 0xb7: key_value=5;break;
			case 0xd7: key_value=9;break;
			case 0xe7: key_value=13;break;
		}
	}
	while(P1!=0xf7);//�ȴ������ɿ�	
	
	P1=0xfb;//���ڶ��и�ֵ0������ȫΪ1
	if(P1!=0xfb)//�жϵڶ��а����Ƿ���
	{
		delay_10us(1000);//����
		switch(P1)//����ڶ��а������º�ļ�ֵ	
		{
			case 0x7b: key_value=2;break;
			case 0xbb: key_value=6;break;
			case 0xdb: key_value=10;break;
			case 0xeb: key_value=14;break;
		}
	}
	while(P1!=0xfb);//�ȴ������ɿ�	
	
	P1=0xfd;//�������и�ֵ0������ȫΪ1
	if(P1!=0xfd)//�жϵ����а����Ƿ���
	{
		delay_10us(1000);//����
		switch(P1)//��������а������º�ļ�ֵ	
		{
			case 0x7d: key_value=3;break;
			case 0xbd: key_value=7;break;
			case 0xdd: key_value=11;break;
			case 0xed: key_value=15;break;
		}
	}
	while(P1!=0xfd);//�ȴ������ɿ�	
	
	P1=0xfe;//�������и�ֵ0������ȫΪ1
	if(P1!=0xfe)//�жϵ����а����Ƿ���
	{
		delay_10us(1000);//����
		switch(P1)//��������а������º�ļ�ֵ	
		{
			case 0x7e: key_value=4;break;
			case 0xbe: key_value=8;break;
			case 0xde: key_value=12;break;
			case 0xee: key_value=16;break;
		}
	}
	while(P1!=0xfe);//�ȴ������ɿ�
	
	return key_value;		
}

/*******************************************************************************
* �� �� ��       : key_matrix_flip_scan
* ��������		 : ʹ���߷�תɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
* ��    ��       : ��
* ��    ��    	 : key_value��1-16����ӦS1-S16����
				   0������δ����
*******************************************************************************/
/*
u8 key_matrix_flip_scan(void)
{
	static u8 key_value=0;

	P1=0x0f;//�������и�ֵ0����ȫΪ1
	if(P1!=0x0f)//�жϰ����Ƿ���
	{
		delay_10us(1000);//����
		if(P1!=0x0f)
		{
			//������
			P1=0x0f;
			switch(P1)//������Ϊ0���������º����ֵ	
			{
				case 0x07: key_value=1;break;
				case 0x0b: key_value=2;break;
				case 0x0d: key_value=3;break;
				case 0x0e: key_value=4;break;
			}
			//������
			P1=0xf0;
			switch(P1)//������Ϊ0���������º�ļ�ֵ	
			{
				case 0x70: key_value=key_value;break;
				case 0xb0: key_value=key_value+4;break;
				case 0xd0: key_value=key_value+8;break;
				case 0xe0: key_value=key_value+12;break;
			}
			while(P1!=0xf0);//�ȴ������ɿ�	
		}
	}
	else
		key_value=0;		
	
	return key_value;		
}
*/