#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT
public:
    explicit DataObject(QString __name, QString __count ="0", QString __percent = "0", QObject *parent = nullptr);

    Q_PROPERTY(QString myName READ myName WRITE setMyName NOTIFY myNameChanged)
    Q_PROPERTY(QString myCount READ myCount WRITE setMyCount NOTIFY myCountChanged)
    Q_PROPERTY(QString myPercent READ myPercent WRITE setMyPercent NOTIFY myPercentChanged)
    Q_PROPERTY(QString myPercentBar READ myPercentBar WRITE setMyPercentBar  NOTIFY myPercentBarChanged)
    Q_PROPERTY(double myCountMax READ myCountMax WRITE setMyCountMax NOTIFY myCountMaxChanged)

    QString myName();
    QString myCount();
    QString myPercent();
    QString myPercentBar();
    double myCountMax();

    double countLoadingFileBar;
    double countLoadingPercent;
    double maxWorking;

signals:
    void myNameChanged(QString);
    void myCountChanged(QString);
    void myPercentChanged(QString);
    void myPercentBarChanged(QString);
    void myCountMaxChanged(int myCountMax);

public slots:
    void setMyName(QString myName);
    void setMyCount(QString myCount);
    void setMyPercent(QString myPercent);
    void setMyPercentBar(QString myPercentBar);
    void setMyCountMax(double count);


private:
    QString _name;
    QString _count;
    double _countMax;
    QString _percent;
    QString _percentBar;

};

#endif // DATAOBJECT_H
