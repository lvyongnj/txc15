#ifndef TXCDEF
#define TXCDEF

typedef unsigned char byte;

///////////////////////////////////////////////////////////////////////////////////////////////
//  命令字

typedef enum {
    txCmdRead_Sender        = 0xaa, // 读取发送卡中基本参数   数据：无    回送：16字节版本号+64字节文件名+48字节发送卡基本参数
    txCmdWrite_Sender       = 0xbb, // 发送发送卡基本参数    数据：数据部分长度为48字节  回送：发送后等待回送‘G’，确认发送正确
    txCmdWrite_Fpga         = 0xcc, // 写入发送卡fpga的程序
    txCmdWrite_paixu        = 0xdd, // 发送接收卡排序参数，存储在发送卡中
                                    // 数据：数据部分长度2048字节，
                                    // 回送：发送完0xdd后，可以接收到‘G’回送信号，接收到后开始每256字节发送一次数据，每隔256字节可以接收到回送‘G’，接收到回送后才可以再发下256字节。
    txCmdWrite_Receiver     = 0x01, // 发送接收卡参数  数据：数据部分长度为276字节 回送：发送完成，等待回送‘G’信号
    txCmdRead_Page          = 0x07, // 或0x0a，读出任意页位置的256字节，该命令主要用做测试或维护   数据：数据部分2个字节，表示读出的位置 回送：发送完毕，接收到256字节内容
    txCmdErase_Page         = 0x08, // 擦除板载256k字节数据存储区  数据：无数据部分 回送：发送完成，等待回送‘G’信号
    txCmdWrite_Page         = 0x09, // 写入256k字节存储区的任意页，每页长度256字节    数据：数据部分长度为258字节。其中第一第二字节指定写入位置，其余256字节为数据   回送：发送完成，等待回送‘G’信号
    txCmdWrite_Resolution   = 0x0b, // 写入发送卡分辨率，共1个字节   数据：第1个字节为分辨率选择：
                                                        // 0x00 800x600         0x01 1024x768       0x02 1280x720       0x03 1280x800
                                                        // 0x04 1280x1024       0x05 1366x768       0x06 1440x900       0x07 1600x900
                                                        // 0x08 1600x1200       0x09 1680x1050      0x0A 1920x1080      0x0B 1920x1200
                                                        // 0x0C 2048x1152       0xFF 自适应
                                    // 回送：发送完成，等待回送‘G’信号
    txCmdRead_Resolution    = 0x0c, // 读回发送卡分辨率 数据：无    回送：回送1字节数据，0x00~0x0C 有效
    txCmdRead_Receiver_Data = 0x0d, // 读回接收卡返回的数据   数据：无    回送：回送接收卡返回数据，目前322字节，内容同接收卡回送数据包
    txCmd_Function1         = 0x0e, // 独立播放机：独立播放器控制大屏电源    数据：0xFF，关闭电源，其他打开   回送：无
                                    // DVI发送卡：DVI发送卡时间查看    数据：无    回送：6字节实时时间+6字节保护目标时间+2无效字节
    txCmd_SetTime           = 0x0f, // 校时   数据：7字节实时时间（秒分时日月年周） 回送：发送完成，等待回送‘G’信号
    txCmdRead_Sensor        = 0x10, // 读传感器数据   数据：无    回送：11字节（详见下表）
                                    // 数据段      数据长度(byte)          说明
                                    // 前导码      3                       0x54,0x4C,0x41
                                    // 亮度        2                       高字节在先
                                    // 温度        2                       高字节在先，最高位为符号位，1表示负值，温度以10倍计算，除以10，得到0.5度精度的温度值
                                    // 相对湿度    2                       高字节在先，湿度度以10倍计算，主机收到后除以10。有效值为2%~100%
                                    // 噪声        2                       高字节在先
    txCmd_ResetWatchDog     = 0x11, // 软件复位独立播放机看门狗
    txCmd_ResetArm          = 0x12  // 独立播放机复位核心板
} TxCommand;

///////////////////////////////////////////////////////////////////////////////////////////////
// 主控参数

struct zkByteX1 {
    byte    mode    : 2;            // 发送帧频倍数（无发送卡时无效），由所控制面积计算得出  0：60hz  1：30hz   2：20hz   3：15hz
    byte    cls     : 1;            // 清屏    0：正常显示    1：清除屏幕（黑屏）
    byte    lock    : 1;            // 锁屏    0：正常显示    1：画面停止
    byte    na0     : 1;            // 备用0
    byte    sameOut : 1;            // 双口输出是否相同    0：不同    1：相同
    byte    na1     : 1;            // 备用1
    byte    fullClr : 1;            // 双色/全色选择（由发送卡序列号确定）    0：双色    1：全色
};

struct zkByteX2 {
    byte    xh4     : 4;            // 发送卡列基准起点，共12位，高4位
    byte    yh3     : 3;            // 发送卡行基准起点，共11位，高3位
    byte    na2     : 1;            // 备用2
};

struct zkByteX13 {
    byte    vPix    : 1;            // 虚拟    0：不虚拟    1：虚拟显示
    byte    vpMode  : 2;            // 虚拟时颜色排列    0：RGBR    1：RBGR    2：GRRB    3：BRRG
    byte    vpColor : 1;            // 虚拟时颜色混合方式    0：灰度优先    1：亮度优先
    byte    vpTria  : 1;            // 启用三角虚拟方式    0：正常    1：启用三角虚拟
    byte    vSource : 2;            // TX13A视频源选择：    00： DVI优先    01： ARM优先    10：保留    11：保留
    byte    tx13eBF : 1;            // TX13E B/F即1,2或3,4端口标识，软件不可访问
};

