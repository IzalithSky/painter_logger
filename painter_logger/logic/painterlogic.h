#ifndef PAINTERLOGIC_H
#define PAINTERLOGIC_H

#include <QObject>
#include <QPoint>

struct LinePosition {
    QPoint a;
    QPoint b;
};

class PainterLogic : public QObject
{
    Q_OBJECT
public:
    explicit PainterLogic(QPoint startPosition, QObject *parent = 0);
    const QList<LinePosition> &getLineList();
signals:
public slots:
    void reset(QPoint startPosition);
    void onCursorReseted(QPoint startPosition);
    void onPositionChanged(QPoint currentPosition);
private:
    LinePosition currentLine;
    QList<LinePosition> linesList;
};

#endif // PAINTERLOGIC_H
