#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "tcontainer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void inactivateWgts();

protected slots:
    void restoreSettings();
    void updateGeometry(const QString &id, const QRect &g);
    void addWidget(const QString &id, QWidget *wgt);
    void widgetDelete(const QString &id);

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;
    TContainer *con;
    QSettings *settings;
};

#endif // MAINWINDOW_H
