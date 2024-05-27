#include <Windows.h>
#include <tchar.h>

TCHAR gamePlayTime[20];
HFONT hFont, oldfont;

void DrawEXP_Bar(HDC mDC) {
	RoundRect(mDC, 100, 0, 1100, 30, 20, 20);
}

void TimeBar(HDC mDC, int Timer1Count, int gamePlayminute) {

	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, _T("�ü�"));
	oldfont = (HFONT)SelectObject(mDC, hFont);
	wsprintf(gamePlayTime, TEXT("%d : %d"), gamePlayminute, Timer1Count);
	TextOut(mDC, 550, 32, gamePlayTime, _tcslen(gamePlayTime));
	SelectObject(mDC, oldfont);
	DeleteObject(hFont);

}