#ifndef STAR_H
#define STAR_H

#include <QtCore>
#include <QDebug>
#include <cmath>
#include <algorithm>
#include <constants.h>

//загаловочный файл

//создание класса для описания объекта звезды
class Star
{
public:
    //открытые методы

    unsigned long int id() const;               //функция получения индетификатора звезды
    void setid(unsigned long int id);           //функция установления индетификатора звезды

    double RA() const;                          //функция получения прямого восхождения
    void setRA(double RA);                      //функция установления прямого восхождения

    double dec() const;                         //функция получения склонения
    void setDec(double dec);                    //функция установления склонения

    double mRA() const;                         //функция получения собственного движения по координате прямого восхождения
    void setmRA(double mRA);                    //функция установления собственного движения по координате прямого восхождения

    double mdec() const;                        //функция получения собственного движения по координате склонения
    void setmdec(double mdec);                  //функция установления собственного движения по координате склонения

    double magV() const;                        //функция получения видимой звездной величины
    void setmagV(double magV);                  //функция установления видимой звездной величины

    double BV() const;                          //функция получения показателя цвета B-V
    void setBV(double BV);                      //функция установления показателя цвета B-V

    double dist() const;                        //функция получения расстояния
    void setdist(double dist);                  //функция установления расстояния

    QString getSpectralClass() const;           //функция получения спектрального класса
    void setSpectralClass(const QString &sp);   //функция установления спектрального класса

    bool readFromFile(QFile &);                 //функция чтения из файла
    Star();                                     //конструктор класса по умолчанию
    Star(QFile &nm);                            //конструктор класса с аргументом объекта файла

    void printInfo();                           //функция печати информации о звезде

    int spectralClassNumber()const;             //функция сопоставления показателя цвета и спектрального класса

private:
    //закрытые методы и поля класса

    unsigned long int _id;                      //Индентификатор звезды
    double _RA, _dec;                           //Координаты звезды
    double _mRA, _mdec;                         //Собственные движения по координатам
    double _magV, _BV;                          //Фотометрические величины
    double _dist;                               //Расстояние
    QString _spClass;                           //Спектральный класс
};

double convertFromGradToRadians(double grad);   //функция преобразования градусы в радианы

#endif // STAR_H
