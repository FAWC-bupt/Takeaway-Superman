#include "../Global/header.h"

/*
    �����յ�ͷ���
 */

/*
    ��������
 */
OrderList *creatOrderList()
{
    OrderList *p = (OrderList *)malloc(sizeof(OrderList));
    p->Cur_order = NULL;
    p->Nxt_order = NULL;
    p->Pre_order = NULL;
    return p;
}

/*
    ��������
 */
RiderList *creatRiderList()
{
    RiderList *p = (RiderList *)malloc(sizeof(RiderList));
    p->Cur_rider = NULL;
    p->Nxt_rider = NULL;
    p->Pre_rider = NULL;
    return p;
}