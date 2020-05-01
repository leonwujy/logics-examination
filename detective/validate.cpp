#include "validate.h"

static SELECTION result[QUEST_NUM];
static long unsigned int val_countS, val_countNS, val_countTotal;

/*********************************************************************
Function       :VAL_Init
Description    :验证器模块初始化
Parameters     :none
Returns        :none
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
void VAL_Init(void)
{
	/*初始化各计数器*/
	val_countS = 0;        /*严格解数量*/
	val_countNS = 0;       /*非严格解数量*/
	val_countTotal = 0;    /*共计数量*/

	/*通过输入的方式设定各题的选项*/
	//TBD
}

/*********************************************************************
Function       :VAL_Validate
Description    :执行验证并打印
Parameters     :const SELECTION* result, PRINT_SW print
Returns        :none
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
void VAL_Validate(const SELECTION* result, PRINT_SW print)
{
	VAL_RESULT valResult[QUEST_NUM];
	int qCount_S = 0, qCount_NS = 0;

	/* 执行所有题目的验证器 */
	for (int Index = QUEST_1; Index < QUEST_NUM; Index++)
	{
		valResult[Index] = val_Pf[Index](result);
		if (PASS == valResult[Index])
		{
			qCount_S++;
		}
		else if (NOT_STRICT == valResult[Index])
		{
			qCount_NS++;
		}
		else
		{
			/* do nothing */
		}
	}

	/*判断是否严格有效*/
	if ((qCount_S == QUEST_NUM) && (qCount_S + qCount_NS == QUEST_NUM))
	{
		val_countS++;

		if (PRINT_ON == print)
		{
			printf("-----------------------------------------\n");
			printf("题目序号: 1,2,3,4,5,6,7,8,9,X\n");
			printf(" 严格解 : ");
			for (int i = QUEST_1; i < QUEST_NUM; i++)
			{
				printf("%c,", ASCII_BIAS + result[i]);
			}
			printf("\b \n-----------------------------------------\n");
		}
		else
		{
			/* do nothing */
		}
	}
	/* 非严格解 */
	else if ((qCount_NS <= QUEST_BIAS) && (qCount_S + qCount_NS == QUEST_NUM))
	{
		val_countNS++;

		if (PRINT_ON == print)
		{
			printf("-----------------------------------------\n");
			printf("题目序号: 1,2,3,4,5,6,7,8,9,X\n");
			printf("非严格解: ");
			for (int i = QUEST_1; i < QUEST_NUM; i++)
			{
				printf("%c,", ASCII_BIAS + result[i]);
			}
			printf("\b \n");

			printf("各题情况: ");
			for (int i = QUEST_1; i < QUEST_NUM; i++)
			{
				switch (valResult[i])
				{
				case PASS:
					printf("P,");
					break;
				case FAIL:
					printf("F,");
					break;
				case NOT_STRICT:
					printf("N,");
					break;
				default:
					printf("-,");
				}	
			}
			printf("\b \n-----------------------------------------\n");
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}
	val_countTotal++;
}

