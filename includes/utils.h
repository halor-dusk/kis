#ifndef UTILS_H
#define UTILS_H

#include <QString>

class QWidget;

/*
 * @brief Displays a message boc with an error message and then closes the application.
 *
 * @param parent What widget is emmiting this message.
 * @param prefix The text that comes before the error message.
 * @param error The error message.
 */
void fatalError(QWidget *parent, const QString &prefix, const QString &error);

/*
 * @brief Takes a value in cents and converts to euro.
 *
 * @param cents Values to be converted.
 *
 * @return The converted euro value.
 */
float euro(int cents);

#endif // UTILS_H
