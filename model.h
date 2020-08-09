#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>
#include <QtCore>
#include "star.h"
#include "constants.h"




//класс Model реализует логику обработки данных
class Model : public QThread
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

private:
    //создание вектора объектов класса Star. В нем хранится информация о звездах.
    QVector<Star> cat;
    QVector <double> hist;
    QString filename;

protected:
    //функция нахождения апекса по фильтрованным значениям апеска
    void findApex(const QList <int>& ind);

    //функция подготовки визуализации по отфильтрованным значениям списка индексов
    void preparePlot(const QList <int>& ind);

    //функция для решения системы уравнения методом Гаусса
    void solverGauss(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1], double var[SIZE_SYSTEM]);

    //функция  умножения матрицы на вектор
    void multiplyMatrixVec(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1], double var[SIZE_SYSTEM]);

    //функция печати матрицы
    void printMatrix(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1]);

    void prepareHistogram(const QList <int>& ind);

    virtual void run();

signals:
    //сигнал об удачном чтении файла
    void readFileOk();

    //сигнал об неудачном чтении файла
    void readFileFail();

    //сигнал об отрисовке звезд
    void drawStars(QVector<QVector<double> >alphas, QVector<QVector<double> >deltas,
                   QVector<quint32>colors);

    //сигнал об отрисовке апекса
    void drawApex(double ra, double dec);

    //сигнал отправки статуса
    void drawStatus(unsigned long long n, double ra, double dec);

    //сигнал отправки статуса
    void loaded(int percent);

public slots:
    //слот чтения из файла
    void readFromFile(const QString &filename);

    //слот выбора звезд по критериям расстояния, спектрального класса, и звездной величины
    void selectStars(const QString &dist, const QString &sp, const QString &mag);

public:
    const QVector<double> & getSpHistogram() const {return hist;}


    
};

#endif // MODEL_H
