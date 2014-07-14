#include <QApplication>
#include <QQmlApplicationEngine>

#include"DesktopVideoProducer.h"

int main(int argc, char *argv[])
{
    DesktopVideoProducer::registerQmlType();

    //для возможности вызова QApplication::desktop() QGuiApplication недостаточно
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
