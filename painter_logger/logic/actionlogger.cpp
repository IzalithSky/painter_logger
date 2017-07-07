#include "actionlogger.h"

ActionLogger::ActionLogger(QObject *parent) : QObject(parent) {
    reset();
}

void ActionLogger::reset() {
    lastAction = "";
    actionSequenceCounter = 0;
    actionList.clear();
}

const QStringList& ActionLogger::getActionList() {
    return actionList;
}

void ActionLogger::onKeyCodeAccepted(int keyCode) {
    QString actionString = actionStringFromKey(keyCode);
    updateActionList(actionString);
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
    updateSequenceCounterAndLastAction(actionString);

    if (actionSequenceCounter > 0) {
        QString actionNoPrefix = QString::number(actionList.length()) + ". ";
        QString newAction = actionNoPrefix + actionString;
        QString sequenceNoPostfix = " x" + QString::number(actionSequenceCounter + 1);
        newAction.append(sequenceNoPostfix);
        actionList.replace(actionList.length() - 1, newAction); // replace last
    } else {
        QString actionNoPrefix = QString::number(actionList.length() + 1) + ". ";
        QString newAction = actionNoPrefix + actionString;
        actionList.append(newAction);
    }
}

void ActionLogger::updateSequenceCounterAndLastAction(QString actionString) {
    if (actionString == lastAction)
        actionSequenceCounter++;
    else
        actionSequenceCounter = 0;

    lastAction = actionString;
}

void ActionLogger::onCursorReseted(QPoint) {
    reset();
}
