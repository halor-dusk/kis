#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QDialog>

namespace Ui {
class ScreenSaver;
}

class ScreenSaver : public QDialog
{
    Q_OBJECT

public:
    explicit ScreenSaver(QWidget *parent = nullptr);
    ~ScreenSaver();

private slots:
    void on_backgroundButtonimage_clicked();

private:
    Ui::ScreenSaver *ui;
};

#endif // SCREENSAVER_H
