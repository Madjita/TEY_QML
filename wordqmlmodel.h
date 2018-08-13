#ifndef WORDQMLMODEL_H
#define WORDQMLMODEL_H

#include <QObject>

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

signals:
    void countBarChanged(double countBar);
    void rowsChanged(int rows);

public slots:
    void changeWork(int rows);


private:
    double _countBar;
    int _rows;
};

#endif // WORDQMLMODEL_H
