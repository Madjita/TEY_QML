#include "word.h"

#include <QtDebug>

#include <QThread>
#include <QtCore/qmath.h>

//MYWORD::MYWORD(QString _FileDir, QString _FileDir_S_R,QString _FileDir_XP_XS_XW_X,QString _FileDir_C_Z,QString _FileDir_BQ,QString _FileDir_DA,QString _FileDir_U,QString _FileDir_L,QString _FileDir_DD,QString _FileDir_TV,QString _FileNames_HL_VD,QString _FileNames_VT,QObject *parent) : QObject(parent),
//    FileDir(_FileDir),
//    FileDir_S_R(_FileDir_S_R),
//    FileDir_XP_XS_XW_X(_FileDir_XP_XS_XW_X),
//    FileDir_C_Z(_FileDir_C_Z),
//    FileDir_BQ(_FileDir_BQ),
//    FileDir_DA(_FileDir_DA),
//    FileDir_DD(_FileDir_DD),
//    FileDir_U(_FileDir_U),
//    FileDir_L(_FileDir_L),
//    FileDir_TV(_FileDir_TV),
//    FileDir_HL_VD(_FileNames_HL_VD),
//    FileDir_VT(_FileNames_VT),




MYWORD::MYWORD(QObject *parent):
    QObject(parent),
    FileDir(""),
    temp("150"),
    stateViewWord(false)
{

    saveDir = QDir::currentPath();

    connect(this, &MYWORD::qml_StartFind,this,&MYWORD::Work,Qt::QueuedConnection);
    connect(this, &MYWORD::qml_CreateShablon,this,&MYWORD::creatShablon,Qt::QueuedConnection);



    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/RShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/XPXSXWShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/CZShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/BQGShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/DAShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/DDShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/UShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/LShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/TVShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/VTShablon.docx");
    listMYWORD << QDir::currentPath()+QString("/Shablon")+QString("/HLVDShablon.docx");


    this->moveToThread(new QThread());
    connect(this->thread(),&QThread::started,this,&MYWORD::process_start);
    this->thread()->start();


}

MYWORD::~MYWORD()
{
    this->thread()->wait();
    delete this;
}

void MYWORD::setBD(BData *_data)
{
    bd = _data;

    QSqlQueryModel* model =  bd->getInquiry("SELECT *"
                                            " FROM R_GRM");

    c_grm_codePower.clear();
    c_grm_codeTemperatureRange.clear();
    c_grm_power.clear();
    c_grm_TemperatureRange.clear();

    for (int i = 0; i < model->rowCount(); ++i)
    {
        if(model->record(i).value("Power").toString() != "")
        {
            c_grm_codePower << model->record(i).value("Code").toString();
            c_grm_power << model->record(i).value("Power").toString();
        }
        else
        {
            c_grm_codeTemperatureRange << model->record(i).value("Code").toString();
            c_grm_TemperatureRange << model->record(i).value("TemperatureRange").toString();
        }
    }
    /*qDebug() << r_grm_codePower;
    qDebug() << r_grm_codeTemperatureRange;
    qDebug() << r_grm_power;
    qDebug() << r_grm_TemperatureRange;
    */

    model =  bd->getInquiry("SELECT *"
                            " FROM C_CR");

    r_cr_code.clear();
    r_cr_power.clear();
    r_cr_TemperatureRange.clear();
    r_cr_Void.clear();

    for (int i = 0; i < model->rowCount(); ++i)
    {
        r_cr_code << model->record(i).value("Code").toString();
        r_cr_power << model->record(i).value("Power").toString();
        r_cr_TemperatureRange << model->record(i).value("TemperatureRange").toString();
        r_cr_Void << model->record(i).value("Void").toString();
    }

    model =  bd->getInquiry("SELECT *"
                            " FROM Z_NFM");

    z_nfm_code.clear();
    z_nfm_power.clear();


    for (int i = 0; i < model->rowCount(); ++i)
    {
        z_nfm_code << model->record(i).value("Code").toString();
        z_nfm_power << model->record(i).value("Power").toString();
    }

    model =  bd->getInquiry("SELECT *"
                            " FROM C_AVX");

    c_avx_codePower.clear();
    c_avx_power.clear();
    c_avx_TemperatureRange.clear();

    for (int i = 0; i < model->rowCount(); ++i)
    {
        c_avx_codePower << model->record(i).value("Code").toString();
        c_avx_power << model->record(i).value("Power").toString();
        c_avx_TemperatureRange << model->record(i).value("TemperatureRange").toString();
    }

    delete model;

}

void MYWORD::process_start()
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
}

void MYWORD::setTemp(QString R)
{
    temp = R;
}

QString MYWORD::getTemp()
{
    return temp; //QString::number(temp);
}

void MYWORD::SetDirFindMSWord(QString data)
{
    FileDir_FindMSWord = data;
}


void MYWORD::Work()
{
    // OpenWord();

    // CoInitialize(0);

    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    OpenWord_Perechen();
}

void MYWORD::setViewFlag(int flag)
{
    switch (flag) {
        case 0: stateViewWord = false;break;
        case 2: stateViewWord = true;break;
    }

}

int MYWORD::getViewFlag()
{
    if(stateViewWord)
    {
        return 2;
    }

    return 0;
}

QVariant MYWORD::qml_getlistMYWORD()
{

    return  QVariant::fromValue(listMYWORD);
}

QVariant MYWORD::qml_setChangeListMYWORD(QString index, QString shablonName)
{
    QString shbalonNameFind = shablonName.split('/').last().split('.').first() ;
    QString shablonNameState = listMYWORD.value(index.toInt()).split('/').last().split('.').first();

    shablonName.remove(0,8);

    if(shbalonNameFind == shablonNameState)
    {
        listMYWORD.replace(index.toInt(),shablonName);
    }

    return  QVariant::fromValue(listMYWORD);
}



void MYWORD::qml_getFileName(QString str)
{
    FileDir = str;

}



