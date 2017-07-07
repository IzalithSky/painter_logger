#ifndef ACTIONLOGGER_H
#define ACTIONLOGGER_H

#include <QObject>
#include <QPoint>

class ActionLogger : public QObject
{
    Q_OBJECT
public:
    explicit ActionLogger(QObject *parent = 0);
    const QStringList &getActionList();
signals:
public slots:
    void reset();
    void onCursorReseted(QPoint);
    void onKeyCodeAccepted(int keyCode);
private:
    QString lastAction;
    int actionSequenceCounter;
    QStringList actionList;
    QString actionStringFromKey(int keyCode);
    void updateActionList(QString actionString);
    void updateSequenceCounterAndLastAction(QString actionString);
};

#endif // ACTIONLOGGER_H
