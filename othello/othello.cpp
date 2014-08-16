// othello.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

void CheckClock(); // timeGetTime�֐��̃`�F�b�N
void CheckInputingInRealTime(); // ���A���^�C�����͂̃`�F�b�N
void PumpMessage(); //(http://codezine.jp/article/detail/5332���)

#define UseExacterTime // timeBeginPeriod���g�����Ƃ�Sleep�֐��̐��x���グ��

int _tmain(int argc, _TCHAR* argv[])
{
	//if (DxLib_Init() == -1) return -1; // DX���C�u�����̏���������(���g��Ȃ�������)
	
	//CheckClock();
	CheckInputingInRealTime();
	return 0;
}

void CheckClock()
{
	int test = 0;
	DWORD myTime;

	printf_s("�J�n����ɂ͉������͂��ĂˁB\n");
	scanf_s("%d", &test);

	for (test = 0; test < 1000; test++)
	{
		myTime = timeGetTime();
		printf_s("%d���:\t%d\n", test, myTime);
	}

	printf_s("�I������ɂ͉������͂��ĂˁB\n");
	scanf_s("%d", &test);
	return;
}

void CheckInputingInRealTime()
{
	DWORD interval;
	DWORD loopStart, checkingTime;
	byte keyState[256], keyStateBefore[256];

	printf_s("�����̃`�F�b�N���s���܂��BSpace�L�[�ŏI�����܂��B\n");
	printf_s("�����̃C���^�[�o�����~���b�œ��͂��ĂˁB\n");
	scanf_s("%d", &interval);

#ifdef UseExacterTime
	timeBeginPeriod(1);
#endif
	GetKeyboardState((PBYTE)&keyStateBefore);
	printf_s("�X�^�[�g�I\n");

	while (true)
	{
		if (GetKeyState(VK_SPACE) & 0x80) break;
		//if (GetKeyState('A') & 0x80) break; // A�L�[
		//if (GetKeyState(0x0D) & 0x80) break; // Enter�L�[
		loopStart = timeGetTime();
		if (GetKeyboardState((PBYTE)&keyState) == 0)
		{
			printf_s("GetKeyboardState�֐������s�ł��Ȃ��u�Ԃ�����܂����B\n");
			break;
		}
		checkingTime = timeGetTime() - loopStart;

		for (int i = 0; i < 256; i++)
		{
			if ((keyState[i] & 0x80) != (keyStateBefore[i] & 0x80))
			{
				keyStateBefore[i] = keyState[i];
				if (keyState[i] & 0x80) printf_s("��\t");
				else printf_s("\t��");
				printf_s("\tNo: %3d (0x%02x)\t\t[Time:%2dms]\n", i, i, checkingTime);
			}
		}

		while (timeGetTime() - loopStart < interval) Sleep(1);

	}

#ifdef UseExacterTime
	timeEndPeriod(1);
#endif
	printf_s("�I�����܂����B\n");
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