#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "kernel.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QGuiApplication::setWindowIcon(QIcon(":/appicon.png"));

  QCoreApplication::setOrganizationName("AstroGroup");
  QCoreApplication::setApplicationName("MonitoringSystem");

  Kernel kernel;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("Kernel", &kernel);

  const QUrl url(QStringLiteral("qrc:/Main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
