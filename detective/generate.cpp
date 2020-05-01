#include "generate.h"

static SELECTION gen_Result[QUEST_NUM];
bool gen_InitSt = false;

/*********************************************************************
Function       :GEN_Init
Description    :生成器模块初始化
Parameters     :none
Returns        :none
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
void GEN_Init(void)
{
	int Index = 0;

	for (Index = QUEST_1; Index < QUEST_NUM; Index++)
	{
		gen_Result[Index] = A;
	}
	gen_InitSt = true;
}

/*********************************************************************
Function       :GEN_Next
Description    :生成下一个序列
Parameters     :none
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
bool GEN_Next(void)
{
	bool funResult;

	if (true == gen_InitSt)
	{
		/* 生成下一个序列数 */
		gen_Result[QUEST_NUM - 1] = (SELECTION)(gen_Result[QUEST_NUM - 1] + 1);
		for (int index = QUEST_NUM - 1; index > QUEST_1; index--)
		{
			if (gen_Result[index] == ANSWER_NUM)
			{
				gen_Result[index] = A;
				gen_Result[index - 1] = (SELECTION)(gen_Result[index - 1] + 1);
			}
		}

		/* 判断是否到末尾 */
		if (gen_Result[QUEST_1] == ANSWER_NUM)
		{
			GEN_Init();
			funResult = false;
		}
		else
		{
			funResult = true;
		}
	}
	else
	{
		funResult = false;
	}
	return(funResult);
}

/*********************************************************************
Function       :GEN_GetSequence
Description    :获取当前序列
Parameters     :none
Returns        :const SELECTION*
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
const SELECTION* GEN_GetSequence(void)
{
	return (gen_Result);
}