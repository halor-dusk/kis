#include "utils.h"

#include <QMessageBox>
#include <QApplication>

void fatalError(QWidget *parent, const QString &prefix, const QString &error)
{
    QMessageBox::critical(parent, "Erro fatal", prefix + " " + error);
    QApplication::quit();
}

float euro(int cents)
{
    return cents/100.0f;
}