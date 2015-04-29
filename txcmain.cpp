#include "txcmain.h"
#include "ui_txcmain.h"

txcMain::txcMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::txcMain)
{
    ui->setupUi(this);
    ledlight = new txledlight();
    ui->layoutHead->addWidget(ledlight,0,Qt::AlignLeft);
    ledlight->show();

    lastPanel = NULL;
    ui->wdgMsender->hide();
    ui->wdgMreceiver->hide();
    ui->wdgMconnection->hide();
    ui->wdgMproject->hide();
    ui->wdgMother->hide();
    ui->wdgMsender->setMaximumHeight(200);
    ui->wdgMreceiver->setMaximumHeight(200);
    ui->wdgMproject->setMaximumHeight(200);
    ui->wdgMconnection->setMaximumHeight(200);
    ui->wdgMother->setMaximumHeight(200);
    ui->layoutMLeft->invalidate();

    connect(ui->btnMwelcome,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));
    connect(ui->btnMquik,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));
    connect(ui->btnMsend,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));
    connect(ui->btnMreceiver,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));
    connect(ui->btnMconnection,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));
    connect(ui->btnMproject,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));
    connect(ui->btnMother,SIGNAL(clicked()),this,SLOT(mainButtonsClicked()));

    retranslateUi();
}

txcMain::~txcMain()
{
    delete ui;
}

// 主界面左边按钮按下后的事件处理槽
void txcMain::mainButtonsClicked() {
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());
    if (btn==NULL) return;
    if (!btn->property("cmdindex").isValid()) return;
    bool ok = false;
    mainCmdIndex = btn->property("cmdindex").toInt(&ok);
    if (!ok) return;

    switch(mainCmdIndex) {
    case 0: {   // 欢迎
        if (lastPanel!=NULL) lastPanel->hide();
        lastPanel = NULL;
        ui->swMainPage->setCurrentIndex(0);
        break;
    }
    case 1: {   // 快捷设置
        if (lastPanel!=NULL) lastPanel->hide();
        lastPanel = NULL;
        ui->swMainPage->setCurrentIndex(0);
        break;
    }
    case 2: {   // 发送卡
        if (lastPanel!=NULL) lastPanel->hide();
        ui->wdgMsender->show();
        lastPanel = ui->wdgMsender;
        break;
    }
    case 3: {   // 接收卡
        if (lastPanel!=NULL) lastPanel->hide();
        ui->wdgMreceiver->show();
        lastPanel = ui->wdgMreceiver;
        break;
    }
    case 4: {   // 排序
        if (lastPanel!=NULL) lastPanel->hide();
        ui->wdgMconnection->show();
        lastPanel = ui->wdgMconnection;
        break;
    }
    case 5: {   // 工程项目
        if (lastPanel!=NULL) lastPanel->hide();
        ui->wdgMproject->show();
        lastPanel = ui->wdgMproject;
        break;
    }
    case 6: {   // 其它选项
        if (lastPanel!=NULL) lastPanel->hide();
        ui->wdgMother->show();
        lastPanel = ui->wdgMother;
        break;
    }
    default: {
        if (lastPanel!=NULL) lastPanel->hide();
        lastPanel = NULL;
        break;
    }
    }
}

void txcMain::retranslateUi() {
    this->setWindowTitle(tr("聚诚LED控制系统 v%1").arg(qApp->applicationVersion()));
}

// 语言选择
void txcMain::on_cbbLanguage_currentIndexChanged(int index)
{
    QString qmPath = ":/language/";
    QString local = "";
    QTranslator appTranslator;
    switch(index) {
    case 1: {
        local = "zh_TW";
        break;
    }
    case 2: {
        local = "en";
        break;
    }
    case 3: {
        local = "ru";
        break;
    }
    case 0:
    default: {
        local = "";
        break;
    }
    }
    if (lastTrans!=NULL) qApp->removeTranslator(lastTrans);
    if (!local.isEmpty()) {
        appTranslator.load("txlg_"+local,qmPath);
        lastTrans = &appTranslator;
        qApp->installTranslator(lastTrans);
    }
    else lastTrans = NULL;
    retranslateUi();
    ui->retranslateUi(this);
}
