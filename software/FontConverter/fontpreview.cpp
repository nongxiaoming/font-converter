#include "fontpreview.h"
#include "ui_fontpreview.h"
#include <QPainter>


FontPreview::FontPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontPreview)
{
    ui->setupUi(this);
    this->setFixedHeight(800);
    this->bg_color = QColor(120, 120, 120);
    this->fill_color = QColor(100, 200, 230);
    this->grid_color=QColor(68, 116, 175, 255);
    this->grid_size=6;
    this->show_grid=true;
}

FontPreview::~FontPreview()
{
    delete ui;
}
void FontPreview::setText(QString &text)
{
this->disp_text=text;
    this->update();
}
void FontPreview::setFontConfig(FontConfig *config)
{
    this->font_config = config;
    QObject::connect(this->font_config,SIGNAL(textChanged()),this,SLOT(update()));
    QObject::connect(this->font_config,SIGNAL(sizeChanged()),this,SLOT(update()));
}
void FontPreview::paintEvent(QPaintEvent*)
{
    QPixmap pixmap(width(), height());
    QPainter painter;
    painter.begin(&pixmap);
    drawMainGrid(painter);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

}
void FontPreview::bgcolor_changed (QColor c)
{
    this->bg_color=c;
    this->update ();
}
void FontPreview::fillcolor_changed (QColor c)
{
    this->fill_color=c;
    this->update ();
}
void FontPreview::gridcolor_changed (QColor c)
{
    this->grid_color=c;
    this->update ();
}
void FontPreview::showgrid_changed(bool b)
{
    this->show_grid=b;
    this->update();
}
void FontPreview::gridsize_changed(int size)
{
    this->grid_size=size;
    this->update();
}
void FontPreview::text_changed(const QString &txt)
{
    this->disp_text=txt;
    this->update();
}
void FontPreview::drawMainGrid(QPainter &painter)
{
    Q_ASSERT(grid_size > 0);
    QRect rectf = this->rect();
     int xgrid_count = rectf.width() / grid_size;
    if(xgrid_count/this->font_config->width()<5)
    {
        xgrid_count=5*this->font_config->width();
        this->setFixedWidth(xgrid_count*grid_size);
    }
    int ygrid_count = rectf.height() / grid_size;
    painter.save();
    painter.setBrush(Qt::NoBrush);
    if(this->font_config->isReverse())
    {
        painter.fillRect(rectf,this->bg_color);
    }else{
    painter.fillRect(rectf,this->bg_color);
    }
    QImage fontImage;
    if (this->font_config->isLSB())
        fontImage = QImage(xgrid_count, ygrid_count, QImage::Format_MonoLSB);
    else
        fontImage = QImage(xgrid_count, ygrid_count, QImage::Format_Mono);

    QPainter paintCanvas(&fontImage);
    paintCanvas.setPen(Qt::white);//设置白色画笔
    paintCanvas.setFont(this->font_config->font());
    paintCanvas.fillRect(fontImage.rect(), Qt::black);//设置黑色背景
    int index = 0;
    for (int y = 0; y < ygrid_count / this->font_config->height(); y++)
    {
        for (int x = 0; x < ygrid_count / (this->font_config->width() / 2);)
        {
            if (index == font_config->text().count())
                break;
            QChar ch = this->font_config->text().at(index);
            QRectF cellRectF(x * (this->font_config->width() / 2), y * this->font_config->height(), this->font_config->width(), this->font_config->height());
            paintCanvas.drawText(cellRectF, ch);
            if (ch.unicode() > 0xff)
            {
                x += 2;
            }
            else
            {
                x++;
            }
            index++;

        }
    }

    for (int col = 0; col < fontImage.height(); ++col)
    {
        const uchar *pLineBits = fontImage.scanLine(col);
        for (int row = 0; row < fontImage.width(); row++)
        {
            bool bitOn = false;
            if (this->font_config->isLSB())
                bitOn = (*(pLineBits + row / 8) & (0x01 << row % 8)) != 0;
            else
                bitOn = (*(pLineBits + row / 8) & (0x80 >> row % 8)) != 0;

            int x = rectf.left() + row * grid_size;
            int y = rectf.top() + col * grid_size;
            QRectF cellRectF(x+1, y+1, grid_size-1, grid_size-1);

            if (this->font_config->isReverse() == false)
            {
                if (bitOn)
                {
                    painter.fillRect(cellRectF, this->fill_color);
                }
                else
                {
                    painter.fillRect(cellRectF, this->bg_color);
                }
            }
            else
            {
                if (bitOn)
                {
                     painter.fillRect(cellRectF, this->bg_color);
                }
                else
                {
                     painter.fillRect(cellRectF, this->fill_color);
                }
            }
        }
    }
    //绘制网格
    if(this->show_grid){
    painter.setPen(this->grid_color);
    //绘制竖线
    for (int x = rectf.left(); x < rectf.right(); x += grid_size)
    {
        painter.drawLine(x, rectf.top(), x, rectf.bottom());
    }
    //绘制横线
    for (int y = rectf.top(); y < rectf.bottom(); y += grid_size)
    {
      painter.drawLine(rectf.left(), y, rectf.right(), y);
    }
     painter.setPen(QColor(255, 0, 128, 128));
     for (int x = rectf.left(); x < rectf.right(); x += grid_size*(this->font_config->width() / 2))
     {
         painter.drawLine(x, rectf.top(), x, rectf.bottom());
     }
     for (int y = rectf.top(); y < rectf.bottom(); y += grid_size*this->font_config->height())
     {
          painter.drawLine(rectf.left(), y, rectf.right(), y);
     }
    }
    painter.restore();
}
