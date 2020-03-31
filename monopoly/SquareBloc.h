#include "stdafx.h"
class SquareBloc
{
private:
	int x=0, y=0;//坐标
	int id=1;//id号
	int price=10;//价格
	int ownid = 0;//拥有者
	COLORREF rgb=RGB(128,128,128);
	bool isUpdate=false;//是否升级
	RECT rect;
	HBRUSH hb ;
public:
	SquareBloc();
	SquareBloc(int x,int y,int id);
	void setPrice(int price);
	int getPrice();
	void setColor(COLORREF rgb);
	void setOwnid(int ownid);
	int getOwnid();
	void setUpdate(bool update);
	bool getUpdate();
	void display(HDC hdc);//显示方块

	void display2(HDC hdc,int who);//显示玩家

	
	~SquareBloc();
};
