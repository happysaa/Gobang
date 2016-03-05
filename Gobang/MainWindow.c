//MainWindow.c
//��������Ϸ������
#include <WindowsX.h>
#include <windows.h>
#include <stdlib.h>
#include "Gobang.h"
//�����������׵�����
#ifndef LINECOUNT 
#define LINECOUNT 15
#endif
//�������������Ӱ뾶
#ifndef RADIUS
#define RADIUS 15
#endif
//#pragma comment(lib, "gdi32.lib")
//#pragma comment(lib, "User32.lib")
//�������ڹ��̺���
LRESULT CALLBACK WinProc(
						 HWND hwnd,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 );

//����������
int WINAPI WinMain(
				   HINSTANCE hInstance,		//��ǰ�Ľ���ʵ��
				   HINSTANCE hPrevInstance,	//ǰһ����ʵ��,Ĭ��ΪNULL
				   LPSTR lpCmdLine,			//�����в���
				   int nCmdShow				//������ʾ״̬
				   )
{
	HBRUSH hBrush;
	WNDCLASS wndcls;
	HWND hwnd = NULL;
	MSG msg;

	hBrush=CreateSolidBrush(RGB(255,250,20));

	//��ƴ�����
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	//	wndcls.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.hbrBackground=hBrush;
	wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);
	//	wndcls.hIcon=LoadIcon(NULL,IDI_WINLOGO);
	wndcls.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE( 100 ));
	wndcls.hInstance=hInstance;
	wndcls.lpfnWndProc=WinProc;
	wndcls.lpszClassName=TEXT("Gobang");
	wndcls.lpszMenuName=NULL;
	wndcls.style=CS_HREDRAW | CS_VREDRAW;
	//ע�ᴰ����
	RegisterClass(&wndcls);

	//��������

	hwnd=CreateWindow(TEXT("Gobang"),TEXT("��������Ϸ"),WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,550,600,NULL,NULL,hInstance,NULL);
	//��ʾ�����´���
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);


	//������Ϣѭ��
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
	//	UNREFERENCED_PARAMETER(lpCmdLine); 
}

