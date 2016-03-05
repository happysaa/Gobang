//Gobang.c
//�����庯����ʵ���ļ�
#ifndef _WINDOWS_
#include <windows.h>
#endif
#include <math.h>
#ifndef _INC_STDLIB
#include <stdlib.h>
#endif
#include "Gobang.h"
//�����������׵�����
#ifndef LINECOUNT 
#define LINECOUNT 15
#endif
//��ʾ��������Ϸ����
//�������Ϊ�豸�������ָ��pdc����ǰ���ڴ�Сr�Լ��߶ȷ����ϵ�ƫ��offset
BOOL DisplayInitBackground(HDC* pdc, RECT r, unsigned offset)
{
	//��������ÿ�С��п��߶�
	unsigned width = (r.right-r.left)/(LINECOUNT+1);
	//��Ե���������ֵ������һ���������µ�ֵ
	unsigned edge = r.right-r.left-width*(LINECOUNT+1);
	//��������λ�ڴ�������ϵ�е����Ͻǵ�����
	unsigned left = edge/2+width;
	unsigned top = offset+edge/2+width;
	int i = 0;
	/*
	char str[25];
	itoa(left, str, 10);
	MessageBox(NULL, str, "��ʾ", MB_OKCANCEL);
	itoa(top, str, 10);
	MessageBox(NULL, str, "��ʾ", MB_OKCANCEL);
	*/

	HPEN hPen;			//��Ҫʹ�õĻ���
	HPEN hPenOld;		//��ǰ����

	//���廭��
	hPen = CreatePen(PS_SOLID, 2, RGB(0 , 0 , 0));
	if (hPen==NULL) return FALSE;
	//ѡ�л���
	hPenOld = (HPEN)SelectObject(*pdc , hPen );
	if (hPenOld==NULL) return FALSE;

	//������������
	//���ƺ���
	for (i = 0; i < LINECOUNT; ++i)
	{
		MoveToEx(*pdc, left, top+i*width, NULL);
		LineTo(*pdc, left+(LINECOUNT-1)*width, top+i*width);
	}
	//��������
	for (i = 0; i < LINECOUNT; ++i)
	{
		MoveToEx(*pdc, left+i*width, top, NULL);
		LineTo(*pdc, left+i*width, top+(LINECOUNT-1)*width);
	}
	if(SelectObject(*pdc, hPenOld)==NULL)
		return FALSE;
	return TRUE;

}

