// othello.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

void CheckClock(); // timeGetTime�֐��̃`�F�b�N


int _tmain(int argc, _TCHAR* argv[])
{
	CheckClock();
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

