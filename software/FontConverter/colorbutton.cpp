#include "colorbutton.h"
#include <QPainter>
#include <QColorDialog>
ColorButton::ColorButton(QWidget *parent) :
    QLabel(parent)
{
}


void ColorButton::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(),m_color);
    painter.drawRect(rect());
}


void ColorButton::mouseReleaseEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);
    QColorDialog cd(color(),parentWidget());
    if (cd.exec()==QDialog::Accepted) {
        setColor(cd.selectedColor());
        repaint();
        colorChanged(color());
        colorChanged();
    }
}
