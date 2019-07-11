#include "../Global/header.h"
/*
	�Ʋ����㺯��
*/

/*
	�ж�ÿ�������Ƿ����
	��ɷ���1��δ��ɷ���0
*/
int isAllOrderFinished()
{
	OrderList *nowOrder = AllOrderLog->Nxt_order;
	if (nowOrder == NULL)
	{
		return 0;
	}
	while (nowOrder)
	{
		if (nowOrder->Cur_order->status != 3)
			return 0;
		nowOrder = nowOrder->Nxt_order;
	}
	return 1;
}
/*
	�Ʋ�����
	�����г����øú��������(int reason)��
	0. �Ʋ����ʽ�Ϊ����
	1. �ܵ�������DEAD_TIME��ʱ�䵥λ�ӵ�
	2. �����ϵ����ڶ��γ�ʱ�����ӵ�����FINE_SECOND_TIMEʱ�䵥λ��δ�ʹ�
	3. ����״̬����
	4. �����ʽ����
	5. ���������쳣��eg. զ�����ܵ��������ˣ���
*/
void gameOver(int reason)
{
	printf("\n------------------------------------------------\n");
	printf("��˾�Ѿ��Ʋ�!!!\n");
	printf("��˾�Ʋ�ԭ��:");
	if (reason == 0)
		printf("�Ʋ�\n");
	else if (reason == 1)
		printf("�ܵ�������ִ�գ�\n");
	else if (reason == 2)
		printf("����ϵ����Ʋ���\n");
	else
		printf("�쳣ԭ��,�������Ϊ%d\n", reason);
	printf("���ι�˾���ڵ�ַ:(%d��%d)\n", COMPANY_X, COMPANY_Y);
	printf("��˾ʣ���ֽ���:%d\n", CompanyMoney);
	printf("��˾��������:%d\n", CompanyRiderCount);
	printf("��˾��������:%d\n", CompanyMoney + CompanyRiderCount * HIRE_MONEY - INIT_MONEY);
	printf("�Ʋ�ʱ��:%d��ʱ�䵥λ\n", Time);
	printf("��˾�ӵ���:%d\n", CompanyOrderSum);
	printf("��˾��ɵ���:%d\n", CompanyOrderFinish);
	printf("��˾��ʱ����:%d\n", CompanyOrderOverTime);

	// �ͷ�ȫ�ֱ����ڴ�
	OrderList *p1 = AllOrderLog;
	RiderList *p2 = AllRiderLog;
	OrderList *p3 = Buffer;

	// �ͷ�AllOrderLog
	while (p1)
	{
		free(p1->Pre_order);
		free(p1->Cur_order);
		p1->Pre_order = NULL;
		p1->Cur_order = NULL;
		p1 = p1->Nxt_order;
	}
	AllOrderLog = NULL;
	// �ͷ�Buffer
	while (p3)
	{
		free(p3->Pre_order);
		free(p3->Cur_order);
		p3->Pre_order = NULL;
		p3->Cur_order = NULL;
		p3 = p3->Nxt_order;
	}
	Buffer = NULL;
	// �ͷ�AllRiderLog
	while (p2)
	{
		if (p2->Cur_rider)
		{
			free(p2->Pre_rider);
			p1 = p2->Cur_rider->Bag;
			// �ͷ�bag
			while (p1)
			{
				free(p1->Pre_order);
				free(p1->Cur_order);
				p1->Pre_order = NULL;
				p1->Cur_order = NULL;
				p1 = p1->Nxt_order;
			}
			free(p2->Cur_rider);
		}
		else
		{
			break;
		}
		p2->Pre_rider = NULL;
		p2->Cur_rider = NULL;
		p2 = p2->Nxt_rider;
	}
	AllRiderLog = NULL;
	printf("GAME OVER!!!\n");
	system("PAUSE");
	exit(0);
}

/*
	�Ʋ����㣨�������棩
*/

