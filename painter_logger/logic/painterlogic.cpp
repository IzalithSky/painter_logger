#include "painterlogic.h"

PainterLogic::PainterLogic(QPoint startPosition, QObject *parent) : QObject(parent) {
    reset(startPosition);
}

void PainterLogic::reset(QPoint startPosition) {
    startPoint = startPosition;
    linesList.clear();
}

const QList<LinePosition> &PainterLogic::getLineList() {
    return linesList;
}

void PainterLogic::onPositionChanged(QPoint currentPosition) {
    LinePosition lp;
    if (linesList.isEmpty())
        lp.a = startPoint;
    else
        lp.a = linesList.last().b;
    lp.b = currentPosition;
    linesList.append(lp);
}

void PainterLogic::undo() {
    if (linesList.isEmpty() == false)
        linesList.takeLast();
}

void PainterLogic::onCursorReseted(QPoint startPosition) {
    reset(startPosition);
}
