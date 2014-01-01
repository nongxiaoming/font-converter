#include "fontconfigframe.h"
#include "ui_fontconfigframe.h"
#include <QDebug>

FontConfigFrame::FontConfigFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontConfigFrame)
{
    ui->setupUi(this);
    this->FontConfigFrame_Init ();
}

FontConfigFrame::~FontConfigFrame()
{
    delete ui;
}
void FontConfigFrame::fontSetting ()
{
         bool ok;
        QFont font=this->font_dialog->getFont (&ok);
         if(true==ok)
         {
             QString family=font.family ();
             qDebug()<<tr("Font Family:%1").arg (family);
             ui->family_label->setText (tr("Family:%1").arg (family));
             int size=font.pointSize ();
             //qDebug()<<"Font weight:"<<weight;
             ui->size_label->setText (tr("Size:%1").arg (size));
         }
}
void FontConfigFrame::FontConfigFrame_Init ()
{
    this->font_dialog = new QFontDialog(this);

QObject::connect (ui->pushButton,SIGNAL(clicked()),this,SLOT(fontSetting()));
}
