#ifndef TXCDATABASE_H
#define TXCDATABASE_H

#include "txcdef.h"

class TxcDataBase
{
public:
    TxcDataBase();

    TxCommand command;  // 命令
    byte data[];        // 数据
    int datalen;        // 数据长度
protected:
    //  包头
    const byte head[16] = { 0x54, 0x58, 0x4c, 0x45, 0x44, 0x43, 0x4f, 0x4e, 0x54, 0x52, 0x4f, 0x4c, 0x4c, 0x45, 0x52, 0xbb };  // "TXLEDCONTROLLER" + 0XBB

private:
    virtual byte *getData() const = 0;

};

#endif // TXCDATABASE_H
