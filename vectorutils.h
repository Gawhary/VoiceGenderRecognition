#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <QVector>

namespace vector
{
QVector<double> subrange(const QVector<double> &a, int from, int to);

QVector<double> add(const QVector<double> &a, const QVector<double> &b);

QVector<double> subtract(const QVector<double> &a, const QVector<double> &b);

QVector<double> subtract(const QVector<double> &a, double x);

QVector<double> multipli(const QVector<double> &a, const QVector<double> &b);

QVector<double> abs(const QVector<double> &a);

double sum(const QVector<double> &a);

double dot(const QVector<double> &a, const QVector<double> &b);

double max(const QVector<double> &a);

void max(const QVector<double> &a, double &maxVal, int &maxIdx);

double min(const QVector<double> &a);

double avg(const QVector<double> &a);

double median(const QVector<double> &a);

double var(const QVector<double> &a, bool flag=false);

double std(const QVector<double> &a, bool flag=false);

QVector<double> conv(const QVector<double> &a, const QVector<double> &b);

QVector<double> xcorr(const QVector<double> &a, const QVector<double> &b, bool coeff=false);
}

#endif // VECTORUTILS_H
