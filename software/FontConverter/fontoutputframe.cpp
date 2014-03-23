#include "fontoutputframe.h"
#include "ui_fontoutputframe.h"
#include "fontcreator.h"
#include <QFileDialog>

FontOutputFrame::FontOutputFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontOutputFrame)
{
    ui->setupUi(this);
    QObject::connect (ui->convert_btn,SIGNAL(clicked()),this,SLOT(createfont_click()));
    QObject::connect (ui->savefile_btn,SIGNAL(clicked()),this,SLOT(saveFile_click()));
    QObject::connect (ui->filename_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(saveFileName_change(QString)));
}


FontOutputFrame::~FontOutputFrame()
{
    delete ui;
}
void FontOutputFrame::setFontConfig (FontConfig *config)
{
    this->font_config=config;
}
void FontOutputFrame::createfont_click ()
{

    if(ui->msb_radiobtn->isChecked())
    {
        this->font_config->setLSB(false);
    }else
    {
        this->font_config->setLSB(true);
    }
    FontCreator creater(this,this->font_config);
    connect(&creater, &FontCreator::progress, this, & FontOutputFrame::progress);
    creater.start();

}
void FontOutputFrame::saveFile_click ()
{
   QString fileName=QFileDialog::getSaveFileName(this,tr("保存文件"),tr("./myfont.c"), tr("font code (*.c)"));
   if(fileName==tr(""))
   {
       return;
   }
   ui->filename_lineEdit->setText(fileName);
   this->font_config->setSaveFontName(fileName);

}
void FontOutputFrame::saveFileName_change(QString txt)
{
     this->font_config->setSaveFontName(txt);
}
void FontOutputFrame::progress(int finish, int total)
{
    int val =(finish*100)/total;
    ui->progressBar->setValue(val);
}
