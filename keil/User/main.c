#include "reg52.h"
#include "stdlib.h"

#include "public.h"

#include "beep.h"
#include "key_fun.h"
#include "lcd1602.h"
#include "key_matrix.h"

//�Ƿ��ڼ������״̬
u8 i,is_calculate=0;
int count_array_value[8]={0};
char count_array_symbol[11]={' '};
//��������±�
u8 key=0;
//���ܼ�
u8 key_fun=0;
//��������б�
u8 gsmg_code[16]={'7','8','9','/','4','5','6','*',
				'1','2','3','-','0','.','=','+'};
//lcd��һ����ʾ����
u8 lcd0_show[17]={' ',' ',' ',' ',' ',' ',' ',' ',
				' ',' ',' ',' ',' ',' ',' ',' ','\0'};
/*
//lcd�ڶ�����ʾ����
u8 lcd1_show[17]={' ',' ',' ',' ',' ',' ',' ',' ',
				' ',' ',' ',' ',' ',' ',' ',' ','\0'};
*/

//��ȡ��ʾ����Ŀɲ���λ��		
int get_show_end(u8 show[]){
	for(i=0;i<16;i++){
		if(show[i]==' '){
			return i;
		}
	}
	return -1;
}
//ɾ��ĩβ����
void del_show_end(){
	i=get_show_end(lcd0_show);
	if(i>0){
		lcd0_show[i-1]=' ';
	}
	lcd1602_show_string(0, 0, lcd0_show);
}
//����
void reset_show(){
	for(i=0;i<16;i++){
		lcd0_show[i]=' ';
	}
	is_calculate=0;
	lcd1602_show_string(0, 0, lcd0_show);
	lcd1602_show_string(0, 1, lcd0_show);
	beep_work(500);
}
//д�����
void write_error(){
	lcd1602_show_string(0, 1, "          ERROR!");
	beep_work(500);
}
//д��
void write_show(u8 write,u8 show[]){
	u8 write_site=get_show_end(show);
	if(write=='*'||write=='/'){
		if(write_site==0||show[write_site-1]=='('){
			beep_work(500);
		}else if(show[write_site-1]=='+'||show[write_site-1]=='-'
		||show[write_site-1]=='*'||show[write_site-1]=='/'){
			show[write_site-1]=write;
		}else{
			show[write_site]=write;
		}
	}else if(write=='-'){
		if(write_site==0){
			show[write_site]=write;
		}else if(show[write_site-1]=='+'){
			show[write_site-1]=write;
		}else if(show[write_site-1]=='-'){
			beep_work(500);
		}else{
			show[write_site]=write;
		}
	}else if(write=='+'){
		if(write_site==0||show[write_site-1]=='('){
			beep_work(500);
		}else if(show[write_site-1]=='*'||show[write_site-1]=='/'||show[write_site-1]=='+'){
			show[write_site-1]=write;
		}else if(show[write_site-1]=='-'){
			if(show[write_site-2]=='+'||show[write_site-2]=='-'
		||show[write_site-2]=='*'||show[write_site-2]=='/'||show[write_site-2]=='('){
				beep_work(500);
			}else{
				show[write_site-1]=write;
			}
		}else{
			show[write_site]=write;
		}
	}else if(write=='('){
		if(write_site==0){
			show[write_site]=write;
		}else if(show[write_site-1]=='+'||show[write_site-1]=='-'
		||show[write_site-1]=='*'||show[write_site-1]=='/'){
			show[write_site]=write;
		}else{
			beep_work(500);
		}
	}else if(write==')'){
		if(write_site==0){
			beep_work(500);
		}else if(show[write_site-1]=='+'||show[write_site-1]=='-'
		||show[write_site-1]=='*'||show[write_site-1]=='/'){
			beep_work(500);
		}else{
			show[write_site]=write;
		}
	}else if(write=='.'){
	
	
	}else{
		if(show[write_site-1]==')'){
			beep_work(500);
		}else{
			show[write_site]=write;
		}
	}
	return;
}
//intתchar
char* Int_to_String(int num,char *str){
	int i = 0; 
	int j = 0;
	if(num<0)
	{
		num = -num;
		str[i++] = '-';
	} 
	do
	{
		str[i++] = num%10+'0';
		num /= 10;
	}while(num);
	
	str[i] = '\0';
	
	if(str[0]=='-')
	{
		j = 1;
		++i;
	}
	for(;j<i/2;j++)
	{
		str[j] = str[j] + str[i-1-j];
		str[i-1-j] = str[j] - str[i-1-j];
		str[j] = str[j] - str[i-1-j];
	} 
	
	return str;//??????? 
}

