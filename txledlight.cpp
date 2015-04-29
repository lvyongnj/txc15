#include "txledlight.h"

txledlight::txledlight(QWidget *parent) :
    QGraphicsView(parent)
{
    setScene(&m_scene);
    setFixedSize(64,64);

    setupScene();
    setRenderHint(QPainter::Antialiasing, true);
    setFrameStyle(QFrame::NoFrame);
}

void txledlight::setupScene()
{
    m_scene.setSceneRect(0, 0, 64, 64);
    setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    setBackgroundBrush(QImage(":/ledlight/Resources/bg.png"));
    setCacheMode(QGraphicsView::CacheBackground);

    QPixmap pixmap(64, 64);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.drawImage(0,0,QImage(":/ledlight/Resources/bgdown.png"));
    painter.end();
    //painter.setPen(Qt::NoPen);
    //painter.setBrush(radialGrad);
    //painter.drawEllipse(0, 0, 60, 60);
    m_bgdown = m_scene.addPixmap(pixmap);
    m_bgdown->setPos(0,0);
    m_bgdown->hide();
    //m_light->setZValue(2);    

    QPixmap pixLed(48,48);
    pixLed.fill(Qt::transparent);
    QPainter painterLed(&pixLed);
    painterLed.drawImage(0,0,QImage(":/ledlight/Resources/ledR.png"));
    //painterLed.end();
    m_ledR = m_scene.addPixmap(pixLed);
    m_ledR->hide();

    pixLed.fill(Qt::transparent);
    painterLed.drawImage(0,0,QImage(":/ledlight/Resources/ledR_l.png"));
    //painterLed.end();
    m_ledRl = m_scene.addPixmap(pixLed);
    m_ledRl->hide();

    pixLed.fill(Qt::transparent);
    painterLed.drawImage(0,0,QImage(":/ledlight/Resources/ledG.png"));
    //painterLed.end();
    m_ledG = m_scene.addPixmap(pixLed);
    m_ledG->hide();

    pixLed.fill(Qt::transparent);
    painterLed.drawImage(0,0,QImage(":/ledlight/Resources/ledG_l.png"));
    //painterLed.end();
    m_ledGl = m_scene.addPixmap(pixLed);
    m_ledGl->hide();

    pixLed.fill(Qt::transparent);
    painterLed.drawImage(0,0,QImage(":/ledlight/Resources/ledB.png"));
    //painterLed.end();
    m_ledB = m_scene.addPixmap(pixLed);
    m_ledB->hide();

    pixLed.fill(Qt::transparent);
    painterLed.drawImage(0,0,QImage(":/ledlight/Resources/ledB_l.png"));
    m_ledBl = m_scene.addPixmap(pixLed);
    m_ledBl->hide();

    pixLed.fill(Qt::transparent);
    painterLed.drawImage(0,0,QImage(":/txcmain/Resources/txlogo.png"));
    painterLed.end();
    m_txled = m_scene.addPixmap(pixLed);
    m_txled->setPos(8,11);
    //m_txled->setZValue(9);
    lastLed = m_txled;

    m_scene.update();
}

void txledlight::showLed(bool bOn, int nColor)
{    
    QGraphicsItem *currentLed = NULL;
    m_bgdown->hide();
    if (bOn) {
        if (nColor<0) {
            currentLed = m_txled;
        }
        else if (nColor==0) currentLed = m_ledRl;
        else if (nColor==1) currentLed = m_ledGl;
        else currentLed = m_ledBl;
    }
    else {
        if (nColor<0) {
            m_bgdown->setPos(0,0);
            m_bgdown->show();
            currentLed = m_txled;
        }
        else if (nColor==0) currentLed = m_ledR;
        else if (nColor==1) currentLed = m_ledG;
        else currentLed= m_ledB;
    }
    if (currentLed==NULL) return;
    if (currentLed==m_txled)
        currentLed->setPos(8,11);
    else currentLed->setPos(8,7);
    if (lastLed!=NULL && lastLed!=currentLed) {
        lastLed->hide();
        currentLed->show();
        lastLed = currentLed;
    }
    m_scene.update();
}

void txledlight::mousePressEvent(QMouseEvent *event) {
    if (lastLed==m_txled) showLed(false,-1);
}

void txledlight::mouseReleaseEvent(QMouseEvent *event) {
    //if (lastLed==m_txled) {
        showLed(true,-1);
        emit onClick();
    //}
}