void MYWORD::OpenWord()
{
    QAxObject* WordApplication = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    // WordApplication->setProperty("Visible", 1);

    QAxObject* WordDocuments = WordApplication->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments->querySubObject( "Open(%T)",FileDir); //D:\\11111\\One.docx

    connect(
                WordApplication,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments->querySubObject("Add(QVariant)", FileDir);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication->dynamicCall("Quit (void)");
        delete WordApplication;
        return;
    }


    QAxObject* ActiveDocument = WordApplication->querySubObject("ActiveDocument()");



    QAxObject *selection2 = WordApplication->querySubObject("Selection()");


    QAxObject* Tables = selection2->querySubObject("Tables(1)");



    QAxObject* StartCell  = Tables->querySubObject("Cell(Row, Column)", 6, 2); // (ячейка C1)
    QAxObject* CellRange = StartCell->querySubObject("Range()");



    //CellRange->dynamicCall("InsertAfter(Text)", "НУ");


    //    StartCell = Tables->querySubObject("Cell(Row, Column)", 8, 3);

    //    CellRange = StartCell->querySubObject("Range()");



    //    auto lol =  CellRange->property("Text");

    //    qDebug () << lol.toString();

    auto columns = Tables->querySubObject("Columns")->property("Count").toInt();

    auto rows = Tables->querySubObject("Rows")->property("Count").toInt();

    qDebug () << "Колонки = " << columns;

    qDebug () <<"Строки = " << rows;


    //////////////////////////////////////////////////////////////////////////////
    int count_find = 0;

    for(int i=1; i <  rows;i++)
    {
        for(int j=1; j < columns; j++)
        {

            StartCell = Tables->querySubObject("Cell(Row, Column)", i, j);

            CellRange = StartCell->querySubObject("Range()");

            QString text =  CellRange->property("Text").toString();

            if((text[0] == "R") && (j == 2))
            {
                count_find++;

            }
        }
    }

    qDebug () << QString::number(count_find);

    ///////////////////////////////////////////////////////////////////////////////


    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    // WordApplication_2->setProperty("Visible", 1);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

  //  WordDocuments_2->querySubObject( "Open(%T)",FileDir_S_R); //D:\\11111\\One.docx


    connect(
                WordDocuments_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument2 = WordDocuments_2->querySubObject("Add(QVariant)", FileDir_S_R);

    if(newDocument2 == nullptr)
    {
        qDebug() << "ERROR";
        WordDocuments_2->dynamicCall("Quit (void)");
        delete WordDocuments_2;
        return;
    }



    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");



    // ActiveDocument_2->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");







    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");




    qDebug() <<"count_find/3 = " << QString::number(count_find/3);



    for(int i=0; i < (count_find/3);i++)
    {

        selection_2->dynamicCall("EndKey(wdStory)");
        selection_2->dynamicCall("InsertBreak()");
        selection_2->dynamicCall("Paste()");
    }



    //    QAxObject* Tables_2 = ActiveDocument_2->querySubObject("Tables(1)");



    //    QAxObject* StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 2); // (ячейка C1)
    //    QAxObject* CellRange_2 = StartCell_2->querySubObject("Range()");

    //    QAxObject* StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 2); // (ячейка C1)
    //    QAxObject* CellRange_2_3 = StartCell_2_3->querySubObject("Range()");




    /////////////////////////////////////////////////////


    QAxObject* Tables_2,*StartCell_2,*CellRange_2,*StartCell_2_3,*CellRange_2_3;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=1; i <  rows;i++)
    {
        for(int j=1; j < columns; j++)
        {

            StartCell = Tables->querySubObject("Cell(Row, Column)", i, j);

            CellRange = StartCell->querySubObject("Range()");

            QString text =  CellRange->property("Text").toString();

            if((text[0] == "R") && (j == 2))
            {

                flag++;

                StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
                CellRange_2 = StartCell_2->querySubObject("Range()");

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2->dynamicCall("InsertAfter(Text)", text);

                StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);

                CellRange = StartCell->querySubObject("Range()");

                text =  CellRange->property("Text").toString();

                CellRange_2_3->dynamicCall("InsertAfter(Text)", text);



                if(flag == 3)
                {
                    flag =0;

                    k++;
                    if(k > (count_find/3)+1 )
                    {

                        qDebug () << "Конец ; K = " << k;
                        break;
                    }
                    else
                    {
                        Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));

                        qDebug () << "K = " << k;
                    }

                }

            }
        }
    }






    //Сохранить pdf
  //  ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//Good" ,"17");//fileName.split('.').first()

    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT");//"D://11111//1//Good");
    //ActiveDocument_2->dynamicCall("Close (boolean)", false);
    ActiveDocument->dynamicCall("Close (boolean)", false);



    WordApplication->dynamicCall("Quit (void)");

    WordApplication_2->dynamicCall("Quit (void)");
}

void MYWORD::OpenWord_Perechen()
{

    Part("Открытие документа : " + FileDir);

    WordApplication = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    Part("[Load] Открытие документа : " + FileDir);

    //  WordApplication->setProperty("Visible", 1); //Показать (Открыть) окно MSWord с документом

    WordDocuments = WordApplication->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

    Part("[Documents()] Открытие документа : " + FileDir);

    WordDocuments->querySubObject( "Open(%T)",FileDir); //D:\\11111\\One.docx

    Part("[OK] Открытие документа : " + FileDir);

    ActiveDocument = WordApplication->querySubObject("ActiveDocument()"); // Сделать документ активным



    selection2 = WordApplication->querySubObject("Selection()");  // Создать класс Области страницы


    Tables = selection2->querySubObject("Tables(1)"); // Выбираем 1 таблицу в документе


    StartCell  = Tables->querySubObject("Cell(Row, Column)", 6, 2); // (ячейка C1)

    CellRange = StartCell->querySubObject("Range()"); // Область выбранной ячейки

    columns = Tables->querySubObject("Columns")->property("Count").toInt();

    rows = Tables->querySubObject("Rows")->property("Count").toInt();

    qDebug () << "Колонки = " << columns;

    qDebug () <<"Строки = " << rows;


    Part("Открыт : " + FileDir + " Количество Колонок: " + QString::number(columns) + " Строк: " +  QString::number(rows));


    Findelements_Perechen();

}

////////////////////////////////////////////////////////////////