//charתint
int String_to_Int(const char *str,char **s){
	char flag = '+';//????????? 
	long res = 0;
	
	if(*str=='-')//?????? 
	{
		++str;//??????? 
		flag = '-';//??????? 
	} 
	//??????,??????res 
	while(*str>='0' && *str<='9')//??????????,??0~9?ASCII?:48~57 
	{
		res = 10*res+  *str++ - '0';//??'0'?ASCII??48,48-48=0???????0 
	} 
 
    if(flag == '-')//????????
	{
		res = -res;
	}
	*s=str;
	return (int)res;
}

//������
u8 find_bracket(u8 j){
	for(;j>=0;j--){
		if(count_array_symbol[j]=='('){
			return j;
		}
	}
	return (u8)11;
}

//����
u8 calculate(u8 j,u8 z){
	u8 show[5]={" "};
	//Int_to_String(j,show);
	//lcd1602_show_string(9, 0, show);
	//lcd1602_show_string(10, 0, count_array_symbol);
	switch(count_array_symbol[j]){
		case '+':
			//lcd1602_show_string(10, 0, "+");
			//Int_to_String(count_array_value[z-1],show);
			//lcd1602_show_string(10, 0, show);
			count_array_value[z-1]=count_array_value[z-1]+count_array_value[z];
			//Int_to_String(count_array_value[z-1],show);
			//lcd1602_show_string(10, 0, show);
			count_array_symbol[j]=' ';
			break;
		case '-':
			count_array_value[z-1]=count_array_value[z-1]-count_array_value[z];
			count_array_symbol[z]=' ';
			break;
		case '*':
			//lcd1602_show_string(10, 0, "*");
			count_array_value[z-1]=count_array_value[z-1]*count_array_value[z];
			count_array_symbol[z]=' ';
			break;
		case '/':
			count_array_value[z-1]=count_array_value[i-1]/count_array_value[z];
			count_array_symbol[z]=' ';
			break;
		default:
			write_error();
			return;
	}
	return j;
}
//�����㷨
void post_Poland(){
	char show[16]={' '};
	u8 j=0,z=0,p=0,f=0,*show_subscript=&lcd0_show[0];

	show[15]='\0';
	
	for(;show_subscript!=&lcd0_show[get_show_end(lcd0_show)];){
		if(*show_subscript=='+'||*show_subscript=='*'||*show_subscript=='/'
		||*show_subscript=='('||*show_subscript==')'){
		
		}else{
			count_array_value[z++]=String_to_Int(show_subscript,&show_subscript);
		}
		
		
		//Int_to_String(z,show);
		//lcd1602_show_string(1, 0, show);
		
		
		if(show_subscript==&lcd0_show[get_show_end(lcd0_show)]){
			//lcd1602_show_string(10, 0, "<");
			//lcd1602_show_string(10, 0, count_array_symbol);
			for(;j!=0;){
				
				//lcd1602_show_string(10, 0, "<");
				j=calculate(j-1,--z);
			}
			//lcd1602_show_string(10, 0, "P");
			
			break;
		}
		
		for(;*show_subscript=='+'||*show_subscript=='-'||*show_subscript=='*'
		||*show_subscript=='/'||*show_subscript=='('||*show_subscript==')';){

			if(j==0){
				if(*show_subscript=='('){
					p++;
				}else if(*show_subscript==')'){
					write_error();
					return;
				}
				//Int_to_String(j,show);
				//lcd1602_show_string(8, 0, show);
				//lcd1602_show_string(8, 0, show_subscript);
				count_array_symbol[j++]=*show_subscript++;
				//lcd1602_show_string(10, 0, "P");
				//lcd1602_show_string(10, 0, count_array_symbol);
			}else if(count_array_symbol[j-1]=='('){
				if(*show_subscript=='('){
					p++;
				}else if(*show_subscript==')'){
					write_error();
					return;
				}
				count_array_symbol[j++]=*show_subscript++;
			}else if(*show_subscript=='+'||*show_subscript=='-'){
				if(p){
					f=find_bracket(j);
					for(;j!=f+1;){
						j=calculate(j-1,--z);
					}
				}else{
					for(;j!=0;){
						j=calculate(j-1,--z);
					}
				}
				count_array_symbol[j++]=*show_subscript++;
			}else if(*show_subscript=='*'||*show_subscript=='/'){
				if(p){
					f=find_bracket(j);
					for(;j!=f+1;){
						if(count_array_symbol[j-1]=='+'||count_array_symbol[j-1]=='+'){
							
							break;
						}
						j=calculate(j-1,--z);
					}
				}else{
					for(;j!=0;){
						//lcd1602_show_string(10, 0, count_array_symbol);
						if(count_array_symbol[j-1]=='+'||count_array_symbol[j-1]=='-'){
							//lcd1602_show_string(10, 0, "*");
							break;
						}
						j=calculate(j-1,--z);
					}
				}
				//lcd1602_show_string(10, 0, "*");
				count_array_symbol[j++]=*show_subscript++;
			}else if(*show_subscript=='('){
				if(*show_subscript=='('){
					p++;
				}else if(*show_subscript==')'){
					write_error();
					return;
				}
				count_array_symbol[j++]=*show_subscript++;
			}else if(*show_subscript==')'){
				if(p){
					//lcd1602_show_string(10, 0, ")");
					p--;
					f=find_bracket(j);
	
					//Int_to_String(f,show);
					//lcd1602_show_string(8, 0, show);
					//Int_to_String(j,show);
					//lcd1602_show_string(9, 0, show);
	
					for(;j!=f+1;){
						j=calculate(j-1,--z);
					}
					
					//Int_to_String(count_array_value[z],show);
					//lcd1602_show_string(10, 0, show);

					--j;
					//Int_to_String(j,show);
					//lcd1602_show_string(10, 0, show);
					//Int_to_String(z,show);
					//lcd1602_show_string(9, 0, show);
					count_array_symbol[j]=' ';
					show_subscript++;
				}else{
					write_error();
					return;
				}
			}
			
			//show_subscript++;
		}
		
		
		
		if(show_subscript==&lcd0_show[get_show_end(lcd0_show)]){
			//lcd1602_show_string(10, 0, "<");
			//lcd1602_show_string(10, 0, count_array_symbol);
			for(;j!=0;){
				
				//lcd1602_show_string(10, 0, "<");
				j=calculate(j-1,--z);
			}
			//lcd1602_show_string(10, 0, "P");
			
			break;
		}
		
	}
	
	
	//count_array_value[0]=String_to_Int(show_subscript,&show_subscript);
	//show_subscript++;
	//lcd1602_show_string(1, 1, show_subscript);
	
	
	Int_to_String(count_array_value[0],show);
	lcd1602_show_string(0, 1, "=");
	lcd1602_show_string(1, 1, show);
	
}
//���㿪ʼ
void evaluation(){
	int left_bracket_count=0,right_bracket_count=0;
	is_calculate=1;
	if(lcd0_show[get_show_end(lcd0_show)-1]=='+'||lcd0_show[get_show_end(lcd0_show)-1]=='-'||lcd0_show[get_show_end(lcd0_show)-1]=='*'
		||lcd0_show[get_show_end(lcd0_show)-1]=='/'||lcd0_show[get_show_end(lcd0_show)-1]=='('){
		write_error();
		lcd1602_show_string(0, 1, "1^");
		return;
	}
	for(i=0;i<16;i++){
		if(lcd0_show[i]=='('){
			left_bracket_count++;
		}else if(lcd0_show[i]==')'){
			right_bracket_count++;
		}
	}
	if(left_bracket_count!=right_bracket_count){
		write_error();
		return;
	}
	post_Poland();
}

