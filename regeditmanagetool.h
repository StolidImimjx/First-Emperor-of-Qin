#ifndef REGEDITMANAGETOOL_H
#define REGEDITMANAGETOOL_H

#include "regeditmanager.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QDebug>

namespace Ui {
class RegeditManageTool;
}

class RegeditManageTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegeditManageTool(QWidget *parent = 0);


    ~RegeditManageTool();

signals:

public slots:
    void onTrigerMenu(QAction* act);
    void onBrowseFileClicked();
    void onAddToolClicked();
    void onDelToolClicked();

private:
    Ui::RegeditManageTool *ui;


};

#endif // REGEDITMANAGETOOL_H
