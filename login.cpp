#include "login.h"
#include "ui_login.h"
#include "screensaver.h"

#include <QMessageBox>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_cancel_clicked()
{
    QMessageBox::Button reply = QMessageBox::question(
        this,
        "Cancelar",
        "Tens certeza que deseja cancelar essa operação?"
    );

    if (reply == QMessageBox::Yes)
    {
        ScreenSaver *screenSaver = new ScreenSaver();
        this->hide();
        screenSaver->showFullScreen();
    }
}

