//WindowsProject1.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WindowsProject1.h"
#include "SquareBloc.h"
#include "Player.h"
#include <time.h>
#define MAX_LOADSTRING 100
#define MAX_SQUARE 80

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING] ;             // 主窗口类名

WCHAR keyInput; //键盘输入
bool isStart = false;//是否开始
bool isEnd = false;//是否结束
bool waityou = false;//等你决定是否购买


SquareBloc squareBloc[MAX_SQUARE];
WCHAR tipInfo[MAX_LOADSTRING];   //一些提示信息
Player pc, player;
int steps = 1;//游戏步骤

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                initSquareBloc();
void dealKeyDown(WCHAR keyInput);
void showInfo(HDC hdc);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	szTitle[MAX_LOADSTRING] ;                  // 标题栏文本
	szWindowClass[MAX_LOADSTRING] ;
    MyRegisterClass(hInstance);

	//初始化squarebloc
	initSquareBloc(); SquareBloc squareBloc[MAX_SQUARE];


    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, L"Monopoly", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 1200, CW_USEDEFAULT, 1200, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
	{

	
		keyInput = wParam;
		dealKeyDown(keyInput);
		InvalidateRect(hWnd, NULL, true);
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

		
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			// 设置hdc颜色
			
			SetTextColor(ps.hdc, RGB(0,0,0));//设置文本颜色  
			SetBkMode(ps.hdc,TRANSPARENT);
			TextOut(ps.hdc, 400,0, _T("Monopoly"), wcslen(_T("Monopoly")));
			
			
			showInfo(ps.hdc);
			

			// 填充图形  
			// 创建画刷  
		//	HBRUSH hb = CreateSolidBrush(RGB(0, 255, 0));
			// 画刷选择到当前DC中  
		//	HBRUSH orgBrs = (HBRUSH)SelectObject(ps.hdc, hb);
			
			for (int i = 0; i<MAX_SQUARE; i++)
			{				
				squareBloc[i].display(hdc);
			}

			pc.display(hdc);
			squareBloc[pc.getPos()].display2(hdc,1);
			player.display(hdc);			;
			squareBloc[player.getPos()].display2(hdc, 2);
			
			// 选回原先的画刷  
		//	SelectObject(ps.hdc, orgBrs);
		//	DeleteObject(hb); //清理对
            EndPaint(hWnd, &ps);
        }		
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
//显示游戏的一些说明信息
void showInfo(HDC hdc)
{
	TextOut(hdc, 100, 80, _T("DOWN  ARROW key=buy it"), wcslen(_T("DOWN  ARROW key=buy it")));
	TextOut(hdc, 100, 100, _T("RIGHT  ARROW key=pass it"), wcslen(_T("RIGHT  ARROW key=pass it")));
	TextOut(hdc, 100, 120, _T("UP ARROW key=update it"), wcslen(_T("UP ARROW key=update it")));
	TextOut(hdc, 100, 140, _T("KEYBOARD SPACE TO dice"), wcslen(_T("KEYBOARD SPACE TO dice")));

	TextOut(hdc, 400, 200, tipInfo, wcslen(tipInfo));
}
//处理键盘输入
void dealKeyDown(WCHAR keyInput)
{

	if (!isStart)
	{
		if (keyInput== VK_SPACE)
		{
		
			wcscpy_s(tipInfo, L"go go go");
			
			isStart = true;
		}

		
		return;
	}
	if (isEnd)
	{
		if (pc.getDeposit() <= 0)
		{
			wcscpy_s(tipInfo, L"game over you win!");
		}
		if (player.getDeposit() <= 0)
		{
			wcscpy_s(tipInfo, L"game over pc win!");
		}


		return;
	}

	if (waityou)//等你输入
	{
		switch (keyInput)
		{
		case VK_DOWN:

			if (squareBloc[player.getPos()].getOwnid() != 2)
			{
				squareBloc[player.getPos()].setOwnid(2);
				squareBloc[player.getPos()].setColor(player.getColor());
				player.setDeposit(player.getDeposit() - squareBloc[player.getPos()].getPrice());
				wcscpy_s(tipInfo, L"you buy it");
			}
			else
			{
				wcscpy_s(tipInfo, L"you cannot buy it,again");
			}
			break;
		case  VK_UP:

			if (squareBloc[player.getPos()].getOwnid() != 2)
			{
				wcscpy_s(tipInfo, L"first,you must buy it");
				return;
			}
			if (!squareBloc[player.getPos()].getUpdate())
			{
				squareBloc[player.getPos()].setUpdate(true);
				player.setDeposit(player.getDeposit() - squareBloc[player.getPos()].getPrice() / 2);
				wcscpy_s(tipInfo, L"you update it");
			}
			else
			{
				wcscpy_s(tipInfo, L"you cannot update it,again");
			}


			break;
		case VK_RIGHT:
			waityou = false;
			wcscpy_s(tipInfo, L"pass it");
			steps++;
			break;

		}
		return;
	}

	switch (keyInput)
	{
	case VK_SPACE:
		
		int buf=rand() % 6 + 1;
		int tariff = 10;
		int pos = 0;
			switch ((steps % 2 + 1))
			{
			case 1:  //pc
				pos = pc.getPos();
				if ((pos + buf) >= MAX_SQUARE)
				{
					pc.setDeposit(pc.getDeposit()+200);
				}
				pc.setPos((pos + buf) % MAX_SQUARE);//走到下一步;
				pos = pc.getPos();
				switch (squareBloc[pos].getOwnid())
				{
				case 0://无主地块；
					squareBloc[pos].setOwnid(1);
					squareBloc[pos].setColor(pc.getColor());
					pc.setDeposit(pc.getDeposit() - squareBloc[pos].getPrice());
					break;
				case 1://pc地块
					break;
					case 2://你的地块
						if (squareBloc[pos].getUpdate())//升级过
						{
							tariff = tariff + 5;
						}
						if (squareBloc[(pos+1) % MAX_SQUARE].getOwnid()==2)//前面地块也是你的
						{
							tariff = tariff + 5;
						}
						if (squareBloc[(pos +79) % MAX_SQUARE].getOwnid() == 2)//后面地块也是你的
						{
							tariff = tariff + 5;
						}
						pc.setDeposit(pc.getDeposit() - squareBloc[pos].getPrice()*tariff /100);
					break;

				}

				break;
			case 2:  //you
				pos = player.getPos();
				if ((pos + buf) >= MAX_SQUARE)
				{
					player.setDeposit(player.getDeposit() + 200);
				}
				player.setPos((pos + buf) % MAX_SQUARE);
				pos = player.getPos();
				switch (squareBloc[pos].getOwnid())
				{
				case 0://无主地块；
					waityou = true;
					
					break;
				case 1://pc地块

					if (squareBloc[pos].getUpdate())//升级过
					{
						tariff = tariff + 5;
					}
					if (squareBloc[(pos + 1) % MAX_SQUARE].getOwnid() == 1)//前面地块也是pc的
					{
						tariff = tariff + 5;
					}
					if (squareBloc[(pos + 79) % MAX_SQUARE].getOwnid() == 1)//后面地块也是pc的
					{
						tariff = tariff + 5;
					}
					player.setDeposit(player.getDeposit() - squareBloc[pos].getPrice()*tariff / 100);



					break;
				case 2://你的地块

					break;

				}

				break;

			}

			if (pc.getDeposit() <= 0)
			{
				isEnd = true;
			}
			if (player.getDeposit() <= 0)
			{
				isEnd = true;
			}
			if (!waityou)//等你输入
			{
				steps++;
			}
		swprintf_s(tipInfo, L"your dice:%d", buf);
		
		break;
	}


}
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void initSquareBloc()
{
	srand((unsigned)time(NULL));

	wcscpy_s(tipInfo, L"press KEYBOARD SPACE start game! ");

	squareBloc[0] = SquareBloc(20 , 620, 0);
	squareBloc[0].setPrice(0);
	squareBloc[0].setColor(RGB(0,200,0));
	squareBloc[0].setOwnid( -1);
	for (int i=1;i<MAX_SQUARE/4;i++)
	{
		squareBloc[i] =  SquareBloc(20 + i * 40,620,i);
		squareBloc[i].setPrice(rand() % 491 + 10);
	}
	
	for (int i = MAX_SQUARE / 4; i<MAX_SQUARE / 2; i++)
	{
		squareBloc[i] = SquareBloc(20 + MAX_SQUARE / 4 * 40,620+30*(MAX_SQUARE / 4-i),  i);
		squareBloc[i].setPrice(rand() % 491 + 10);
	}
	for (int i = 2*MAX_SQUARE / 4; i<3 * MAX_SQUARE / 4; i++)
	{
		squareBloc[i] = SquareBloc(20 + (3*MAX_SQUARE / 4 -i)* 40, 620 - 30 * (MAX_SQUARE / 4 ), i);
		squareBloc[i].setPrice(rand() % 491 + 10);
	}
	for (int i = 3*MAX_SQUARE / 4; i<MAX_SQUARE ; i++)
	{
		squareBloc[i] = SquareBloc(20 , 620 + 30 * (i-MAX_SQUARE), i);
		squareBloc[i].setPrice(rand() % 491 + 10);
	}

	pc = Player(1, _T("PC"),300,280);
	pc.setColor(RGB(200,0,0));
	player= Player(2, _T("Player"),460,280);
	player.setColor(RGB(0, 0, 200));
}
