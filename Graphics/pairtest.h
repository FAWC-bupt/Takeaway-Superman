#include "../Global/header.h"
#include <MMSystem.h>
#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

int mapsignal = 0; // �Ƿ�������ֶ���

HANDLE hMutex1, hMutex2, hMutex3; // ������

/*
	�����û����������
	Pair *par��
	int *sum�������������ڼ�¼��Buffer����Ķ���ID

 */
void clickMap(Pair *par, int *sum)
{
	mouse_msg msg = {0};
	int now_x = -1;
	int now_y = -1;
	if (mousemsg())
	{
		msg = getmouse();
		if (msg.is_left() && msg.is_down())
		{
			now_x = graphXToMapY(msg.x);
			now_y = graphYToMapX(msg.y);
			if (now_x >= 0 && now_x <= 8 && now_y >= 0 && now_y <= 8)
			{
				if (par->is_start && now_y == par->start_x && now_x == par->start_y)
				{
					par->is_start = 0;
				}
				else if (par->is_end && now_y == par->end_x && now_x == par->end_y)
				{
					par->is_end = 0;
				}
				else if (!par->is_start)
				{
					par->is_start = 1;
					par->start_x = now_y;
					par->start_y = now_x;
				}
				else if (!par->is_end)
				{
					par->is_end = 1;
					par->end_x = now_y;
					par->end_y = now_x;
				}
			}
			else if (msg.x >= 700 && msg.y >= 510 && msg.x <= 965 && msg.y <= 595)
			{
				par->is_start = 0;
				par->is_end = 0;
				// ��Buffer������
				WaitForSingleObject(hMutex1, INFINITE);
				Order *p = (Order *)malloc(sizeof(Order));
				p->id = *sum;
				(*sum)++;
				p->rest_x = par->start_x * 2;
				p->rest_y = par->start_y * 2;
				p->cust_x = par->end_x * 2;
				p->cust_y = par->end_y * 2;
				p->begin_time = Time + 1;
				p->turn_time = 0x3f3f3f3f;
				p->end_time = 0x3f3f3f3f;
				p->status = 0;
				push_back_order(p, Buffer);
				ReleaseMutex(hMutex1);
			}
			else if (msg.x >= 700 && msg.y >= 605 && msg.x <= 965 && msg.y <= 690)
			{
				if (!CompanyOrderSum)
					exit(0);
				IsEnd = 1;
			}
		}
	}
}

/*
	��Ļ���Ϸ����������
 */
void printText()
{
	char s[110];
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfontbkcolor(EGERGB(220, 220, 220));
	setcolor(BLACK);
	setfont(40, 0, "΢���ź�");
	sprintf(s, "ʱ��: %d\nǮ: %d\n�ӵ���: %d\n�����: %d\n��ʱ��: %d", Time, CompanyMoney, CompanyOrderSum, CompanyOrderFinish, CompanyOrderOverTime);
	outtextrect(700, 60, 300, 300, s);
	PIMAGE img[3];
	for (int i = 0; i < 3; i++)
		img[i] = newimage();
	getimage(img[0], "House.png", 0, 0);
	getimage(img[1], "Restaurant.png", 0, 0);
	getimage(img[2], "Dormitory.png", 0, 0);
	putimage(700, 320, img[0]);
	putimage(800, 320, img[1]);
	putimage(900, 320, img[2]);
	setfont(16, 0, "����");
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	//sprintf(s, "%d", (*sum);
	outtextrect(705, 370, 50, 50, "����");
	outtextrect(800, 370, 50, 50, "�͹�(A)");
	outtextrect(900, 370, 50, 50, "����(B)");
	setfont(25, 0, "΢���ź�");
	outtextrect(700, 400, 220, 220, "*������͸��ѡ�в���\n*��͸��ѡ������\n*����ʾͣ��");
	for (int i = 0; i < 3; i++)
		delimage(img[i]);
}

