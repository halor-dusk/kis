#include "user.h"

User::User(const QString &cardId, const QString &firstName, const QString &lastName, int balance)
    : cardId(cardId)
    , firstName(firstName)
    , lastName(lastName)
    , balance(balance)
{}
