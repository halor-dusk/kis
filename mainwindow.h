#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "includes/user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_screenSaver_Button_clicked();

    void on_cancelButton_clicked();

    void on_loginButton_clicked();

    void on_charge_clicked();

    void on_quit_clicked();

private:
    User *user;
    Ui::MainWindow *ui;

    bool connectDb(const QString &dbHost, const QString &dbName, const QString& dbUser, const QString &dbPassword);
    User *login(const QString &id, const QString &password);

    void updateBalanceLabel();
};
#endif // MAINWINDOW_H
