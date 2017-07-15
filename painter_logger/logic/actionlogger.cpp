#include "actionlogger.h"

ActionLogger::ActionLogger(QObject *parent) : QObject(parent) {
    reset();
}

void ActionLogger::reset() {
    actionRecordList.clear();
}

QStringList ActionLogger::getActionList() {
    QStringList actionList;
    int i = 1;
    foreach (ActionRecord ar, actionRecordList)
    {
        QString str = QString::number(i) + ". " + ar.action;
        if (ar.count > 1)
            str.append(" " +  QString::number(ar.count));

        actionList.append(str);

        i++;
    }
    return actionList;
}

void ActionLogger::onKeyCodeAccepted(int keyCode) {
    QString actionString = actionStringFromKey(keyCode);
    updateActionList(actionString);
}

void ActionLogger::undo() {
    if (actionRecordList.isEmpty() == false) {
        if (actionRecordList.last().count == 1)
            actionRecordList.takeLast();
        else
            actionRecordList.last().count--;
    }
}

QString ActionLogger::actionStringFromKey(int keyCode) {
    QString actionString;

    if (keyCode == Qt::Key_8) {       // ↑
        actionString = "↑";
    } else if(keyCode == Qt::Key_2) { // ↓
        actionString = "↓";
    } else if(keyCode == Qt::Key_4) { // ←
        actionString = "←";
    } else if(keyCode == Qt::Key_6) { // →
        actionString = "→";
    } else if(keyCode == Qt::Key_7) { // ↖
        actionString = "↖";
    } else if(keyCode == Qt::Key_9) { // ↗
        actionString = "↗";
    } else if(keyCode == Qt::Key_3) { // ↘
        actionString = "↘";
    } else if(keyCode == Qt::Key_1) { // ↙
        actionString = "↙";
    }

    return actionString;
}

void ActionLogger::updateActionList(QString actionString) {
    if (actionRecordList.isEmpty())
        actionRecordList.append(ActionRecord(actionString, 1));
    else {
        if (actionString == actionRecordList.last().action)
            actionRecordList.last().count++;
        else
            actionRecordList.append(ActionRecord(actionString, 1));
    }
}

void ActionLogger::onCursorReseted(QPoint) {
    reset();
}
