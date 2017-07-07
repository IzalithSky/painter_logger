#include "painterwidget.h"
#include <QPixmap>

PainterWidget::PainterWidget(QWidget *parent) : QWidget(parent)
{
    tracerHidden = false;
    gridPosX = 0;
    gridPosY = 0;

    cursor = new Cursor(this);
    cursor->setStartPosition(QPoint(0, 0));
    cursor->setGridStep(20);

    painterLogic = new PainterLogic(cursor->getStartPosition(), this);
    connect(cursor, SIGNAL(reseted(QPoint)), painterLogic, SLOT(onCursorReseted(QPoint)));
    connect(cursor, SIGNAL(positionChanged(QPoint)), painterLogic, SLOT(onPositionChanged(QPoint)));

    actionLogger = new ActionLogger(this);
    connect(cursor, SIGNAL(reseted(QPoint)), actionLogger, SLOT(onCursorReseted(QPoint)));
    connect(cursor, SIGNAL(keyCodeAccepted(int)), actionLogger, SLOT(onKeyCodeAccepted(int)));

    connect(cursor, SIGNAL(cursorIsBeyondRange()), this, SIGNAL(cursourOutOfRange()));

    installEventFilter(this);
}

void PainterWidget::setGridStep(int step) {
    cursor->setGridStep(step);
    setPositionX(gridPosX);
    setPositionY(gridPosY);
    update();
}

void PainterWidget::setPositionX(int x) {
    gridPosX = x;
    QPoint startPos = cursor->getStartPosition();
    startPos.setX(gridPosX * cursor->getGridStep());
    cursor->setStartPosition(startPos);
    update();
}

void PainterWidget::setPositionY(int y) {
    gridPosY = y;
    QPoint startPos = cursor->getStartPosition();
    startPos.setY(gridPosY * cursor->getGridStep());
    cursor->setStartPosition(startPos);
    update();
}

void PainterWidget::saveImage(QString path) {
    QPixmap originalPixmap;
    originalPixmap = this->grab();
    if (path.isEmpty())
        path = "img.png";
    originalPixmap.save(path, "PNG");
}

void PainterWidget::clearImage() {
    cursor->reset();
    update();
}

void PainterWidget::setTracerHidden(bool hidden) {
    tracerHidden = hidden;
    update();
}

bool PainterWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();
        if (key >= Qt::Key_1 && key <= Qt::Key_9) {
            processArrowKey(key);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void PainterWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    drawGrid(painter);
    drawLines(painter);
    if (!tracerHidden)
        drawTrace(painter);
}

void PainterWidget::resizeEvent(QResizeEvent *) {
    cursor->setXRange(0, width());
    cursor->setYRange(0, height());
}

void PainterWidget::processArrowKey(int key) {
    cursor->changeCurrentPosition(key);
    emit positionChanged(actionLogger->getActionList());
    update();
}

void PainterWidget::drawGrid(QPainter &painter) {
    painter.fillRect(0, 0, width(), height(), QColor(Qt::white));
    painter.setPen(QPen(Qt::darkGray, 1));
    for (int posx = 0; posx <= width(); posx += cursor->getGridStep())
        painter.drawLine(posx, 0, posx, height());
    for (int posy = 0; posy <= height(); posy += cursor->getGridStep())
        painter.drawLine(0, posy, width(), posy);
}

void PainterWidget::drawTrace(QPainter &painter) {
    painter.setPen(QPen(Qt::red, 3));
    painter.drawEllipse(cursor->getCurrentPosition(), 3, 3);
}

void PainterWidget::drawLines(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 3));
    const QList <LinePosition> lineList = painterLogic->getLineList();
    foreach (LinePosition lp, lineList)
        painter.drawLine(
                    lp.a.x(), lp.a.y(),
                    lp.b.x(), lp.b.y());
}
