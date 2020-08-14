#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imagewidget.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageWidget = new ImageWidget(this);
    this->setCentralWidget(imageWidget);

    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionConvert, &QAction::triggered, this, &MainWindow::convert);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Choose image"),
                                                          QDir::currentPath(),
                                                          tr("Images (*.png)"));
    if (fileName.isEmpty())
        return;

    imageWidget->loadImage(fileName);
}

void MainWindow::convert()
{
    const bool result = imageWidget->convertImage();
    if (!result)
        QMessageBox::critical(this, this->windowTitle(), tr("Error to convert image"));
}

void MainWindow::showAbout()
{
    QMessageBox::information(this, tr("About"), this->windowTitle() + tr("\nCreated by SWS TEAM\n2020"));
}

