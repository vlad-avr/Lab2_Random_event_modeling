#ifndef DICESMANUAL_H
#define DICESMANUAL_H

#include <QDialog>
#include "probexp.h"
#include "dicesreswindow.h"
namespace Ui {
class DicesManual;
}

class DicesManual : public QDialog
{
    Q_OBJECT

public:
    explicit DicesManual(QWidget *parent = nullptr);
    ~DicesManual();

private slots:
    void on_AddEventButton_clicked();


    void on_EditEventButton_clicked();

    void on_RemoveEventButton_clicked();

    void on_EditButton_clicked();

    void on_ComputeButton_clicked();

private:
    ProbExp *exp;
    Ui::DicesManual *ui;
    DicesResWindow * dr_wind;

};

#endif // DICESMANUAL_H
