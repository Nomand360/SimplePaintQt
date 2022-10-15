#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ScribbleArea;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionColor_triggered();

    void on_actionWidth_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    ScribbleArea *area;
};
#endif // MAINWINDOW_H
