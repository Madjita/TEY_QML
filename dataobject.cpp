#include "dataobject.h"
#include <QDebug>

DataObject::DataObject(QString __name, QString __count, QString __percent, QObject *parent) : QObject(parent),
  countLoadingFileBar(0),
  countLoadingPercent(0),
  maxWorking(0),
  _count(__count),
  _percent(__percent)

{
    setMyName(__name);
    setMyCountMax(_count.toInt());

}

QString DataObject::myName()
{
    return _name;
}

QString DataObject::myCount()
{
    return  _count;
}

QString DataObject::myPercent()
{
    return _percent;
}

QString DataObject::myPercentBar()
{
    return _percentBar;
}

double DataObject::myCountMax()
{
    return _countMax;
}

void DataObject::setMyName(QString myName)
{
    if(myName != _name)
    {
        _name = myName;
        emit myNameChanged(_name);
    }
}

void DataObject::setMyCount(QString myCount)
{
    if(myCount != _count)
    {
        _count = myCount;
        emit myCountChanged(_count);
    }
}

void DataObject::setMyPercent(QString myPercent)
{

    countLoadingPercent += 100/maxWorking;
    myPercent = QString::number(countLoadingPercent,'f',2);//round(countLoadingPercent)

    setMyPercentBar(myPercent);

    if(myPercent != _percent)
    {
        _percent = myPercent;
        emit myPercentChanged(_percent);
    }

}

void DataObject::setMyPercentBar(QString myPercentBar)
{
    double row =  360.0/maxWorking; //шаг
    countLoadingFileBar += row;
    myPercentBar = QString::number(countLoadingFileBar,'f',2); //round()

    qDebug() << _name << "\t " << maxWorking;

    if(_name == "DD")
    {
        qDebug () << "LOL";
    }

    if(myPercentBar != _percentBar)
    {
        _percentBar = myPercentBar;
        emit myPercentBarChanged(_percentBar);
    }

}

void DataObject::setMyCountMax(double count)
{

    if(_name == "DD" || _name == "DA")
    {
        if((_count.toInt()%2) > 0 )
        {
           maxWorking = ((_count.toInt()/2))+_count.toInt();
        }
        else
        {
          maxWorking = ((_count.toInt()/2)-1)+_count.toInt();
        }
    }
    else
    {
        if((_count.toInt()%3) > 0 )
        {
           maxWorking = ((_count.toInt()/3))+_count.toInt();
        }
        else
        {
          maxWorking = ((_count.toInt()/3)-1)+_count.toInt();
        }
    }

    if(maxWorking != _countMax)
    {
        _countMax = maxWorking;
        emit myCountMaxChanged(_countMax);
    }
}
