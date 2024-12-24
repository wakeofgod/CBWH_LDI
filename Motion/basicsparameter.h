#ifndef BASICSPARAMETER_H
#define BASICSPARAMETER_H

class BasicsParameter
{
public:
    BasicsParameter();
    unsigned short PulseModel;//脉冲模式
    double PulseEquiv = 0;//脉冲当量
    double Min_Vel = 0;//起始速度
    double Max_Vel = 0;//最大速度
    double Tacc = 0;//加速时间
    double Tdec = 0;//减速时间
    double Stop_Vel = 0;//停止速度
    double S_para = 0;//S段时间
    double Backlash = 0;//反向间隙
    double TdecStopTime = 0;//减速停止时间
};

class GoHomeParameter
{
public:
    double Low_Vel = 0;//回零低速
    double High_Vel = 0;//回零高速
    double Tacc = 0;//加速时间
    double Tdec = 0;//减速时间
    unsigned short home_dir;//回零方向
    double vel_mode;//有效电平，0低，1高
    unsigned short  home_mode;// 回零模式
    unsigned short  pos_source;//回零方式，0：指令，1：反馈
    unsigned short  SeifIOType = 2;//自身IO类型
    unsigned short  MapIOType;//映射IO类型
    unsigned short  MapIOIndex;//映射IO索引
    double Filter_time;//IO信号滤波时间

    unsigned short  org_logic;//有效电平，0低，1高
    double filter;//保留参数
    unsigned short   Enable; //回零完成后设置偏移位置值
    double Position;//设置回原点位置
};

class HardLimitParameter
{
public:
    unsigned short El_enable;//EL 信号使能状态
    unsigned short El_logic;//EL 信号有效电平
    unsigned short El_mode;//EL 制动方式
    unsigned short El_PlusSeifIOType = 0;//自身IO类型
    unsigned short El_PlusMapIOType;//映射IO类型
    unsigned short El_PlusMapIOIndex;//映射IO索引
    double El_PlusFilter_time;//IO信号滤波时间
    unsigned short El_MinusSeifIOType = 1;//自身IO类型
    unsigned short El_MinusMapIOType;//映射IO类型
    unsigned short El_MinusMapIOIndex;//映射IO索引
    double El_MinusFilter_time;//IO信号滤波时间
};

class SoftLimitParameter
{
public:
    unsigned short Enable;//使能状态
    unsigned short Source_sel;//计数器选择
    unsigned short SL_action;//限位停止方式; 0：立即停止，1： 减速停止
    double N_limit = 0;//负限位脉冲数
    double P_limit = 0;//正限位脉冲数
};

class CounterInParameter
{
public:
    unsigned short Model;//编码器模式
    unsigned short Ez_logic;//EZ电平有效
    unsigned short Reverse;//输入脉冲反转
};

class ServoAlarmParameter
{
public:
    unsigned short Enable;//ALM 信号使能状态
    unsigned short Alm_logic; // ALM 信号有效电平
    unsigned short Alm_action; // ALM 信号的制动方式
    unsigned short SeifIOType = 5;//自身ALM-IO类型
    unsigned short MapIOType;//映射ALM-IO类型
    unsigned short MapIOIndex;//映射ALM-IO索引
    double Filter_time;//ALM-IO信号滤波时间
};

class EMGParameter
{
public:
    unsigned short Enable; //使能状态
    unsigned short Emg_logic; //有效电平
    unsigned short SeifIOType = 3;//自身EMG-IO类型
    unsigned short MapIOType;//映射EMG-IO类型
    unsigned short MapIOIndex;//映射EMG-IO索引
    double Filter_time;//EMG-IO信号滤波时间
};

class DstpModelParameter
{
public:
    unsigned short Enable; //使能状态
    unsigned short Dstp_logic;
    unsigned short SeifIOType = 4;//自身DstpModel-IO类型
    unsigned short MapIOType;//映射DstpModel-IO类型
    unsigned short MapIOIndex;//映射DstpModel-IO索引
    double Filter_time;//DstpModel-IO信号滤波时间
};

#endif // BASICSPARAMETER_H
