#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "kernel.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  Kernel kernel;

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/Main.qml"));
  QObject::connect(&engine,
                   &QQmlApplicationEngine::objectCreated,
                   &app,
                   [url](QObject *obj, const QUrl &objUrl) {
                     if (!obj && url == objUrl)
                       QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