//������
void main()
{
	lcd1602_init();	// LCD1602��ʼ��
	
	while(1)
	{
		//��ȡ��ť����
		key_fun = key_scan(0);
		key=key_matrix_ranks_scan();
		//�ж��Ƿ��ڼ�����ɵ�״̬
		if(is_calculate){
			//���ð�ť������
			if(key_fun==KEY_RESET_PRESS){
				reset_show();
			}
		}else{
			//�жϹ��ܼ��Ƿ񱻰���
			switch(key_fun){
				//���ð�ť������
				case KEY_RESET_PRESS:
					reset_show();
					break;
				//ɾ��
				case KEY_DELETE_PRESS:
					del_show_end();
					break; 
				//������
				case KEY_LEFT_BRACKET_PRESS:
					write_show('(',lcd0_show);
					lcd1602_show_string(0, 0, lcd0_show);
					break;
				//������
				case KEY_RIGHT_BRACKET_PRESS:
					write_show(')',lcd0_show);
					lcd1602_show_string(0, 0, lcd0_show);
					break;
			}
			//�ж��Ƿ��в�Ϊ=������
			if(key!=0&&key!=15){
				write_show(gsmg_code[key-1],lcd0_show);
				lcd1602_show_string(0, 0, lcd0_show);
			}else if(key==15){
				evaluation();
			}
		}	
	}
}
