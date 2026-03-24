#include "screensaver.h"
#include "ui_screensaver.h"

#include "login.h"

ScreenSaver::ScreenSaver(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScreenSaver)
{
    ui->setupUi(this);
}

ScreenSaver::~ScreenSaver()
{
    delete ui;
}

void ScreenSaver::on_backgroundButtonimage_clicked()
{
    Login *login = new Login();

    this->hide();
    login->showFullScreen();
}

