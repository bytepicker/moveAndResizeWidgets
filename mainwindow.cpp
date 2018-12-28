#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QTableWidget>
#include <QCalendarWidget>

QString randomHex(const int &length = 6)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QString randomHex;

    for(int i = 0; i < length; i++) {
        int n = qrand() % 16;
        randomHex.append(QString::number(n,16));
    }

    return randomHex;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("Settings", "TestApp");
    this->restoreSettings();

    // fullscreen-no-resize
    this->showMaximized();
    this->statusBar()->setSizeGripEnabled(false);

    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);

    QRect rec = QGuiApplication::primaryScreen()->geometry();
    this->setFixedHeight(rec.height());
    this->setFixedWidth(rec.width());
}

void MainWindow::restoreSettings()
{
    foreach (const QString &val, settings->allKeys()){
        QRect pos = settings->value(val).toRect();

        if(val.contains("label")){
            QLabel *lab = new QLabel(val);
            con = new TContainer(this, val, lab);
        } else if (val.contains("table")){
            QTableWidget *tab = new QTableWidget(3,3);
            con = new TContainer(this, val, tab);
        } else if (val.contains("calendar")){
            QCalendarWidget *cal = new QCalendarWidget;
            con = new TContainer(this, val, cal);
        } else {
            qDebug() << "Unknown settings key";
        }

        connect(con, SIGNAL(newGeometry(QString, QRect)), this, SLOT(updateGeometry(QString, QRect)));
        connect(con, SIGNAL(wgtDelete(QString)), this, SLOT(widgetDelete(QString)));

        // move and resize widget
        con->resizeWgt(pos.size());
        con->moveWgt(pos.topLeft());
    }
}

void MainWindow::updateGeometry(const QString &id, const QRect &g)
{    
    foreach (const QString &value, settings->allKeys())
        if(value == id)
            settings->setValue(value, g);
}

void MainWindow::addWidget(const QString &id, QWidget *wgt)
{
    con = new TContainer(this, id, wgt);

    connect(con, SIGNAL(newGeometry(QString,QRect)), this, SLOT(updateGeometry(QString,QRect)));
    connect(con, SIGNAL(wgtDelete(QString)), this, SLOT(widgetDelete(QString)));

    settings->setValue(id, con->geometry());
}

void MainWindow::widgetDelete(const QString &id)
{
    settings->remove(id);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    QString wgtHex = "label_" + randomHex();
    QLabel *lab1 = new QLabel(wgtHex);

    this->addWidget(wgtHex, lab1);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString wgtHex = "table_" + randomHex();
    QTableWidget *wgt = new QTableWidget(5,5);

    this->addWidget(wgtHex, wgt);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString wgtHex = "calendar_" + randomHex();
    QCalendarWidget *cal = new QCalendarWidget;

    this->addWidget(wgtHex, cal);
}

void MainWindow::on_pushButton_4_clicked()
{
    foreach (TContainer *widget, this->findChildren<TContainer *>())
        widget->deleteLater();

    settings->clear();
}