void MYWORD::Findelements_Perechen()
{

    R.clear();      //отчистка резисторы
    RName.clear();  //отчистка имя резисторов


    C_Z.clear();    //отчистка конденсаторы и фильтры
    C_ZName.clear();  //отчистка имя конденсаторов

    XP_XS_XW_X.clear();  //отчистка Вилка
    XP_XS_XW_XName.clear(); //отчистка ИмяВилки

    DA.clear();
    DAName.clear();

    DD.clear();
    DDName.clear();

    BQ_G.clear();
    BQ_GName.clear();

    L.clear();
    LName.clear();

    TV.clear();
    TVName.clear();

    HL_VD.clear();
    HL_VDName.clear();

    VT.clear();
    VTName.clear();


    int count_find = 0;

    QString text;

    emit changeWork(rows);


    Part("Ищем Элементы... Колонок: " + QString::number(columns) + " Строк: " +  QString::number(rows));


    for(int i=1; i <  rows;i++)
    {
        emit changeWork(rows);

        for(int j=1; j < columns; j++)
        {

            StartCell = Tables->querySubObject("Cell(Row, Column)", i, j);
            CellRange = StartCell->querySubObject("Range()");
            text =  CellRange->property("Text").toString();


            int countStart = 0;
            int countCount = 0;

            QString str = "";
            QString countStartString = "";

            for(int k=0; k < text.count();k++)
            {
                if(text[k] == '-')
                {
                    str +=  text[0];

                   if(str == 'R' || str == 'C' || str == 'Z' || (str == 'X' && (text[1] != 'P' && text[1] !='S' && text[1] !='W')))
                   {
                        for(int l=1;l < k;l++)
                        {
                            countStartString += text[l];
                        }

                        countStart = countStartString.toInt();

                        StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+2);
                        CellRange = StartCell->querySubObject("Range()");
                        text =  CellRange->property("Text").toString();

                        countCount = text.toInt();

                   }
                   else
                   {
                        str +=  text[1];

                        for(int l=2;l < k;l++)
                        {
                            countStartString += text[l];
                        }

                        countStart = countStartString.toInt();

                        StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+2);
                        CellRange = StartCell->querySubObject("Range()");
                        text =  CellRange->property("Text").toString();

                        text.remove(text.count()-2,2);

                        countCount = text.toInt();

                   }

                   break;
                }
            }

            StartCell = Tables->querySubObject("Cell(Row, Column)", i, j);
            CellRange = StartCell->querySubObject("Range()");
            text =  CellRange->property("Text").toString();



            //Ищем R (резисторы)
            if((text[0] == "R") && (j == 2))
            {

                if(str == "R")
                {
                    for(int col = countStart; col <= (countStart+countCount);col++)
                    {
                         count_find++;

                         R.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             R.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 RName.append(text);
                             }
                             else
                             {
                                 RName.append(text);
                             }
                         }


                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    count_find++;
                    R.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        R.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            RName.append(text);
                        }
                        else
                        {
                            RName.append(text);
                        }
                    }
                }

                break;

            }

            //Ищем C (конденсаторы)
            if((text[0] == "C") && (j == 2)) //С
            {

                if(str[0] == "C")
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         C_Z.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             C_Z.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 C_ZName.append(text);
                             }
                             else
                             {
                                 C_ZName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    C_Z.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        C_Z.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            C_ZName.append(text);
                        }
                        else
                        {
                            C_ZName.append(text);
                        }
                    }
                }


                break;
            }

            //Ищем Z (фильтры)
            if((text[0] == "Z") && (j == 2))
            {

                if(str[0] == "Z")
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         C_Z.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             C_Z.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 C_ZName.append(text);
                             }
                             else
                             {
                                 C_ZName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {

                    C_Z.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        C_Z.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            C_ZName.append(text);
                        }
                        else
                        {
                            C_ZName.append(text);
                        }
                    }
                }


                break;
            }


            //Ищем XP (вилка)
            if(((text[0] == "X") && (text[1] == "P")) && (j == 2))
            {

                if(((str[0] == "X") && (str[1] == "P")))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         XP_XS_XW_X.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             XP_XS_XW_X.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 XP_XS_XW_XName.append(text);
                             }
                             else
                             {
                                 XP_XS_XW_XName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {

                    XP_XS_XW_X.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        XP_XS_XW_X.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            XP_XS_XW_XName.append(text);
                        }
                        else
                        {
                            XP_XS_XW_XName.append(text);
                        }
                    }
                }


                break;
            }

            //Ищем XS (Розетка)
            if(((text[0] == "X") && (text[1] == "S")) && (j == 2))
            {

                if(((str[0] == "X") && (str[1] == "S")))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         XP_XS_XW_X.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             XP_XS_XW_X.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 XP_XS_XW_XName.append(text);
                             }
                             else
                             {
                                 XP_XS_XW_XName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    XP_XS_XW_X.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        XP_XS_XW_X.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            XP_XS_XW_XName.append(text);
                        }
                        else
                        {
                            XP_XS_XW_XName.append(text);
                        }
                    }
                }


                break;
            }

            //Ищем XW (Вилка)
            if(((text[0] == "X") && (text[1] == "W")) && (j == 2))
            {

                if(((str[0] == "X") && (str[1] == "W")))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         XP_XS_XW_X.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             XP_XS_XW_X.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 XP_XS_XW_XName.append(text);
                             }
                             else
                             {
                                 XP_XS_XW_XName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {

                    XP_XS_XW_X.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        XP_XS_XW_X.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            XP_XS_XW_XName.append(text);
                        }
                        else
                        {
                            XP_XS_XW_XName.append(text);
                        }
                    }
                }

                break;
            }

            //Ищем X (вилка)
            if((text[0] == "X") && (j == 2))
            {

                if(str[0] == "X")
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         XP_XS_XW_X.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             XP_XS_XW_X.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                                 CellRange = StartCell->querySubObject("Range()");

                                 text+=CellRange->property("Text").toString();

                                 XP_XS_XW_XName.append(text);
                             }
                             else
                             {
                                 XP_XS_XW_XName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    XP_XS_XW_X.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                        XP_XS_XW_X.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            XP_XS_XW_XName.append(text);
                        }
                        else
                        {
                            XP_XS_XW_XName.append(text);

                        }
                    }
                }

                break;
            }


            //Ищем BQ (Резонатор)
            if(((text[0] == "B") && (text[1] == "Q")) && (j == 2))
            {
                if(((str[0] == "B") && (str[1] == "Q")))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         BQ_G.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             BQ_G.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 BQ_GName.append(text);
                             }
                             else
                             {
                                 BQ_GName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {

                    BQ_G.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    qDebug () << text;

                    if(text == "Отсутствует\r\u0007")
                    {
                        BQ_G.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            BQ_GName.append(text);
                        }
                        else
                        {
                            BQ_GName.append(text);
                        }
                    }
                }

                break;
            }


            //Ищем G
            if((text[0] == "G") && (j == 2))
            {
                if(str[0] == "G")
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         BQ_G.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             BQ_G.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 BQ_GName.append(text);
                             }
                             else
                             {
                                 BQ_GName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    BQ_G.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    qDebug () << text;

                    if(text == "Отсутствует\r\u0007")
                    {
                        BQ_G.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            BQ_GName.append(text);
                        }
                        else
                        {
                            BQ_GName.append(text);
                        }
                    }
                }

                break;
            }

            //Ищем DA (Микросхема)
            if(((text[0] == "D") && (text[1] == "A")) && (j == 2))
            {
                if((str[0] == "D" && str[1] == "A"))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         DA.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             DA.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 DAName.append(text);
                             }
                             else
                             {
                                 DAName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {

                    DA.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       DA.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            DAName.append(text);
                        }
                        else
                        {
                            DAName.append(text);
                        }
                    }
                }

                break;
            }

            //Ищем DD (Микросхема)
            if(((text[0] == "D") && (text[1] == "D")) && (j == 2))
            {
                if((str[0] == "D" && str[1] == "D"))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         DD.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             DD.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 DDName.append(text);
                             }
                             else
                             {
                                 DDName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    DD.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       DD.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            DDName.append(text);
                        }
                        else
                        {
                            DDName.append(text);
                        }
                    }
                }

                break;
            }

            //Ищем U (источники питания)
            if((text[0] == "U") && (j == 2))
            {
                if(str[0] == "U")
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         U.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             U.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 UName.append(text);
                             }
                             else
                             {
                                 UName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    U.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();


                    if(text == "Отсутствует\r\u0007")
                    {
                       U.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            UName.append(text);
                        }
                        else
                        {
                            UName.append(text);
                        }
                    }
                }

                break;

            }

            //Ищем L
            if((text[0] == "L") && (j == 2))
            {
                if(str[0] == "L")
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         L.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             L.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 LName.append(text);
                             }
                             else
                             {
                                 LName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    L.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       L.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            LName.append(text);
                        }
                        else
                        {
                            LName.append(text);
                        }
                    }
                }


                break;

            }

            //Ищем TV
            if(((text[0] == "T") && (text[1] == "V"))  && (j == 2))
            {
                if((str[0] == "T") && (str[1] == "V"))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         TV.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             TV.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 TVName.append(text);
                             }
                             else
                             {
                                 TVName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    TV.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       TV.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            TVName.append(text);
                        }
                        else
                        {
                            TVName.append(text);
                        }
                    }
                }

                break;

            }

            //Ищем VT
            if(((text[0] == "V") && (text[1] == "T"))  && (j == 2))
            {
                if((str[0] == "V") && (str[1] == "T"))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         VT.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             VT.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 VTName.append(text);
                             }
                             else
                             {
                                 VTName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    VT.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       VT.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            VTName.append(text);
                        }
                        else
                        {
                            VTName.append(text);
                        }
                    }
                }


                break;

            }

            //Ищем HL
            if(((text[0] == "H") && (text[1] == "L"))  && (j == 2))
            {
                if((str[0] == "H") && (str[1] == "L"))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         HL_VD.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             HL_VD.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 HL_VDName.append(text);
                             }
                             else
                             {
                                 HL_VDName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    HL_VD.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       HL_VD.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                            CellRange = StartCell->querySubObject("Range()");
                            text+=CellRange->property("Text").toString();

                            HL_VDName.append(text);
                        }
                        else
                        {
                            HL_VDName.append(text);
                        }
                    }
                }


                break;

            }

            //Ищем VD
            if(((text[0] == "V") && (text[1] == "D"))  && (j == 2))
            {
                if((str[0] == "V") && (str[1] == "D"))
                {
                    for(int col = countStart; col < (countStart+countCount);col++)
                    {
                         count_find++;

                         HL_VD.append(str+QString::number(col)+"\r\u0007");

                         StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                         CellRange = StartCell->querySubObject("Range()");
                         text =  CellRange->property("Text").toString();

                         if(text == "Отсутствует\r\u0007")
                         {
                             HL_VD.removeLast();
                         }
                         else
                         {
                             if(findRussianLanguage(text))
                             {
                                 StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);
                                 CellRange = StartCell->querySubObject("Range()");
                                 text+=CellRange->property("Text").toString();

                                 HL_VDName.append(text);
                             }
                             else
                             {
                                 HL_VDName.append(text);
                             }
                         }
                    }

                    emit changeWork(rows);
                    i++;

                    break;
                }
                else
                {
                    HL_VD.append(text);

                    StartCell = Tables->querySubObject("Cell(Row, Column)", i, j+1);
                    CellRange = StartCell->querySubObject("Range()");
                    text =  CellRange->property("Text").toString();

                    if(text == "Отсутствует\r\u0007")
                    {
                       HL_VD.removeLast();
                    }
                    else
                    {
                        if(findRussianLanguage(text))
                        {
                            StartCell = Tables->querySubObject("Cell(Row, Column)", i+1, j+1);

                            CellRange = StartCell->querySubObject("Range()");

                            text+=CellRange->property("Text").toString();

                            HL_VDName.append(text);
                        }
                        else
                        {
                            HL_VDName.append(text);
                        }
                    }
                }

                break;

            }




        }
    }

    Part("Поиск завершен. Закрытие документа.");

    emit findData(R.count(),C_Z.count(),XP_XS_XW_X.count(),BQ_G.count(),DD.count(),DA.count(),U.count(),L.count(),TV.count(),HL_VD.count(),VT.count());

    //ActiveDocument->dynamicCall("Close (boolean)", false);

    WordApplication->dynamicCall("Quit (void)");


    delete WordApplication;


    // creatShablon();

}

