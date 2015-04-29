#include "txcmain.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);
    //QFont font("wenquanyi",6);
    //a.setFont(font);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    txcMain w;
    w.show();

    return a.exec();
}
