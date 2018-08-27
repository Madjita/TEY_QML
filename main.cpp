#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlComponent>
#include <QLoggingCategory>

#include <word.h>
#include <wordqmlmodel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    QLoggingCategory::setFilterRules("*.debug=false\n"
//                                           "driver.usb.debug=true");

    QStringList fileNames,fileNames_S_R,fileNames_XP_XS_XW_X,fileNames_C_Z,fileNames_BQ,fileNames_DA,fileNames_DD,fileNames_findMSWord;

    QStringList fileNames_U , fileNames_L,fileNames_TV;

    QStringList fileNames_VT , fileNames_HL_VD;

    fileNames_S_R  << "D:/PROJECTS/TEY2/1111/RShablon.docx";
    fileNames_XP_XS_XW_X << "D:/PROJECTS/TEY2/1111/XPXSXWShablon.docx";
    fileNames_C_Z << "D:/PROJECTS/TEY2/1111/CZShablon.docx";
    fileNames_BQ << "D:/PROJECTS/TEY2/1111/BQGShablon.docx";
    fileNames_DA << "D:/PROJECTS/TEY2/1111/DAShablon.docx";
    fileNames_DD << "D:/PROJECTS/TEY2/1111/DDShablon.docx";
    fileNames_U << "D:/PROJECTS/TEY2/1111/UShablon.docx";
    fileNames_L << "D:/PROJECTS/TEY2/1111/LShablon.docx";
    fileNames_TV << "D:/PROJECTS/TEY2/1111/TVShablon.docx";
    fileNames_VT << "D:/PROJECTS/TEY2/1111/VTShablon.docx";
    fileNames_HL_VD << "D:/PROJECTS/TEY2/1111/HLVDShablon.docx";
    fileNames_findMSWord << "";
    fileNames << "";





    MYWORD* word = new MYWORD(fileNames[0],fileNames_S_R[0],fileNames_XP_XS_XW_X[0],fileNames_C_Z[0],fileNames_BQ[0],fileNames_DA[0],fileNames_U[0],fileNames_L[0],fileNames_DD[0],fileNames_TV[0],fileNames_HL_VD[0],fileNames_VT[0]);


    BData* bd = new BData();

    word->setBD(bd);



    WordQMLModel* wordQMLModel = new WordQMLModel();


    QObject::connect(word,&MYWORD::changeWork,wordQMLModel,&WordQMLModel::changeWork);
    QObject::connect(word,&MYWORD::findData,wordQMLModel,&WordQMLModel::findData);

    QObject::connect(word,&MYWORD::updateR,wordQMLModel,&WordQMLModel::updateR);
    QObject::connect(word,&MYWORD::updateC_Z,wordQMLModel,&WordQMLModel::updateC_Z);
    QObject::connect(word,&MYWORD::updateXP_XS_XW_X,wordQMLModel,&WordQMLModel::updateXP_XS_XW_X);
    QObject::connect(word,&MYWORD::updateBQ_G,wordQMLModel,&WordQMLModel::updateBQ_G);
    QObject::connect(word,&MYWORD::updateDD,wordQMLModel,&WordQMLModel::updateDD);
    QObject::connect(word,&MYWORD::updateDA,wordQMLModel,&WordQMLModel::updateDA);
    QObject::connect(word,&MYWORD::updateU,wordQMLModel,&WordQMLModel::updateU);
    QObject::connect(word,&MYWORD::updateL,wordQMLModel,&WordQMLModel::updateL);
    QObject::connect(word,&MYWORD::updateTV,wordQMLModel,&WordQMLModel::updateTV);
    QObject::connect(word,&MYWORD::updateHL_VD,wordQMLModel,&WordQMLModel::updateHL_VD);
    QObject::connect(word,&MYWORD::updateVT,wordQMLModel,&WordQMLModel::updateVT);



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("word",word);
    engine.rootContext()->setContextProperty("wordQMLModel", wordQMLModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //  QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));
    //   QObject* contentView = component.create();
    // qDebug() <<  contentView->findChild<QObject*>(QString("page3"));//->setProperty("end","360");

    // qDebug() << engine.findChild<QObject*>(QString("page3"));//->findChild<QObject*>(QString("listSeitings"))-> setProperty("model",list);



    return app.exec();
}
