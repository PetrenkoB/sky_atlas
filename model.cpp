#include <algorithm>
#include "model.h"
#include "star.h"

//конструктор класса
Model::Model(QObject *parent) :
    QThread(parent)
{
    hist.resize(SP_N);
}

void Model::run()
{
    //создание объекта файла
    QFile file;
    file.setFileName(filename);

    //Проверка возможности чтения файла и его открытие
    bool file_ok = file.open(QFile::ReadOnly);
    if (!file_ok)
    {
        QDebug(QtDebugMsg) << "Error: unable to open from file!";
        emit readFileFail();        //вызов сигнала об неудачном чтении файла
        return;
    }

    cat.clear();
    unsigned long long numberOfLines = 0;
    while (!file.atEnd())
    //while (numberOfLines < numberOfStars && !file.atEnd())
    {
        Star s(file);
        cat.push_back(s);
        ++numberOfLines;
        if(numberOfLines % (numberOfStars / 10) == 0)
        {
            qDebug() << "load!";
            emit loaded((numberOfLines *100 ) / numberOfStars);
        }
    }
    emit loaded(100);
    emit readFileOk();              //вызов сигнала об удачном чтении файла
    selectStars(ALL, ALL, ALL);     //вызов слота выбора звезд по всем критериям расстояния, спектрального класса, и звездной величины
    file.close();                   //закрытие файла
}

//реализация слота чтения из файла
void Model::readFromFile(const QString &filename)
{
    this->filename = filename;
    start();
}

//реализации слота выбора звезд по критериям расстояния, спектрального класса, и звездной величины
void Model::selectStars(const QString &dist, const QString &sp, const QString &mag)
{
    QList<int> ind;                                         //создание списка индексов

    unsigned long long int initial_size = cat.size();
    for(int i = 0; i < cat.size(); ++i) ind.push_back(i);   //заполнение списка индексов

    //сортировка объектов по расстоянию
    if (dist==DIST_SELECT[1])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].dist() > 10.0 || cat[i].dist() == BAD_VALUE || cat[i].dist() < 0.0 )
            {
                ind.removeOne(i);
            }
        }
    }
    else if (dist==DIST_SELECT[2])
    {
         for (int i = 0; i < cat.size(); ++i)
         {
             if (cat[i].dist() <= 10.0 || cat[i].dist() > 50.0 || cat[i].dist() == BAD_VALUE)
             {
                 ind.removeOne(i);
             }
         }
    }
    else if (dist==DIST_SELECT[3])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].dist() <= 50.0 || cat[i].dist() > 100.0 || cat[i].dist() == BAD_VALUE)
            {
                ind.removeOne(i);
            }
        }
    }
    else if (dist==DIST_SELECT[4])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].dist() <= 100.0 || cat[i].dist() == BAD_VALUE)
            {
                ind.removeOne(i);
            }
        }
    }


    if (dist==DIST_SELECT[1])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].dist() > 10.0 || cat[i].dist() == BAD_VALUE || cat[i].dist() < 0.0 )
            {
                ind.removeOne(i);
            }
        }
    }


    //сортировка объектов по спектральному классу
    if (sp==SP_SELECT[1])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[0])
            {
                ind.removeOne(i);
            }
        }
    }
    else if (sp==SP_SELECT[2])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[1])
            {
                ind.removeOne(i);
            }
        }
    }
    else if (sp==SP_SELECT[3])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[2])
            {
                ind.removeOne(i);
            }
        }
    }
    else if (sp==SP_SELECT[4])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[3])
            {
                ind.removeOne(i);
            }
        }
    }
    else if (sp==SP_SELECT[5])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[4])
            {
                ind.removeOne(i);
            }
        }
    }
    else if (sp==SP_SELECT[6])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[5])
            {
                ind.removeOne(i);
            }
        }
    }
    else if (sp==SP_SELECT[7])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].spectralClassNumber() != SP_NUMBERS[6])
            {
                ind.removeOne(i);
            }
        }
    }


    //сортировка объектов по видимой звездной величине
    if (mag==MAG_SELECT[1])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].magV() > 5.0 || cat[i].magV() == BAD_VALUE)
            {
                ind.removeOne(i);
            }
        }
    }
    else if (mag==MAG_SELECT[2])
    {
         for (int i = 0; i < cat.size(); ++i)
         {
             if (cat[i].magV() <= 5.0 || cat[i].magV() > 10.0 || cat[i].magV() == BAD_VALUE)
             {
                 ind.removeOne(i);
             }
         }
    }
    else if (mag==MAG_SELECT[3])
    {
        for (int i = 0; i < cat.size(); ++i)
        {
            if (cat[i].magV() <= 10.0 ||  cat[i].magV() == BAD_VALUE)
            {
                ind.removeOne(i);
            }
        }
    }

    qDebug() << "NUMBER OF INITIAL STARS: " << initial_size;
    qDebug() << "NUMBER OF FILTERED STARS: " << ind.size();
    prepareHistogram(ind);
    preparePlot(ind);
    findApex(ind);

}

