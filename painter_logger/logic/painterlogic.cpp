#include "painterlogic.h"

PainterLogic::PainterLogic(QPoint startPosition, QObject *parent) : QObject(parent) {
    reset(startPosition);
}

void PainterLogic::reset(QPoint startPosition) {
    currentLine.a = startPosition;
    currentLine.b = startPosition;
    linesList.clear();
}

const QList<LinePosition> &PainterLogic::getLineList() {
    return linesList;
}

void PainterLogic::onPositionChanged(QPoint currentPosition) {
    currentLine.a = currentLine.b;
    currentLine.b = currentPosition;
    linesList.append(currentLine);
}

void PainterLogic::onCursorReseted(QPoint startPosition) {
    reset(startPosition);
}
