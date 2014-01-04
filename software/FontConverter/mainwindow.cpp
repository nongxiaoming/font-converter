#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QMetaProperty>

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
    bool font_config_block = font_config->blockSignals(true);
     font_config->normalize();
     ui->frameCharacters->setConfig(font_config);
     ui->fontConfigFrame->setFontConfig(font_config);
    this->mainToolBar_init();
}
void MainWindow::mainToolBar_init()
{
 QToolButton *import_charlist,*export_charlist,*output_bmp;
 import_charlist = new QToolButton(ui->centralWidget);
 import_charlist->setText(tr("import char list"));
 import_charlist->setIcon(QIcon(":/resource/image/icon_48.png"));
 ui->mainToolBar->addWidget(import_charlist);

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
