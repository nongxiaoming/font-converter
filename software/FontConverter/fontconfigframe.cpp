#include "fontconfigframe.h"
#include "ui_fontconfigframe.h"
#include <QDebug>
#include <QPaintDevice>
#include <QFontInfo>

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
            QFontMetrics *fontMetrics=new QFontMetrics(font);
             QString family=font.family();
                 qDebug()<<tr("Font Family:%1").arg (family);
             ui->family_label->setText (tr("Family:%1").arg (family));
             int size=font.pointSize ();
             //qDebug()<<"Font weight:"<<weight;
             qDebug()<<tr("Font width:%1").arg(QString::number(fontMetrics->width(tr("赢"))));
             qDebug()<<tr("Font height:%1").arg(QString::number(fontMetrics->height()));
             qDebug()<<tr("Font maxwidth:%1").arg(QString::number(fontMetrics->maxWidth()));
             ui->font_size_spinBox->setValue(size);
             //qDebug()<<tr("Font Style:%1").arg (font.StyleItalic);

             if(ui->AutoSize_checkBox->isChecked())
             {
               int width=fontMetrics->maxWidth();
               int height=fontMetrics->height();
               font_config->setWidth(width);
               font_config->setHeight(height);
               ui->font_height_spinBox->setValue(height);
               ui->font_width_spinBox->setValue(width);
             }
             delete fontMetrics;
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
   QObject::connect(ui->Positive_radiobtn,SIGNAL(clicked()),this,SLOT(Positive_click()));
   QObject::connect(ui->Reverse_radiobtn,SIGNAL(clicked()),this,SLOT(Positive_click()));
   QObject::connect (ui->font_width_spinBox,SIGNAL(valueChanged(int)),this,SLOT(font_width_change(int)));
   QObject::connect (ui->font_height_spinBox,SIGNAL(valueChanged(int)),this,SLOT(font_height_change(int)));
   QObject::connect (ui->font_size_spinBox,SIGNAL(valueChanged(int)),this,SLOT(font_size_change(int)));
}
void FontConfigFrame::font_width_change (int value)
{
    this->font_config->setWidth (value);
    if(ui->AutoSize_checkBox->isChecked())
    {
        QFont font=this->font_config->font();
        font.setPixelSize(value);
        this->font_config->setFont(font);
         QFontMetrics *fontMetrics=new QFontMetrics(font);
         int height=fontMetrics->height();
         font_config->setHeight(height);
         ui->font_height_spinBox->setValue(height);
         qDebug()<<tr("Font size:%1").arg(QString::number(font.pointSize()));
         //ui->font_size_spinBox->setValue(font.pointSize());
         delete fontMetrics;
    }
}
void FontConfigFrame::font_height_change (int value)
{
    this->font_config->setHeight (value);
    if(ui->AutoSize_checkBox->isChecked())
    {
        QFont font=this->font_config->font();
        font.setPixelSize(value);
        this->font_config->setFont(font);
         QFontMetrics *fontMetrics=new QFontMetrics(font);
         int width=fontMetrics->maxWidth();
         font_config->setWidth(width);
         ui->font_width_spinBox->setValue(width);
         //ui->font_size_spinBox->setValue(font.weight());
         delete fontMetrics;
    }
}
void FontConfigFrame::font_size_change (int value)
{
    QFont font=this->font_config->font();
    font.setPointSize(value);
    this->font_config->setFont(font);
    if(ui->AutoSize_checkBox->isChecked())
    {
         QFontMetrics *fontMetrics=new QFontMetrics(font);
         int width=fontMetrics->maxWidth();
         int height=fontMetrics->height();
         font_config->setWidth(width);
         ui->font_height_spinBox->setValue(height);
         ui->font_width_spinBox->setValue(width);
          this->font_config->setHeight (height);
         delete fontMetrics;
    }
}
void FontConfigFrame::Positive_click()
{
    if(ui->Positive_radiobtn->isChecked())
    {
        this->font_config->setReverse(false);
    }else
    {
        this->font_config->setReverse(true);
    }
}
