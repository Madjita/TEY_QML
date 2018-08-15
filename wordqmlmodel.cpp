#include "wordqmlmodel.h"

#include <QDebug>

WordQMLModel::WordQMLModel():
    _countBar(0),
    _rows(0)
{

}

const double &WordQMLModel::countBar() const
{
    return _countBar;
}

const int &WordQMLModel::rows() const
{
    return _rows;
}

const QStringList &WordQMLModel::dataFind() const
{
    return _dataFind;
}

void WordQMLModel::changeWork(int rows)
{
    if(_countBar == 0.0)
    {
        _rows = rows;
        emit rowsChanged(_rows);
    }

    double row =  360.0/rows;

    _countBar += row;


    emit countBarChanged(_countBar);

    if(_countBar >= (row*rows)-row)
    {
        _countBar = 0;
        _rows = 0;
         emit countBarChanged(_countBar);
    }

   qDebug () << _countBar;
   qDebug () << row*rows;

}

void WordQMLModel::findData(int R, int C_Z, int XP_XS_XW_X, int BQ_G, int DD, int DA, int U, int L, int TV, int HL_VD, int VT)
{
   if(_dataFind.isEmpty())
   {
       _dataFind.append(QString::number(R));
       _dataFind.append(QString::number(C_Z));
       _dataFind.append(QString::number(XP_XS_XW_X));
       _dataFind.append(QString::number(BQ_G));
       _dataFind.append(QString::number(DD));
       _dataFind.append(QString::number(DA));
       _dataFind.append(QString::number(U));
       _dataFind.append(QString::number(L));
       _dataFind.append(QString::number(TV));
       _dataFind.append(QString::number(HL_VD));
       _dataFind.append(QString::number(VT));
   }
   else
   {
       _dataFind.replace(0,QString::number(R));
       _dataFind.replace(1,QString::number(C_Z));
       _dataFind.replace(2,QString::number(XP_XS_XW_X));
       _dataFind.replace(3,QString::number(BQ_G));
       _dataFind.replace(4,QString::number(DD));
       _dataFind.replace(5,QString::number(DA));
       _dataFind.replace(6,QString::number(U));
       _dataFind.replace(7,QString::number(L));
       _dataFind.replace(8,QString::number(TV));
       _dataFind.replace(9,QString::number(HL_VD));
       _dataFind.replace(10,QString::number(VT));
   }

   emit dataFindChanged(_dataFind);
}
