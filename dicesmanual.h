#ifndef DICESMANUAL_H
#define DICESMANUAL_H

#include <QDialog>

namespace Ui {
class DicesManual;
}

class DicesManual : public QDialog
{
    Q_OBJECT

public:
    explicit DicesManual(QWidget *parent = nullptr);
    ~DicesManual();

private:
    Ui::DicesManual *ui;
};

#endif // DICESMANUAL_H
