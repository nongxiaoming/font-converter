#include "fontconfigframe.h"
#include "ui_fontconfigframe.h"

FontConfigFrame::FontConfigFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontConfigFrame)
{
    ui->setupUi(this);
}

FontConfigFrame::~FontConfigFrame()
{
    delete ui;
}
