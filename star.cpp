#include "star.h"


//файл реализации методов класса Star

//реализация функции получения индетификатора звезды
unsigned long int Star::id() const
{
    return _id;
}

//реализация функции установления индетификатора звезды
void Star::setid(unsigned long int id)
{
    _id =  id;
}

//реализация функции получения прямого восхождения
double Star::RA() const
{
    return _RA;
}

//реализация функции установления прямого восхождения
void Star::setRA(double RA)
{
    _RA = RA;
}

//реализация функции получения склонения
double Star::dec() const
{
    return _dec;
}

//реализация функции установления склонения
void Star::setDec(double dec)
{
    _dec = dec;
}

//реализация функции получения собственного движения по координате прямого восхождения
double Star::mRA() const
{
    return _mRA;
}

//реализация функции установления собственного движения по координате прямого восхождения
void Star::setmRA(double mRA)
{
    _mRA = mRA;
}

//реализация функции получения собственного движения по координате склонения
double Star::mdec() const
{
    return _mdec;
}

//реализация функции установления собственного движения по координате склонения
void Star::setmdec(double mdec)
{
    _mdec = mdec;
}

//реализация функции получения видимой звездной величины
double Star::magV() const
{
    return _magV;
}

//реализация функции установления видимой звездной величины
void Star::setmagV(double magV)
{
    _magV = magV;
}

//реализация функции получения показателя цвета B-V
double Star::BV() const
{
    return _BV;
}

//реализация функции установления показателя цвета B-V
void Star::setBV(double BV)
{
    _BV = BV;
}

//реализация функции получения расстояния
double Star::dist() const
{
    return _dist;
}

//реализация функции установления расстояния
void Star::setdist(double dist)
{
    _dist = dist;
}

//реализация функции спектрального класса
QString Star::getSpectralClass() const
{
    return _spClass;
}

//реализация функции установления спектрального класса
void Star::setSpectralClass(const QString &sp)
{
    _spClass = sp;
}


//реализация функции чтения из файла
bool Star::readFromFile(QFile &file)
{
    QString line = file.readLine();
    if (line.isEmpty())
    {
        qDebug() << "Error: unable to read from file!";
        return false;
    }
    QStringList list = line.split("|");
    QString temp;

    //чтение из файла индетификатора
    temp = list[1].trimmed();
    if(!temp.isEmpty())
        setid(temp.toULong());
    else
        setid(BAD_VALUE);
    temp.clear();

    //чтение из файла звездной величины
    temp = list[5].trimmed();
    if(!temp.isEmpty())
        setmagV(temp.toDouble());
    else
        setmagV(BAD_VALUE);
    temp.clear();

    //чтение из файла показателя цвета
    temp = list[37].trimmed();
    if(!temp.isEmpty())
        setBV(temp.toDouble());
    else
        setBV(BAD_VALUE);
    temp.clear();

    //чтение из файла параллакса и преобразование в расстояние
    temp = list[11].trimmed();
    if(!temp.isEmpty())
        setdist(1000. / (temp.toDouble()));
    else
        setdist(BAD_VALUE);
    temp.clear();

    //чтение из файла прямого восхождения и преобразование в радианы
    temp = list[3].trimmed();
    if(!temp.isEmpty())
    {
        QStringList templist = temp.split(" ");
        double opp = 15. * templist[0].toDouble() +
                1. / 4. * templist[1].toDouble() +
                15./3600. * templist[2].toDouble();
        setRA(convertFromGradToRadians(opp));
    }
    else
        setRA(BAD_VALUE);
    temp.clear();

    //чтение из файла склонения и преобразование в радианы
    temp = list[4].trimmed();
    if(!temp.isEmpty())
    {
        QStringList templist = temp.split(" ");
        double opp = fabs(templist[0].toDouble()) +
                1. / 60. * templist[1].toDouble() +
                1./ 3600. * templist[2].toDouble();
        if (templist[0].startsWith("-"))
            opp = -opp;
        setDec(convertFromGradToRadians(opp));
    }
    else
        setDec(BAD_VALUE);
    temp.clear();

    //чтение из файла собственного движения по прямому восхождению
    temp = list[12].trimmed();
    if(!temp.isEmpty())
        setmRA(convertFromGradToRadians(1. / 3600. * 1000. * temp.toDouble()));
    else
        setmRA(BAD_VALUE);
    temp.clear();

    //чтение из файла собственного движения по склонению
    temp = list[13].trimmed();
    if(!temp.isEmpty())
    {
        setmdec(convertFromGradToRadians(1. / 3600. * 1000. * temp.toDouble()));
    }
    else
        setmdec(BAD_VALUE);
    temp.clear();

    //чтение из файла спектрального класса
    temp = list[76].trimmed();
    if(!temp.isEmpty())
        setSpectralClass(temp);
    else
        setSpectralClass(BAD_VALUE_STR);
    temp.clear();


    return true;

}



//реализация функции вывода информации
void Star::printInfo()
{

    qDebug() << "#---------------------------------#";
    qDebug() << "STAR INFORMATION";
    qDebug() << "ID:" << id();
    qDebug() << "RIGHT ACCENSION:" << RA();
    qDebug() << "DECLINATION:" << dec();
    qDebug() << "MOTION IN RIGHT ACCENSION:" << mRA();
    qDebug() << "MOTION IN DECLINATION:" << mdec();
    qDebug() << "MAGNITUDE:" << magV();
    qDebug() << "COLOR INDEX B-V:" << BV();
    qDebug() << "DISTANCE:" << dist();
    qDebug() << "SPECTRAL CLASS:" << getSpectralClass();
    qDebug() << "#---------------------------------#";
}

//реализация конструктора класса по умолчанию
Star::Star()
{
    setid(0);
    setRA(0.0);
    setDec(0.0);
    setmRA(0.0);
    setmdec(0.0);
    setdist(0.0);
    setmagV(0.0);
    setBV(0.0);
    setSpectralClass(BAD_VALUE_STR);
}

//реализация конструктора класса с аргументом объекта файла
Star::Star(QFile &nm)
{
    bool ok = readFromFile(nm);
    if(!ok)
    {
        setid(int(BAD_VALUE));
        setRA(BAD_VALUE);
        setDec(BAD_VALUE);
        setmRA(BAD_VALUE);
        setmdec(BAD_VALUE);
        setdist(BAD_VALUE);
        setmagV(BAD_VALUE);
        setBV(BAD_VALUE);
        setSpectralClass(BAD_VALUE_STR);
    }
}


//реализация функции преобразования арксекунд в радианы
double convertFromGradToRadians(double grad)
{
    return grad / 180.0 * M_PI;
}

int Star::spectralClassNumber() const
{
    if (BV() == BAD_VALUE) return  SP_NUMBERS[7];
    if (BV() < SP_BV[1]) return SP_NUMBERS[0];
    if (BV() < SP_BV[2]) return  SP_NUMBERS[1];
    if (BV() < SP_BV[3]) return  SP_NUMBERS[2];
    if (BV() < SP_BV[4]) return  SP_NUMBERS[3];
    if (BV() < SP_BV[5]) return  SP_NUMBERS[4];
    if (BV() < SP_BV[6]) return  SP_NUMBERS[5];
    if (BV() >= SP_BV[6]) return  SP_NUMBERS[6];
}
