#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

User *login(const QString &number, const QString &password);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pages->setCurrentIndex(0);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Kis");
    db.setUserName("root");
    db.setPassword("1234");
    if (!db.open())
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

void MainWindow::on_screenSaver_Button_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::on_cancelButton_clicked()
{
    QMessageBox::Button reply = QMessageBox::question(this,
        "Confirmar ação",
        "Tens certeza que queres cancelar essa operação e retornar a tela de descanço?"
    );

    if (reply == QMessageBox::Yes)
        ui->pages->setCurrentIndex(0);
}


void MainWindow::on_loginButton_clicked()
{
    QString cardId = ui->cardNumber_lineEdit->text(),
            password = ui->password_lineEdit->text();

    this->user = login(cardId, password);
    if (!this->user)
        QMessageBox::Button reply = QMessageBox::warning(
            this,
            "Não foi possivel conecta-se",
            "Palavra passe e/ou numero de cartão esta/estão invalido(s)."
        );
    else
        ui->pages->setCurrentIndex(2);
}

User *login(const QString &id, const QString &password)
{
    QSqlQuery query;
    query.prepare(
        "SELECT `card_id`, `first_name`, `last_name`, `balance` FROM `users` "
        "WHERE `card_id` = :cardId AND `password` = SHA2(:password, 256)"
    );

    query.bindValue(":cardId", id);
    query.bindValue(":password", password);

    query.exec();

    if (!query.next())
        return nullptr;

    return new User(
        query.value(0).toString(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toInt()
    );
}
