#ifndef TCONTAINER_H
#define TCONTAINER_H

#include <QWidget>
#include <QMouseEvent>
#include <QtGui>
#include <QVBoxLayout>
#include <QMenu>

enum modes{
    NONE = 0,
    MOVE = 1,
    RESIZETL = 2,
    RESIZET = 3,
    RESIZETR = 4,
    RESIZER = 5,
    RESIZEBR = 6,
    RESIZEB = 7,
    RESIZEBL = 8,
    RESIZEL = 9
};

class TContainer : public QWidget {
    Q_OBJECT

public:
    TContainer(QWidget *parent, const QString &wgtId, QWidget *cWidget = 0);
    void moveWgt(QPoint p);
    void resizeWgt(QSize s);
    ~TContainer();
    QWidget *childWidget;

protected:
    QString id;
    int mode;
    QPoint position;
    QVBoxLayout* vLayout;

    void setCursorShape(const QPoint &e_pos);
    void keyPressEvent(QKeyEvent*);
    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);

    bool m_infocus;
    bool m_showMenu;
    bool m_isEditing;

signals:
    void inFocus(bool mode);
    void outFocus(bool mode);
    void newGeometry(const QString &id, const QRect &rect);
    void wgtDelete(const QString &id);
};

#endif //TCONTAINER_H
