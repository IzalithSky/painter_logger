#ifndef CURSOR_H
#define CURSOR_H

#include <QObject>
#include <QPoint>

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
signals:
    void reseted(QPoint startPosition);
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
    QPoint currentPosition;
    bool positionIsAllowed(QPoint position);
    void resetToDefault();
};

#endif // CURSOR_H
