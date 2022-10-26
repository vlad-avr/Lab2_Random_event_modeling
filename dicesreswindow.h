#ifndef DICESRESWINDOW_H
#define DICESRESWINDOW_H

#include <QDialog>
#include "probexp.h"

namespace Ui {
class DicesResWindow;
}

class DicesResWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DicesResWindow(QWidget *parent = nullptr);
    ~DicesResWindow();
    void set_ui(ProbExp* exp, int N);

private:
    Ui::DicesResWindow *ui;
};

#endif // DICESRESWINDOW_H
