#ifndef CURSOR_H
#define CURSOR_H

#include <QObject>
#include <QPoint>
#include <QList>

class Cursor : public QObject
{
    Q_OBJECT
public:
    explicit Cursor(QObject *parent = 0);
    void reset();
    void setXRange(int minX, int maxX);
    void setYRange(int minY, int maxY);
    void setStartPosition(QPoint getStartPosition);
    void setGridStep(int gridStep);
    QPoint getStartPosition();
    QPoint getCurrentPosition();
    int getGridStep();
    bool changeCurrentPosition(int keyCode);
    void undo();
signals:
    void reseted(QPoint startPosition);
    void undone();
    void keyCodeAccepted(int keyCode);
    void positionChanged(QPoint currentPos);
    void cursorIsBeyondRange();
public slots:
private:
    int minX;
    int maxX;
    int minY;
    int maxY;
    int gridStep;
    QPoint startPosition;
    QList <QPoint> history;
    bool positionIsAllowed(QPoint position);
    void resetToDefault();
};

#endif // CURSOR_H
