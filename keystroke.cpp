#include <Windows.h>
#include <WinUser.h>

void keystroke(char* rec)
{
	INPUT ks;					//INPUT from keystroke
	ks.type = INPUT_KEYBOARD;
	ks.ki.wScan = 0;
	ks.ki.time = 0;
	ks.ki.dwExtraInfo = 0;

	if (strcmp(rec, "gu") == 0)
	{
		ks.ki.wVk = VK_PRIOR;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_PRIOR;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gd") == 0)
	{
		ks.ki.wVk = VK_NEXT;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_NEXT;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gl") == 0)
	{
		ks.ki.wVk = VK_LEFT;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_LEFT;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gr") == 0)
	{
		ks.ki.wVk = VK_RIGHT;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_RIGHT;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gul") == 0)
	{
		ks.ki.wVk = 'P';
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = 'P';
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gur") == 0)
	{
		ks.ki.wVk = 'N';
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = 'N';
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "grl") == 0)
	{
		ks.ki.wVk = 'M';
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = 'M';
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gdr") == 0)
	{
		ks.ki.wVk = VK_SPACE;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_SPACE;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gdl") == 0)
	{
		ks.ki.wVk = 'S';
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = 'S';
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gurd") == 0)
	{
		ks.ki.wVk = VK_MENU;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_F4;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_F4;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));

		ks.ki.wVk = VK_MENU;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "gru") == 0)
	{
		int i = 0;

		ks.ki.wVk = VK_CONTROL;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		for (; i < 4; i++)
		{
			ks.ki.wVk = VK_UP;
			ks.ki.dwFlags = 0;
			SendInput(1, &ks, sizeof(INPUT));

			ks.ki.wVk = VK_UP;
			ks.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ks, sizeof(INPUT));
		}

		ks.ki.wVk = VK_CONTROL;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}

	if (strcmp(rec, "grd") == 0)
	{
		int i = 0;

		ks.ki.wVk = VK_CONTROL;
		ks.ki.dwFlags = 0;
		SendInput(1, &ks, sizeof(INPUT));

		for (; i < 4; i++)
		{
			ks.ki.wVk = VK_DOWN;
			ks.ki.dwFlags = 0;
			SendInput(1, &ks, sizeof(INPUT));

			ks.ki.wVk = VK_DOWN;
			ks.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ks, sizeof(INPUT));
		}

		ks.ki.wVk = VK_CONTROL;
		ks.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ks, sizeof(INPUT));
	}
}
