//Gobang.h
//�����庯����ʵ���ļ�
#ifndef _WINDOWS_
#include <windows.h>
#endif

//��ʾ��������Ϸ����
//�������Ϊ�豸�������ָ��pdc����ǰ���ڴ�Сr�Լ��߶ȷ����ϵ�ƫ��offset
BOOL DisplayInitBackground(HDC* pdc, RECT r, unsigned offset);

//�жϵ���������Ƿ��������ߵĽ����ϣ��Ƿ���Է�������
//����ͻ�ȥ����ϵ�еĺ������ꡢ��ǰ�����ڿͻ�����ϵ�е�λ�á��߶�ƫ���Լ�
//����������ƫ��
BOOL IsIntersection(int x, int y, RECT r, int offset, int shift);

//�ҵ������ĺϷ������Ӧ�������߽����λ��
//���뵥���ĺ������꣬���ڿͻ���λ�á��߶�ƫ�ƺ�����ĵ���ƫ��
POINT FindPosition(int x, int y, RECT r, int offset, int shift);

//��ָ�������̽������ʾ����
//�������Ϊ�豸������ָ��,���̽����λ�������Ӱ뾶
BOOL DisplayBlackChess(HDC* pdc, POINT pos, int radius);

//��ָ�������̽������ʾ����
//�������Ϊ�豸������ָ��,���̽����λ�������Ӱ뾶
BOOL DisplayWhiteChess(HDC* pdc, POINT pos, int radius);

//��鵥���������߽�����Ƿ���������
//�������Ϊ�������ӵ���������ͷָ�룬���µ����Ӹ�������жϵ���������
BOOL IsChessExisted(POINT* existedPoint, int count, POINT pt);

//ͨ�����ӵĿͻ�������������Ӷ�Ӧ����������
//�������ӵĿͻ������꣬�ͻ�����С��߶�ƫ��
POINT FindIndex(POINT pt,  RECT r, int offset);

//���������������ػ棩��ʾ����
//�������Ϊ�豸������ָ��,���̽����λ����������ͷָ�룬
//���µ����Ӹ����Ϳͻ�����С���߶�ƫ�������Ӱ뾶
BOOL DisplayChess(HDC* pdc, POINT* existedPoint,
				 int count, RECT r,  int offset, int radius);

//����Ƿ�Ӯ���˴˾�
//������µ������������������µ�������������
BOOL IsWin(POINT ptIndex, int chessIndex[15][15]);

//��ʾ������״̬������ǰ�ĺڰ�����ɫ
//�����豸�������ָ�룬���µ��������ڴ�С�Լ��߶�ƫ����
void ShowGameStatus(HDC* pdc, int count, RECT r, int offset);