//���崰�ڹ��̺���
LRESULT CALLBACK WinProc(
						 HWND hwnd,
						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam
						 )
{
	HDC hdc;
	//	HPEN hPen;
	//	HPEN hPenOld;
	//�ͻ�������ϵ�е�����
	RECT rectClient;
	//��Ļ����ϵ�е�����
	RECT rectWin;
	PAINTSTRUCT ps;


	//�߶ȵ�ƫ����
	static unsigned  offset=40;
	//�߶����ȵĲ�
	static unsigned heightSubWid=50;
	//��ʼ���
	static unsigned initWidth=550;
	int xPos;
	int yPos;
	int screenWidth;
	int screenHeight;

	static int preWinx;
	static unsigned count=0;			//�������ӵĸ���
	POINT pt;							//����ѡ�еĽ����ͻ�������
	POINT ptIndex;						//�����ͻ��������Ӧ����������

	static POINT existedPoint[225];			//�洢�������ӵ���������	
	static int blackIndex[15][15];
	static int whiteIndex[15][15];

	RECT rt;
	unsigned width = 0;
	unsigned height = 0;
	unsigned titleHeight = 0;

	switch(uMsg)
	{
		//�����ַ���Ϣ
	case WM_CHAR:
		MessageBox(hwnd,TEXT("char"),TEXT("char"),0);
		break;
		//	case WM_CREATE:
		//	GetWindowRect(hwnd, &r);
		//	hdc=GetDC(hwnd);
		//	hPen = CreatePen( PS_SOLID , 3 , RGB( 0 , 0 , 0 ));
		//	hPenOld = ( HPEN )SelectObject ( hdc , hPen );
		//	MoveToEx(hdc, 100, 0, NULL);
		//	LineTo(hdc, 100, 100);
		//	SelectObject(hdc, hPenOld);
		//	DeleteObject(hPen);
		//	break;
		//		case WM_SIZING:
		//			GetWindowRect(hwnd, &r);
		//	break;
		//���ڴ�С�ı���Ϣ
	case WM_SIZE:
		//��ô�������Ļ����ϵ�µ�����
		GetWindowRect(hwnd, &rectWin);
		//��ô����ڿͻ�������ϵ�µ�����
		GetClientRect(hwnd, &rectClient);

		SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, SPIF_SENDCHANGE);	
		//���㴰�ڵĿ�Ⱥ͸߶ȣ��߶�Ϊʵ�ʼ�ȥƫ��ֵ
		width = rectWin.right - rectWin.left;
		height = rectWin.bottom - rectWin.top - heightSubWid;
		titleHeight = rectWin.bottom - rectWin.top -
			(rectClient.bottom - rectClient.top);
		//	screenWidth = GetSystemMetrics(SM_CXFRAME);
		//	screenHeight = GetSystemMetrics(SM_CYFRAME);
		screenWidth = rt.right - rt.left;
		screenHeight = rt.bottom - rt.top;


		/*
		char str[25];
		itoa(rt.bottom-rt.top, str, 10);
		MessageBox(hwnd, str, "��ʾ", MB_OKCANCEL);
		//	itoa(rectWin.left, str, 10);
		//	MessageBox(hwnd, str, "��ʾ", MB_OKCANCEL);						
		*/
		//��С�ڳ�ʼ��Ȼ�߶ȣ��ָ�Ϊ��ʼֵ

		if (wParam == SIZE_MAXIMIZED)
		{
			//	MessageBox(hwnd, "���", "��ʾ", MB_OKCANCEL);
			MoveWindow(hwnd, preWinx, 0, 
				screenHeight - offset, screenHeight, TRUE);
			UpdateWindow(hwnd);
		}
		else if(width < initWidth || height < initWidth )
			MoveWindow(hwnd, rectWin.left, rectWin.top, 
			initWidth, initWidth+heightSubWid, TRUE);
		//���ڳ�ʼ�߶Ȼ��ȣ�����������
		else
		{
			if(width<height)
				MoveWindow(hwnd, rectWin.left, rectWin.top, 
				height, height+offset, TRUE);
			else if(width>height)
				MoveWindow(hwnd, rectWin.left, rectWin.top, 
				width, width+offset, TRUE);

		}
		preWinx=rectWin.left;
		break;

	case WM_PAINT:
		//		hdc=GetDC(hwnd);
		hdc=BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rectClient);
		GetWindowRect(hwnd, &rectWin);

		/*
		char str[25];
		//	itoa(rectWin.right - rectWin.left , str, 10);
		//	MessageBox(hwnd, str, "��ʾ", MB_OKCANCEL);
		itoa(rectClient.bottom-rectClient.top , str, 10);
		MessageBox(hwnd, str, "��ʾ", MB_OKCANCEL);
		*/

		DisplayInitBackground(&hdc, rectClient, offset);
		DisplayChess(&hdc, existedPoint, count, rectClient, offset, RADIUS);
		ShowGameStatus(&hdc, count, rectClient, offset);
		EndPaint(hwnd, &ps);
		//			ReleaseDC(hwnd, hdc);
		break;

	case WM_LBUTTONDOWN:
		//��õ���������
		xPos = GET_X_LPARAM(lParam); 
		yPos = GET_Y_LPARAM(lParam);
		GetClientRect(hwnd, &rectClient);
		hdc=GetDC(hwnd);



		/*			char str[25];
		itoa(screenWidth, str, 10);
		MessageBox(hwnd, str, "��ʾ", MB_OKCANCEL);
		itoa(screenHeight, str, 10);
		MessageBox(hwnd, str, "��ʾ", MB_OKCANCEL);
		*/


		//�жϵ������Ƿ�Ϊ���̵Ľ����
		if(IsIntersection(xPos, yPos, rectClient, offset, 5))
		{
			//�ҵ������ĵ�
			pt = FindPosition(xPos, yPos, rectClient, offset, 5);
			//�ҵ�������Ӧ����������
			ptIndex = FindIndex(pt, rectClient, offset);
			//�õ㲻�������ӣ���������
			if (!IsChessExisted(existedPoint, count, ptIndex))
			{

				//�����������������У������¼�������
				existedPoint[count++] = ptIndex;

				//��ʾ���ӣ������¶�Ӧ����������
				//����������
				if (count%2)
				{
					DisplayBlackChess(&hdc, pt, RADIUS);
					blackIndex[ptIndex.x][ptIndex.y]=1;
					if(IsWin(ptIndex, blackIndex))
						MessageBox(hwnd,TEXT("����ʤ"),TEXT("�������")
						,MB_OKCANCEL | MB_ICONWARNING);
				}
				else
				{
					DisplayWhiteChess(&hdc, pt, RADIUS);
					whiteIndex[ptIndex.x][ptIndex.y]=1;
					if(IsWin(ptIndex, whiteIndex))
						MessageBox(hwnd,TEXT("����ʤ"),TEXT("�������"),MB_OKCANCEL);
				}
				ShowGameStatus(&hdc, count, rectClient, offset);

			}


		}

		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}

	return 0;
}