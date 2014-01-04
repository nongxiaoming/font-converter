#include "fontpreview.h"
#include "ui_fontpreview.h"
#include <QPainter>

FontPreview::FontPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontPreview)
{
    ui->setupUi(this);
}

FontPreview::~FontPreview()
{
    delete ui;
}
void FontPreview::setText(QString &text)
{


}
void FontPreview::setFont(QFont *font)
{


}
void FontPreview::paintEvent(QPaintEvent *event)
{
QPainter paiinter(this);


}
