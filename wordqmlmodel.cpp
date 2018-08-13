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

void WordQMLModel::changeWork(int rows)
{
    if(_countBar == 0.0)
    {
        _rows = rows;
        emit rowsChanged(_rows);
    }

    double row =  360.0/rows;

    _countBar += row;

    if(_countBar >= 359)
    {
        _countBar = 0;
        _rows = 0;
    }

//    qDebug () << _countBar;
//    qDebug () << row;

    emit countBarChanged(_countBar);
}
