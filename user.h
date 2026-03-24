#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    QString firstName, lastName, cardId;
    int balance = 0; // In cents

    User(const QString &cardId, const QString &firstName, const QString &lastName, int balance = 0);
};

#endif // USER_H
