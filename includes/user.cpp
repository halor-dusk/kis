#include "user.h"

User::User(int id, const QString &cardId, const QString &firstName, const QString &lastName, int balance)
    : id(id)
    , cardId(cardId)
    , firstName(firstName)
    , lastName(lastName)
    , balance(balance)
{}

bool User::deposit(int amount)
{
    if (amount < 0)
        return false;

    this->balance += amount;

    return true;
}

bool User::withdraw(int amount)
{
    if (amount < 0)
        return false;

    this->balance += amount;

    return true;
}

int User::getBalance() const
{
    return this->balance;
}

int User::getId() const
{
    return this->id;
}