//�жϵ���������Ƿ��������ߵĽ����ϣ��Ƿ���Է�������
//����ͻ�ȥ����ϵ�еĺ������ꡢ��ǰ�����ڿͻ�����ϵ�е�λ�á��߶�ƫ���Լ�
//����������ƫ��
BOOL IsIntersection(int x, int y, RECT r, int offset, int shift)
{
	//��������ÿ�С��п��߶�
	int width = (r.right-r.left)/(LINECOUNT+1);
	//��Ե���������ֵ������һ���������µ�ֵ
	int edge = r.right-r.left-width*(LINECOUNT+1);
	//��������λ�ڴ�������ϵ�е����Ͻǵ�����
	int left = edge/2+width;
	int top = offset+edge/2+width;

	/*	
	char str[25];
	itoa(abs((x-left)%width), str, 10);
	MessageBox(NULL, str, "��ʾ", MB_OKCANCEL);
	itoa(abs((y-top)%width), str, 10);
	MessageBox(NULL, str, "��ʾ", MB_OKCANCEL);
	*/
	//�����̷�Χ��
	if ((x-left) >= -shift  &&	(x-left) <= ((LINECOUNT-1)*width+shift)
		&& (y-top) >= -shift  && (y-top) <= ((LINECOUNT-1)*width+shift)  
		//�������߽�����Χ��
		&&( (x-left)%width <= shift  || (x-left)%width >= width-shift )
		&&( (y-top)%width <= shift  || (y-top)%width >= width-shift )  )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

//�ҵ������ĺϷ������Ӧ�������߽����λ��
//���뵥���ĺ������꣬���ڿͻ���λ�á��߶�ƫ�ƺ�����ĵ���ƫ��
POINT FindPosition(int x, int y, RECT r, int offset, int shift)
{
	//��������ÿ�С��п��߶�
	int width = (r.right-r.left)/(LINECOUNT+1);
	//��Ե���������ֵ������һ���������µ�ֵ
	int edge = r.right-r.left-width*(LINECOUNT+1);
	//��������λ�ڴ�������ϵ�е����Ͻǵ�����
	int left = edge/2+width;
	int top = offset+edge/2+width;
	//�����߽����
	POINT pt;

	//Ѱ�Һ�����
	//��������
	if (abs((x-left)%width) <= shift)
	{
		pt.x = x-(x-left)%width;
	}
	//��������
	else if ((x-left)%width >= width-shift)
	{
		pt.x = x-(x-left)%width+width;
	}

	//Ѱ��������
	//��������
	if (abs((y-top)%width) <= shift)
	{
		pt.y = y-(y-top)%width;
	}
	//��������
	else if ((y-top)%width >= width-shift)
	{
		pt.y = y-(y-top)%width+width;
	}

	return pt;
}

//��ָ�������̽������ʾ����
//�������Ϊ�豸������ָ��,���̽����λ�������Ӱ뾶
BOOL DisplayBlackChess(HDC* pdc, POINT pos, int radius)
{
	HBRUSH hBrush;		//��Ҫʹ�õĻ�ˢ
	HBRUSH hBrushOld;	//��ǰ��ˢ

	HRGN rgn;			//���ӵ�����

	//������ˢ
	hBrush=CreateSolidBrush(RGB(0,0,0));
	//ѡ�л�ˢ
	hBrushOld = (HBRUSH)SelectObject(*pdc , hBrush );

	//������������
	rgn=CreateEllipticRgn(pos.x-radius, pos.y-radius, 
		pos.x+radius, pos.y+radius);
	//��������
	PaintRgn(*pdc, rgn);
	//ɾ�����������
	DeleteObject(rgn);
	if(SelectObject(*pdc, hBrushOld)==NULL)
		return FALSE;
	return TRUE;
}

//��ָ�������̽������ʾ����
//�������Ϊ�豸������ָ��,���̽����λ�������Ӱ뾶
BOOL DisplayWhiteChess(HDC* pdc, POINT pos, int radius)
{
	HBRUSH hBrush;		//��Ҫʹ�õĻ�ˢ
	HBRUSH hBrushOld;	//��ǰ��ˢ

	HRGN rgn;			//���ӵ�����

	//������ˢ
	hBrush=CreateSolidBrush(RGB(255,255,255));
	//ѡ�л�ˢ
	hBrushOld = (HBRUSH)SelectObject(*pdc , hBrush );

	//������������
	rgn = CreateEllipticRgn(pos.x-radius, pos.y-radius, 
		pos.x+radius, pos.y+radius);
	//��������
	PaintRgn(*pdc, rgn);
	//ɾ�����������
	DeleteObject(rgn);
	if(SelectObject(*pdc, hBrushOld)==NULL)
		return FALSE;
	return TRUE;
}

//��鵥���������߽�����Ƿ���������
//�������Ϊ�������ӵ���������ͷָ�룬���µ����Ӹ�������жϵ���������
BOOL IsChessExisted(POINT* existedPoint, int count, POINT pt)
{
	int i = 0;
	for (i = 0; i < count; ++i)
	{
		if(pt.x == existedPoint[i].x && pt.y == existedPoint[i].y)
			return TRUE;
	}

	return FALSE;
}

//ͨ�����ӵĿͻ�������������Ӷ�Ӧ����������
//�������ӵĿͻ������꣬�ͻ�����С��߶�ƫ��
POINT FindIndex(POINT pt,  RECT r, int offset)
{
	//��������ÿ�С��п��߶�
	int width = (r.right-r.left)/(LINECOUNT+1);
	//��Ե���������ֵ������һ���������µ�ֵ
	int edge = r.right-r.left-width*(LINECOUNT+1);
	//��������λ�ڴ�������ϵ�е����Ͻǵ�����
	int left = edge/2+width;
	int top = offset+edge/2+width;
	//�����߽������������
	POINT ptIndex;

	//������ת��Ϊ����
	ptIndex.x = (pt.x-left)/width;
	ptIndex.y = (pt.y-top)/width;

	return ptIndex;
}

//���������������ػ棩��ʾ����
//�������Ϊ�豸������ָ��,���̽����λ����������ͷָ�룬
//���µ����Ӹ����Ϳͻ�����С���߶�ƫ�������Ӱ뾶
BOOL DisplayChess(HDC* pdc, POINT* existedPoint,
				  int count, RECT r,  int offset, int radius)
{
	//��������ÿ�С��п��߶�
	int width = (r.right-r.left)/(LINECOUNT+1);
	//��Ե���������ֵ������һ���������µ�ֵ
	int edge = r.right-r.left-width*(LINECOUNT+1);
	//��������λ�ڴ�������ϵ�е����Ͻǵ�����
	int left = edge/2+width;
	int top = offset+edge/2+width;
	//�����߽����ͻ�������
	POINT pt;

	int i = 0;

	//�ػ桢��ʾ����
	for(i = 0; i < count; i++)
	{
		//��������ת��Ϊ�ͻ�������
		pt.x = existedPoint[i].x*width+left;
		pt.y = existedPoint[i].y*width+top;

		//��������
		//iΪ����������
		if(i%2)
		{
			if(!DisplayWhiteChess(pdc, pt, radius))
				return FALSE;
		}

		//ż��������
		else
		{
			if(!DisplayBlackChess(pdc, pt, radius))
				return FALSE;
		}


	}
	return TRUE;
}

//����Ƿ�Ӯ���˴˾�
//������µ������������������µ�������������
BOOL IsWin(POINT ptIndex, int chessIndex[15][15])
{
	int i = 1;
	int count = 1;		//��¼���������Ӹ���		
	//���ˮƽ����
	//������
	while(chessIndex[ptIndex.x-i][ptIndex.y])
	{
		count++;
		i++;
	}
	//���Ҽ��
	i = 1;
	while(chessIndex[ptIndex.x+i][ptIndex.y])
	{
		count++;
		i++;
	}
	//�ж�
	if(count >= 5)
		return TRUE;

	//�����ֱ����
	//���ϼ��
	i = 1;
	count = 1;
	while(chessIndex[ptIndex.x][ptIndex.y-i])
	{
		count++;
		i++;
	}
	//���Ҽ��
	i = 1;
	while(chessIndex[ptIndex.x][ptIndex.y+i])
	{
		count++;
		i++;
	}
	//�ж�
	if(count >= 5)
		return TRUE;

	//������Խ��߷���
	//�����ϼ��
	i = 1;
	count = 1;
	while(chessIndex[ptIndex.x-i][ptIndex.y-i])
	{
		count++;
		i++;
	}
	//�����¼��
	i = 1;
	while(chessIndex[ptIndex.x+i][ptIndex.y+i])
	{
		count++;
		i++;
	}
	//�ж�
	if(count >= 5)
		return TRUE;

	//��鸱�Խ��߷���
	//�����ϼ��
	i = 1;
	count = 1;
	while(chessIndex[ptIndex.x+i][ptIndex.y-i])
	{
		count++;
		i++;
	}
	//�����¼��
	i = 1;
	while(chessIndex[ptIndex.x-i][ptIndex.y+i])
	{
		count++;
		i++;
	}
	//�ж�
	if(count >= 5)
		return TRUE;

	return FALSE;
}

//��ʾ������״̬������ǰ�ĺڰ�����ɫ
//�����豸�������ָ�룬���µ��������ڴ�С�Լ��߶�ƫ����
void ShowGameStatus(HDC* pdc, int count, RECT r, int offset)
{
	HPEN hPen;
	HPEN hOldPen;
	HFONT hFont;
	HFONT hOldFont;

	hPen=CreatePen(PS_SOLID, 3, RGB(0,0,0));
	hOldPen=SelectObject(*pdc, hPen);

	hFont=CreateFont(offset, (int)(offset/1.5),
		0,0,FW_THIN,FALSE,FALSE,FALSE,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN,TEXT("����"));
	hOldFont=SelectObject(*pdc, hFont);
	if (count%2)
	{
		TextOut(*pdc, 2, 2, TEXT("���ڰ���"),4);
	}
	else
	{
		TextOut(*pdc, 2, 2, TEXT("���ں���"),4);
	}


	SelectObject(*pdc, hOldPen);
	DeleteObject(hPen);
	SelectObject(*pdc, hOldFont);
	DeleteObject(hFont);
}