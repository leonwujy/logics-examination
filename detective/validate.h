#ifndef __VALIDATE_H__
#define __VALIDATE_H__

#define ASCII_BIAS 65
#define QUEST_BIAS 1
#define INIT_MIN 0xFFFF

#include <iostream>

/*选项枚举*/
enum SELECTION
{
	A,
	B,
	C,
	D,
	ANSWER_NUM
};

/*题目枚举*/
enum QUEST_INDEX
{
	QUEST_1,
	QUEST_2,
	QUEST_3,
	QUEST_4,
	QUEST_5,
	QUEST_6,
	QUEST_7,
	QUEST_8,
	QUEST_9,
	QUEST_10,
	QUEST_NUM
};

/* 各题验证结果 */
enum VAL_RESULT
{
	PASS,
	FAIL,
	NOT_STRICT
};

/* 打印开关 */
enum PRINT_SW
{
	PRINT_ON,
	PRINT_OFF
};

/* 数值类型 */
enum COUNT_TYPE
{
	COUNT_S,
	COUNT_NS,
	COUNT_TOTAL
};

void VAL_Init(void);
void VAL_Validate(const SELECTION* result,PRINT_SW print);
long unsigned int VAL_GetCountNumber(COUNT_TYPE CountType);

VAL_RESULT val_Question1(const SELECTION* result);
VAL_RESULT val_Question2(const SELECTION* result);
VAL_RESULT val_Question3(const SELECTION* result);
VAL_RESULT val_Question4(const SELECTION* result);
VAL_RESULT val_Question5(const SELECTION* result);
VAL_RESULT val_Question6(const SELECTION* result);
VAL_RESULT val_Question7(const SELECTION* result);
VAL_RESULT val_Question8(const SELECTION* result);
VAL_RESULT val_Question9(const SELECTION* result);
VAL_RESULT val_Question10(const SELECTION* result);

/* 函数指针数组 */
static VAL_RESULT(*val_Pf[QUEST_NUM])(const SELECTION*) =
{
	val_Question1,
	val_Question2,
	val_Question3,
	val_Question4,
	val_Question5,
	val_Question6,
	val_Question7,
	val_Question8,
	val_Question9,	
	val_Question10
};

#endif
