
#include "charsselectwidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QToolTip>

static  int cell_size = 24;
static const int columns = 16;

CharsSelectWidget::CharsSelectWidget(QWidget *parent) :
    QWidget(parent) , m_codes_begin(0x0000),m_codes_end(0xFFFF)
{
    m_codes = 0;
    m_track_mouse = false;
    m_track_erase = false;
    setMouseTracking(true);
}


//QSize CharsSelectWidget::sizeHint() const {
   // cell_size=rect().width()/16;
   // return QSize(columns*cell_size, ((m_codes_end-m_codes_begin)/columns+1)*cell_size);
//}


void CharsSelectWidget::setRange(uint begin,uint end) {
    m_codes_begin = begin;
    m_codes_end = end;
   // setMinimumSize(sizeHint());
   // setMaximumSize(sizeHint());
   // adjustSize();
    update();
}

void CharsSelectWidget::paintEvent(QPaintEvent *event) {
    //绘制控件本身
    QPainter painter(this);
    cell_size=rect().width()/columns;
    int h=((m_codes_end-m_codes_begin)/columns+1)*cell_size;
    this->setFixedHeight(h);
    //填充白色背景
    painter.fillRect(event->rect(),QBrush(Qt::white));
    //检查字符表字符个数不为0
    Q_ASSERT(m_codes!=0);
    QRect redrawRect = event->rect();
    int beginRow = redrawRect.top()/cell_size;
    int endRow = redrawRect.bottom()/cell_size;
    int beginColumn = redrawRect.left()/cell_size;
    int endColumn = redrawRect.right()/cell_size;

    painter.setPen(QPen(Qt::gray));
    for (int row = beginRow; row <= endRow; ++row) {
        for (int column = beginColumn; (column <= endColumn ) && (column < columns); ++column) {
            uint key =  m_codes_begin+row*columns + column;
            if ( key <= m_codes_end) {
                if (m_codes->contains(key))
                    painter.fillRect(column*cell_size, row*cell_size, cell_size, cell_size,QBrush(Qt::lightGray));
                painter.drawRect(column*cell_size, row*cell_size, cell_size, cell_size);
            }
        }
    }

    QFontMetrics fontMetrics(painter.font());
     painter.setPen(QPen(Qt::black));
     for (int row = beginRow; row <= endRow; ++row) {

         for (int column = beginColumn; (column <= endColumn ) && (column < columns); ++column) {

             uint key = m_codes_begin+row*columns + column;
             if (key<=m_codes_end) {
                 painter.setClipRect(column*cell_size, row*cell_size, cell_size, cell_size);

                 painter.drawText(column*cell_size + (cell_size / 2) - fontMetrics.width(QChar(key))/2,
                                  row*cell_size + 4 + fontMetrics.ascent(),
                                  QString(QChar(key)));
             }
         }
     }
}


void CharsSelectWidget::mousePressEvent(QMouseEvent *event)
{
     if (event->button() == Qt::LeftButton) {
         if (event->x()<0) return;
         if (event->x()>=width()) return;
         if (event->y()<0) return;
         if (event->y()>=height()) return;

         m_select_last_code = m_select_begin_code = m_codes_begin + (event->y()/cell_size)*columns + event->x()/cell_size;
         if (QChar(m_select_begin_code).category() != QChar::Other_NotAssigned) {
             m_track_mouse = true;
             if (m_codes->contains(m_select_begin_code)) {
                 m_codes->erase(m_codes->find(m_select_begin_code));
                 codesChanged(m_select_begin_code,false);
                 m_track_erase = true;
             } else {
                 m_codes->insert(m_select_begin_code);
                 codesChanged(m_select_begin_code,true);
                 m_track_erase = false;
             }
         } else {
             m_track_mouse = false;
        }
         update();
     }
     else
         QWidget::mousePressEvent(event);
}


void CharsSelectWidget::mouseReleaseEvent(QMouseEvent *event) {
     if (event->button() == Qt::LeftButton)
        m_track_mouse = false;
     else
        QWidget::mouseReleaseEvent(event);
}

void CharsSelectWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->x()<0) return;
    if (event->x()>=width()) return;
    if (event->y()<0) return;
    if (event->y()>=height()) return;
    uint code = m_codes_begin +(event->y()/cell_size)*columns + event->x()/cell_size;

    if (m_track_mouse) {
        if (code!=m_select_last_code) {
            if (code!=m_select_begin_code) {
                /*uint from = qMin(m_select_begin_code,code);
                uint to = qMax(m_select_begin_code,code);*/
                /*for (uint c = from;c<=to;c++)*/ {
                    if (m_track_erase) {
                        QSet<uint>::Iterator i=m_codes->find(code);
                        if ( i!=m_codes->end()) {
                            m_codes->erase(i);
                            codesChanged(code,false);
                        }
                    } else {
                        m_codes->insert(code);
                        codesChanged(code,true);
                    }
                }
            }
            m_select_last_code = code;
            update();
        }
    } else {
        QString scode = QString::number(code, 16);
        while (scode.length()<4) {
            scode=QString("0")+scode;
        }
        QString text = QString::fromLatin1("<p>Character: <span>")
                           + QChar(code)
                           + QString::fromLatin1("</span><p>Value: U+")
                           + scode;
        QToolTip::showText(event->globalPos(), text, this);
    }
}
