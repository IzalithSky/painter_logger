#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>

#include "cursor.h"
#include "painterlogic.h"
#include "actionlogger.h"

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PainterWidget(QWidget *parent = 0);
signals:
    void positionChanged(QStringList actionList);
    void cursourOutOfRange();
public slots:
    void undo();
    void setGridStep(int step);
    void setPositionX(int x);
    void setPositionY(int y);
    void saveImage(QString path);
    void clearImage();
    void setTracerHidden(bool hidden);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
private:
    int gridPosX;
    int gridPosY;
    Cursor *cursor;
    PainterLogic *painterLogic;
    ActionLogger *actionLogger;
    bool tracerHidden;
    void processArrowKey(int key);
    void drawGrid(QPainter &painter);
    void drawTrace(QPainter &painter);
    void drawLines(QPainter &painter);
};

#endif // PAINTERWIDGET_H
