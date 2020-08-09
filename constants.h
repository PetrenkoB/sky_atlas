#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QtCore>

const int BAD_VALUE = -999;                         //константа заполнения отсутствующих значений
const unsigned long long numberOfStars = 120000;    //число звезд, читаемых из файла каталога

const int STAR_DRAW = 10000;                        //максимальное количество звезд для отрисовки
const int STAR_DISK_RADIUS = 3;                     //радиус звезд на рисунке
const int SIZE_SYSTEM = 3;                          //размерность системы линейных уравнений
const int N_SP = 8;                                 //количество цветов для отрисовки

const int DIST_N = 5;                               //количество критериев селекции по расстоянию
const int SP_N = 8;                                 //количество критериев селекции по спектральному классу
const int MAG_N = 4;                                //количество критериев селекции по визуальной видимой величине

const QString ALL = "All";                                                                                                  //универсальная строка для критерия по умолчанию
const QString DIST_SELECT[] = {ALL, "<10", "10-50", "50-100",">100"};                                                       //строки критериев селекции по расстоянию
const QString SP_SELECT[] = {ALL, "O", "B", "A", "F", "G", "K", "M"};                                                       //строки критериев селекции по спектральному классу
const QString MAG_SELECT[] = {ALL, "<5", "5-10", ">10"};                                                                    //строки критериев селекции по звездной величине
const quint32 SP_COLORS[] = {Qt::blue, Qt::cyan, Qt::white, Qt::yellow, Qt::darkYellow, Qt::red, Qt::darkRed, Qt::green};   //цвета отрисовки
const float SP_BV[] = {-0.33, -0.30, -0.02, 0.30, 0.58, 0.81, 1.40};                                                        //разграничения по спектральным классам по значению B-V
const int SP_NUMBERS[] = {0, 1, 2, 3, 4, 5, 6, 7};                                                                          //нумерация по спектральным классам

//const QString DIRECTOTY_DEFAULT = "";
//const QString DIRECTOTY_DEFAULT = "E:/MyC++/MyQt/catalogue";
const QString DIRECTOTY_DEFAULT = "/Students/astro6/catalogue";

const QString BAD_VALUE_STR = "";

#endif // CONSTANTS_H



