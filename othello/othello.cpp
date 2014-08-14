// othello.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

void CheckClock(); // timeGetTime関数のチェック


int _tmain(int argc, _TCHAR* argv[])
{
	CheckClock();
	return 0;
}

void CheckClock()
{
	int test = 0;
	DWORD myTime;
	printf_s("開始するには何か入力してね。\n");
	scanf_s("%d", &test);

	for (test = 0; test < 1000; test++)
	{
		myTime = timeGetTime();
		printf_s("%d回目:\t%d\n", test, myTime);
	}

	printf_s("終了するには何か入力してね。\n");
	scanf_s("%d", &test);
	return;
}

