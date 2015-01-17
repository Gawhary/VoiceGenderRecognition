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
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this, QString("Select sound files"), QString(), QString("WAV-files (*.wav);;All Files (*.*)"));

    foreach (QString f, fileNames) {
        analyzeFile(f);
    }

}

void MainWindow::analyzeFile(QString fileName)
{
    QString results;

    if (m_analyzer->analyzeFile(fileName))
    {
        results += fileName + "\n";
        results += QString("sampled data length:%1\n").arg(m_analyzer->sampledData().count());
        results += QString("sampled rate:%1\n").arg(m_analyzer->sampleRate());
        results += QString("median:%1\n").arg(m_analyzer->median());
        results += QString("Male Energy:%1\n").arg(m_analyzer->mEnergy());
        results += QString("Feale Energy:%1\n").arg(m_analyzer->fEnergy());
        results += QString("std:%1").arg(m_analyzer->std());
    }
    else
    {
        results = "error:" + m_analyzer->errorMsg();
    }

    ui->resultEdit->appendPlainText(results);
}
