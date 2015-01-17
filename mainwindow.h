#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WavAnalyzer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();
    void analyzeFile(QString fileName);

private:
    Ui::MainWindow *ui;
    WavAnalyzer *m_analyzer;
};

#endif // MAINWINDOW_H
