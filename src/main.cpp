#include <QApplication>

#include "mainwindow.h"


class Application
{
public:
    static int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);
        PasswordGenerator wind;
        wind.show();

        return app.exec();
    }
};


int main(int argc, char* argv[])
{
    return Application::main(argc, argv);
}