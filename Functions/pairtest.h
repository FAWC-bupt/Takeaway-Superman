#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <windows.h>
#include "../Global/header.h"

using namespace std;


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
	PIMAGE img[7];
	for (int i = 1; i <= 6; i++)
		img[i] = newimage();
	getimage(img[1], "House.png", 0, 0);
	getimage(img[2], "Restaurant.png", 0, 0);
	getimage(img[3], "Dormitory.png", 0, 0);
	getimage(img[4], "House1.png", 0, 0);
	getimage(img[5], "Restaurant1.png", 0, 0);
	getimage(img[6], "Dormitory1.png", 0, 0);
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			if ((par.is_start && par.start_x == i && par.start_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[abs(Map[i * 2][j * 2])], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x80);
			}
			else if ((par.is_end && par.end_x == i && par.end_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[abs(Map[i * 2][j * 2])], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x20);
			}
			else if (Map[i * 2][j * 2] < 0)	// ͣ��
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_transparent(NULL, img[-Map[i * 2][j * 2] + 3], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK);
			}
			else
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_transparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK);
			}
		}
	for (int i = 1; i <= 6; i++)
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
				Order* p = (Order*)malloc(sizeof(Order));
				p->id = *sum;
				(*sum)++;
				p->rest_x = par->start_x * 2;
				p->rest_y = par->start_y * 2;
				p->cust_x = par->end_x * 2;
				p->cust_y = par->end_y * 2;
				p->begin_time = Time + 1;
				p->end_time = 0x3f3f3f3f;
				p->status = 0;
				push_back_order(p, Buffer);
				ReleaseMutex(hMutex1);
			}
			else if (msg.x >= 700 && msg.y >= 605 && msg.x <= 965 && msg.y <= 690)
			{
				// TODO: ����
				exit(0);
			}
		}
	}
}

void createRoad()
{
	//����һ��imgͼƬ����
	PIMAGE img[3];
	//��������
	for (int i = 0; i < 3; i++)
		img[i] = newimage();
	getimage(img[0], "ʮ��·��.png", 25, 25);
	getimage(img[1], "�����·.png", 25, 25);
	getimage(img[2], "�����·.png", 25, 25);

	setbkcolor(DARKGRAY);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			setviewport(25, 50, 675, 700, 0);
			if (i % 2 == 1 && j % 2 == 0)		//�����·
			{
				putimage(j / 2 * (HWID + RWID), (i - 1) / 2 * (HWID + RWID) + HWID, img[1]);
				putimage(j / 2 * (HWID + RWID) + RWID, (i - 1) / 2 * (HWID + RWID) + HWID, img[1]);
			}
			else if (i % 2 == 0 && j % 2 == 1)	//�����·
			{
				putimage((j - 1) / 2 * (HWID + RWID) + HWID, i / 2 * (HWID + RWID), img[2]);
				putimage((j - 1) / 2 * (HWID + RWID) + HWID, i / 2 * (HWID + RWID) + RWID, img[2]);
			}
			else if (i % 2 == 1 && j % 2 == 1)	//ʮ��·��
			{
				putimage((j - 1) / 2 * (HWID + RWID) + HWID, (i - 1) / 2 * (HWID + RWID) + HWID, img[0]);
			}
		}
	}
	setviewport(0, 0, 1000, 750, 0);
	//�ͷŶ���
	for (int i = 0; i < 3; i++)
		delimage(img[i]);
}

