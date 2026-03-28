#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "./dialogs/charge_dialog.h"
#include "./includes/utils.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pages->setCurrentIndex(0); // Because QStackWidgets keeps track of last current index after closing this is need to
    // restart the application

    QString dbName = qgetenv("DB_NAME"),
        dbUser = qgetenv("DB_USERNAME"),
        dbPassword = qgetenv("DB_PASSWORD"),
        dbHost = qgetenv("DB_HOST")
    ;
    if (!connectDb(dbHost, dbName, dbUser, dbPassword))
    {
        QMessageBox::Button reply = QMessageBox::critical(
            this,
            "Problema ao tentar conectar a base de dados",
            "Desculpa, porem programa não pode ser iniciado. Pois não conseguimos conectar a base de dados."
            );

        QApplication::quit();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::connectDb(const QString &dbHost, const QString &dbName, const QString& dbUser, const QString &dbPassword)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbHost);
    db.setDatabaseName(dbName);
    db.setUserName(dbUser);
    db.setPassword(dbPassword);
    return db.open();
}

User *MainWindow::login(const QString &id, const QString &password)
{
    QSqlQuery query;
    query.prepare(
        "SELECT `id`, `card_id`, `first_name`, `last_name`, `balance` FROM `users` "
        "WHERE `card_id` = :cardId AND `password` = SHA2(:password, 256)"
        );

    query.bindValue(":cardId", id);
    query.bindValue(":password", password);

    if (!query.exec())
        fatalError(this, "Problem trying to login user:", query.lastError().text());

    if (!query.next())
        return nullptr;

    return new User(
        query.value(0).toInt(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toString(),
        query.value(4).toInt()
    );
}

void MainWindow::updateBalanceLabel()
{
    ui->balance->setText("Seu saldo atual é de: " + QString::number(euro(this->user->getBalance()), 'f', 2) + "€");
}

// Screen saver
void MainWindow::on_screenSaver_Button_clicked()
{
    ui->pages->setCurrentIndex(1);
}

// Login
void MainWindow::on_loginButton_clicked()
{
    QString cardId = ui->cardNumber_lineEdit->text(),
            password = ui->password_lineEdit->text();

    this->user = this->login(cardId, password);
    if (!this->user)
        QMessageBox::Button reply = QMessageBox::warning(
            this,
            "Não foi possivel conecta-se",
            "Palavra passe e/ou numero de cartão esta/estão invalido(s)."
        );
    else {
        ui->userName->setText(this->user->firstName);
        ui->cardId->setText("Numero de processo: " + this->user->cardId);
        updateBalanceLabel(); // This actually is starting the balance label, but here is the only place where this happens

        ui->pages->setCurrentIndex(2);
        ui->cardNumber_lineEdit->clear();
        ui->password_lineEdit->clear();
    }
}

void MainWindow::on_cancelButton_clicked()
{
    QMessageBox::Button reply = QMessageBox::question(
        this,
        "Confirmar ação",
        "Tens certeza que queres cancelar essa operação e retornar a tela de descanço?"
    );

    if (reply == QMessageBox::Yes) {
        ui->pages->setCurrentIndex(0);
        ui->cardNumber_lineEdit->clear();
        ui->password_lineEdit->clear();
    }
}

// Home
void MainWindow::on_charge_clicked()
{
    ChargeDialog *chargeDialog = new ChargeDialog(this->user, this);
    chargeDialog->exec();
    updateBalanceLabel();
}

void MainWindow::on_quit_clicked()
{
    QMessageBox::Button reply = QMessageBox::question(this, "Confirmar ação", "Tens certesa que desejas sair e voltar a tela de descanço");

    if (reply == QMessageBox::Yes)
    {
        ui->pages->setCurrentIndex(0);
        this->user = nullptr;
    }
}

