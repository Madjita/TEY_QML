#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlComponent>
#include <QLoggingCategory>

#include <word.h>
#include <wordqmlmodel.h>

#include <QQuickWindow>

#include <QtWinExtras>

QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    QLoggingCategory::setFilterRules("*.debug=false\n"
//                                           "driver.usb.debug=true");


    MYWORD* word = new MYWORD();
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


//    QObject *rootObject = engine.rootObjects().first();
//    QObject *qmlObject = rootObject->findChild<QObject*>("mainWindow");



//    if (QtWin::isCompositionEnabled())
//        QtWin::extendFrameIntoClientArea(dynamic_cast<QQuickWindow*>(qmlObject), 0, 0, 0, 0);
//    else
//        QtWin::resetExtendedFrame(dynamic_cast<QQuickWindow*>(qmlObject));


//    HINSTANCE hMod;
//     HWND hwnd;
//     ShellExecuteA(NULL,"open","notepad.exe",NULL,NULL,SW_SHOWNORMAL);
//     hMod = LoadLibraryA("user32.dll");


    if (engine.rootObjects().isEmpty())
        return -1;

    //  QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));
    //   QObject* contentView = component.create();
    // qDebug() <<  contentView->findChild<QObject*>(QString("page3"));//->setProperty("end","360");

    // qDebug() << engine.findChild<QObject*>(QString("page3"));//->findChild<QObject*>(QString("listSeitings"))-> setProperty("model",list);



    return app.exec();
}
