#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <windows.h>
#include "../Global/header.h"

using namespace std;

const int HWID = 50;
const int RWID = 25;

struct Pair
{
	int start_x, start_y;
	int end_x, end_y;
	int is_start = 0, is_end = 0;
};

void createGraph()
{
	// ����
	setbkcolor(EGERGB(238, 233, 233));
	// ģ��
	setfillcolor(LIGHTGRAY);
	bar(25, 50, 675, 700);
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfillcolor(EGERGB(176, 196, 222));
	bar(690, 510, 975, 595);
	setfillcolor(EGERGB(233, 150, 122));
	bar(690, 615, 975, 700);
	// ��ť������
	setfontbkcolor(EGERGB(176, 196, 222));
	setcolor(EGERGB(119, 136, 153));
	setfont(50, 0, "����");
	outtextxy(770, 530, "ȷ��");
	setfontbkcolor(EGERGB(233, 150, 122));
	outtextxy(770, 635, "�˳�");
}

void createMap(Pair par)
{
	PIMAGE img[6];
	for (int i = 1; i <= 3; i++)
		img[i] = newimage();
	getimage(img[1], "House.png", 0, 0);
	getimage(img[2], "Restaurant.png", 0, 0);
	getimage(img[3], "Dormitory.png", 0, 0);
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			if ((par.is_start && par.start_x == i && par.start_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x80);
			}
			else if ((par.is_end && par.end_x == i && par.end_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x20);
			}
			else
				putimage_transparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK);
			//putimage(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, img[Map[i * 2][j * 2]]);
		}
	//	if(sub_cnt)
	//	{
	//		sub_cnt = 0;
	//	}
	for (int i = 1; i <= 3; i++)
		delimage(img[i]);
}
// ��ͼ�е�x����ת�������������Ͻ�y����
int mapXToGraphY(int now_x)
{
	now_x /= 2;
	return (HWID + (HWID + RWID) * now_x);
}
// ��ͼ�е�y����ת�������������Ͻ�x����
int mapYToGraphX(int now_y)
{
	now_y /= 2;
	return (RWID + (HWID + RWID) * now_y);
}
// ����x����ת��Ϊ��ͼy����
int graphXToMapY(int now_x)
{
	now_x -= RWID;
	now_x /= (HWID + RWID);
	return now_x;
}
// ����y����ת��Ϊ��ͼx����
int graphYToMapX(int now_y)
{
	now_y -= HWID;
	now_y /= (HWID + RWID);
	return now_y;
}

void clickMap(Pair* par, int* sum)
{
	mouse_msg msg = { 0 };
	int now_x = -1;
	int now_y = -1;
	int sub_cnt = 0;
	int ext_cnt = 0;
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
				sub_cnt = 1;
				// ��Buffer������
				Order* p = (Order*)malloc(sizeof(Order));
				p->id = (*sum)++;
				p->rest_x = par->start_x * 2;
				p->rest_y = par->start_y * 2;
				p->cust_x = par->end_x * 2;
				p->cust_y = par->end_y * 2;
				p->begin_time = Time;
				p->end_time = 0x3f3f3f3f;
				push_back_order(p, Buffer);
				free(p);
			}
			else if (msg.x >= 700 && msg.y >= 605 && msg.x <= 965 && msg.y <= 690)
			{
				// TODO: ����
				exit(0);
			}
		}
	}
}

void mainFunction()
{
	initMap();
	int sum = 0;	// ��¼���������������ڱ�дID��
	Pair par;
	initgraph(1000, 750);
	createGraph();

	for (; is_run(); delay_fps(120))
	{
		clickMap(&par, &sum);
		createMap(par);
	}
	closegraph(); // �ر�ͼ�ν���




	//while (Buffer->Nxt_order || !isAllOrderFinished()) // ���������ǻ�����Ϊ��
	//{
	//	Time++;
	//	//���������еĶ����ŵ�ȫ�ֶ�����¼��
	//	OrderList* tempOrderList = Buffer->Nxt_order;
	//	while (tempOrderList)
	//	{
	//		if (tempOrderList->Cur_order->begin_time == Time)
	//		{
	//			push_back_order(tempOrderList->Cur_order, AllOrderLog);
	//			tempOrderList = delete_order(tempOrderList);
	//			CompanyOrderSum++; // ��˾���ܶ���+1
	//		}
	//		tempOrderList = tempOrderList->Nxt_order;
	//	}
	//	//��ļ����

	//	while (CompanyMoney >= 400)
	//	{
	//		hireRider();
	//	}
	//	//�ɵ�֮ǰ�����ֱ�����ɵĶ�������
	//	initRiderBag();
	//	//�ɵ��㷨
	//	arrangeNewOrder(); // �˴��������Ż�
	//	//�ж��Ƿ�ʱ���Ʋ�
	//	isAnyOrderOverTime();
	//	//�����ƶ�
	//	AllRiderMove();
	//	//�ж�ÿһ�������Ƿ����
	//	//���ÿһ����Ҫ��ɵĶ��� ���������ֱ����ﲻ��������ɵĶ��� ������ļ�ʱ�ж�ͣ��ʹ�ã�
	//	int isAnyOrderComplish = 0;
	//	RiderList* tempRider = AllRiderLog->Nxt_rider;
	//	while (tempRider) // ����
	//	{
	//		OrderList* tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
	//		while (tempOrder) // ����
	//		{
	//			if (isComplishOrder(tempOrder, tempRider))
	//			{
	//				tempOrder = complishOrder(tempOrder);
	//				isAnyOrderComplish = 1;
	//			}
	//			tempOrder = tempOrder->Nxt_order;
	//		}
	//		tempRider = tempRider->Nxt_rider;
	//	}
	//	//�ж������ʱ�����������ˢ��һ��
	//	if (isAnyOrderComplish)
	//	{
	//		system("cls");
	//		outputMap();
	//		outputKey();
	//	}
	//	//����ļ�
	//	outputOnFile();
	//}
}