//void DrawRider(int* countTime)
//{
//	PIMAGE rider_img = newimage();
//	for (int i = 0; i < 17; i++)
//	{
//		for (int j = 0; j < 17; j++)
//		{
//			if (Map[i][j] >= 4 && Map[i][j] <= 9)
//			{
//				int pathMode = Map[i][j] - 4;
//				if (i % 2 == 1 && j % 2 == 0)	//�����·
//				{
//					if (pathMode >= 0 && pathMode <= 2)					//��������
//					{
//						if (*countTime <= 152)	//������
//						{
//							getimage(rider_img, "Rider(right).png", 26, 24);
//							putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
//						}
//						else if (*countTime > 152 && *countTime <= 300)	//������ͬ������
//						{
//							switch (pathMode)
//							{
//							case 0:			//������
//								getimage(rider_img, "Rider(right).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 9, BLACK);
//								break;
//							case 1:			//������
//								getimage(rider_img, "Rider(up).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (*countTime - 152) / 4, BLACK);
//								break;
//							case 2:			//������
//								getimage(rider_img, "Rider(down).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (*countTime - 152) / 4, BLACK);
//								break;
//							}
//						}
//						else											//ͣһ��(��ֹ���)
//						{
//							switch (pathMode)
//							{
//							case 0:
//								getimage(rider_img, "Rider(right).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (300) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 9, BLACK);
//								break;
//							case 1:
//								getimage(rider_img, "Rider(up).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (300 - 152) / 4, BLACK);
//								break;
//							case 2:
//								getimage(rider_img, "Rider(down).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (300 - 152) / 4, BLACK);
//								break;
//							}
//						}
//
//					}
//					else												//��������
//					{
//						if (*countTime <= 152)	//������
//						{
//							getimage(rider_img, "Rider(left).png", 26, 24);
//							putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
//						}
//						else if (*countTime > 152 && *countTime <= 300)	//������ͬ������
//						{
//							switch (pathMode)
//							{
//							case 3:			//������
//								getimage(rider_img, "Rider(left).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
//								break;
//							case 4:			//������
//								getimage(rider_img, "Rider(up).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (*countTime - 152) / 4, BLACK);
//								break;
//							case 5:			//������
//								getimage(rider_img, "Rider(down).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (*countTime - 152) / 4, BLACK);
//								break;
//							}
//						}
//						else											//ͣһ��(��ֹ���)
//						{
//							switch (pathMode)
//							{
//							case 3:
//								getimage(rider_img, "Rider(left).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (300) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
//								break;
//							case 4:
//								getimage(rider_img, "Rider(up).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (300 - 152) / 4, BLACK);
//								break;
//							case 5:
//								getimage(rider_img, "Rider(down).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (300 - 152) / 4, BLACK);
//								break;
//							}
//						}
//					}
//				}
//				else if (i % 2 == 0 && j % 2 == 1)	//�����·
//				{
//					if (pathMode >= 0 && pathMode <= 2)					//��������
//					{
//						if (*countTime <= 152)	//������
//						{
//							getimage(rider_img, "Rider(up).png", 17, 26);
//							putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (*countTime) / 4, BLACK);
//						}
//						else if (*countTime > 152 && *countTime <= 300)		//��������������
//						{
//							switch (pathMode)
//							{
//							case 0:			//������
//								getimage(rider_img, "Rider(up).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (*countTime) / 4, BLACK);
//								break;
//							case 1:			//������
//								getimage(rider_img, "Rider(left).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
//								break;
//							case 2:			//������
//								getimage(rider_img, "Rider(right).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
//								break;
//							}
//						}
//						else											//ͣһ��(��ֹ���)
//						{
//							switch (pathMode)
//							{
//							case 0:
//								getimage(rider_img, "Rider(up).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (300) / 4, BLACK);
//								break;
//							case 1:
//								getimage(rider_img, "Rider(left).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
//								break;
//							case 2:
//								getimage(rider_img, "Rider(right).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
//								break;
//							}
//						}
//					}
//					else												//��������
//					{
//						if (*countTime <= 152)	//������
//						{
//							getimage(rider_img, "Rider(down).png", 17, 26);
//							putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (*countTime) / 4, BLACK);
//						}
//						else if (*countTime > 152 && *countTime <= 300)	//��������������
//						{
//							switch (pathMode)
//							{
//							case 3:			//������
//								getimage(rider_img, "Rider(down).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (*countTime) / 4, BLACK);
//								break;
//							case 4:			//������
//								getimage(rider_img, "Rider(left).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
//								break;
//							case 5:			//������
//								getimage(rider_img, "Rider(right).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
//								break;
//							}
//						}
//						else											//ͣһ��(��ֹ���)
//						{
//							switch (pathMode)
//							{
//							case 3:
//								getimage(rider_img, "Rider(down).png", 17, 26);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (300) / 4, BLACK);
//								break;
//							case 4:
//								getimage(rider_img, "Rider(left).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
//								break;
//							case 5:
//								getimage(rider_img, "Rider(right).png", 26, 24);
//								putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
//								break;
//							}
//						}
//					}
//				}
//			}
//			else if (Map[i][j] == 10)
//			{
//				if (i % 2 == 1 && j % 2 == 0)//�����·
//				{
//					getimage(rider_img, "Rider(right).png", 26, 24);
//					putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
//				}
//				else if (i % 2 == 0 && j % 2 == 1)
//				{
//					getimage(rider_img, "Rider(down).png", 17, 26);
//					putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1, BLACK);
//				}
//			}
//		}
//	}
//	delimage(rider_img);
//}