void Model::prepareHistogram(const QList <int>& ind)
{
    std::fill(hist.begin(), hist.end(), 0.0);
    for (int i = 0; i < ind.size(); ++i)
    {
        hist[cat[ind[i]].spectralClassNumber()]++;
    }
}


//реализация функции подготовки визуализации по отфильтрованным значениям списка индексов
void Model::preparePlot(const QList<int> &ind)
{
    //вектор координат объекта по спектральным классам
    QVector<QVector<double> > alphas(N_SP), deltas(N_SP);
    QVector<quint32> colors;

    for (int  i = 0; i < N_SP; ++i)
    {
        colors.push_back(SP_COLORS[i]);
    }

    int overdrawing = ind.size() - STAR_DRAW;       //ограничение количества звезд по отрисовке
    for (int  i = 0; i < ind.size(); ++i)
    {

        Star &s = cat[ind[i]];
        alphas[s.spectralClassNumber()].push_back(s.RA() * 12 / M_PI);
        deltas[s.spectralClassNumber()].push_back(s.dec() * 180 / M_PI);
        if (overdrawing > 0)
        {
            i += ind.size() / STAR_DRAW;
            continue;
        }
    }
    //посылка сигнала об отрисовке звезд
    emit drawStars(alphas, deltas, colors);

}


//реализации функции для решения системы уравнения методом Гаусса
void Model::solverGauss(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1], double var[SIZE_SYSTEM])
{
    for (int i = 0; i < SIZE_SYSTEM; ++i)
    {
        double max_element = abs(a[i][i]);
        int max_row = i;
        for (int k = i + 1; k < SIZE_SYSTEM; ++k)
        {
            if (abs(a[k][i]) > max_element)
            {
                max_element = abs(a[k][i]);
                max_row = k;
            }
        }

        for (int k = i; k < SIZE_SYSTEM + 1; ++k)
        {
            double temp = a[max_row][k];
            a[max_row][k] = a[i][k];
            a[i][k] = temp;
        }

        for (int k = i + 1; k < SIZE_SYSTEM; ++k)
        {
            double coef = -a[k][i]/a[i][i];
            for (int j = i; j < SIZE_SYSTEM + 1; ++j)
            {
                if (i==j)
                {
                    a[k][j] = 0;
                }
                else
                {
                    a[k][j] += coef * a[i][j];
                }
            }
        }
    }

    for (int i = SIZE_SYSTEM - 1; i >= 0; --i)
    {
        var[i] = a[i][SIZE_SYSTEM]/a[i][i];
        for (int k = i - 1; k >= 0; --k)
        {
            a[k][SIZE_SYSTEM] -= a[k][i] * var[i];
        }
    }
}

