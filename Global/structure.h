
/*
    ȫ�ֽṹ��
    ע�⣺����Ŀ�����������п�ͷ��㣡����
 */

#ifndef _STRUCTURE
#define _STRUCTURE

#include "header.h"

typedef struct _Order // ����
{
    int id;             // ����ID
    int begin_time;     // ��ʼʱ���
    int warn_time;      // ��ʱʱ���
    int end_time;       // ��ֹʱ���
    int rest_x, rest_y; // ����λ��
    int cust_x, cust_y; // �˿�λ��
    int status;         // ����״̬ 0δ�ӵ���1ȡ�ͣ�2�Ͳͣ�3���
} Order;

typedef struct _OrderList // ��������
{
    struct _OrderList *Pre_order; // ��һ������
    struct _OrderList *Nxt_order; // ��һ������
    Order *Cur_order;             // ��ǰ����
} OrderList;

typedef struct _Rider // ����
{
    int id;               // ����ID
    int rider_x, rider_y; // ���ֵ�ǰλ��
    OrderList *Bag;       // ���ֱ�������
    //Order *Cur_order;     // ���ֵ�ǰ����
} Rider;

typedef struct _RiderList // �����б�(���ڱ���)
{
    struct _RiderList *Pre_rider; // ��һ������
    struct _RiderList *Nxt_rider; // ��һ������
    Rider *Cur_rider;             // ��ǰ����
} RiderList;

#endif