void DrawRider(int* countTime)
{
	PIMAGE rider_img = newimage();

	RiderList* nowRider = AllRiderLog->Nxt_rider;
	while (nowRider)
	{

		int i = nowRider->Cur_rider->rider_x;
		int j = nowRider->Cur_rider->rider_y;
		int pathMode = nowRider->Cur_rider->path_mode;
		if (i % 2 == 1 && j % 2 == 0)	//�����·
		{
			if (pathMode >= 0 && pathMode <= 2)					//��������
			{
				if (*countTime <= 152)	//������
				{
					getimage(rider_img, "Rider(right).png", 26, 24);
					putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300)	//������ͬ������
				{
					switch (pathMode)
					{
					case 0:			//������
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 9, BLACK);
						break;
					case 1:			//������
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (*countTime - 152) / 4, BLACK);
						break;
					case 2:			//������
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (*countTime - 152) / 4, BLACK);
						break;
					}
				}
				else											//ͣһ��(��ֹ���)
				{
					switch (pathMode)
					{
					case 0:
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (300) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 9, BLACK);
						break;
					case 1:
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (300 - 152) / 4, BLACK);
						break;
					case 2:
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (300 - 152) / 4, BLACK);
						break;
					}
				}

			}
			else if (pathMode >= 3 && pathMode <= 5)												//��������
			{
				if (*countTime <= 152)	//������
				{
					getimage(rider_img, "Rider(left).png", 26, 24);
					putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300)	//������ͬ������
				{
					switch (pathMode)
					{
					case 3:			//������
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
						break;
					case 4:			//������
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (*countTime - 152) / 4, BLACK);
						break;
					case 5:			//������
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (*countTime - 152) / 4, BLACK);
						break;
					}
				}
				else											//ͣһ��(��ֹ���)
				{
					switch (pathMode)
					{
					case 3:
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (300) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
						break;
					case 4:
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (300 - 152) / 4, BLACK);
						break;
					case 5:
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (300 - 152) / 4, BLACK);
						break;
					}
				}
			}
			else if (pathMode == 6)
			{
				getimage(rider_img, "Rider(right).png", 26, 24);
				putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
			}
		}
		else if (i % 2 == 0 && j % 2 == 1)	//�����·
		{
			if (pathMode >= 0 && pathMode <= 2)					//��������
			{
				if (*countTime <= 152)	//������
				{
					getimage(rider_img, "Rider(up).png", 17, 26);
					putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (*countTime) / 4, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300)		//��������������
				{
					switch (pathMode)
					{
					case 0:			//������
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (*countTime) / 4, BLACK);
						break;
					case 1:			//������
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					case 2:			//������
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					}
				}
				else											//ͣһ��(��ֹ���)
				{
					switch (pathMode)
					{
					case 0:
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (300) / 4, BLACK);
						break;
					case 1:
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					case 2:
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					}
				}
			}
			else if (pathMode >= 3 && pathMode <= 5)											//��������
			{
				if (*countTime <= 152)	//������
				{
					getimage(rider_img, "Rider(down).png", 17, 26);
					putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (*countTime) / 4, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300)	//��������������
				{
					switch (pathMode)
					{
					case 3:			//������
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (*countTime) / 4, BLACK);
						break;
					case 4:			//������
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					case 5:			//������
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					}
				}
				else											//ͣһ��(��ֹ���)
				{
					switch (pathMode)
					{
					case 3:
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (300) / 4, BLACK);
						break;
					case 4:
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					case 5:
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					}
				}
			}
			else if (pathMode == 6)
			{
				getimage(rider_img, "Rider(down).png", 17, 26);
				putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1, BLACK);
			}
		}
		nowRider = nowRider->Nxt_rider;
	}

	delimage(rider_img);
}

