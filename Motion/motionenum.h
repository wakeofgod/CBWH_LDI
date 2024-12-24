#ifndef MOTIONENUM_H
#define MOTIONENUM_H
namespace MotionEnum
{
enum AxisEnum
{
    AxisX,
    AxisY,
    AxisZ,
    AxisU,
    AxisV,
    AxisW,
};

enum IOType
{
    AxisIoInMsg_PEL,// 0：正限位信号，AxisIoInMsg_PEL
    AxisIoInMsg_NEL,//1：负限位信号，AxisIoInMsg_NEL
    AxisIoInMsg_ORG,//2：原点信号，AxisIoInMsg_ORG
    AxisIoInMsg_EMG,//3：急停信号，AxisIoInMsg_EMG
    AxisIoInMsg_DSTP,//4：减速停止信号，AxisIoInMsg_DSTP（保留）
    AxisIoInMsg_ALM,//5：伺服报警信号，AxisIoInMsg_ALM
    AxisIoInMsg_RDY,//6：伺服准备信号，AxisIoInMsg_RDY（保留）
    AxisIoInMsg_INP,//7：伺服到位信号，AxisIoInMsg_INP
};
}
#endif // MOTIONENUM_H
