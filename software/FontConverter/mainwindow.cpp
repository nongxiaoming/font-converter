#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QMetaProperty>
#include <QDebug>
#include <QTextCodec>
#include <QTextEncoder>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->MainWindow_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::MainWindow_init()
{
     font_config = new FontConfig(this);
     font_config->normalize();
     ui->charactersFrame->setConfig(font_config);
     ui->fontConfigFrame->setFontConfig(font_config);
     ui->fontPreviewFrame->setFontConfig(font_config);
     ui->fontOutputFrame->setFontConfig (font_config);
     this->mainToolBar_init();
     ui->bgcolor_Btn->setColor (QColor(120, 120, 120));
     ui->fillcolor_Btn->setColor (QColor(100, 200, 230));
     ui->gridcolor_Btn->setColor (QColor(68, 116, 175, 255));
     QObject::connect (ui->bgcolor_Btn,SIGNAL(colorChanged(QColor)),ui->fontPreviewFrame,SLOT(bgcolor_changed(QColor)));
     QObject::connect (ui->fillcolor_Btn,SIGNAL(colorChanged(QColor)),ui->fontPreviewFrame,SLOT(fillcolor_changed(QColor)));
     QObject::connect (ui->gridcolor_Btn,SIGNAL(colorChanged(QColor)),ui->fontPreviewFrame,SLOT(gridcolor_changed(QColor)));
     QObject::connect (ui->showgrid_checkBox,SIGNAL(toggled(bool)),ui->fontPreviewFrame,SLOT(showgrid_changed(bool)));
     QObject::connect(ui->gridsize_Slider,SIGNAL(valueChanged(int)),ui->fontPreviewFrame,SLOT(gridsize_changed(int)));
     //菜单信号绑定
      QObject::connect(ui->action_import_text,SIGNAL(triggered()),ui->charactersFrame,SLOT(on_pushButtonImport_clicked()));
      QObject::connect(ui->action_export_text,SIGNAL(triggered()),ui->charactersFrame,SLOT(on_pushButtonExport_clicked()));
        QObject::connect(ui->action_text_default,SIGNAL(triggered()),ui->charactersFrame,SLOT(on_pushButtonDefault_clicked()));
         QObject::connect(ui->actionSelect_From_Charsmap,SIGNAL(triggered()),ui->charactersFrame,SLOT(on_pushButton_SelectFromCharsMap_clicked()));
          QObject::connect(ui->actionFont,SIGNAL(triggered()),ui->fontConfigFrame,SLOT(fontSetting()));
           QObject::connect(ui->action_save_font,SIGNAL(triggered()),ui->fontOutputFrame,SLOT(saveFile_click()));
             //QObject::connect(ui->a,SIGNAL(clicked()),ui->fontOutputFrame,SLOT(createfont_click()));
}
void MainWindow::mainToolBar_init()
{
 ui->mainToolBar->addWidget(ui->open_chars_toolBtn);
 QObject::connect(ui->open_chars_toolBtn,SIGNAL(clicked()),ui->charactersFrame,SLOT(on_pushButtonImport_clicked()));
 ui->mainToolBar->addWidget(ui->save_chars_toolBtn);
  QObject::connect(ui->save_chars_toolBtn,SIGNAL(clicked()),ui->charactersFrame,SLOT(on_pushButtonExport_clicked()));
 ui->mainToolBar->addWidget(ui->load_defaultchars_toolBtn);
  QObject::connect(ui->load_defaultchars_toolBtn,SIGNAL(clicked()),ui->charactersFrame,SLOT(on_pushButtonDefault_clicked()));
 ui->mainToolBar->addWidget(ui->open_charsmap_toolBtn);
 QObject::connect(ui->open_charsmap_toolBtn,SIGNAL(clicked()),ui->charactersFrame,SLOT(on_pushButton_SelectFromCharsMap_clicked()));
 ui->mainToolBar->addWidget(ui->font_setting_toolBtn);
 QObject::connect(ui->font_setting_toolBtn,SIGNAL(clicked()),ui->fontConfigFrame,SLOT(fontSetting()));
 ui->mainToolBar->addWidget(ui->save_to_toolBtn);
  QObject::connect(ui->save_to_toolBtn,SIGNAL(clicked()),ui->fontOutputFrame,SLOT(saveFile_click()));
 ui->mainToolBar->addWidget(ui->convert_toolBtn);
  QObject::connect(ui->convert_toolBtn,SIGNAL(clicked()),ui->fontOutputFrame,SLOT(createfont_click()));
 //ui->showgrid_checkBox->setCheckState(Qt::PartiallyChecked);
}

void MainWindow::saveConfig(QSettings& settings,
                             const QString& name,
                             const QObject* object) {
    settings.beginGroup(name);
    const QMetaObject *metaobject = object->metaObject();
     int count = metaobject->propertyCount();
     for (int i=0; i<count; ++i) {
         QMetaProperty metaproperty = metaobject->property(i);
         const char *name = metaproperty.name();
         QVariant value = object->property(name);
         settings.setValue(name,value);
     }
    settings.endGroup();
}
void MainWindow::readConfig(QSettings& settings,
                             const QString& name,
                             QObject* object) {
    settings.beginGroup(name);
    const QMetaObject *metaobject = object->metaObject();
     int count = metaobject->propertyCount();
     for (int i=0; i<count; ++i) {
         QMetaProperty metaproperty = metaobject->property(i);
         const char *name = metaproperty.name();
         if (settings.contains(name))
             object->setProperty(name,settings.value(name));
      }
    settings.endGroup();
}
void MainWindow::Langli_change()
{

}
