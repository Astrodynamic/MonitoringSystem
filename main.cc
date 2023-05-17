#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "agent_manager.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  // qmlRegisterType<Kernel>("Kernel", 1, 0, "Kernel");

  AgentManager agent_manager;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("AgentManager", &agent_manager);

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
