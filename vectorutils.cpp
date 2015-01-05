#ifndef VECTORUTILSIMPL_H
#define VECTORUTILSIMPL_H

#include "vectorutils.h"

#include <math.h>
#include <QtMath>
#include <QtAlgorithms>
#include <QVector>


QVector<double> vector::subrange(const QVector<double> &a, int from, int to)
{
    return a.mid(from - 1, to - from + 1);
}

QVector<double> vector::add(const QVector<double> &a, const QVector<double> &b)
{
    Q_ASSERT(a.count() == b.count());

    QVector<double> res;
    for (int i = 0; i < a.count(); ++i)
    {
        res.append(a.at(i) + b.at(i));
    }

    return res;
}

QVector<double> vector::subtract(const QVector<double> &a, const QVector<double> &b)
{
    Q_ASSERT(a.count() == b.count());

    QVector<double> res;
    for (int i = 0; i < a.count(); ++i)
    {
        res.append(a.at(i) - b.at(i));
    }

    return res;
}

QVector<double> vector::subtract(const QVector<double> &a, double x)
{
    QVector<double> res;
    for (int i = 0; i < a.count(); ++i)
    {
        res.append(a.at(i) - x);
    }

    return res;
}

QVector<double> vector::multipli(const QVector<double> &a, const QVector<double> &b)
{
    Q_ASSERT(a.count() == b.count());

    QVector<double> res;
    for (int i = 0; i < a.count(); ++i)
    {
        res.append(a.at(i) * b.at(i));
    }

    return res;
}

QVector<double> vector::abs(const QVector<double> &a)
{
    QVector<double> res;
    foreach (double x, a)
    {
        res.append(qFabs(x));
    }

    return res;
}

double vector::sum(const QVector<double> &a)
{
    double res = 0;

    for (int i = 0; i < a.count(); ++i)
    {
        res += a.at(i);
    }

    return res;
}

double vector::dot(const QVector<double> &a, const QVector<double> &b)
{
    return vector::sum(vector::multipli(a, b));
}

double vector::max(const QVector<double> &a)
{
    if (a.isEmpty())
        return 0;

    double res = a.first();

    // start loop with second value
    for (int i = 1; i < a.count(); ++i)
    {
        if (a.at(i) > res)
            res = a.at(i);
    }

    return res;
}


void vector::max(const QVector<double> &a, double &maxVal, int &maxIdx)
{
    if (a.isEmpty())
        return;

    maxVal = a.first();
    maxIdx = 0;

    // start loop with second value
    for (int i = 1; i < a.count(); ++i)
    {
        if (a.at(i) > maxVal)
        {
            maxVal = a.at(i);
            maxIdx = i;
        }
    }
}

double vector::min(const QVector<double> &a)
{
    if (a.isEmpty())
        return 0;

    double res = a.first();

    // start loop with second value
    for (int i = 1; i < a.count(); ++i)
    {
        if (a.at(i) < res)
            res = a.at(i);
    }

    return res;
}

double vector::avg(const QVector<double> &a)
{
    if (a.isEmpty())
        return 0;

    return vector::sum(a) / a.count();
}

double vector::median(const QVector<double> &a)
{
    if (a.isEmpty())
        return 0;

    QVector<double> x = a;
    qSort(x.begin(), x.end());

    if (x.count() % 2 == 1) // if odd
    {
        return x.at(x.count() / 2);
    }
    else
    {
        return (x.at(x.count() / 2) + x.at(x.count() / 2 - 1)) / 2;
    }

    return 0;
}

double vector::var(const QVector<double> &a, bool flag)
{
    double mean = vector::avg(a);
    double sdiff = 0;
    foreach (double x, a)
    {
        sdiff += (x-mean)*(x-mean);
    }

    if (flag)
        return sdiff / a.count();
    //else
    return sdiff / (a.count() - 1);
}

double vector::std(const QVector<double> &a, bool flag)
{
    return qSqrt(vector::var(a, flag));
}

QVector<double> vector::conv(const QVector<double> &a, const QVector<double> &b)
{
    QVector<double> res(a.count() + b.count() - 1);

    for (int i = 0; i < res.count(); i++)
    {
        double s = 0.0;
        int n_lo = 0 > (i - b.count() + 1) ? 0 : i - b.count() + 1;
        int n_hi = a.count() - 1 < i ? a.count() - 1 : i;
        int ai = n_lo;
        int bi = i - n_lo;

        for (int n = n_lo; n <= n_hi; n++)
        {
            s += a.at(ai) * b.at(bi);
            ai++;
            bi--;
        }

        res[i] = s;
    }

    return res;
}

QVector<double> vector::xcorr(const QVector<double> &a, const QVector<double> &b, bool coeff)
{
    QVector<double> res(a.count() + b.count() - 1);

    for (int i = 0; i < res.count(); i++)
    {
        double s = 0.0;
        int n_lo = 0 > (i - b.count() + 1) ? 0 : i - b.count() + 1;
        int n_hi = a.count() - 1 < i ? a.count() - 1 : i;
        int ai = n_lo;
        int bi = i - n_lo;

        for (int n = n_lo; n <= n_hi; n++)
        {
            s += a.at(ai) * b.at(b.count() - bi - 1);
            ai++;
            bi--;
        }

        res[i] = s;
    }

    if (coeff)
    {
        double mx = vector::max(res);
        for (int i = 0; i < res.count(); ++i)
        {
            res[i] = res.at(i) / mx;
        }
    }

    return res;
}

#endif // VECTORUTILSIMPL_H
