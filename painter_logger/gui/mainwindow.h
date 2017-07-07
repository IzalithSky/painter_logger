#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setOpacity(int opacity);
    void stateBegginingPoint();
private slots:
    void onPositionChanged(QStringList msgList);
    void on_spinBoxX_editingFinished();
    void on_spinBoxY_editingFinished();
    void on_pushButtonClear_clicked();
    void on_pushButtonSave_clicked();
    void on_toolButtonBrowse_clicked();
    void on_spinBoxStep_editingFinished();
    void on_pushButtonHideTrace_toggled(bool checked);
    void on_horizontalSliderOpacity_valueChanged(int value);
    void onCursourOutOfRange();
};

#endif // MAINWINDOW_H
