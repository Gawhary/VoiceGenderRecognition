#ifndef WAVANALYZER_H
#define WAVANALYZER_H

#include <QObject>
#include <QVector>

class WavAnalyzer : public QObject
{
    Q_OBJECT

public:
    WavAnalyzer(QObject *parent = 0);

public:
    QString fileName() const { return m_fileName; }
    QString errorMsg() const { return m_errorMsg; }
    QVector<double> sampledData() const { return m_sampledData; }
    double sampleRate() const { return m_sampleRate; }
    double median() const { return m_median; }
    double std() const { return m_std; }
    double fEnergy() const {return m_femaleEnergy;}
    double mEnergy() const {return m_maleEnergy;}

    bool analyzeFile(const QString &fileName);
    void analyzeData(const QVector<double> &sampledData, int sampleRate);

private:
    bool loadFile();
    void analyzeSampledData();

private:
    QString m_fileName;
    QString m_errorMsg;
    QVector<double> m_sampledData;
    int m_sampleRate;
    double m_median;
    double m_std;
    double m_maleEnergy;
    double m_femaleEnergy;
};

#endif // WAVANALYZER_H
