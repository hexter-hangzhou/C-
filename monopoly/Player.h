#include "stdafx.h"

class Player
{
private :
	int id = 0;
	int x, y;
	int deposit = 10000;
	const WCHAR  *name;
	COLORREF rgb = RGB(128, 128, 128);
	int pos=0;//Ëù´¦Î»ÖÃ
	RECT rect;
public:
	Player();
	void setColor(COLORREF rgb);
	COLORREF getColor();
	int getDeposit();
	void setDeposit(int deposit);
	int getPos();
	void setPos(int pos);
	Player(int id, const WCHAR *name,int x,int y);
	void display(HDC hdc);
	~Player();
};

