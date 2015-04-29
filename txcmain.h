#ifndef TXCMAIN_H
#define TXCMAIN_H

#include <QMainWindow>
#include <QTranslator>
#include "txledlight.h"
#include <QPushButton>
//#include "txcdef.h"

namespace Ui {
class txcMain;
}

class txcMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit txcMain(QWidget *parent = 0);
    ~txcMain();

private slots:
    void mainButtonsClicked();
    void on_cbbLanguage_currentIndexChanged(int index);

private:
    Ui::txcMain *ui;
    txledlight *ledlight;
    QWidget *lastPanel;
    QTranslator *lastTrans;

    int mainCmdIndex;   // 用于记录当前选择的功能按钮序号

    void retranslateUi();
};

#endif // TXCMAIN_H