void printText()
{
	char s[110];
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfontbkcolor(EGERGB(220, 220, 220));
	setfont(50, 0, "΢���ź�");
	sprintf(s, "ʱ��: %d\nǮ: %d\n�ӵ���: %d\n�����: %d\n��ʱ��: %d", Time, CompanyMoney, CompanyOrderSum, CompanyOrderFinish, CompanyOrderOverTime);
	outtextrect(700, 60, 965, 475, s);
}


unsigned __stdcall runGraph(void* pArgument)
{
	int sum = 0;	// ��¼���������������ڱ�дID
	Pair par;
	int countTime = 0;
	initgraph(1000, 750);
	createGraph();
	for (; is_run(); delay_fps(160))
	{
		createMap(par);
		clickMap(&par, &sum);
		createRoad();
		printText();
		if (mapsignal)
		{
			//WaitForSingleObject(hMutex2, INFINITE);
			DrawRider(&countTime);
			mapsignal = 0;
			countTime = 0;
			//  //�ź�
			//ReleaseMutex(hMutex2);
		}
		else
			DrawRider(&countTime);
		countTime++;
	}
	_endthreadex(0);
	return 0;
}


void mainFunction()
{
	////��ļ����

	//while (CompanyMoney >= 400)
	//{
	//	hireRider();
	//}
	//updateMap();
	HANDLE hThread;
	clock_t start_clock, end_clock; // ���ڼ����������ʱ��
	//initMap();
	unsigned int ThreadID = 1;
	hThread = (HANDLE)_beginthreadex(NULL, 0, runGraph, NULL, 0, &ThreadID);
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
	//while (Buffer->Nxt_order || !isAllOrderFinished()) // ���������ǻ�����Ϊ��
	for (;;)
	{
		start_clock = clock();
		Time++;
		//���������еĶ����ŵ�ȫ�ֶ�����¼��
		WaitForSingleObject(hMutex1, INFINITE);
		OrderList* tempOrderList = Buffer->Nxt_order;
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
			hireRider();
		//�ɵ�֮ǰ�����ֱ�����ɵĶ�������
		initRiderBag();
		//�ɵ��㷨
		arrangeNewOrder(); // �˴��������Ż�
		//�ж��Ƿ�ʱ���Ʋ�
		isAnyOrderOverTime();
		//�����ƶ�
		AllRiderMove();
		//�ж�ÿһ�������Ƿ����
		//���ÿһ����Ҫ��ɵĶ��� ���������ֱ����ﲻ��������ɵĶ��� ������ļ�ʱ�ж�ͣ��ʹ�ã�
		int isAnyOrderComplish = 0;
		RiderList* tempRider = AllRiderLog->Nxt_rider;
		while (tempRider) // ����
		{
			OrderList* tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
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
		//hMutex2 = CreateMutex(NULL, FALSE, NULL);
		//WaitForSingleObject(hMutex2, INFINITE);
		updateMap();
		//ReleaseMutex(hMutex2);
		mapsignal = 1;
		end_clock = clock();
		// TIME_UNIT * 1000 - (end_clock - start_clock)
		api_sleep(TIME_UNIT * 2000 - (end_clock - start_clock)); // ׼ȷ2��ˢ��
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	closegraph(); // �ر�ͼ�ν���
}