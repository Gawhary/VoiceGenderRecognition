#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include "wavanalyzer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_analyzer = new WavAnalyzer(this);

    connect(ui->actionAnalyze, SIGNAL(triggered()), this, SLOT(analyzeFile()));
    connect(ui->analyzeButton, SIGNAL(clicked()), this, SLOT(analyzeFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, QString("Select sound files"), QString(), QString("WAV-files (*.wav);;All Files (*.*)"));

    ui->fileNameEdit->setText(fileName);
}

void MainWindow::analyzeFile()
{
    QString fileName = ui->fileNameEdit->text();
    QString results = "";

    if (m_analyzer->analyzeFile(fileName))
    {
        results += QString("sampled data length:%1\n").arg(m_analyzer->sampledData().count());
        results += QString("sampled rate:%1\n").arg(m_analyzer->sampleRate());
        results += QString("median:%1\n").arg(m_analyzer->median());
        results += QString("std:%1").arg(m_analyzer->std());
    }
    else
    {
        results = "error:" + m_analyzer->errorMsg();
    }

    ui->resultEdit->setPlainText(results);
}
