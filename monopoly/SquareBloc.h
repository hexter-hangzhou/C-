#include "stdafx.h"
class SquareBloc
{
private:
	int x=0, y=0;//����
	int id=1;//id��
	int price=10;//�۸�
	int ownid = 0;//ӵ����
	COLORREF rgb=RGB(128,128,128);
	bool isUpdate=false;//�Ƿ�����
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
	void display(HDC hdc);//��ʾ����

	void display2(HDC hdc,int who);//��ʾ���

	
	~SquareBloc();
};
