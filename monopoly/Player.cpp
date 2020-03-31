#include "stdafx.h"
#include "Player.h"
#include "stdio.h"

Player::Player()
{
}
Player::Player(int id, const WCHAR *name,int x,int y)
{
	this->id = id; this->name = name;
	this->x = x;
	this->y = y;
	this->rect.top = y;
	this->rect.left = x;
	this->rect.bottom = this->rect.top + 80;
	this->rect.right = this->rect.left + 100;
}

int Player::getDeposit() {
	return deposit;
}
void Player::setDeposit(int deposit) {
	this->deposit = deposit;
}
int  Player::getPos()
{
	return pos;
}
void  Player::setPos(int pos)
{
	this->pos = pos;
}
void Player::setColor(COLORREF rgb)
{
	this->rgb = rgb;
}
COLORREF Player::getColor()
{
	return rgb;
}
void Player::display(HDC hdc)
{
	HBRUSH hb = CreateSolidBrush(this->rgb);
	FillRect(hdc, &rect, hb); //FillRect
	wchar_t buf[10];
	int len = swprintf_s(buf, L"%d", deposit);
	
	TextOut(hdc, x + 20, y + 10, name, wcslen(name));
	TextOut(hdc, x + 20, y + 30, buf, wcslen(buf));

}

Player::~Player()
{
}
