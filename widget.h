#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QObject>
#include <QProgressBar>
#include "constants.h"
#include "qcustomplot.h"

//класс Widget реализует графический интерфейс и взаимодействие с пользователем
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);


private:
    //создание кнопок
    QPushButton *load;
    QPushButton *save_figure;

    //создание полей для вывода
    QLineEdit *qe_ra, *qe_dec;

    //создание выпадающих списков
    QComboBox *dist, *sp, *mag;

    //создание главного изображения
    QCustomPlot *plot;


    //создание прогресс бара
    QProgressBar *pb;
    
signals:
    //сигнал о загрузке файла
    void loadFile(const QString &fn);

    //сигнал об изменении параметров
    void changeParameters(const QString &dst, const QString &spec, const QString &mg);

    
public slots:
    //слот о загрузке файла
    void onLoad();

    //слот о количестве загрузки
    void onLoaded(int percent);

    //слот о загрузке рисунка
    void onSaveImage();



    //слот об отрисовке звезд
    void onDrawStars(QVector<QVector<double> >alphas, QVector<QVector<double> >deltas,
                   QVector<quint32>colors);

   //слот об изменениях параметров
   void onParameters();

   //слот об отрисовке апекса
   void onDrawApex(double ra, double dec);

protected:
    //функция изменения параметров графика
    void configurePlot();
    
};

#endif // WIDGET_H