bool MYWORD::findRussianLanguage(QString text)
{
    QString russian = "ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮЁ";

    if(text[0] == " ")
    {
        text.remove(0,1);
    }



    auto list = text.split(' ');


    for(int i=0; i < text.count()-1;i++)
    {
        if(text[i] == "Т" && text[i+1] =="У")
        {
             return false;
        }

        if(text[i] == "У" && text[i+1] =="Э")
        {
             return false;
        }
    }

    QString str = text.split(' ').last();

    if(str == "ТУ" || str == "УЭ")
    {
        return false;
    }
    else
    {
        str = text.split(' ').value(1).toUpper();



        /*
        if(str == "КОНДЕНСАТОР")
        {
          str = text.split(' ').value(2).toUpper();
        }
        if(str == "МИКРОСХЕМА")
        {
            str = text.split(' ').value(2).toUpper();
        }s

        */
    }

    qDebug () << str;
    qDebug () << text;

    for(int i=0; i < str.count();i++)
    {
        for(int j=0; j < russian.count();j++)
        {
            if(str[i] == russian[j])
            {
                return true;
            }
        }
    }

    return false;
}

void MYWORD::creatShablon()
{
    Part("Создание шаблона с R. ["+saveDir+"//R]");

    if(R.count() > 0)
    {
        CreatShablon_R();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с С Z. ["+saveDir+"//СZ]");

    if(C_Z.count() > 0)
    {
        CreatShablon_C_Z();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с XP XS XW X. ["+saveDir+"//XPXSXWX]");

    if(XP_XS_XW_X.count() > 0)
    {
        CreatShablon_XP_XS_XW_X();
    }

   //this->thread()->msleep(10);

    Part("Создание шаблона с BQ. ["+saveDir+"//BQ]");

    if(BQ_G.count() > 0)
    {
        CreatShablon_BQ();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с DD. ["+saveDir+"//DD]");

    if(DD.count() > 0)
    {
        CreatShablon_DD();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с DA. ["+saveDir+"//DA]");

    if(DA.count() > 0)
    {
        CreatShablon_DA();
    }

    //this->thread()->msleep(10);


    Part("Создание шаблона с U. ["+saveDir+"//U]");

    if(U.count() > 0)
    {
        CreatShablon_U();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с L. ["+saveDir+"//L]");

    if(L.count() > 0)
    {
        CreatShablon_L();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с TV. ["+saveDir+"//TV]");

    if(TV.count() > 0)
    {
        CreatShablon_TV();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с HL VD. ["+saveDir+"//HLVD]");

    if(HL_VD.count() > 0)
    {
        CreatShablon_HL_VD();
    }

    //this->thread()->msleep(10);

    Part("Создание шаблона с VT. ["+saveDir+"//VT]");

    if(VT.count() > 0)
    {
        CreatShablon_VT();
    }

    //this->thread()->msleep(10);


    R.clear();      //отчистка резисторы
    RName.clear();  //отчистка имя резисторов


    C_Z.clear();    //отчистка конденсаторы и фильтры
    C_ZName.clear();  //отчистка имя конденсаторов

    XP_XS_XW_X.clear();  //отчистка Вилка
    XP_XS_XW_XName.clear(); //отчистка ИмяВилки

    DA.clear();
    DAName.clear();

    DD.clear();
    DDName.clear();

    BQ_G.clear();
    BQ_GName.clear();

    U.clear();
    UName.clear();

    L.clear();
    LName.clear();

    VT.clear();
    VTName.clear();

    HL_VD.clear();
    HL_VDName.clear();

    Part("Шаблоны созданны.");


}


QString MYWORD::addData_R_Power_NTD(int i)
{
    QString code = "";
    int findIndex = 0;
    QString str = RName[i].split(' ').last();

    if(str[0] == 'C' && str[1] == 'R')
    {
        code += str[2];
        code += str[3];
        code += str[4];
        code += str[5];

        findIndex = r_cr_code.indexOf(code);

        if(findIndex != -1)
        {
            return r_cr_power.value(findIndex);
        }
    }

    return "";

}

QString MYWORD::addData_R_TemperatureRange_NTD(int i)
{
    QString code = "";
    int findIndex = 0;
    QString str = RName[i].split(' ').last();

    if(str[0] == 'C' && str[1] == 'R')
    {
        code += str[2];
        code += str[3];
        code += str[4];
        code += str[5];

        findIndex = r_cr_code.indexOf(code);

        if(findIndex != -1)
        {
            return r_cr_TemperatureRange.value(findIndex);
        }
    }

    return "";

}

QString MYWORD::addData_R_U_NTD(int i,double p)
{
    QString code = "";
    QString str = RName[i].split(' ').last();
    QString strR = str.split('-').last();

    double u = 0;


    if(str[0] == 'C' && str[1] == 'R')
    {
        code += strR[0];

        if(strR[1] == 'R')
        {
            code += ".";
            code += strR[2];
            code += strR[strR.count()-3];

            u = qSqrt(code.toDouble() *p);
        }
        else
        {
            if(strR[2] == 'R')
            {
                code += strR[1];
                code += ".";
                code += strR[strR.count()-3];

                u = qSqrt(code.toDouble() *p);
            }
            else
            {
                code += strR[1];
                code += strR[2];

                u = qSqrt((code.toInt() * qPow(10,QString(strR[strR.count()-3]).toInt()))*p);
            }
        }

        if( u == 0.0 )
        {
            code = "";
            code += str[2];
            code += str[3];
            code += str[4];
            code += str[5];

            int  findIndex = r_cr_code.indexOf(code);

            if(findIndex != -1)
            {
                return r_cr_Void.value(findIndex);
            }
        }
        else
        {
            code = "";
            code += str[2];
            code += str[3];
            code += str[4];
            code += str[5];

            int  findIndex = r_cr_code.indexOf(code);

            if(findIndex != -1)
            {
                if(u > r_cr_Void.value(findIndex).toDouble())
                {
                    return r_cr_Void.value(findIndex);
                }
            }


        }

        return QString::number(u,'f', 2);
    }

    return "";
}


void MYWORD::CreatShablon_R()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[0]); //D:\\11111\\One.docx


    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[0]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }




    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//R");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//R");




    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");




    qDebug () << "Example R: " << (R.count()%3) << " ; " <<  (R.count()/3)+1 << " ; " << (R.count()/3);


    if((R.count()%3) > 0 )
    {
        for(int i=1; i < (R.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateR(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (R.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateR(QString::number(i));
        }
    }


    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < R.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateR(QString::number(i+1));

        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", R[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", RName[i]);


        switch (flag) {

            case 1:
            {
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 14, 4);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);


                //////////////////////
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 16, 4);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)",addData_R_Power_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 14, 5);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_TemperatureRange_NTD(i));


                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 4, 5);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_U_NTD(i,addData_R_Power_NTD(i).toDouble()));


                break;
            }
            case 2:
            {
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 14, 6);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);

                //////////////////////
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 16, 6);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_Power_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 14, 7);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_TemperatureRange_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 4, 7);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_U_NTD(i,addData_R_Power_NTD(i).toDouble()));

                break;
            }
            case 3:
            {
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 14, 8);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);

                //////////////////////
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 16, 8);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_Power_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 14, 9);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_TemperatureRange_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 4, 9);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_R_U_NTD(i,addData_R_Power_NTD(i).toDouble()));

                break;
            }

        }




        if(flag == 3)
        {
            flag =0;

            k++;


            if((R.count()%3) > 0  && k > (R.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((R.count()%3) == 0  && k > (R.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//R" ,"17");//fileName.split('.').first()

   ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//R");
   ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//R");


   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
   if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");


   delete WordApplication_2;
}

QString MYWORD::addData_C_Power_NTD(int i)
{
    QString codePower = "";
    int findIndex = 0;
    QString str = C_ZName[i].split(' ').last();

    if(str[0] == 'G' && str[1] == 'R' && str[2] == 'M') //GRM155R61A474KE15
    {
        codePower += str[8];
        codePower += str[9];

        findIndex = c_grm_codePower.indexOf(codePower);

        if(findIndex != -1)
        {
            return c_grm_power.value(findIndex);
        }
    }

    if(str[0] == 'N' && str[1] == 'F' && str[2] == 'M')
    {
        codePower += str[11];
        codePower += str[12];

        findIndex = z_nfm_code.indexOf(codePower);

        if(findIndex != -1)
        {
            return z_nfm_power.value(findIndex);
        }
    }

    if(str[0] == 'A' && str[1] == 'V' && str[2] == 'X')
    {
        codePower += str[11];
        codePower += str[12];
        codePower += str[13];

        findIndex = c_avx_codePower.indexOf(codePower);

        if(findIndex != -1)
        {
            return c_avx_power.value(findIndex);
        }
    }

    return "";
}

QString MYWORD::addData_C_TemperatureRange_NTD(int i)
{
    QString codeTemperatureRange = "";
    int findIndex = 0;
    QString str = C_ZName[i].split(' ').last();

    if(str[0] == 'G' && str[1] == 'R' && str[2] == 'M') //GRM155R61A474KE15
    {
        codeTemperatureRange += str[6];
        codeTemperatureRange += str[7];

        findIndex = c_grm_codeTemperatureRange.indexOf(codeTemperatureRange);

        if(findIndex != -1)
        {
            return c_grm_TemperatureRange.value(findIndex);
        }
    }

    if(str[0] == 'A' && str[1] == 'V' && str[2] == 'X')
    {

        if(c_avx_TemperatureRange.count() > 0)
        {
            return c_avx_TemperatureRange.first();
        }

    }

    return "";
}

////////////////////////////////////////////////////




void MYWORD::CreatShablon_C_Z()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject("Documents()"); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

    //WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[2]); //D:\\11111\\One.docx


    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[2]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }




    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");



    // ActiveDocument_2->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//CZ");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//CZ");





    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");




     qDebug () << "Example C_Z: " << (C_Z.count()%3) << " ; " <<  (C_Z.count()/3)+1 << " ; " << (C_Z.count()/3);

    if((C_Z.count()%3) > 0 )
    {
        for(int i=1; i < (C_Z.count()/3)+1;i++)
        {
            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");


            emit updateC_Z(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (C_Z.count()/3);i++)
        {
            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateC_Z(QString::number(i));
        }
    }


    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < C_Z.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateC_Z(QString::number(i));

        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", C_Z[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", C_ZName[i]);


        //Темпиратура


        switch (flag) {

            case 1:
            {
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 4); // (ячейка C1)
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 4, 5);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_C_Power_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 5);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_C_TemperatureRange_NTD(i));

                break;
            }
            case 2:
            {
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 6); // (ячейка C1)
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);


                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 4, 7);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_C_Power_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 7);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_C_TemperatureRange_NTD(i));

                break;
            }
            case 3:
            {
                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 8); // (ячейка C1)
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

                CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);


                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 4, 9);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_C_Power_NTD(i));

                StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 9);
                CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
                CellRange_2_3->dynamicCall("InsertAfter(Text)", addData_C_TemperatureRange_NTD(i));

                break;
            }

        }

        if(flag == 3)
        {
            flag =0;

            k++;

            if((C_Z.count()%3) > 0  && k > (C_Z.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((C_Z.count()%3) == 0  && k > (C_Z.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }
        }

    }





    //Сохранить pdf
    //  ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//CZ" ,"17");//fileName.split('.').first()

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//CZ");//"D://11111//1//CZ");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//CZ");//"D://11111//1//CZ");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
    if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

    delete WordApplication_2;
}

void MYWORD::CreatShablon_XP_XS_XW_X()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[1]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[1]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }



    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");



    // ActiveDocument_2->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//XPXSXWX");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//XPXSXWX");




    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");




    qDebug () << "Example XP_XS_XW_X: " << (XP_XS_XW_X.count()%3) << " ; " <<  (XP_XS_XW_X.count()/3)+1 << " ; " << (XP_XS_XW_X.count()/3);


    if((XP_XS_XW_X.count()%3) > 0 )
    {
        for(int i=1; i < (XP_XS_XW_X.count()/3)+1;i++)
        {
            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateXP_XS_XW_X(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (XP_XS_XW_X.count()/3);i++)
        {
            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateXP_XS_XW_X(QString::number(i));

        }
    }



    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < XP_XS_XW_X.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateXP_XS_XW_X(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", XP_XS_XW_X[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", XP_XS_XW_XName[i]);


        //Темпиратура


        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 25, 3); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 25, 5); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 3:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 25, 7); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }

        }


        if(flag == 3)
        {
            flag =0;

            k++;

            if((XP_XS_XW_X.count()%3) > 0  && k > (XP_XS_XW_X.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((XP_XS_XW_X.count()%3) == 0  && k > (XP_XS_XW_X.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }
        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//XPXSXW" ,"17");//fileName.split('.').first()

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//XPXSXWX");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//XPXSXWX");


   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
    if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

    delete WordApplication_2;
}

void MYWORD::CreatShablon_VT()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[9]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[9]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//VT");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//VT");


    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");


    qDebug () << "Example VT: " << (VT.count()%3) << " ; " <<  (VT.count()/3)+1 << " ; " << (VT.count()/3);
    if((VT.count()%3) > 0 )
    {
        for(int i=1; i < (VT.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateVT(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (VT.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateVT(QString::number(i));

        }
    }



    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < VT.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateVT(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", VT[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", VTName[i]);


        //Темпиратура


        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 22, 3); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 22, 5); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 3:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 22, 7); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }

        }



        if(flag == 3)
        {
            flag =0;

            k++;


            if((VT.count()%3) > 0  && k > (VT.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((VT.count()%3) == 0  && k > (VT.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }


    //Сохранить pdf

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//VT");//"D://11111//1//BQ");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//VT");//"D://11111//1//BQ");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
    if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

    delete WordApplication_2;
}

void MYWORD::CreatShablon_HL_VD()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[10]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[10]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//HLVD");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//HLVD");


    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");


    qDebug () << "Example HL_VD: " << (HL_VD.count()%3) << " ; " <<  (HL_VD.count()/3)+1 << " ; " << (HL_VD.count()/3);

    if((HL_VD.count()%3) > 0 )
    {
        for(int i=1; i < (HL_VD.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateHL_VD(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (HL_VD.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateHL_VD(QString::number(i));
        }
    }



    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < HL_VD.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateHL_VD(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", HL_VD[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", HL_VDName[i]);


        //Темпиратура


        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 12, 3); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 12, 5); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 3:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 12, 7); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }

        }



        if(flag == 3)
        {
            flag =0;

            k++;

            if((HL_VD.count()%3) > 0  && k > (HL_VD.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((HL_VD.count()%3) == 0  && k > (HL_VD.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//HLVD");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//HLVD");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
    if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");


    delete WordApplication_2;
}

void MYWORD::CreatShablon_BQ()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[2]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[2]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }



    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//BQG");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//BQG");


    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");


     qDebug () << "Example BQ_G: " << (BQ_G.count()%3) << " ; " <<  (BQ_G.count()/3)+1 << " ; " << (BQ_G.count()/3);

    if((BQ_G.count()%3) > 0 )
    {
        for(int i=1; i < (BQ_G.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateBQ_G(QString::number(i));

        }
    }
    else
    {
        for(int i=1; i < (BQ_G.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateBQ_G(QString::number(i));

        }
    }



    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < BQ_G.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateBQ_G(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");
        CellRange_2->dynamicCall("InsertAfter(Text)", BQ_G[i]);

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");
        CellRange_2_3->dynamicCall("InsertAfter(Text)", BQ_GName[i]);


        //Темпиратура


        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 4); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 6); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 3:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 15, 8); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }

        }



        if(flag == 3)
        {
            flag =0;

            k++;

            if((BQ_G.count()%3) > 0  && k > (BQ_G.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((BQ_G.count()%3) == 0  && k > (BQ_G.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//BQ" ,"17");//fileName.split('.').first()

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//BQG");//"D://11111//1//BQ");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//BQG");//"D://11111//1//BQ");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
    if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

    delete WordApplication_2;
}

void MYWORD::CreatShablon_DA()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[4]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[4]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//DA");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//DA");

    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");


    qDebug () << "Example DA: " << (DA.count()%2) << " ; " <<  (DA.count()/2)+1 << " ; " << (DA.count()/2);

    if((DA.count()%2) > 0 )
    {
        for(int i=1; i < (DA.count()/2)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateDA(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (DA.count()/2);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateDA(QString::number(i));

        }
    }






    /////////////////////////////////////////////////////


    QAxObject* Tables_2,*StartCell_2,*CellRange_2,*StartCell_2_3,*CellRange_2_3;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < DA.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateDA(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", DA[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", DAName[i]);


        //Темпиратура


        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 23, 4); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 23, 7); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }


        }



        if(flag == 2)
        {
            flag =0;

            k++;


            if((DA.count()%2) > 0  && k > (DA.count()/2)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((DA.count()%2) == 0  && k > (DA.count()/2))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//DADD" ,"17");//fileName.split('.').first()

   ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//DA");
   ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//DA");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
   if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

   delete WordApplication_2;
}

void MYWORD::CreatShablon_DD()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[5]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[5]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)",saveDir+"//RESULT//DD");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)",saveDir+"//RESULT//DD");

    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");


    qDebug () << "Example DD: " << (DD.count()%2) << " ; " <<  (DD.count()/2)+1 << " ; " << (DD.count()/2);

    if((DD.count()%2) > 0 )
    {
        for(int i=1; i < (DD.count()/2)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateDD(QString::number(i));

        }
    }
    else
    {
        for(int i=1; i < (DD.count()/2);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateDD(QString::number(i));
        }
    }






    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2 = nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < DD.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateDD(QString::number(i));
        flag++; //чет не так в нижней ячейке

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", DD[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", DDName[i]);


        //Темпиратура


        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 18, 4); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 18, 7); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }


        }



        if(flag == 2)
        {
            flag =0;

            k++;


            if((DD.count()%2) > 0  && k > (DD.count()/2)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((DD.count()%2) == 0  && k > (DD.count()/2))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//DADD" ,"17");//fileName.split('.').first()

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)",saveDir+"//RESULT//DD"); //"D://11111//1//DD");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)",saveDir+"//RESULT//DD"); //"D://11111//1//DD");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
    if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

    delete WordApplication_2;
}

