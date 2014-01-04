#include "fontconfigframe.h"
#include "ui_fontconfigframe.h"
#include <QDebug>
#include <QPaintDevice>

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
        QFont font=this->font_dialog->getFont (&ok,this->font_config->font(),this);
        this->font_config->setFont(font);
         if(true==ok)
         {
             QString family=font.family ();
             qDebug()<<tr("Font Family:%1").arg (family);
             ui->family_label->setText (tr("Family:%1").arg (family));
             int size=font.pointSize ();
             //qDebug()<<"Font weight:"<<weight;
             ui->size_label->setText (tr("Size:%1").arg (size));
             //qDebug()<<tr("Font Style:%1").arg (font.StyleItalic);

             if(ui->checkBox->isChecked())
             {
               int dpi_x= QPaintDevice::logicalDpiX();
               int dpi_y= QPaintDevice::logicalDpiY();
               int width=  font.pointSize()*dpi_x/72;
               int height=  font.pointSize()*dpi_y/72;
               font_config->setWidth(width);
               font_config->setWidth(height);
               ui->font_height_spinBox->setValue(height);
               ui->font_width_spinBox->setValue(width);
             }

         }
}
void FontConfigFrame::setFontConfig(FontConfig *config)
{
    this->font_config=config;
}
void FontConfigFrame::FontConfigFrame_Init ()
{
    this->font_dialog = new QFontDialog(this);
   QObject::connect (ui->pushButton,SIGNAL(clicked()),this,SLOT(fontSetting()));
}
