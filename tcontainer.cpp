#include "tcontainer.h"
#include <QApplication>

#define SQUARE_SIDE 300
#define TRANS_SPEED 20

TContainer::TContainer(QWidget *parent, const QString &wgtId, QWidget *cWidget) : QWidget(parent) {
    this->id = wgtId;
    mode = NONE;
    childWidget = cWidget;
    setAttribute(Qt::WA_DeleteOnClose);
    this->setVisible(true);
    this->setAutoFillBackground(false);

    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setFocus();

    /* place to show new widget */
    QRect rec = QGuiApplication::primaryScreen()->geometry();
    int h = (rec.height() - SQUARE_SIDE) / 2;
    int w = (rec.width() - SQUARE_SIDE) / 2;
    this->move(QPoint(w,h));

    /* widget size */
    this->resize(QSize(SQUARE_SIDE, SQUARE_SIDE));

    vLayout = new QVBoxLayout(this);

    if (cWidget != 0) {
        cWidget->setParent(this);
        cWidget->releaseMouse();

        cWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        vLayout->addWidget(cWidget);
        vLayout->setContentsMargins(0, 0, 0, 0);
    }

    this->setLayout(vLayout);

    m_infocus = true;
    m_showMenu = false;
    m_isEditing = true;

    this->installEventFilter(parent);
}

void TContainer::mouseDoubleClickEvent(QMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton )
        this->childWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void TContainer::moveWgt(QPoint p)
{
    this->move(p);
}

void TContainer::resizeWgt(QSize s)
{
    this->resize(s);
}

void TContainer::finishEditing()
{
    this->childWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

TContainer::~TContainer() {
    emit wgtDelete(this->id);
    delete vLayout;
}

void TContainer::focusInEvent(QFocusEvent *) {
    m_infocus = true;
    this->parentWidget()->installEventFilter(this);
    this->parentWidget()->repaint();
    emit inFocus(true);
}

void TContainer::focusOutEvent(QFocusEvent *) {
    if (!m_isEditing) return;
    if (m_showMenu) return;
    mode = NONE;
    emit outFocus(false);
    m_infocus = false;
}

void TContainer::mousePressEvent(QMouseEvent *e) {
    position = QPoint(e->globalX()-geometry().x(), e->globalY()-geometry().y());

    if (!m_isEditing) return;
    if (!m_infocus) return;

    if (!e->buttons() && Qt::LeftButton) {
        setCursorShape(e->pos());
        return;
    }
}

void TContainer::keyPressEvent(QKeyEvent *e) {
    if (!m_isEditing) return;
    if (e->key() == Qt::Key_Delete) {
        this->deleteLater();
    }
    // Moving container with arrows
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
        QPoint newPos(this->x(),this->y());
        if (e->key() == Qt::Key_Up) newPos.setY(newPos.y() - TRANS_SPEED);
        if (e->key() == Qt::Key_Down) newPos.setY(newPos.y() + TRANS_SPEED);
        if (e->key() == Qt::Key_Left) newPos.setX(newPos.x() - TRANS_SPEED);
        if (e->key() == Qt::Key_Right) newPos.setX(newPos.x() + TRANS_SPEED);
        move(newPos);
    }
    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
        if (e->key() == Qt::Key_Up) resize(width(), height() - TRANS_SPEED);
        if (e->key() == Qt::Key_Down) resize(width(), height() + TRANS_SPEED);
        if (e->key() == Qt::Key_Left) resize(width() - TRANS_SPEED, height());
        if (e->key() == Qt::Key_Right) resize(width() + TRANS_SPEED, height());
    }
    emit newGeometry(this->id, this->geometry());
}

