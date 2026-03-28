#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    QString firstName, lastName, cardId;

    User(int id, const QString &cardId, const QString &firstName, const QString &lastName, int balance = 0);

    /*
     * @brief Adds money (in cents) to the user's balance.
     *
     * @param amount Amount to add. Must be >= 0.
     *
     * @return True on success, false if the input is less than 0.
     */
    bool deposit(int amount);

    /*
     * @brief Removes money (in cents) from the user's balance.
     *
     * @param amount Amount to add. Must be >= 0.
     *
     * @return True on success, false if the input is less than 0.
     */
    bool withdraw(int amount);

    int getBalance() const;
    int getId() const;
private:
    int balance = 0, id; // In cents
};

#endif // USER_H
