#include "cursor.h"

Cursor::Cursor(QObject *parent) : QObject(parent) {
    minX = 0;
    maxX = 100;
    minY = 0;
    maxY = 100;
    gridStep = 10;
    startPosition = QPoint(0, 0);
    currentPosition = startPosition;
}

void Cursor::reset() {
    currentPosition = startPosition;
    emit reseted(startPosition);
}

void Cursor::setXRange(int minX, int maxX) {
    this->minX = minX;
    this->maxX = maxX;

    if (minX >= maxX)
        resetToDefault();

    if (positionIsAllowed(startPosition) == false ||
        positionIsAllowed(currentPosition) == false) {
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
        positionIsAllowed(currentPosition) == false) {
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
    return currentPosition;
}

int Cursor::getGridStep() {
    return gridStep;
}

bool Cursor::changeCurrentPosition(int keyCode)
{
    QPoint pos = currentPosition;

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
        currentPosition = pos;
    else
        return false;

    emit keyCodeAccepted(keyCode);
    emit positionChanged(pos);

    return true;
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
    currentPosition = startPosition;
}
