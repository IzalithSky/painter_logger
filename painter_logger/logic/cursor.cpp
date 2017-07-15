#include "cursor.h"

Cursor::Cursor(QObject *parent) : QObject(parent) {
    minX = 0;
    maxX = 100;
    minY = 0;
    maxY = 100;
    gridStep = 10;
    startPosition = QPoint(0, 0);
    history.append(startPosition);
}

void Cursor::reset() {
    history.clear();
    history.append(startPosition);
    emit reseted(startPosition);
}

void Cursor::setXRange(int minX, int maxX) {
    this->minX = minX;
    this->maxX = maxX;

    if (minX >= maxX)
        resetToDefault();

    if (positionIsAllowed(startPosition) == false ||
        positionIsAllowed(history.last()) == false) {
        emit cursorIsBeyondRange();
        startPosition.setX(minX);
        reset();
    }
}

void Cursor::setYRange(int minY, int maxY) {
    this->minY = minY;
    this->maxY = maxY;

    if (minY >= maxY)
        resetToDefault();

    if (positionIsAllowed(startPosition) == false ||
        positionIsAllowed(history.last()) == false) {
        emit cursorIsBeyondRange();
        startPosition.setY(minY);
        reset();
    }
}

void Cursor::setStartPosition(QPoint startPosition) {
    if (positionIsAllowed(startPosition))
        this->startPosition = startPosition;
    else {
        emit cursorIsBeyondRange();
        resetToDefault();
    }
    reset();
}

void Cursor::setGridStep(int gridStep) {
    this->gridStep = gridStep;
    reset();
}

QPoint Cursor::getStartPosition() {
    return startPosition;
}

QPoint Cursor::getCurrentPosition() {
    return history.last();
}

int Cursor::getGridStep() {
    return gridStep;
}

bool Cursor::changeCurrentPosition(int keyCode)
{
    QPoint pos = history.last();

    if (keyCode == Qt::Key_8) {       // ↑
        pos.setY(pos.y() - gridStep);
    } else if(keyCode == Qt::Key_2) { // ↓
        pos.setY(pos.y() + gridStep);
    } else if(keyCode == Qt::Key_4) { // ←
        pos.setX(pos.x() - gridStep);
    } else if(keyCode == Qt::Key_6) { // →
        pos.setX(pos.x() + gridStep);
    } else if(keyCode == Qt::Key_7) { // ↖
        pos.setX(pos.x() - gridStep);
        pos.setY(pos.y() - gridStep);
    } else if(keyCode == Qt::Key_9) { // ↗
        pos.setX(pos.x() + gridStep);
        pos.setY(pos.y() - gridStep);
    } else if(keyCode == Qt::Key_3) { // ↘
        pos.setX(pos.x() + gridStep);
        pos.setY(pos.y() + gridStep);
    } else if(keyCode == Qt::Key_1) { // ↙
        pos.setX(pos.x() - gridStep);
        pos.setY(pos.y() + gridStep);
    } else
        return false;


    if (positionIsAllowed(pos))
        history.append(pos);
    else
        return false;

    emit keyCodeAccepted(keyCode);
    emit positionChanged(pos);

    return true;
}

void Cursor::undo() {
    if (history.length() > 1)
        history.takeLast();

    emit undone();
}

bool Cursor::positionIsAllowed(QPoint position) {
    if (position.x() < minX || position.x() > maxX)
        return false;
    if (position.y() < minY || position.y() > maxY)
        return false;
    return true;
}

void Cursor::resetToDefault() {
    minX = 0;
    maxX = 100;
    minY = 0;
    maxY = 100;
    gridStep = 10;
    startPosition = QPoint(0, 0);
    history.clear();
    history.append(startPosition);
}
