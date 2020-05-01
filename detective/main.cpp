#include "generate.h"
#include "validate.h"

/*********************************************************************
Function       :main 
Description    :主函数
Parameters     :none
Returns        :int
Create&Verlog  :Wu Junyi  Date:   2019-01-12    Version:   01 init
**********************************************************************/
int main(void)
{
	/* 模块初始化 */
	GEN_Init();
	VAL_Init();

	/* 求解答案 */
	printf("开始解题...\n\n符号说明: P = PASS, F = FAIL , N = NOT SRTICT \n\n");
	do
	{
		VAL_Validate(GEN_GetSequence(),PRINT_ON);	
	} while (GEN_Next());

	/* 打印统计结果 */
	printf("\n结果统计：\n\n1.严格解  %10lu 个\n2.非严格解%10lu 个\n3.共计检索%10lu 个\n\n",VAL_GetCountNumber(COUNT_S), VAL_GetCountNumber(COUNT_NS), VAL_GetCountNumber(COUNT_TOTAL));
	system("pause");

	return(0);
}

