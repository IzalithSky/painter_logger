#include <QString>
#include <QtTest>

#include <QList>
#include <QPoint>
#include <QStringList>

#include "cursor.h"
#include "painterlogic.h"
#include "actionlogger.h"

// Copy symbols from here ↑ ↓ ← → ↖ ↗ ↘ ↙

class Tests : public QObject {
    Q_OBJECT
public:
    Tests();
private:
    int gridStep;
    QPoint startPos;

    Cursor *cursor;
    PainterLogic *painterLogic;
    ActionLogger *actionLogger;
private Q_SLOTS:
    void init();
    void cleanup();

    void cursor_currentPositionOutOfRange_test();
    void cursor_negativeRange_test();
    void cursor_resetedIsEmitted_test();
    void cursor_positionChangedIsEmitted_test();
    void cursor_keyCodeAcceptedIsEmitted_test();
    void cursor_cursorIsBeyondRangeEmmited_test();

    void cursor_BumpWallUp_test();
    void cursor_BumpWallDown_test();
    void cursor_BumpWallLeft_test();
    void cursor_BumpWallRight_test();

    void cursor_Undo_test();

    void painterLogic_SingleMoveUp_test();
    void painterLogic_SingleMoveDown_test();
    void painterLogic_SingleMoveLeft_test();
    void painterLogic_SingleMoveRight_test();
    void painterLogic_SingleMoveUpLeft_test();
    void painterLogic_SingleMoveUpRight_test();
    void painterLogic_SingleMoveDownLeft_test();
    void painterLogic_SingleMoveDownRight_test();

    void painterLogic_MoveAround_test();

    void painterLogic_Undo_test();

    void actionLogger_SingleMoveUp_test();
    void actionLogger_SingleMoveDown_test();
    void actionLogger_SingleMoveLeft_test();
    void actionLogger_SingleMoveRight_test();
    void actionLogger_SingleMoveUpLeft_test();
    void actionLogger_SingleMoveUpRight_test();
    void actionLogger_SingleMoveDownLeft_test();
    void actionLogger_SingleMoveDownRight_test();

    void actionLogger_MoveAround_test();

    void actionLogger_SequenceUp_test();
    void actionLogger_SequenceDownLeft_test();
    void actionLogger_SequenceDownThenUpRight_test();
    void actionLogger_MoveAroundWithSeqences_test();

    void actionLogger_Undo_test();
};

Tests::Tests() {}

void Tests::init() {
    gridStep = 10;
    startPos = QPoint(100, 100);
    int minX = 0, maxX = 200, minY = 0, maxY = 200;

    cursor = new Cursor(this);
    cursor->setStartPosition(startPos);
    cursor->setGridStep(gridStep);
    cursor->setXRange(minX, maxX);
    cursor->setYRange(minY, maxY);

    painterLogic = new PainterLogic(startPos, this);
    connect(cursor, SIGNAL(reseted(QPoint)), painterLogic, SLOT(onCursorReseted(QPoint)));
    connect(cursor, SIGNAL(positionChanged(QPoint)), painterLogic, SLOT(onPositionChanged(QPoint)));

    actionLogger = new ActionLogger(this);
    connect(cursor, SIGNAL(reseted(QPoint)), actionLogger, SLOT(onCursorReseted(QPoint)));
    connect(cursor, SIGNAL(keyCodeAccepted(int)), actionLogger, SLOT(onKeyCodeAccepted(int)));
}

void Tests::cleanup() {
    actionLogger->deleteLater();
    painterLogic->deleteLater();
    cursor->deleteLater();
}

void Tests::cursor_currentPositionOutOfRange_test() {
    cursor->setXRange(-20, 0);
    cursor->setYRange(10, 90);

    QCOMPARE(cursor->getStartPosition(), QPoint(-20, 10));
    QCOMPARE(cursor->getCurrentPosition(), QPoint(-20, 10));
}

void Tests::cursor_negativeRange_test() {
    cursor->setXRange(-20, -50);
    QCOMPARE(cursor->getStartPosition(), QPoint(0, 0));

    cursor->setYRange(100, 90);
    QCOMPARE(cursor->getCurrentPosition(), QPoint(0, 0));
}

void Tests::cursor_resetedIsEmitted_test() {
    QSignalSpy spy(cursor, SIGNAL(reseted(QPoint)));

    cursor->reset();

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.count(), 1);
}


void Tests::cursor_positionChangedIsEmitted_test() {
    QSignalSpy spy(cursor, SIGNAL(positionChanged(QPoint)));

    cursor->changeCurrentPosition(Qt::Key_2);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.count(), 1);
}

void Tests::cursor_keyCodeAcceptedIsEmitted_test() {
    QSignalSpy spy(cursor, SIGNAL(keyCodeAccepted(int)));

    cursor->changeCurrentPosition(Qt::Key_2);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.count(), 1);
}

