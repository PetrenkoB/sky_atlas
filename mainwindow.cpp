#include <QMetaType>
#include "mainwindow.h"
#include "star.h"


//конструктор класса
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new Model(this);        //инициализация объекта класса Model
    widget = new Widget();          //инициализация объекта класса Widget
    setCentralWidget(widget);       //размещение объекта виджета в качестве центрального
    setWindowTitle("Solar Apex");   //установление названия

    proc = new QProcess();


//    prbr= new QProgressBar();
//    prbr->setPalette(QPalette(QColor((Qt::green))));
//    prbr->setVisible(false);
//    prbr->setRange(0, 100);prbr->setValue(0);
//    statusBar()->addWidget(prbr);
    statusBar()->showMessage("Hello!");



    //виджет возбуждает сигнал о необходимости загрузки файла и посылает его модели
    connect(widget, SIGNAL(loadFile(QString)), model, SLOT(readFromFile(QString)));

    //модель посылает виджету сигнал об отрисовке звезд
    qRegisterMetaType<QVector<QVector<double> > >("QVector<QVector<double> >");
    qRegisterMetaType<QVector<quint32> >("QVector<quint32>");
    connect(model, SIGNAL(drawStars(QVector<QVector<double> >,QVector<QVector<double> >,QVector<quint32>)), widget, SLOT(onDrawStars(QVector<QVector<double> >,QVector<QVector<double> >,QVector<quint32>)));

    //виджет посылает модели сигнал об изменении параметров выбора звезд
    connect(widget, SIGNAL(changeParameters(QString,QString,QString)), model, SLOT(selectStars(QString,QString,QString)));

    //модель посылает виджету сигнал об рисовании апекса
    connect(model, SIGNAL(drawApex(double,double)), widget, SLOT(onDrawApex(double,double)));

    connect(model, SIGNAL(drawStatus(unsigned long long,double,double)), SLOT(showApex(unsigned long long,double,double)));

    connect(model, SIGNAL(loaded(int)), widget, SLOT(onLoaded(int)));
    createMenu();


}

void MainWindow::showApex(unsigned long long n, double r, double d)
{
    QString s = "Number of filtered stars: " + QString::number(n) + " Apex: " + QString::number(r * 12. / M_PI) + ", " + QString::number(d * 180. / M_PI);
    statusBar()->showMessage(s);
}

void MainWindow::createMenu()
{
    QMenu *file = new QMenu("&File");
    file->addAction("&Load catalogue...", widget, SLOT(onLoad()), Qt::CTRL + Qt::Key_O);
    file->addAction("&Save as...", widget, SLOT(onSaveImage()), Qt::CTRL + Qt::Key_S);
    file->addSeparator();
    file->addAction("E&xit", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);
    menuBar()->addMenu(file);

    QMenu *tools = new QMenu("&Tools");
    tools->addAction("&Plot histogram", this, SLOT(onPlotHistogram()), Qt::CTRL + Qt::Key_P);
    menuBar()->addMenu(tools);

    QMenu *help = new QMenu("&Help");
    help->addAction("&Help", this, SLOT(onHelp()), Qt::Key_F1);
    help->addAction("&About Qt", qApp, SLOT(aboutQt()), Qt::CTRL + Qt::Key_F1);
    menuBar()->addMenu(help);
}

void MainWindow::onHelp()
{
    QMessageBox::warning(this, "Help", "No help available!");
}

void MainWindow::onPlotHistogram()
{
    QCustomPlot *histogram = new QCustomPlot;
    const QVector<double> &value = model->getSpHistogram();
    QCPBars *bars = new QCPBars(histogram->xAxis, histogram->yAxis);
    QVector<double> ticks;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
    bars->setData(ticks, value);
    //histogram->yAxis->
    histogram->yAxis->rescale();
    histogram->xAxis->setRange(0, 9);
    histogram->resize(500, 300);
    histogram->show();
}

//деструктор класса
MainWindow::~MainWindow()
{

}
