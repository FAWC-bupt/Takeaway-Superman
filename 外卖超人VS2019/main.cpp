
#include "../Global/header.h"
#include <graphics.h>


/*
	�ļ�/����̨���������
*/
void console()
{
	AllOrderLog = creatOrderList(); // ȫ��������¼(����ͷ���)
	Buffer = creatOrderList();      // ������(����ͷ���)
	AllRiderLog = creatRiderList(); // ȫ�����ּ�¼(����ͷ���)
	clock_t start_clock, end_clock; // ���ڼ����������ʱ��
	int flag = 0;
	if (inputFileOrder())
		;
	else
	{
		printf("�������ļ�sales.txt!\n");
		printf("1. �Ӽ�������\n");
		printf("2. ���������\n");
		printf("����������:\n");
		for (;;)
		{
			scanf("%d", &flag);
			if (flag == 1)
			{
				system("cls");
				inputKeyOrder();
				break;
			}
			else if (flag == 2)
			{
				HWND hwnd;
				hwnd = FindWindow("ConsoleWindowClass", NULL);	//���������ڵ������ʹ�������ƥ��ָ�����ַ���,�������Ӵ��ڡ�
				if (hwnd)
					ShowWindow(hwnd, SW_HIDE);				//����ָ�����ڵ���ʾ״̬���رտ���̨��
				mainFunction();
				exit(0);
			}
			else
			{
				printf("�����������������!\n");
				printf("1. �Ӽ�������\n");
				printf("2. ���������\n");
				printf("����������:\n");
			}
		}
	}

	while (Buffer->Nxt_order || !isAllOrderFinished()) // ���������ǻ�����Ϊ��
	{
		start_clock = clock();
		Time++;
		//���������еĶ����ŵ�ȫ�ֶ�����¼��
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
		//��ļ����

		while (CompanyMoney >= 400)
		{
			hireRider();
		}
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
		//�ж������ʱ�����������ˢ��һ��
		if (isAnyOrderComplish)
		{
			system("cls");
			outputMap();
			outputKey();
		}
		//����ļ�
		outputOnFile();
		end_clock = clock();
		// TIME_UNIT * 1000 - (end_clock - start_clock)
		// Sleep(100); // ׼ȷ2��ˢ��
	}
	gameSuccess();
}

/*
	��ʼ����
*/
int startScreen()
{
	int x, y, flag = 2;
	int point_one[] = { 340,480,340,400,640,400,640,480 },
		point_two[] = { 340,590,340,510,640,510,640,590 },
		point_three[] = { 340,700,340,620,640,620,640,700 };
	mouse_msg msg = { 0 };

	initgraph(1000, 750);   // ��ʼ��Ϊ1000*750��С�Ĵ���
	setcaption("Takeaway Superman");
	setbkcolor(YELLOW);// ����ɫ
	PIMAGE img;
	img = newimage();
	getimage(img, "final-logo.png", 0, 0);// ����
	putimage(-100, 0, img);
	setfillcolor(YELLOW);// �������ɫ
	setcolor(YELLOW);// �������ɫ

	/*
		����/�ļ����밴ť
	*/
	// bar(340, 480, 640, 400);
	fillpoly(4, point_one);
	setfont(40, 0, "΢���ź�");
	setcolor(BLACK);// ������ɫ
	outtextrect(395, 420, 640, 380, "����/�ļ�����");

	/*
		������밴ť
	*/
	setcolor(YELLOW);
	// bar(340, 590, 640, 510);
	fillpoly(4, point_two);
	setfont(40, 0, "΢���ź�");
	setcolor(BLACK);
	outtextrect(430, 530, 640, 490, "�������");

	/*
		�˳���ť
	*/
	setcolor(YELLOW);
	// bar(340, 700, 640, 620);
	fillpoly(4, point_three);
	setfont(40, 0, "΢���ź�");
	setcolor(BLACK);
	outtextrect(460, 640, 640, 500, "�˳�");
	for (; is_run(); delay_fps(60))
	{

		while (mousemsg())// ��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
		{
			msg = getmouse();// �������Ϣ�������ṹ��
		}
		x = msg.x, y = msg.y;
		if (msg.is_left() || msg.is_right())// ����Ҽ�����
		{
			if (x >= 340 && x <= 640 && y >= 400 && y <= 480)// ����/�ļ�����
			{
				setfillcolor(RED);
				fillpoly(4, point_one);
				floodfillsurface(395, 420, YELLOW);
				flag = 0;
				Sleep(2000);
				break;
			}
			else if (x >= 340 && x <= 640 && y >= 510 && y <= 590)// �������
			{
				HWND hwnd;
				hwnd = FindWindow("ConsoleWindowClass", NULL);	//���������ڵ������ʹ�������ƥ��ָ�����ַ���,�������Ӵ��ڡ�
				if (hwnd)
					ShowWindow(hwnd, SW_HIDE);				//����ָ�����ڵ���ʾ״̬���رտ���̨��
				setfillcolor(RED);
				fillpoly(4, point_two);
				floodfillsurface(430, 530, YELLOW);
				flag = 1;
				Sleep(2000);
				break;
			}
			else if (x >= 340 && x <= 640 && y >= 620 && y <= 700)// �˳�
			{
				setfillcolor(RED);
				fillpoly(4, point_three);
				floodfillsurface(460, 640, YELLOW);
				flag = 2;
				Sleep(2000);
				break;
			}
			else
				continue;
		}
	}
	delimage(img);
	ege::closegraph();
	return flag;
}

int main()
{
	int flag = 2;
	flag = startScreen();
	if (flag == 0)
		console();// ����/�ļ�����������
	else if (flag == 1)
	{
		AllOrderLog = creatOrderList(); // ȫ��������¼(����ͷ���)
		Buffer = creatOrderList();      // ������(����ͷ���)
		AllRiderLog = creatRiderList(); // ȫ�����ּ�¼(����ͷ���)
		clock_t start_clock, end_clock; // ���ڼ����������ʱ��
		mainFunction();// �������������
	}
	exit(0);
}