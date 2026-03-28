#ifndef CHARGE_DIALOG_H
#define CHARGE_DIALOG_H

#include <QDialog>
#include <QVector>

#include "../includes/user.h"

namespace Ui {
class ChargeDialog;
}

class ChargeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChargeDialog(User *user, QWidget *parent = nullptr);
    ~ChargeDialog();

private slots:
    void on_cancel_clicked();

    void on_charge_clicked();

private:
    Ui::ChargeDialog *ui;

    User *user;
    const QVector<int> validCoins;
    int charging;

    /*
     * @brief Increment how much the user is charging in this dialog, validating its value.
     *
     * @param value Coin value in cents (10, 20, 50, 100, 200).
     *
     * @return True if the operation completed successfully; false otherwise.
     */
    bool insertCoin(int value);

    /*
     * @brief Adds money to the user's balance and updates the database.
     * Displays an error message and closes the application if a database error occurs.
     *
     * @param amount Amount to add to the user's balance (in cents).
     *
     * @return True if the operation completed successfully; false if the amount is negative
     * or if a database error occurs.
     */
    bool charge(int amount);
};

#endif // CHARGE_DIALOG_H
