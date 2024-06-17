#ifndef _Key_Fun_H
#define _Key_Fun_H

#include "public.h"


// 管脚定义
sbit KEY_RESET = P3 ^ 1;
sbit KEY_DELETE = P3 ^ 0;
sbit KEY_LEFT_BRACKET = P3 ^ 2;
sbit KEY_RIGHT_BRACKET = P3 ^ 3;

#define KEY_RESET_PRESS 1
#define KEY_DELETE_PRESS 2
#define KEY_LEFT_BRACKET_PRESS 3
#define KEY_RIGHT_BRACKET_PRESS 4
#define KEY_UNPRESS 0

// 函数声明
u8 key_scan(u8 mode);

#endif