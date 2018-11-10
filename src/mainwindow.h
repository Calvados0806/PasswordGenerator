#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "PassGen.hpp"
#include "ThreadsManager.hpp"


namespace Ui {
    class PasswordGenerator;
}

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

private:
    Ui::PasswordGenerator *ui;
    ThreadsManager tmanager;

    inline Complexity string2complexity(const QString&);
    void out_result2file(std::string*, size_t);
    void out_result2ui(std::string*, size_t, size_t);

private slots:
    void on_generate_clicked();
    void on_clear_clicked();
    void on_pass2file_stateChanged();
};

#endif // MAINWINDOW_H
