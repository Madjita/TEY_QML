#ifndef WORDQMLMODEL_H
#define WORDQMLMODEL_H

#include <QObject>
#include <dataobject.h>

class WordQMLModel : public QObject
{
    Q_OBJECT

public:
    WordQMLModel();


    //countBar
    Q_PROPERTY(double countBar READ countBar NOTIFY countBarChanged)
    const double & countBar() const;

    //rows
    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
    const int & rows() const;

    //rows
    Q_PROPERTY(QStringList dataFind READ dataFind NOTIFY dataFindChanged)
    const QStringList & dataFind() const;


    Q_PROPERTY(QList<QObject*> dataList READ dataList NOTIFY dataListChanged)

    const QList<QObject*> dataList() const;


signals:
    void countBarChanged(double countBar);
    void rowsChanged(int rows);
    void dataFindChanged(QStringList dataFind);
    void dataListChanged(QList<QObject*>);

    void updateR(QString R);
    void updateC_Z(QString C_Z);
    void updateXP_XS_XW_X(QString XP_XS_XW_X);
    void updateBQ_G(QString);
    void updateDD(QString);
    void updateDA(QString);
    void updateU(QString);
    void updateL(QString);
    void updateTV(QString);
    void updateHL_VD(QString);
    void updateVT(QString);

public slots:
    void changeWork(int rows);
    void findData(int R ,int C_Z,int XP_XS_XW_X,int BQ_G,int DD,int DA,int U,int L,int TV,int HL_VD,int VT);


private:
    double _countBar;
    int _rows;
    QStringList _dataFind;
    QList<QObject*> _dataList;
};

#endif // WORDQMLMODEL_H
