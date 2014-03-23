#ifndef FONTOUTPUTFRAME_H
#define FONTOUTPUTFRAME_H

#include <QWidget>
#include "fontconfig.h"
namespace Ui {
class FontOutputFrame;
}

class FontOutputFrame : public QWidget
{
    Q_OBJECT

public:
    explicit FontOutputFrame(QWidget *parent = 0);
    void setFontConfig(FontConfig *config);
    ~FontOutputFrame();
public slots:
   void createfont_click();
   void saveFile_click();
   void saveFileName_change(QString);
   void progress(int finish,int total);
private:
    Ui::FontOutputFrame *ui;
    FontConfig *font_config;
};

#endif // FONTOUTPUTFRAME_H