void Tests::cursor_cursorIsBeyondRangeEmmited_test() {
    QSignalSpy spy(cursor, SIGNAL(cursorIsBeyondRange()));

//    cursor->setXRange(-100, -10);
    cursor->setStartPosition(QPoint(1000, 1000));

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.count(), 0);
}

void Tests::cursor_BumpWallUp_test() {
    QSignalSpy spy(cursor, SIGNAL(positionChanged(QPoint)));

    cursor->setStartPosition(QPoint(100, 10));

    cursor->changeCurrentPosition(Qt::Key_8);
    cursor->changeCurrentPosition(Qt::Key_8);
    cursor->changeCurrentPosition(Qt::Key_8);
    cursor->changeCurrentPosition(Qt::Key_8);

    QCOMPARE(spy.count(), 1);
}

void Tests::cursor_BumpWallDown_test() {
    QSignalSpy spy(cursor, SIGNAL(positionChanged(QPoint)));

    cursor->setStartPosition(QPoint(100, 190));

    cursor->changeCurrentPosition(Qt::Key_2);
    cursor->changeCurrentPosition(Qt::Key_2);
    cursor->changeCurrentPosition(Qt::Key_2);
    cursor->changeCurrentPosition(Qt::Key_2);

    QCOMPARE(spy.count(), 1);
}

void Tests::cursor_BumpWallLeft_test() {
    QSignalSpy spy(cursor, SIGNAL(positionChanged(QPoint)));

    cursor->setStartPosition(QPoint(10, 100));

    cursor->changeCurrentPosition(Qt::Key_4);
    cursor->changeCurrentPosition(Qt::Key_4);
    cursor->changeCurrentPosition(Qt::Key_4);
    cursor->changeCurrentPosition(Qt::Key_4);

    QCOMPARE(spy.count(), 1);
}

void Tests::cursor_BumpWallRight_test() {
    QSignalSpy spy(cursor, SIGNAL(positionChanged(QPoint)));

    cursor->setStartPosition(QPoint(190, 100));

    cursor->changeCurrentPosition(Qt::Key_6);
    cursor->changeCurrentPosition(Qt::Key_6);
    cursor->changeCurrentPosition(Qt::Key_6);
    cursor->changeCurrentPosition(Qt::Key_6);

    QCOMPARE(spy.count(), 1);
}

void Tests::cursor_Undo_test() {
    cursor->setStartPosition(QPoint(100, 100));

    cursor->changeCurrentPosition(Qt::Key_6);
    cursor->changeCurrentPosition(Qt::Key_6);
    cursor->changeCurrentPosition(Qt::Key_6);
    cursor->changeCurrentPosition(Qt::Key_6);

    cursor->undo();
    cursor->undo();

    QCOMPARE(cursor->getCurrentPosition(), QPoint(120, 100));
}

void Tests::painterLogic_SingleMoveUp_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x(), startPos.y() - gridStep)); // ↑
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x(), startPos.y() - gridStep));
}

void Tests::painterLogic_SingleMoveDown_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x(), startPos.y() + gridStep)); // ↓
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x(), startPos.y() + gridStep));
}

void Tests::painterLogic_SingleMoveLeft_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x() - gridStep, startPos.y())); // ←
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x() - gridStep, startPos.y()));
}

void Tests::painterLogic_SingleMoveRight_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x() + gridStep, startPos.y())); // →
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x() + gridStep, startPos.y()));
}

void Tests::painterLogic_SingleMoveUpLeft_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x() - gridStep, startPos.y() - gridStep)); // ↖
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x() - gridStep, startPos.y() - gridStep));
}

void Tests::painterLogic_SingleMoveUpRight_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x() + gridStep, startPos.y() - gridStep)); // ↗
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x() + gridStep, startPos.y() - gridStep));
}

void Tests::painterLogic_SingleMoveDownLeft_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x() + gridStep, startPos.y() + gridStep)); // ↘
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x() + gridStep, startPos.y() + gridStep));
}

void Tests::painterLogic_SingleMoveDownRight_test() {
    painterLogic->onPositionChanged(QPoint(startPos.x() - gridStep, startPos.y() + gridStep)); // ↙
    const QList<LinePosition> lpl = painterLogic->getLineList();
    QVERIFY(lpl.length() > 0);
    LinePosition lp = lpl.first();
    QCOMPARE(lp.a, QPoint(startPos.x(), startPos.y()));
    QCOMPARE(lp.b, QPoint(startPos.x() - gridStep, startPos.y() + gridStep));
}

void Tests::painterLogic_MoveAround_test() {
    painterLogic->onPositionChanged(QPoint(110, 100));
    painterLogic->onPositionChanged(QPoint(110, 110));
    painterLogic->onPositionChanged(QPoint(100, 110));
    painterLogic->onPositionChanged(QPoint(100, 100));
    const QList<LinePosition> lpl = painterLogic->getLineList();

    QCOMPARE(lpl.length(), 4);

    QCOMPARE(lpl.at(0).a, QPoint(100, 100));
    QCOMPARE(lpl.at(0).b, QPoint(110, 100));

    QCOMPARE(lpl.at(1).a, QPoint(110, 100));
    QCOMPARE(lpl.at(1).b, QPoint(110, 110));

    QCOMPARE(lpl.at(2).a, QPoint(110, 110));
    QCOMPARE(lpl.at(2).b, QPoint(100, 110));

    QCOMPARE(lpl.at(3).a, QPoint(100, 110));
    QCOMPARE(lpl.at(3).b, QPoint(100, 100));
}

