#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QSurfaceFormat>
#include <QQuickView>




int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickWindow* window = (QQuickWindow*) engine.rootObjects().first();
    format.setSamples(16);
    window->setFormat(format);
   if (engine.rootObjects().isEmpty())
      return -1;

    return app.exec();
}