/*********************************************************************
Function       :VAL_GetCountNumber
Description    :获取统计数值
Parameters     :COUNT_TYPE CountType
Returns        :long unsigned int 
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
long unsigned int VAL_GetCountNumber(COUNT_TYPE CountType)
{
	long unsigned int Value;
	
	switch (CountType)
	{
		case COUNT_S:
			Value = val_countS;
			break;
		case COUNT_NS:
			Value = val_countNS;
			break;
		case COUNT_TOTAL:
			Value = val_countTotal;
			break;
		default:
			Value = 0;
	}
	return(Value);
}


/*********************************************************************
Function       :val_Question1
Description    :验证问题1
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question1(const SELECTION* result)
{
	if (result[QUEST_1] < ANSWER_NUM)
	{
		return(PASS);
	}
	else
	{
		return(FAIL);
	}	
}

/*********************************************************************
Function       :val_Question2
Description    :验证问题2
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question2(const SELECTION* result)
{
	SELECTION qSelection[ANSWER_NUM] = { C, D, A, B };
	
	if (result[QUEST_5] == qSelection[result[QUEST_2]])
	{
		return(PASS);
	}
	else
	{
		return(FAIL);
	}
}

/*********************************************************************
Function       :val_Question3
Description    :验证问题3
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question3(const SELECTION* result)
{
	/* 由于是单选题，因此选项分布必须为三个相同，一个与其余三个不同 */
	QUEST_INDEX qContext[ANSWER_NUM] = { QUEST_3, QUEST_6, QUEST_2, QUEST_4 };
	SELECTION sameResult = ANSWER_NUM;
	VAL_RESULT funResult = PASS;

	/* 比较除被选项外的三个题的选项值是否一致 */
	for (int Index = A; Index < ANSWER_NUM; Index++)
	{
		if (Index != result[QUEST_3])
		{
			if (sameResult < ANSWER_NUM)
			{
				/* 比较值是否一致 */
				if (sameResult == result[qContext[Index]])
				{
					 /* do noting */
				}
				else
				{
					funResult = FAIL;
					break;
				}
			}
			else
			{
				sameResult = result[qContext[Index]];  /* 写入基准值 */
			}
		}
		else
		{
			 /* do nothing */
		}
	}

	 /* 检查被选项是否与其他三个值不同*/
	if (PASS == funResult)
	{
		if (sameResult != result[qContext[result[QUEST_3]]])
		{
			 /* do nothing */
		}
		else
		{
			funResult = FAIL;
		}
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question4
Description    :验证问题4
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question4(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM][2] = { {QUEST_1,QUEST_5},{QUEST_2,QUEST_7},{QUEST_1,QUEST_9},{QUEST_6,QUEST_10} };
	VAL_RESULT funResult = PASS;

	for (int Index = A; Index < ANSWER_NUM; Index++)
	{
		if (Index != result[QUEST_4]) /* 非被选项 */
		{
			if (result[qContext[Index][0]] != result[qContext[Index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = NOT_STRICT;
			}
		}
		else /* 是被选项 */
		{
			if (result[qContext[Index][0]] == result[qContext[Index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return (funResult);
}

/*********************************************************************
Function       :val_Question5
Description    :验证问题5
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question5(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM] = {QUEST_8, QUEST_4, QUEST_9, QUEST_7};
	VAL_RESULT funResult = PASS;

	for (int Index = A; Index < ANSWER_NUM; Index++)
	{
		 /* 除被选项外的三个选项应为假 */
		if (Index != result[QUEST_5]) /* 非被选项 */
		{
			 /* 判断是否为假 */
			if (result[qContext[Index]] != Index) /* 是假 */
			{
				 /* do nothing */
			}
			else
			{
				funResult = NOT_STRICT;
			}
		}
		else /* 被选项 */
		{
			 /* 判断是否为真 */
			if (result[qContext[Index]] == Index) /* 是真 */
			{
				 /* do nothing */
			}
			else
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return (funResult);
}

/*********************************************************************
Function       :val_Question6
Description    :验证问题6
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question6(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM][2] = { {QUEST_2,QUEST_4},{QUEST_1,QUEST_6},{QUEST_3,QUEST_10},{QUEST_5,QUEST_9} };
	VAL_RESULT funResult = PASS;

	for (int index = A; index < ANSWER_NUM; index++)
	{
		if (index != result[QUEST_6]) /* 不是被选项 */
		{
			if ((index != result[qContext[index][0]])
				|| index != result[qContext[index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = NOT_STRICT;
			}
		}
		else /* 是被选项 */
		{
			if ((index != result[qContext[index][0]])
				&& index != result[qContext[index][1]])
			{
				 /* do nothing */
			}
			else
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question7
Description    :验证问题7
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question7(const SELECTION* result)
{
	int min = INIT_MIN;
	int selectedCount[ANSWER_NUM] = { 0,0,0,0 };
	SELECTION qSelection[ANSWER_NUM] = {C,B,A,D};
	VAL_RESULT funResult = PASS;
	
	 /* 统计被选次数 */
	for (int index = QUEST_1; index < QUEST_NUM; index++)
	{
		selectedCount[result[index]]++;
	}

	 /* 找到最小数并判断是否唯一 */
	for (int index = A; index < ANSWER_NUM; index++)
	{
		/* 找最小数 */
		if (selectedCount[index] < min)
		{
			min = selectedCount[index];
		}
		/* 唯一性验证 */
		else if(selectedCount[index] == min)
		{
			funResult = NOT_STRICT;
		}
		else
		{
			 /* do nothing */
		}
	}

	if (selectedCount[qSelection[result[QUEST_7]]] == min)
	{
		/* do nothing */
	}
	else
	{
		funResult = FAIL;
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question8
Description    :验证问题8
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question8(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM] = { QUEST_7,QUEST_5,QUEST_2,QUEST_10 };
	unsigned char base,temp;
	VAL_RESULT funResult = PASS;
	
	base = 1 << (result[QUEST_1]);
	base = (base << 1) | (base >> 1) | base;
	base = base & 0x0F;

	for (int index = A; index < ANSWER_NUM; index++)
	{	
		temp = 1 << result[qContext[index]];
		 /* 判断是否不相邻 */
		if ((temp & base) == 0) /* 不相邻时 */
		{
			 /* 判断是否为被选选项 */
			if (index != result[QUEST_8]) /* 不是被选项 */
			{
				funResult = NOT_STRICT;
			}
			else /* 是被选项 */
			{
				 /* do nothing */
			}
		}
		else /* 相邻时 */
		{
			 /* 判断是否为被选选项 */
			if (index != result[QUEST_8]) /* 不是被选项 */
			{
				 /* do nothing */
			}
			else /* 是被选项 */
			{
				funResult = FAIL;
				break;
			}
		}
	}
	return(funResult);
}


/*********************************************************************
Function       :val_Question9
Description    :验证问题9
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question9(const SELECTION* result)
{
	QUEST_INDEX qContext[ANSWER_NUM] = { QUEST_6,QUEST_10,QUEST_2,QUEST_9 };
	VAL_RESULT funResult = PASS;

	 /* 判断第一个条件是否为真 */
	if (result[QUEST_1] == result[QUEST_6]) /* 为真，那么第二条应为假 */
	{
		 /* 因是单选题，只有被选项为假，其余为真 */
		for (int index = A; index < ANSWER_NUM; index++)
		{
			if (index == result[QUEST_9]) /* 是被选项 */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* 为真 */
				{
					funResult = FAIL;
					break;
				}
				else
				{
					 /* do nothing */
				}
			}
			else /* 不是被选项 */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* 为真 */
				{
					 /* do nothing */
				}
				else
				{
					funResult = NOT_STRICT;
				}
			}
		}
	}
	else /* 为假，那么第二条应为真 */
	{
		 /* 因是单选题，只有被选项为真，其余为假 */
		for (int index = A; index < ANSWER_NUM; index++)
		{
			if (index == result[QUEST_9]) /* 是被选项 */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* 为真 */
				{
					 /* do nothing */
				}
				else
				{
					funResult = FAIL;
					break;
				}
			}
			else /* 不是被选项 */
			{
				if (result[qContext[index]] == result[QUEST_5]) /* 为真 */
				{
					funResult = NOT_STRICT;
				}
				else
				{
					 /* do nothing */
				}
			}
		}
	}
	return(funResult);
}

/*********************************************************************
Function       :val_Question10
Description    :验证问题10
Parameters     :const SELECTION* result
Returns        :bool
Create&Verlog  :Wu Junyi  Date:   2019-01-11    Version:   01 init
**********************************************************************/
VAL_RESULT val_Question10(const SELECTION* result)
{
	int qContext[ANSWER_NUM] = { 3, 2, 4, 1 };
	int selectedCount[ANSWER_NUM] = { 0,0,0,0 };
	int max=0,min= INIT_MIN;

	 /* 统计被选次数 */
	for (int index = QUEST_1; index < QUEST_NUM; index++)
	{
		selectedCount[result[index]]++;
	}

	for (int index = A; index < ANSWER_NUM; index++)
	{
		if (selectedCount[index] > max)
		{
			max = selectedCount[index];
		}
		else
		{
			 /* do nothing */
		}

		if (selectedCount[index] < min)
		{
			min = selectedCount[index];
		}
		else
		{
			 /* do nothing */
		}
	}
	/* 判断差值是否符合选项 */
	if ((max - min) == qContext[result[QUEST_10]])
	{
		return (PASS);
	}
	else
	{
		return(FAIL);
	}
}