void gameOverG()
{
	char s[201];
	PIMAGE img[2];
	img[0] = newimage();
	img[1] = newimage();
	getimage(img[0], "BK.png", 0, 0);
	getimage(img[1], "lose.png", 0, 0);
	putimage_alphablend(NULL, img[0], 25, 50, 0x60);
	putimage_transparent(NULL, img[1], 50, 225, BLACK);
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfontbkcolor(EGERGB(220, 220, 220));
	setfont(30, 0, "΢���ź�");
	if (IsEnd == 3)
	{
		sprintf(s, "��˾���Ʋ���\n");
		outtextrect(700, 60, 965, 475, s);
	}
	else if (IsEnd == 4)
	{
		sprintf(s, "��˾�ѱ�����ִ�գ�\n");
		outtextrect(700, 60, 965, 475, s);
	}
	sprintf(s, "���ι�˾���ڵ�ַ:(%d��%d)\n", COMPANY_X, COMPANY_Y);
	outtextrect(700, 90, 965, 475, s);
	sprintf(s, "��˾ʣ���ֽ���:%d\n", CompanyMoney);
	outtextrect(700, 120, 965, 475, s);
	sprintf(s, "��˾��������:%d\n", CompanyRiderCount);
	outtextrect(700, 150, 965, 475, s);
	sprintf(s, "��˾��������:%d\n", CompanyMoney + CompanyRiderCount * HIRE_MONEY - INIT_MONEY);
	outtextrect(700, 180, 965, 475, s);
	sprintf(s, "��Ӫʱ��:%d��ʱ�䵥λ\n", Time);
	outtextrect(700, 210, 965, 475, s);
	sprintf(s, "��˾�ӵ���:%d\n", CompanyOrderSum);
	outtextrect(700, 240, 965, 475, s);
	sprintf(s, "��˾��ɵ���:%d\n", CompanyOrderFinish);
	outtextrect(700, 270, 965, 475, s);
	sprintf(s, "��˾��ʱ����:%d\n", CompanyOrderOverTime);
	outtextrect(700, 300, 965, 475, s);
	sprintf(s, "��������Լ���...\n");
	outtextrect(700, 330, 965, 475, s);
	getch();
	delimage(img[0]);
	delimage(img[1]);
	// �ͷ�ȫ�ֱ����ڴ�
	OrderList *p1 = AllOrderLog;
	RiderList *p2 = AllRiderLog;
	OrderList *p3 = Buffer;

	// �ͷ�AllOrderLog
	while (p1)
	{
		free(p1->Pre_order);
		free(p1->Cur_order);
		p1->Pre_order = NULL;
		p1->Cur_order = NULL;
		p1 = p1->Nxt_order;
	}
	AllOrderLog = NULL;
	// �ͷ�Buffer
	while (p3)
	{
		free(p3->Pre_order);
		free(p3->Cur_order);
		p3->Pre_order = NULL;
		p3->Cur_order = NULL;
		p3 = p3->Nxt_order;
	}
	Buffer = NULL;
	// �ͷ�AllRiderLog
	while (p2)
	{
		if (p2->Cur_rider)
		{
			free(p2->Pre_rider);
			p1 = p2->Cur_rider->Bag;
			// �ͷ�bag
			while (p1)
			{
				free(p1->Pre_order);
				free(p1->Cur_order);
				p1->Pre_order = NULL;
				p1->Cur_order = NULL;
				p1 = p1->Nxt_order;
			}
			free(p2->Cur_rider);
		}
		else
		{
			break;
		}
		p2->Pre_rider = NULL;
		p2->Cur_rider = NULL;
		p2 = p2->Nxt_rider;
	}
	AllRiderLog = NULL;
}

/*
	��������
	�ú���Ӧ��main�е���
	�����г����øú����������
	1. �������ֶ�������Ϸ
	2. �����ļ����޸��ඩ����������֪���������
*/

void gameSuccess()
{
	printf("\n------------------------------------------------\n");
	printf("��˾�������!!!You are the true Takeaway Superman!\n");
	printf("���ι�˾���ڵ�ַ:(%d��%d)\n", COMPANY_X, COMPANY_Y);
	printf("��˾ʣ���ֽ���:%d\n", CompanyMoney);
	printf("��˾��������:%d\n", CompanyRiderCount);
	printf("��˾��������:%d\n", CompanyMoney + CompanyRiderCount * HIRE_MONEY - INIT_MONEY);
	printf("���ʱ��:%d��ʱ�䵥λ\n", Time);
	printf("��˾�ӵ���:%d\n", CompanyOrderSum);
	printf("��˾��ɵ���:%d\n", CompanyOrderFinish);
	printf("��˾��ʱ����:%d\n", CompanyOrderOverTime);

	// �ͷ�ȫ�ֱ����ڴ�
	OrderList *p1 = AllOrderLog;
	RiderList *p2 = AllRiderLog;
	OrderList *p3 = Buffer;
	// �ͷ�AllOrderLog
	while (p1)
	{
		free(p1->Pre_order);
		free(p1->Cur_order);
		p1->Pre_order = NULL;
		p1->Cur_order = NULL;
		p1 = p1->Nxt_order;
	}
	AllOrderLog = NULL;
	// �ͷ�Buffer
	while (p3)
	{
		free(p3->Pre_order);
		free(p3->Cur_order);
		p3->Pre_order = NULL;
		p3->Cur_order = NULL;
		p3 = p3->Nxt_order;
	}
	Buffer = NULL;
	// �ͷ�AllRiderLog
	while (p2)
	{
		free(p2->Pre_rider);
		if (p2->Cur_rider != NULL)
		{
			free(p2->Cur_rider->Bag);
			p2->Cur_rider->Bag = NULL;
		}
		free(p2->Cur_rider);
		p2->Pre_rider = NULL;
		p2->Cur_rider = NULL;
		p2 = p2->Nxt_rider;
	}
	AllRiderLog = NULL;
	printf("GAME SUCCESS!!!\n");
	system("PAUSE");
	exit(0);
}

