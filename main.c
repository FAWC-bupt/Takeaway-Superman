#include "./Global/header.h"

int main()
{
    if (inputFileOrder())
        ;
    else
        inputKeyOrder();

    while (1)//胜利条件
    {
        Time++;
        //招募骑手
        //派单
            //派单之前把骑手背包完成的订单弹出
            initRiderBag();
            //派单算法
        //判断是否超时或破产
        isAnyOrderOverTime();
        //送单
            //骑手移动
            AllRiderMove();
            //判断订单是否完成
            //完成每一个订单 但是在骑手背包里不弹出刚完成的订单 （输出文件时判断停靠使用）
            //完成订单时输出控制台窗口
            system("clr");
            outputMap();
        //输出文件
        outputOnFileKey();
        sleep(TIME_UNIT);
    }
    printf("Successful!"); 
    return 0;
}