#ifndef TXLEDLIGHT_H
#define TXLEDLIGHT_H

#include <QGraphicsView>
#include <QGraphicsItem>

class txledlight : public QGraphicsView
{
    Q_OBJECT
public:
    explicit txledlight(QWidget *parent = 0);
    void showLed(bool bOn, int nColor);
signals:
    void onClick();
public slots:
private:
    bool isLighting;
    int color;
    QGraphicsScene m_scene;
    QGraphicsItem *m_bgdown;
    QGraphicsItem *m_ledR;
    QGraphicsItem *m_ledRl;
    QGraphicsItem *m_ledG;
    QGraphicsItem *m_ledGl;
    QGraphicsItem *m_ledB;
    QGraphicsItem *m_ledBl;
    QGraphicsItem *lastLed;
    QGraphicsItem *m_txled;
    void setupScene();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // TXLEDLIGHT_H
