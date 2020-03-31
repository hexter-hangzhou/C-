#include "stdafx.h"
#include "SquareBloc.h"



SquareBloc::SquareBloc()
{
}
SquareBloc::SquareBloc(int x,int y,int id)
{
	this->x = x;
	this->y = y;
	this->id = id;
	this->rect.top = y;
	this->rect.left	=x;
	this->rect.bottom = this->rect.top + 30;
	this->rect.right = this->rect.left + 40;
	this->hb = CreateSolidBrush(this->rgb);
}
void SquareBloc::setPrice(int price)
{
	this->price = price;
}
int SquareBloc::getPrice()
{
	return price;
}
void SquareBloc::setColor(COLORREF rgb)
{
	this->rgb = rgb;
	this->hb = CreateSolidBrush(this->rgb);
}
int SquareBloc::getOwnid() {
	return ownid;
}
void SquareBloc::setOwnid(int ownid)
{
	this->ownid = ownid;
}
void SquareBloc::setUpdate(bool update) {
	this->isUpdate = update;
}
bool SquareBloc::getUpdate() {
	return this->isUpdate;
}
void SquareBloc::display(HDC hdc)
{
	
	if (ownid == 0)
	{
		FrameRect(hdc, &rect, hb); //FillRect
	}
	else {
		FillRect(hdc, &rect, hb);
	}
	
	wchar_t buf[4];
	int len = swprintf_s(buf, L"%d", price);
	TextOut(hdc, x+2, y+1, _T("P:"), wcslen(_T("P:")));
	TextOut(hdc, x + 14, y + 1, buf, wcslen(buf));
}
void SquareBloc::display2(HDC hdc,int who)
{

	if (who == 1)
	{
		TextOut(hdc, x +6, y + 14, _T("C"), wcslen(_T("C")));
	}

	if (who == 2)
	{
		TextOut(hdc, x + 22, y + 14, _T("U"), wcslen(_T("U")));
	}
}
SquareBloc::~SquareBloc()
{
}
