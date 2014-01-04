#ifndef FONTCONFIGFRAME_H
#define FONTCONFIGFRAME_H
#include <QFontDialog>
#include <QWidget>
#include "fontconfig.h"

namespace Ui {
class FontConfigFrame;
}

class FontConfigFrame : public QWidget
{
    Q_OBJECT

public:
    explicit FontConfigFrame(QWidget *parent = 0);
    ~FontConfigFrame();
    void setFontConfig(FontConfig *config);
public slots:
    void fontSetting();
private:
    FontConfig *font_config;
    Ui::FontConfigFrame *ui;
    QFontDialog *font_dialog;
    void FontConfigFrame_Init();

};

#endif // FONTCONFIGFRAME_H
