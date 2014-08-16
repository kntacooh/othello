// othello.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

void CheckClock(); // timeGetTime関数のチェック
void CheckInputingInRealTime(); // リアルタイム入力のチェック
void PumpMessage(); //(http://codezine.jp/article/detail/5332より)

#define UseExacterTime // timeBeginPeriodを使うことでSleep関数の制度を上げる

int _tmain(int argc, _TCHAR* argv[])
{
	//if (DxLib_Init() == -1) return -1; // DXライブラリの初期化処理(※使わない方向で)
	
	//CheckClock();
	CheckInputingInRealTime();
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

void CheckInputingInRealTime()
{
	DWORD interval;
	DWORD loopStart, checkingTime;
	byte keyState[256], keyStateBefore[256];

	printf_s("反応のチェックを行います。Spaceキーで終了します。\n");
	printf_s("反応のインターバルをミリ秒で入力してね。\n");
	scanf_s("%d", &interval);

#ifdef UseExacterTime
	timeBeginPeriod(1);
#endif
	GetKeyboardState((PBYTE)&keyStateBefore);
	printf_s("スタート！\n");

	while (true)
	{
		if (GetKeyState(VK_SPACE) & 0x80) break;
		//if (GetKeyState('A') & 0x80) break; // Aキー
		//if (GetKeyState(0x0D) & 0x80) break; // Enterキー
		loopStart = timeGetTime();
		if (GetKeyboardState((PBYTE)&keyState) == 0)
		{
			printf_s("GetKeyboardState関数を実行できない瞬間がありました。\n");
			break;
		}
		checkingTime = timeGetTime() - loopStart;

		for (int i = 0; i < 256; i++)
		{
			if ((keyState[i] & 0x80) != (keyStateBefore[i] & 0x80))
			{
				keyStateBefore[i] = keyState[i];
				if (keyState[i] & 0x80) printf_s("↓\t");
				else printf_s("\t↑");
				printf_s("\tNo: %3d (0x%02x)\t\t[Time:%2dms]\n", i, i, checkingTime);
			}
		}

		while (timeGetTime() - loopStart < interval) Sleep(1);

	}

#ifdef UseExacterTime
	timeEndPeriod(1);
#endif
	printf_s("終了しました。\n");
	return;
}

void PumpMessage()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}