void Tests::painterLogic_Undo_test() {
    painterLogic->onPositionChanged(QPoint(110, 100));
    painterLogic->onPositionChanged(QPoint(110, 110));
    painterLogic->onPositionChanged(QPoint(100, 110));

    painterLogic->undo();
    painterLogic->undo();

    painterLogic->onPositionChanged(QPoint(110, 90));

    const QList<LinePosition> lpl = painterLogic->getLineList();

    QCOMPARE(lpl.last().a, QPoint(110, 100));
    QCOMPARE(lpl.last().b, QPoint(110, 90));
}

void Tests::actionLogger_SingleMoveUp_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QString msg = lmsg.last();
    QCOMPARE(msg, QString("1. ↑"));
}

void Tests::actionLogger_SingleMoveDown_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↓"));
}

void Tests::actionLogger_SingleMoveLeft_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_4);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ←"));
}

void Tests::actionLogger_SingleMoveRight_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_6);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. →"));
}

void Tests::actionLogger_SingleMoveUpLeft_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_7);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↖"));
}

void Tests::actionLogger_SingleMoveUpRight_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_9);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↗"));
}

void Tests::actionLogger_SingleMoveDownLeft_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_1);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↙"));
}

void Tests::actionLogger_SingleMoveDownRight_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_3);
    const QStringList lmsg = actionLogger->getActionList();
    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↘"));
}

void Tests::actionLogger_MoveAround_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_6);
    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    actionLogger->onKeyCodeAccepted(Qt::Key_4);
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    const QStringList lmsg = actionLogger->getActionList();

    QCOMPARE(lmsg.length(), 4);

    QCOMPARE(QString(lmsg.at(0)), QString("1. →"));
    QCOMPARE(QString(lmsg.at(1)), QString("2. ↓"));
    QCOMPARE(QString(lmsg.at(2)), QString("3. ←"));
    QCOMPARE(QString(lmsg.at(3)), QString("4. ↑"));
}

void Tests::actionLogger_SequenceUp_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    const QStringList lmsg = actionLogger->getActionList();

    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↑ 3"));
}

void Tests::actionLogger_SequenceDownLeft_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_1);
    actionLogger->onKeyCodeAccepted(Qt::Key_1);
    actionLogger->onKeyCodeAccepted(Qt::Key_1);
    const QStringList lmsg = actionLogger->getActionList();

    QCOMPARE(lmsg.length(), 1);
    QCOMPARE(QString(lmsg.last()), QString("1. ↙ 3"));
}

void Tests::actionLogger_SequenceDownThenUpRight_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    actionLogger->onKeyCodeAccepted(Qt::Key_9);
    actionLogger->onKeyCodeAccepted(Qt::Key_9);
    const QStringList lmsg = actionLogger->getActionList();

    QCOMPARE(lmsg.length(), 2);
    QCOMPARE(QString(lmsg.at(0)), QString("1. ↓ 3"));
    QCOMPARE(QString(lmsg.at(1)), QString("2. ↗ 2"));
}

void Tests::actionLogger_MoveAroundWithSeqences_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_6);

    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    actionLogger->onKeyCodeAccepted(Qt::Key_2);
    actionLogger->onKeyCodeAccepted(Qt::Key_2);

    actionLogger->onKeyCodeAccepted(Qt::Key_4);

    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    actionLogger->onKeyCodeAccepted(Qt::Key_8);
    const QStringList lmsg = actionLogger->getActionList();

    QCOMPARE(lmsg.length(), 4);

    QCOMPARE(QString(lmsg.at(0)), QString("1. →"));
    QCOMPARE(QString(lmsg.at(1)), QString("2. ↓ 3"));
    QCOMPARE(QString(lmsg.at(2)), QString("3. ←"));
    QCOMPARE(QString(lmsg.at(3)), QString("4. ↑ 4"));
}

void Tests::actionLogger_Undo_test() {
    actionLogger->onKeyCodeAccepted(Qt::Key_4);
    actionLogger->onKeyCodeAccepted(Qt::Key_4);
    actionLogger->onKeyCodeAccepted(Qt::Key_4);
    actionLogger->onKeyCodeAccepted(Qt::Key_4);

    actionLogger->undo();
    actionLogger->undo();

    const QStringList lmsg = actionLogger->getActionList();

    QCOMPARE(QString(lmsg.last()), QString("1. ← 2"));
}

QTEST_APPLESS_MAIN(Tests)

#include "tests.moc"
