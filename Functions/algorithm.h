#include "../Global/header.h"

/*
    �Ѷ��������Ӧ���ֵı���
    Var: Order���Ͷ���������ID
*/
void assignOrder(Order *AOrder, int RiderID)
{
    RiderList *findRider = AllRiderLog->Nxt_rider;
    while (findRider && findRider->Cur_rider->id != RiderID) //�ҵ�IDΪRiderID������
        findRider = findRider->Nxt_rider;
    if (findRider == NULL) //�ж��Ƿ����ҵ�������
    {
        return;
    }
    else
    {
        OrderList *nowOrder = AllOrderLog->Nxt_order;
        while (nowOrder)
        {
            if (nowOrder->Cur_order->id == AOrder->id)
            {
                nowOrder->Cur_order->status = 1;
                break;
            }
            nowOrder = nowOrder->Nxt_order;
        }
        AOrder->status = 1;                                 //������״̬��Ϊ��ȡ�͡�
        push_back_order(AOrder, findRider->Cur_rider->Bag); //�������������ֱ���
    }
}

/*
    ͳ��ģ���ܵ�Ŀ�ĵصĲ������㷨��riderMoveͬ
*/
int virtualRun(int *cur_x, int *cur_y, int pos_x, int pos_y)
{
    int cnt = 0;
    // �Ż��㷨���Ѳ��ԣ�����ȷ���Ƿ���ȫ��ȷ...
    if (abs((*cur_y) - pos_y) > 1)
    {
        if ((*cur_x) % 2 == 1 && ((*cur_y) % 2 == 0)) // �����·
        {
            cnt += abs((*cur_y) - pos_y) / 2;
            *cur_y = pos_y;
        }
        else if ((*cur_x) % 2 == 0 && ((*cur_y) % 2 == 1)) // �����·
        {
            cnt += abs(((*cur_y)) - pos_y) / 2 + 1;
            *cur_y = pos_y;
            if (pos_x > *cur_x)
                (*cur_x)++;
            else
                (*cur_x)--;
        }
    }
    if (abs((*cur_x) - pos_x) > 1)
    {
        if ((*cur_x) % 2 == 0 && ((*cur_y) % 2 == 1)) // �����·
        {
            cnt += abs((*cur_x) - pos_x) / 2;
            *cur_x = pos_x;
        }
        else if ((*cur_x) % 2 == 1 && ((*cur_y) % 2 == 0)) // �����·
        {
            cnt += abs(((*cur_x)) - pos_x) / 2 + 1;
            *cur_x = pos_x;
            if (pos_y > *cur_y)
                (*cur_y)++;
            else if (pos_y < *cur_y)
                (*cur_y)--;
            else
            {
                if (pos_y == 0)
                    (*cur_y)++;
                else
                    (*cur_y)--;
            }
        }
    }
    return cnt;
}

/*
    ��ȡ����֮��������پ���
 */
int getDis(int a_x, int a_y, int b_x, int b_y)
{
    return abs(a_x - b_x) + abs(a_y - b_y);
}

/*
    ģ����һ�鵱ǰ���м���Ӷ������������
    API: Rider *, Order *
    return: int
 */
int getPath(Rider *nowRider, Order *nowOrder)
{
    int sum = 0;
    int now_x = nowRider->rider_x, now_y = nowRider->rider_y;
    OrderList *nowBag = nowRider->Bag->Nxt_order;
    while (nowBag)
    {
        if (nowBag->Cur_order->status == 1)
            sum += virtualRun(&now_x, &now_y, nowBag->Cur_order->rest_x, nowBag->Cur_order->rest_y);
        else if (nowBag->Cur_order->status == 2)
            sum += virtualRun(&now_x, &now_y, nowBag->Cur_order->cust_x, nowBag->Cur_order->cust_y);
        nowBag = nowBag->Nxt_order;
    }
    sum += virtualRun(&now_x, &now_y, nowOrder->rest_x, nowOrder->rest_y);
    return sum;
}

/*
    �ҵ�����ɵ�����
 */
void getBestRider(Order *nowOrder)
{
    RiderList *chooseRider = AllRiderLog->Nxt_rider;
    int path_min = 0x3f3f3f3f;
    int path_now = 0x3f3f3f3f, id_min = 0x3f3f3f3f;
    // �ҳ��������
    while (chooseRider)
    {
        path_now = getPath(chooseRider->Cur_rider, nowOrder); // �Ѱ����������ֵ�ʱ��
        if (path_min > path_now)
        {
            path_min = path_now;
            id_min = chooseRider->Cur_rider->id;
        }
        chooseRider = chooseRider->Nxt_rider;
    }
    // �������������ֱ���
    chooseRider = AllRiderLog->Nxt_rider;
    assignOrder(nowOrder, id_min);
}