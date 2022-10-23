#ifndef DICESRESWINDOW_H
#define DICESRESWINDOW_H

#include <QDialog>

namespace Ui {
class DicesResWindow;
}

class DicesResWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DicesResWindow(QWidget *parent = nullptr);
    ~DicesResWindow();

private:
    Ui::DicesResWindow *ui;
};

#endif // DICESRESWINDOW_H