/*
	�������㣨�������棩
*/

void gameSuccessG()
{
	char s[201];
	PIMAGE img[2];
	img[0] = newimage();
	img[1] = newimage();
	getimage(img[0], "BK.png", 0, 0);
	getimage(img[1], "congratulations.png", 0, 0);
	putimage_alphablend(NULL, img[0], 25, 50, 0x60);
	putimage_transparent(NULL, img[1], 50, 225, BLACK);
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfontbkcolor(EGERGB(220, 220, 220));
	setfont(30, 0, "΢���ź�");
	sprintf(s, "���ι�˾���ڵ�ַ:(%d��%d)\n", COMPANY_X, COMPANY_Y);
	outtextrect(700, 60, 965, 475, s);
	sprintf(s, "��˾ʣ���ֽ���:%d\n", CompanyMoney);
	outtextrect(700, 90, 965, 475, s);
	sprintf(s, "��˾��������:%d\n", CompanyRiderCount);
	outtextrect(700, 120, 965, 475, s);
	sprintf(s, "��˾��������:%d\n", CompanyMoney + CompanyRiderCount * HIRE_MONEY - INIT_MONEY);
	outtextrect(700, 150, 965, 475, s);
	sprintf(s, "��Ӫʱ��:%d��ʱ�䵥λ\n", Time);
	outtextrect(700, 180, 965, 475, s);
	sprintf(s, "��˾�ӵ���:%d\n", CompanyOrderSum);
	outtextrect(700, 210, 965, 475, s);
	sprintf(s, "��˾��ɵ���:%d\n", CompanyOrderFinish);
	outtextrect(700, 240, 965, 475, s);
	sprintf(s, "��˾��ʱ����:%d\n", CompanyOrderOverTime);
	outtextrect(700, 270, 965, 475, s);
	sprintf(s, "��������Լ���...\n");
	outtextrect(700, 300, 965, 475, s);
	delimage(img[0]);
	delimage(img[1]);
	// �ͷ�ȫ�ֱ����ڴ�
	OrderList *p1 = AllOrderLog;
	RiderList *p2 = AllRiderLog;
	OrderList *p3 = Buffer;

	// �ͷ�AllOrderLog
	while (p1)
	{
		free(p1->Pre_order);
		free(p1->Cur_order);
		p1->Pre_order = NULL;
		p1->Cur_order = NULL;
		p1 = p1->Nxt_order;
	}
	AllOrderLog = NULL;
	// �ͷ�Buffer
	while (p3)
	{
		free(p3->Pre_order);
		free(p3->Cur_order);
		p3->Pre_order = NULL;
		p3->Cur_order = NULL;
		p3 = p3->Nxt_order;
	}
	Buffer = NULL;
	// �ͷ�AllRiderLog
	while (p2)
	{
		if (p2->Cur_rider)
		{
			free(p2->Pre_rider);
			p1 = p2->Cur_rider->Bag;
			// �ͷ�bag
			while (p1)
			{
				free(p1->Pre_order);
				free(p1->Cur_order);
				p1->Pre_order = NULL;
				p1->Cur_order = NULL;
				p1 = p1->Nxt_order;
			}
			free(p2->Cur_rider);
		}
		else
		{
			break;
		}
		p2->Pre_rider = NULL;
		p2->Cur_rider = NULL;
		p2 = p2->Nxt_rider;
	}
	AllRiderLog = NULL;
}