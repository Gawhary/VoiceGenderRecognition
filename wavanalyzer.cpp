#include "wavanalyzer.h"

#include <QDebug>
#include <QtMath>
#include <QDataStream>

#include "wavfile.h"
#include "utils.h"
#include "vectorutils.h"

WavAnalyzer::WavAnalyzer(QObject *parent):
    QObject(parent)
{
}

bool WavAnalyzer::analyzeFile(const QString &fileName)
{
    m_errorMsg = "";
    m_fileName = fileName;
    m_sampledData.clear();
    m_sampleRate = 0;
    m_median = m_std = 0.0;

    if (loadFile())
    {
        analyzeSampledData();
        return true;
    }
    return false;
}

void WavAnalyzer::analyzeData(const QVector<double> &sampledData, int sampleRate)
{
    m_errorMsg = "";
    m_fileName = "";
    m_sampledData = sampledData;
    m_sampleRate = sampleRate;
    m_median = m_std = 0.0;

    analyzeSampledData();
}

bool WavAnalyzer::loadFile()
{
    WavFile file;
    if (! file.open(m_fileName))
    {
        m_errorMsg = "Could not open file";
        return false;
    }

    QAudioFormat format = file.fileFormat();
    qDebug() << format;

    if (! isPCMS16LE(format))
    {
        m_errorMsg = "Audio format not supported";
        return false;
    }

    m_sampleRate = format.sampleRate();

    // check form expected format
    if (format.sampleSize() == 16 &&
        format.sampleType() == QAudioFormat::SignedInt &&
        format.byteOrder() == QAudioFormat::LittleEndian)
    {
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::LittleEndian);

        while (! stream.atEnd())
        {
            short val = 0;
            stream >> val;
            m_sampledData << (double)(val / pow(2.0, 15));
        }
    }

    qDebug() << "sampled data length:" << m_sampledData.length();

    file.close();
    return true;
}

void WavAnalyzer::analyzeSampledData()
{
    int ms2 = qFloor(m_sampleRate * 0.002);
    int ms10 = qFloor(m_sampleRate * 0.01);
    int ms20 = qFloor(m_sampleRate * 0.02);
    int ms30 = qFloor(m_sampleRate * 0.03);

    int pos = 1, fxval;
    QVector<double> fx, energy, y, r, absR;
    double ethr, rmax;

    while (pos+ms30 <= m_sampledData.count())
    {
        y = vector::subrange(m_sampledData, pos, pos + ms30 - 1);
        y = vector::subtract(y, vector::avg(y));
        energy << 10 * log10(vector::dot(y, y));
        ethr = 0.1 * energy.last();

        r = vector::xcorr(y, y, true);
        //r = vector::xcorr(y, ms20, true);
        r = vector::subrange(r, ms20 + 1, 2 * ms20 + 1);

        absR = vector::abs(vector::subrange(r, ms2, ms20));
        vector::max(absR, rmax, fxval);

        if (rmax > 0.6 && energy.last() > ethr)
        {
            fx << m_sampleRate / (ms2 + fxval - 1);
        }
        else
        {
            fx << NAN;
        }

        pos += ms10;
    }

    QVector<double> gx;
    for (int i = 0; i < fx.count(); i++)
    {
        if (fx.at(i) > 75 && fx.at(i) < 275)
        {
            gx << fx.at(i);
        }
    }

    m_median = vector::median(gx);
    m_std = vector::std(gx);

    qDebug() << "median:" << m_median;
    qDebug() << "std:" << m_std;
}
