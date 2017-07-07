#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setOpacity(ui->horizontalSliderOpacity->value());

    stateBegginingPoint();

    connect(ui->widget, SIGNAL(positionChanged(QStringList)), this, SLOT(onPositionChanged(QStringList)));
    connect(ui->widget, SIGNAL(cursourOutOfRange()), this, SLOT(onCursourOutOfRange()));
    ui->widget->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPositionChanged(QStringList msgList) {
    ui->textBrowser->clear();
    stateBegginingPoint();
    foreach (QString msg, msgList)
        ui->textBrowser->append(msg);
}

void MainWindow::onCursourOutOfRange() {
    ui->spinBoxX->setValue(0);
    ui->spinBoxY->setValue(0);
}

void MainWindow::on_spinBoxX_editingFinished()
{
    ui->widget->setPositionX(ui->spinBoxX->value());
    ui->textBrowser->clear();
    stateBegginingPoint();
}

void MainWindow::on_spinBoxY_editingFinished()
{
    ui->widget->setPositionY(ui->spinBoxY->value());
    ui->textBrowser->clear();
    stateBegginingPoint();
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->widget->clearImage();
    ui->textBrowser->clear();
    stateBegginingPoint();
}

void MainWindow::on_pushButtonSave_clicked()
{
    ui->widget->saveImage(ui->lineEditPath->text());
}

void MainWindow::on_toolButtonBrowse_clicked()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                tr("Save Image"),
                NULL,
                tr("PNG (*.png)"));
    ui->lineEditPath->setText(path);
}

void MainWindow::on_spinBoxStep_editingFinished()
{
    ui->widget->setGridStep(ui->spinBoxStep->value());
}

void MainWindow::on_pushButtonHideTrace_toggled(bool checked)
{
    ui->widget->setTracerHidden(checked);
}

void MainWindow::on_horizontalSliderOpacity_valueChanged(int value)
{
    setOpacity(value);
}

void MainWindow::setOpacity(int opacity) {
    double val = .1 + (static_cast <double> (opacity) / 100) * .9;
    setWindowOpacity(val);
}

void MainWindow::stateBegginingPoint() {
    ui->textBrowser->append("Начало: " + QString::number(ui->spinBoxX->value()) + ", " + QString::number(ui->spinBoxY->value()));
}