unsigned __stdcall runGraph(void *cnt_hire)
{
	int *cnt = (int *)cnt_hire;
	int sum = 0; // ��¼���������������ڱ�дID
	Pair par;
	int countTime = 0;
	initgraph(1000, 750);
	createGraph();
	for (; is_run(); delay_fps(160))
	{
		createMap(par, &sum);
		clickMap(&par, &sum);
		createRoad();
		if (IsEnd == 2)
		{
			gameSuccessG();
			break;
		}
		else if (IsEnd == 3)
		{
			gameOverG();
			break;
		}
		else if (IsEnd == 4)
		{
			gameOverG();
			break;
		}
		printText();
		if (mapsignal)
		{
			drawRider(&countTime, cnt);
			mapsignal = 0;
			countTime = 0;
		}
		else
			drawRider(&countTime, cnt);
		countTime++;
	}
	getch();
	_endthreadex(0);
	return 0;
}

/*
	������룬���������������
 */
void mainFunction()
{
	PlaySound("11303.wav", NULL, SND_LOOP | SND_ASYNC);
	int cnt_hire = 0; // ��¼ÿ����ļ��������
	updateMap();
	HANDLE hThread;
	clock_t start_clock, end_clock; // ���ڼ����������ʱ��
	//initMap();
	unsigned int ThreadID = 1;
	hThread = (HANDLE)_beginthreadex(NULL, 0, runGraph, (void *)&cnt_hire, 0, &ThreadID);
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
	//while (Buffer->Nxt_order || !isAllOrderFinished()) // ���������ǻ�����Ϊ��
	while (!(IsEnd == 1 && isAllOrderFinished()))
	{
		cnt_hire = 0;
		start_clock = clock();
		Time++;
		//���������еĶ����ŵ�ȫ�ֶ�����¼��
		WaitForSingleObject(hMutex1, INFINITE);
		OrderList *tempOrderList = Buffer->Nxt_order;
		while (tempOrderList)
		{
			if (tempOrderList->Cur_order->begin_time == Time)
			{
				push_back_order(tempOrderList->Cur_order, AllOrderLog);
				tempOrderList = delete_order(tempOrderList);
				CompanyOrderSum++; // ��˾���ܶ���+1
			}
			tempOrderList = tempOrderList->Nxt_order;
		}
		ReleaseMutex(hMutex1);
		//��ļ����
		while (CompanyMoney >= 400)
		{
			hireRider();
			cnt_hire++;
		}
		//�ɵ�֮ǰ�����ֱ�����ɵĶ�������
		initRiderBag();
		//�ɵ��㷨
		arrangeNewOrder(); // �˴��������Ż�
		//�ж��Ƿ�ʱ���Ʋ�
		isAnyOrderOverTime();
		if (IsEnd == 3 || IsEnd == 4)
		{
			break;
		}
		//�����ƶ�
		AllRiderMove();
		mapsignal = 1;
		//�ж�ÿһ�������Ƿ����
		//���ÿһ����Ҫ��ɵĶ��� ���������ֱ����ﲻ��������ɵĶ��� ������ļ�ʱ�ж�ͣ��ʹ�ã�
		end_clock = clock();
		api_sleep(TIME_UNIT * 1500 - (end_clock - start_clock)); // ׼ȷ2��ˢ��
		start_clock = clock();
		int isAnyOrderComplish = 0;
		RiderList *tempRider = AllRiderLog->Nxt_rider;
		while (tempRider) // ����
		{
			OrderList *tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
			while (tempOrder) // ����
			{
				if (isComplishOrder(tempOrder, tempRider))
				{
					tempOrder = complishOrder(tempOrder);
					isAnyOrderComplish = 1;
				}
				tempOrder = tempOrder->Nxt_order;
			}
			tempRider = tempRider->Nxt_rider;
		}
		updateMap();
		////end_clock = clock();
		// TIME_UNIT * 1000 - (end_clock - start_clock)
	}
	if (!(IsEnd == 3 || IsEnd == 4))
		IsEnd = 2;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	closegraph(); // �ر�ͼ�ν���
}