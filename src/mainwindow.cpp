#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>


PasswordGenerator::PasswordGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);
    ui->progress->setValue(0);
    ui->path2dir->setEnabled(false);
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}

Complexity PasswordGenerator::string2complexity(const QString& str)
{
    if (str == "Easy")
        return Complexity::EASY;
    else if (str == "Medium")
        return Complexity::MEDIUM;
    else
        return Complexity::HARD;
}

void PasswordGenerator::out_result2file(std::string* result, size_t count)
{
    QString path2file = ui->path2dir->text();
    QFile file(path2file + "/result.txt");

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "No such directory");
        return;
    }
    QTextStream out(&file);

    for (size_t i = 0; i < count; ++i) {
        out << result[i].c_str() << "\n";
        ui->progress->setValue(((i+1) / (float)count) * 100);
    }

    //ui->progress->setValue(0);
}

void PasswordGenerator::out_result2ui(std::string* result, size_t count, size_t pass_len)
{
    QString out(pass_len*count, 0);

    for (size_t i = 0; i < count; ++i) {
        out += QString((result[i] + "\n").c_str());
        ui->progress->setValue(((i+1) / (float)count) * 100);
    }

    ui->out->setPlainText(out);
    //ui->progress->setValue(0);
}

void PasswordGenerator::on_generate_clicked()
{
    size_t pass_len = ui->pass_len->value();
    size_t pass_count = ui->pass_count->value();
    Complexity complexity = string2complexity(ui->complexity->currentText());

    PassGen generator(pass_len, complexity);

    std::string* result = tmanager(generator, pass_count);
    tmanager.join();

    if (ui->pass2file->checkState() == Qt::CheckState::Checked) {
        out_result2file(result, pass_count);
    } else {
        out_result2ui(result, pass_count, pass_len);
    }
}

void PasswordGenerator::on_clear_clicked()
{
    ui->out->setPlainText(QString(""));
    ui->progress->setValue(0);
}

void PasswordGenerator::on_pass2file_stateChanged()
{
    ui->path2dir->setEnabled(
            ui->pass2file->checkState() == Qt::CheckState::Checked
    );
}