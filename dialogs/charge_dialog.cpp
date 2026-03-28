#include "charge_dialog.h"
#include "ui_charge_dialog.h"

#include "../includes/utils.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

ChargeDialog::ChargeDialog(User *user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChargeDialog)
    , user(user)
    , charging(0)
    , validCoins({
        10,
        20,
        50,
        100,
        200
    })
{
    ui->setupUi(this);
    insertCoin(10);
}

ChargeDialog::~ChargeDialog()
{
    delete ui;
}

void ChargeDialog::on_cancel_clicked()
{
    if (this->charging > 0)
        QMessageBox::warning(
            this,
            "Não podes cancelar essa operação!",
            "Desculpa mas já não podes cancelar essa operação pois inseriste moedas."
            );
    else
        this->hide();
}

void ChargeDialog::on_charge_clicked()
{
    if (this->charging <= 0)
        QMessageBox::warning(
            this,
            "Por favor insira moedas",
            "Para carregar seu cartão, insira moedas primeiro, por favor"
            );
    else if (!charge(this->charging))
        return;

    this->hide();
}

bool ChargeDialog::insertCoin(int value)
{
    if (!this->validCoins.contains(value))
        return false;

    this->charging += value;
    ui->totalCharged->setText("Total carregado: " + QString::number(euro(this->charging), 'f', 2) + "€");

    return true;
}

bool ChargeDialog::charge(int amount)
{
    if (amount < 0)
        return false;

    QSqlQuery query;
    query.prepare(
        "UPDATE `users` "
        "SET `balance` = `balance` + :amount "
        "WHERE `id` = :id"
    );

    query.bindValue(":amount", amount);
    query.bindValue(":id", this->user->getId());

    if (!query.exec())
    {
        fatalError(this, "Error trying to charge card:", query.lastError().text());
        return false;
    }

    return this->user->deposit(amount);
}