void MYWORD::CreatShablon_U()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

    //WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[6]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[6]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");



    // ActiveDocument_2->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//U");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//U");




    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");

    qDebug () << "Example U: " << (U.count()%3) << " ; " <<  (U.count()/3)+1 << " ; " << (U.count()/3);

    if((U.count()%3) > 0 )
    {
        for(int i=1; i < (U.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateU(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (U.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateU(QString::number(i));

        }
    }

    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < U.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateU(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", U[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", UName[i]);

        //Темпиратура

        if(flag == 3)
        {
            flag =0;

            k++;


            if((U.count()%3) > 0  && k > (U.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((U.count()%3) == 0  && k > (U.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//U" ,"17");//fileName.split('.').first()

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//U");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//U");



   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
   if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

   delete WordApplication_2;
}

void MYWORD::CreatShablon_L()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject( "Open(%T)",listMYWORD[7]); //D:\\11111\\One.docx


    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[7]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");



    // ActiveDocument_2->querySubObject("Range()")->dynamicCall("Copy()");


    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//L");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//L");

    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");




   qDebug () << "Example L: " << (L.count()%3) << " ; " <<  (L.count()/3)+1 << " ; " << (L.count()/3);


    if((L.count()%3) > 0 )
    {
        for(int i=1; i < (L.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateL(QString::number(i));

        }
    }
    else
    {
        for(int i=1; i < (L.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateL(QString::number(i));
        }
    }


    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < L.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateL(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", L[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", LName[i]);

        //Темпиратура

        switch (flag) {

        case 1:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 9, 3); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }
        case 2:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 9, 5); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }

        case 3:
        {
            StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 9, 7); // (ячейка C1)
            CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

            CellRange_2_3->dynamicCall("InsertAfter(Text)", temp);
            break;
        }

        }



        if(flag == 3)
        {
            flag =0;

            k++;


            if((L.count()%3) > 0  && k > (L.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((L.count()%3) == 0  && k > (L.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }







    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//L" ,"17");//fileName.split('.').first()

   ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//L");
   ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//L");




   //  ActiveDocument_2->dynamicCall("Close (boolean)", false);
   if(stateViewWord == false)
        WordApplication_2->dynamicCall("Quit (void)");

   delete WordApplication_2;
}

void MYWORD::CreatShablon_TV()
{
    QAxObject* WordApplication_2 = new QAxObject("Word.Application"); // Создаю интерфейс к MSWord

    WordApplication_2->setProperty("Visible", stateViewWord);

    QAxObject* WordDocuments_2 = WordApplication_2->querySubObject( "Documents()" ); // Получаю интерфейсы к его подобъекту "коллекция открытых документов":

   // WordDocuments_2->querySubObject("Open(%T)",listMYWORD[8]); //D:\\11111\\One.docx

    connect(
                WordApplication_2,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(catchException(int, const QString &, const QString &, const QString &)));

    QAxObject *newDocument = WordDocuments_2->querySubObject("Add(QVariant)", listMYWORD[8]);

    if(newDocument == nullptr)
    {
        qDebug() << "ERROR";
        WordApplication_2->dynamicCall("Quit (void)");
        delete WordApplication_2;
        return;
    }


    QAxObject* ActiveDocument_2 = WordApplication_2->querySubObject("ActiveDocument()");

    ActiveDocument_2->querySubObject("Tables(1)")->querySubObject("Range()")->dynamicCall("Copy()");

    ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//TV");
    ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//TV");

    QAxObject *selection_2 = WordApplication_2->querySubObject("Selection()");



    qDebug () << "Example TV: " << (TV.count()%3) << " ; " <<  (TV.count()/3)+1 << " ; " << (TV.count()/3);


    if((TV.count()%3) > 0 )
    {
        for(int i=1; i < (TV.count()/3)+1;i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateTV(QString::number(i));
        }
    }
    else
    {
        for(int i=1; i < (TV.count()/3);i++)
        {

            selection_2->dynamicCall("EndKey(wdStory)");
            selection_2->dynamicCall("InsertBreak()");
            //this->thread()->msleep(10);
            selection_2->dynamicCall("Paste()");

            emit updateTV(QString::number(i));

        }
    }


    /////////////////////////////////////////////////////


    QAxObject* Tables_2= nullptr,*StartCell_2= nullptr,*CellRange_2= nullptr,*StartCell_2_3= nullptr,*CellRange_2_3= nullptr;

    int flag =0;

    int k = 1;


    qDebug () << "K = " << k;

    Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));


    selection_2->dynamicCall("HomeKey(wdStory)");



    for(int i=0;i < TV.count();i++)
    {
        //this->thread()->msleep(10);
        emit updateTV(QString::number(i));
        flag++;

        StartCell_2  = Tables_2->querySubObject("Cell(Row, Column)", 1, 1+flag); // (ячейка C1)
        CellRange_2 = StartCell_2->querySubObject("Range()");

        StartCell_2_3  = Tables_2->querySubObject("Cell(Row, Column)", 2, 1+flag); // (ячейка C1)
        CellRange_2_3 = StartCell_2_3->querySubObject("Range()");

        CellRange_2->dynamicCall("InsertAfter(Text)", TV[i]);

        CellRange_2_3->dynamicCall("InsertAfter(Text)", TVName[i]);

        //Темпиратура

        if(flag == 3)
        {
            flag =0;

            k++;


            if((TV.count()%3) > 0  && k > (TV.count()/3)+1)
            {

                qDebug () << "Конец ; K = " << k;
                break;
            }
            else
            {
                if((TV.count()%3) == 0  && k > (TV.count()/3))
                {
                    qDebug () << "Конец ; K = " << k;
                    break;
                }
                else
                {
                   qDebug () << "K = " << k;
                   Tables_2 = ActiveDocument_2->querySubObject("Tables(%T)",QString::number(k));
                }
            }

        }

    }





    //Сохранить pdf
    //   ActiveDocument_2->dynamicCall("ExportAsFixedFormat (const QString&,const QString&)","D://11111//1//L" ,"17");//fileName.split('.').first()

   ActiveDocument_2->dynamicCall("SaveAs (const QString&)", saveDir+"//RESULT//TV");
   ActiveDocument_2->dynamicCall("SaveAs2 (const QString&)", saveDir+"//RESULT//TV");



    //ActiveDocument_2->dynamicCall("Close (boolean)", false);


   if(stateViewWord == false)
   {
        WordApplication_2->dynamicCall("Quit (void)");
   }

   delete WordApplication_2;

}


void MYWORD::catchException(int id, const QString &a, const QString &b, const QString &c)
{
    qDebug() << id;
    qDebug() << a;
    qDebug() << b;
    qDebug() << c;

    if(b == "This command is not available because no document is open.")
    {

    }
}

