#include "widget.h"
#include "model.h"

//#include <QObject>
//#include <QtWidgets>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>

//конструктор класса Widget
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    load = new QPushButton("Load catalogue");
    save_figure = new QPushButton("Save Image");
    save_figure->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    load->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(load);
    vbl->addWidget(save_figure);
    connect(load, SIGNAL(clicked()), SLOT(onLoad()));
    connect(save_figure, SIGNAL(clicked()), SLOT(onSaveImage()));

    dist = new QComboBox;
    sp = new QComboBox;
    mag = new QComboBox;

    qe_ra = new QLineEdit;
    qe_dec = new QLineEdit;

    dist->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    sp->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    mag->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    qe_ra->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    qe_dec->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);


    qe_ra->setReadOnly(true);
    qe_dec->setReadOnly(true);

    qe_ra->setMaxLength(8);
    qe_dec->setMaxLength(8);

    pb = new QProgressBar;


    for (int i = 0; i < DIST_N; ++i)
    {
        dist->addItem(DIST_SELECT[i]);
    }

    for (int i = 0; i < SP_N; ++i)
    {
        sp->addItem(SP_SELECT[i]);
    }

    for (int i = 0; i < MAG_N; ++i)
    {
        mag->addItem(MAG_SELECT[i]);
    }

    connect(dist, SIGNAL(currentIndexChanged(QString)), SLOT(onParameters()));
    connect(sp, SIGNAL(currentIndexChanged(QString)), SLOT(onParameters()));
    connect(mag, SIGNAL(currentIndexChanged(QString)), SLOT(onParameters()));


    plot = new QCustomPlot;
    QCursor cur(Qt::CrossCursor);
    plot->setCursor(cur);
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout *hbl = new QHBoxLayout;
    hbl->addWidget(plot);
    hbl->addLayout(vbl);
    setLayout(hbl);
    configurePlot();


    vbl->addWidget(new QLabel("Distance (in pc): "));
    vbl->addWidget(dist);
    vbl->addWidget(new QLabel("Spectral class: "));
    vbl->addWidget(sp);
    vbl->addWidget(new QLabel("Magnitude: "));
    vbl->addWidget(mag);
    vbl->addWidget(new QLabel(""));
    vbl->addWidget(new QLabel("Solar Apex"));


    vbl->addWidget(new QLabel("Right Accension (in hours):"));
    QHBoxLayout *subhbl_first = new QHBoxLayout;
    subhbl_first->addWidget(qe_ra);
    vbl->addLayout(subhbl_first);
    vbl->addWidget(new QLabel("Declination (in degrees):"));
    QHBoxLayout *subhbl_second = new QHBoxLayout;
    subhbl_second->addWidget(qe_dec);
    vbl->addLayout(subhbl_second);


    vbl->addStretch();
    setLayout(vbl);

    QPalette pall;
    pall.setColor(this->backgroundRole(), QColor(Qt::green).light());
    setPalette(pall);
    setAutoFillBackground(true);


}

//реализация слота о загрузке файла
void Widget::onLoad()
{
    QString fn = QFileDialog::getOpenFileName(this, "Open catalogue", DIRECTOTY_DEFAULT, "All Files(*.*);;");

    if(!fn.isEmpty())
    {
        pb->setValue(0);
        pb->show();
        //QCoreApplication::processEvents();
        dist->setCurrentIndex(0);
        sp->setCurrentIndex(0);
        mag->setCurrentIndex(0);
        emit loadFile(fn);
    }
}

//реализация слота о загрузке рисунка
void Widget::onSaveImage()
{
    QString fn = QFileDialog::getSaveFileName(this, "Save Image", DIRECTOTY_DEFAULT + "/image.jpg", "All Files(*.*);;");

    if(!fn.isEmpty())
    {
        plot->saveJpg(fn);
    }
}



//реализация слота об отрисовке звезд
void Widget::onDrawStars(QVector<QVector<double> > alphas, QVector<QVector<double> > deltas, QVector<quint32> colors)
{
    for (int i = 0; i < N_SP; ++i)
    {
        plot->graph(i)->setData(alphas[i], deltas[i]);
        plot->graph(i)->setPen(QPen(QColor(Qt::GlobalColor(colors[i]))));
        plot->graph(i)->setLineStyle(QCPGraph::lsNone);
        plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, STAR_DISK_RADIUS));
    }
    plot->replot();
}

//реализации функции изменения параметров графика
void Widget::configurePlot()
{
    QColor axis_color = Qt::green;
    for (int i = 0; i < N_SP + 1; ++i)
    {
        plot->addGraph();
    }
    plot->xAxis->setRange(0, 24);
    plot->yAxis->setRange(-90, 90);

    plot->xAxis->setTickLabelColor(axis_color);
    plot->yAxis->setTickLabelColor(axis_color);

    plot->xAxis->setLabel("Right accension");
    plot->yAxis->setLabel("Declination");

    plot->xAxis->setLabelColor(axis_color);
    plot->yAxis->setLabelColor(axis_color);

    plot->xAxis->setBasePen(QPen(axis_color, 1));
    plot->yAxis->setBasePen(QPen(axis_color, 1));

    plot->xAxis->setTickPen(QPen(axis_color, 1));
    plot->yAxis->setTickPen(QPen(axis_color, 1));


    plot->xAxis->setSubTickPen(QPen(axis_color, 1));
    plot->yAxis->setSubTickPen(QPen(axis_color, 1));

    plot->xAxis->grid()->setPen(QPen(axis_color, 1, Qt::DotLine));
    plot->yAxis->grid()->setPen(QPen(axis_color, 1, Qt::DotLine));

    plot->xAxis->grid()->setZeroLinePen(axis_color);
    plot->yAxis->grid()->setZeroLinePen(axis_color);

    QSharedPointer<QCPAxisTickerFixed> xfixedTicker(new QCPAxisTickerFixed);
    plot->xAxis->setTicker(xfixedTicker);
    xfixedTicker->setTickStep(3.0);
    QSharedPointer<QCPAxisTickerFixed> yfixedTicker(new QCPAxisTickerFixed);
    plot->yAxis->setTicker(yfixedTicker);
    yfixedTicker->setTickStep(30.0);

    plot->setBackground(Qt::black);
}

//реализация слота об изменениях параметров
void Widget::onParameters()
{
    emit changeParameters(dist->currentText(), sp->currentText(), mag->currentText());
}

//реализация слота об отрисовке апекса
void Widget::onDrawApex(double ra, double dec)
{
    ra *= 12 / M_PI;
    dec *= 180 / M_PI;
    qDebug() << "APEX CALCULATED!";
    QVector<double> r, d;
    r.append(ra); d.append(dec);
    qe_ra->setText(QString::number(ra));
    qe_dec->setText(QString::number(dec));
    plot->graph(N_SP)->setData(r, d);
    plot->graph(N_SP)->setPen(QPen(QColor(Qt::GlobalColor(SP_COLORS[N_SP - 1]))));
    plot->graph(N_SP)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusSquare, 6*STAR_DISK_RADIUS));
    plot->replot();

}

void Widget::onLoaded(int percent)
{
    qDebug() << "onloaded " << percent;
    pb->setValue(percent);
    //QCoreApplication::processEvents();
    if(percent == 100)
    {
        pb->hide();
    }
}
