#ifndef ACTIONLOGGER_H
#define ACTIONLOGGER_H

#include <QObject>
#include <QPoint>
#include <QList>
#include <QStringList>

class ActionRecord {
public:
    QString action;
    int count;
    ActionRecord(QString action, int count) {this->action = action; this->count = count;}
};

class ActionLogger : public QObject
{
    Q_OBJECT
public:
    explicit ActionLogger(QObject *parent = 0);
    QStringList getActionList();
signals:
public slots:
    void reset();
    void onCursorReseted(QPoint);
    void onKeyCodeAccepted(int keyCode);
    void undo();
private:
    QList <ActionRecord> actionRecordList;
    QString actionStringFromKey(int keyCode);
    void updateActionList(QString actionString);
};

#endif // ACTIONLOGGER_H