//реализация функции нахождения апекса по фильтрованным значениям апекса
void Model::findApex(const QList <int>& ind)
{
    double matrix[SIZE_SYSTEM][SIZE_SYSTEM  + 1];
    double matrix_temp[SIZE_SYSTEM][SIZE_SYSTEM  + 1];
    double res[SIZE_SYSTEM];
    double vector_free[SIZE_SYSTEM];
    double work_row[SIZE_SYSTEM  + 1];

    for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
    {
        work_row[j] = 0.0;
        for (int i = 0; i < SIZE_SYSTEM; ++i)
        {
            matrix[i][j] = 0.0;
        }
    }


    double pvar = 0.0;
    double qvar = 0.0;
    double rvar = 0.0;
    double kvar = 0.0;
    for (int i = 0; i < ind.size(); ++i)
    {
        pvar = -sin(cat[ind[i]].RA());
        qvar = cos(cat[ind[i]].RA());
        rvar = 0.0;
        kvar = cat[ind[i]].mRA();

        work_row[0] = pvar * pvar;
        work_row[1] = qvar * pvar;
        work_row[2] = rvar * pvar;
        work_row[3] = kvar * pvar;

        for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
        {
            matrix[0][j] += work_row[j];
        }

        work_row[0] = pvar * qvar;
        work_row[1] = qvar * qvar;
        work_row[2] = rvar * qvar;
        work_row[3] = kvar * qvar;

        for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
        {
            matrix[1][j] += work_row[j];
        }

        work_row[0] = pvar * rvar;
        work_row[1] = qvar * rvar;
        work_row[2] = rvar * rvar;
        work_row[3] = kvar * rvar;

        for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
        {
            matrix[2][j] += work_row[j];
        }


        pvar = -cos(cat[ind[i]].RA()) * sin(cat[ind[i]].dec());
        qvar = -sin(cat[ind[i]].RA()) * sin(cat[ind[i]].dec());
        rvar = cos(cat[ind[i]].dec());
        kvar = cat[ind[i]].mdec();

        work_row[0] = pvar * pvar;
        work_row[1] = qvar * pvar;
        work_row[2] = rvar * pvar;
        work_row[3] = kvar * pvar;

        for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
        {
            matrix[0][j] += work_row[j];
        }

        work_row[0] = pvar * qvar;
        work_row[1] = qvar * qvar;
        work_row[2] = rvar * qvar;
        work_row[3] = kvar * qvar;

        for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
        {
            matrix[1][j] += work_row[j];
        }

        work_row[0] = pvar * rvar;
        work_row[1] = qvar * rvar;
        work_row[2] = rvar * rvar;
        work_row[3] = kvar * rvar;

        for (int j = 0; j < SIZE_SYSTEM  + 1; ++j)
        {
            matrix[2][j] += work_row[j];
        }
    }

    for (int i = 0; i < SIZE_SYSTEM; ++i)
    {
        vector_free[i] = matrix[i][SIZE_SYSTEM];
        for (int j = 0; j < SIZE_SYSTEM; ++j)
        {
            matrix_temp[i][j] = matrix[i][j];
        }
    }
//    qDebug() << "#1";
//    printMatrix(matrix);
//    qDebug() << "#2";
    solverGauss(matrix, res);   //решение системы линейных алгебраических уравнений
    for (int i  = 0; i < SIZE_SYSTEM; ++i)
    {

        matrix_temp[i][SIZE_SYSTEM] = res[i];
    }

    double mult[SIZE_SYSTEM];
    multiplyMatrixVec(matrix_temp, mult);
//    qDebug() << "#3";
//    printMatrix(matrix_temp);
//    qDebug() << "#4";
//    qDebug() << mult[0] << mult[1] << mult[2];
    for (int i  = 0; i < SIZE_SYSTEM; ++i)
    {
        mult[i] = fabs(vector_free[i] - mult[i]);
    }


    //qDebug() << "------------------------";
    //printMatrix(matrix);
    //qDebug() << "------------------------";
    qDebug() << "------------------------";
    qDebug() << "RESULT: ";
    for (int i = 0; i < SIZE_SYSTEM; ++i)
    {
        qDebug() << res[i] << "+-" << mult[i];
    }

    qDebug() << "------------------------";

    double ra_apex = 2 * M_PI - atan2(res[1], res[0]);
    double dec_apex = -atan2(res[2], sqrt(res[0] * res[0] + res[1] * res[1]));
    double ra_apex_err = 1. / (1 + (res[1] / res[0]) * (res[1] / res[0])) * 1. / res[0] *
            sqrt((res[1] * mult[0] / res[0]) * (res[1] * mult[0] / res[0]) + mult[1] * mult[1]);
    double dec_apex_err = 1. / (1 + res[2] / (res[0] * res[0] + res[1] * res[1])) * 1. / sqrt(res[0] * res[0] + res[1] * res[1]) *
            sqrt((res[2] / (res[0] * res[0] + res[1] * res[1])) * (res[2] / (res[0] * res[0] + res[1] * res[1])) *
            ((res[0] * mult[0]) * (res[0] * mult[0]) + (res[1] * mult[1]) * (res[1] * mult[1])) + mult[2] * mult[2]);
    qDebug() << "------------------------";
    qDebug() << "APEX: " << "RA: " << ra_apex << " DEC: " << dec_apex;
    qDebug() << "APEX: " << "RA: " << ra_apex * 12 / M_PI << " DEC: " << dec_apex *  180 / M_PI;
    qDebug() << "APEX_ERR: " << "RA_ERR: " << ra_apex_err << " DEC_ERR: " << dec_apex_err;
    qDebug() << "APEX_ERR: " << "RA_ERR: " << ra_apex_err * 12 / M_PI << " DEC_ERR: " << dec_apex_err *  180 / M_PI;
    qDebug() << "------------------------";
    qDebug() << ind.size();

    //возбуждение сигнала об отрисовке звезд
    emit drawApex(ra_apex, dec_apex);

    //возбуждение сигнала отправки статуса
    emit drawStatus(ind.size(), ra_apex, dec_apex);

}

//реализация функции умножения матрицы на вектор
void Model::multiplyMatrixVec(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1], double var[SIZE_SYSTEM])
{
    for (int i = 0; i < SIZE_SYSTEM; ++i)
    {
        var[i] = 0.0;
        for (int j = 0; j < SIZE_SYSTEM; ++j)
        {
            var[i] += a[i][j] * a[j][SIZE_SYSTEM];
        }
    }

}

//реализации функции печати матрицы
void Model::printMatrix(double a[SIZE_SYSTEM][SIZE_SYSTEM + 1])
{
    for (int i = 0; i < SIZE_SYSTEM; ++i)
    {
        for (int j = 0; j < SIZE_SYSTEM + 1; ++j)
        {
            qDebug() << a[i][j] << " ";
            if (j == SIZE_SYSTEM - 1)
            {
                qDebug() << "| ";
            }
        }
    }

}


