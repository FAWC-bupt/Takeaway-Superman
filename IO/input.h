#include "../Global/header.h"
/*
	���ļ�����
 */
int inputFileOrder() // TODO: �����������ݺ�Ҫ��������ݵĹ�ϵ
{
	//if (_access("D:/code/cpp/Сѧ�ڼƵ�/����ҵ/Takeaway-Superman/sales.txt", 0) == -1)
	//{
	//	// �ж��Ƿ�����ļ����������򷵻�0
	//	return 0;
	//}
	Order* p = (Order*)malloc(sizeof(Order));
	FILE* fp = fopen("./doc/sales.txt", "r"); // ���ļ�
	if (fp == NULL)
	{
		free(p);
		return 0;
	}
	while ((fscanf(fp, "%d %d %d %d %d %d\n", &p->id, &p->begin_time,
		&p->rest_x, &p->rest_y,
		&p->cust_x, &p->cust_y)) != EOF)
	{
		p->status = 0;                                  // δ�ӵ�״̬
		p->end_time = 0x3f3f3f3f; // �Ʋ�ʱ��
		p->warn_time = p->begin_time + FINE_FIRST_TIME; // ����ʱ��
		push_back_order(p, Buffer);                     // ��ӵ�ȫ�ֶ�����¼��
		p = (Order*)malloc(sizeof(Order));             // ��p�µĿռ�
	}
	free(p); // �ͷ�p���ڴ�
	return 1;
}

/*
	�Ӽ�������
 */
int inputKeyOrder()
{
	Order* p = (Order*)malloc(sizeof(Order));
	while (scanf_s("%d %d %d %d %d %d\n", &p->id, &p->begin_time,
		&p->rest_x, &p->rest_y,
		&p->cust_x, &p->cust_y) != EOF)
	{
		p->status = 0;                                  // δ�ӵ�״̬
		p->end_time = 0x3f3f3f3f; // �Ʋ�ʱ��
		p->warn_time = p->begin_time + FINE_FIRST_TIME; // ����ʱ��
		push_back_order(p, Buffer);                     // ��ӵ�ȫ�ֶ�����¼��
		p = (Order*)malloc(sizeof(Order));             // ��p�µĿռ�
	}
	free(p); // �ͷ�p���ڴ�
	return 1;
}
