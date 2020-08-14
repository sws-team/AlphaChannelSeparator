#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    void open();
    void convert();
private Q_SLOTS:
    void showAbout();

private:
    Ui::MainWindow *ui;
    class ImageWidget *imageWidget;
};
#endif // MAINWINDOW_H