struct zkByteX25 {
    byte    xl4     : 4;            // 列起始点低4位
    byte    yl4     : 4;            // 行起始点低4位
};

struct zkByteX26 {
    byte    wl4     : 4;            // 列宽度低4位
    byte    hl4     : 4;            // 行高度低4位
};

struct zkByteX34 {
    byte    autoBri : 1;            // 自动亮度调节：    0：不启用；   1：启用
    byte    parMode : 1;            // 实时参数模式：    0：关闭；    1：启用
    byte    clrBit  : 2;            // 颜色深度：    00：8位；    01：10位；    10：12位；    其他：保留
    byte    rotate  : 2;            // 旋转：    00：0度；    01：90度；    10：180度；    11：270度
    byte    picCmp  : 1;            // 画面压缩：    0：关闭；    1：启用
    byte    na      : 1;            // 保留
};

// 发送卡参数 长度: 48 byte
typedef struct {
    zkByteX1    x1;
    zkByteX2    x2;
    byte        x3_xl;              // 发送卡列基准起点，共12位，低8位
    byte        x4_yl;              // 发送卡行基准起点，共11位，低8位
    byte        x5_1x;              // OUT1 列起点，每16点为单位，最大255，最小为1
    byte        x6_1y;              // OUT1 行起点，每16点为单位，最大127，最小为1
    byte        x7_1w;              // OUT1 宽度，每16点为单位，最大255，最小为1
    byte        x8_1h;              // OUT1 高度，每16点为单位，最大127，最小为1
    byte        x9_2x;              // OUT2 列起点
    byte        x10_2y;             // OUT2 行起点
    byte        x11_2w;             // OUT2 宽度
    byte        x12_2h;             // OUT2 高度
    zkByteX13   x13;
    byte        x14;                // 数据包最大像素，每16像素为单位，最大40，最小为4；测试用，默认值30
    byte        x15;                // 数据包间隔，最大为255，最小为32；测试用，默认64
    byte        x16;                // 保留
    byte        x17_3x;             // OUT3 列起点
    byte        x18_3y;             // OUT3 行起点
    byte        x19_3w;             // OUT3 宽度
    byte        x20_3h;             // OUT3 高度
    byte        x21_4x;             // OUT4 列起点
    byte        x22_4y;             // OUT4 行起点
    byte        x23_4w;             // OUT4 宽
    byte        x24_4h;             // OUT4 高
    zkByteX25   x25_1xyl;           // OUT1 行列起始坐标的低4位
    zkByteX26   x26_1whl;           // OUT1 宽高度的低4位
    zkByteX25   x27_2xyl;           // OUT2 ...
    zkByteX26   x28_2whl;           // OUT2 ...
    zkByteX25   x29_3xyl;           // OUT3 ...
    zkByteX26   x30_3whl;           // OUT3 ...
    zkByteX25   x31_4xyl;           // OUT4 ...
    zkByteX26   x32_4whl;           // OUT4 ...
    byte        x33_bri;            // 显示屏亮度（0~255）
    zkByteX34   x34;
    byte        x35;                // 行放大因子（1~16）
    byte        x36;                // 行缩小因子（1~16）
    byte        x37;                // 列放大因子（1~16）
    byte        x38;                // 列缩小因子（1~16）
    byte        x39[10];            // 保留（均为0xff)
} TxSenderParam;

///////////////////////////////////////////////////////////////////////////////////////////////
// 接收卡参数

// 字节1:模组信号极性，0x00
struct recByteX1 {
    byte        fullClr     : 1;    // 全色是否         0:全色    1:单双色
    byte        na          : 2;    // 保留
    byte        noDecoder   : 1;    // 1/4无译码       0:普通    1:无译码
    byte        hSignal     : 1;    // 行有效方式        0:低有效   1:高有效
    byte        oe          : 1;    // OE信号有效方式     0:低有效   1:高有效
    byte        stb         : 1;    // STB信号有效方式    0:正向    1:反向
    byte        data        : 1;    // DATA信号方式     0:高有效（共阴）   1:低有效（共阳）
};

// 字节2: 0x00
struct recByteX2 {
    byte        fadeIn      : 1;    // 上电渐亮         0:启用    1:禁止
    byte        enCRC       : 1;    // 启用CRC校验      0:不启用   1:启用
    byte        colorBit    : 2;    // 颜色深度         00:8bit     01:10bit    10:12bit
    byte        cls         : 1;    // 清屏：(已不用)     0:正常显示  1:黑屏
    byte        na          : 3;    // 保留
};

// 字节3：行消影时间 0x05
// 字节4：每组数据控制的行数 0x08
struct recByteX4 {
    byte        dataRows     : 7;    // 一组数据控制模组的行数：1~64；其他无效
    byte        na          : 1;    // 保留
};

// 字节5：每组数据控制的列数 0x10
// 字节6：扫描系数 0x08

// 接收卡基本参数
typedef struct {
    recByteX1   x1;
    recByteX2   x2;
    byte        x3_hBlank;          // 行消影时间，实际消隐时间为(输入值*2+1)* 48ns
    recByteX4   x4;
    byte        x5_dataCols;        // 一组数据控制的模组列数：1~128；其他无效
    byte        x6_scanMode;        // 模组扫描方式：1~32；其他无效
} TxReceiverParam;
#endif // TXCDEF