void TContainer::setCursorShape(const QPoint &e_pos) {
    const int diff = 3;
    if (
            //Left-Bottom
            ((e_pos.y() > y() + height() - diff) &&     //Bottom
             (e_pos.x() < x() + diff)) ||               //Left
            //Right-Bottom
            ((e_pos.y() > y() + height() - diff) &&     //Bottom
             (e_pos.x() > x() + width() - diff)) ||     //Right
            //Left-Top
            ((e_pos.y() < y() + diff) &&                //Top
             (e_pos.x() < x() + diff)) ||               //Left
            //Right-Top
            ((e_pos.y() < y() + diff) &&                //Top
             (e_pos.x() > x() + width() - diff))        //Right
            )
    {
        //Left-Bottom
        if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                (e_pos.x() < x() + diff))               //Left
        {
            mode = RESIZEBL;
            setCursor(QCursor(Qt::SizeBDiagCursor));
        }
        //Right-Bottom
        if ((e_pos.y() > y() + height() - diff) &&      //Bottom
                (e_pos.x() > x() + width() - diff))     //Right
        {
            mode = RESIZEBR;
            setCursor(QCursor(Qt::SizeFDiagCursor));
        }
        //Left-Top
        if ((e_pos.y() < y() + diff) &&                 //Top
                (e_pos.x() < x() + diff))               //Left
        {
            mode = RESIZETL;
            setCursor(QCursor(Qt::SizeFDiagCursor));
        }
        //Right-Top
        if ((e_pos.y() < y() + diff) &&                 //Top
                (e_pos.x() > x() + width() - diff))     //Right
        {
            mode = RESIZETR;
            setCursor(QCursor(Qt::SizeBDiagCursor));
        }
    }
    // check cursor horizontal position
    else if ((e_pos.x() < x() + diff) ||                //Left
             ((e_pos.x() > x() + width() - diff)))      //Right
    {
        if (e_pos.x() < x() + diff) {                   //Left
            setCursor(QCursor(Qt::SizeHorCursor));
            mode = RESIZEL;
        } else {                                        //Right
            setCursor(QCursor(Qt::SizeHorCursor));
            mode = RESIZER;
        }
    }
    // check cursor vertical position
    else if (((e_pos.y() > y() + height() - diff)) ||   //Bottom
             (e_pos.y() < y() + diff))                  //Top
    {
        if (e_pos.y() < y() + diff) {                   //Top
            setCursor(QCursor(Qt::SizeVerCursor));
            mode = RESIZET;
        } else {                                        //Bottom
            setCursor(QCursor(Qt::SizeVerCursor));
            mode = RESIZEB;
        }
    } else {
        setCursor(QCursor(Qt::ArrowCursor));
        mode = MOVE;
    }
}

void TContainer::mouseReleaseEvent(QMouseEvent *e) {
    QWidget::mouseReleaseEvent(e);
}

void TContainer::mouseMoveEvent(QMouseEvent *e) {
    QWidget::mouseMoveEvent(e);

    if (!m_isEditing) return;
    if (!m_infocus) return;
    if (!e->buttons() && Qt::LeftButton) {
        QPoint p = QPoint(e->x() + geometry().x(), e->y() + geometry().y());
        setCursorShape(p);
        return;
    }

    if ((mode == MOVE || mode == NONE) && e->buttons() && Qt::LeftButton) {
        QPoint toMove = e->globalPos() - position;
        if (toMove.x() < 0) return;
        if (toMove.y() < 0) return;
        if (toMove.x() > this->parentWidget()->width() - this->width()) return;
        move(toMove);
        emit newGeometry(this->id, this->geometry());
        this->parentWidget()->repaint();
        return;
    }
    if ((mode != MOVE) && e->buttons() && Qt::LeftButton) {
        switch (mode){
        case RESIZETL: {    //Left-Top
            int newwidth = e->globalX() - position.x() - geometry().x();
            int newheight = e->globalY() - position.y() - geometry().y();
            QPoint toMove = e->globalPos() - position;
            resize(this->geometry().width() - newwidth, this->geometry().height() - newheight);
            move(toMove.x(), toMove.y());
            break;
        }
        case RESIZETR: {    //Right-Top
            int newheight = e->globalY() - position.y() - geometry().y();
            QPoint toMove = e->globalPos() - position;
            resize(e->x(), this->geometry().height() - newheight);
            move(this->x(), toMove.y());
            break;
        }
        case RESIZEBL: {    //Left-Bottom
            int newwidth = e->globalX() - position.x() - geometry().x();
            QPoint toMove = e->globalPos() - position;
            resize(this->geometry().width() - newwidth, e->y());
            move(toMove.x(), this->y());
            break;
        }
        case RESIZEB: {     //Bottom
            resize(width(), e->y());
            break;
        }
        case RESIZEL: {     //Left
            int newwidth = e->globalX() - position.x() - geometry().x();
            QPoint toMove = e->globalPos() - position;
            resize(this->geometry().width() - newwidth, height());
            move(toMove.x(), this->y());
            break;
        }
        case RESIZET: {     //Top
            int newheight = e->globalY() - position.y() - geometry().y();
            QPoint toMove = e->globalPos() - position;
            resize(width(), this->geometry().height() - newheight);
            move(this->x(), toMove.y());
            break;
        }
        case RESIZER: {     //Right
            resize(e->x(), height());
            break;
        }
        case RESIZEBR: {    //Right-Bottom
            resize(e->x(), e->y());
            break;
        }
        }
        this->parentWidget()->repaint();
    }
    emit newGeometry(this->id, this->geometry());
}
