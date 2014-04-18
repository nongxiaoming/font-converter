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
    void Positive_click();
    void font_width_change(int value);
    void font_height_change(int value);
    void font_size_change(int value);
private:
    FontConfig *font_config;
    Ui::FontConfigFrame *ui;
    QFontDialog *font_dialog;
    void FontConfigFrame_Init();

};

#endif // FONTCONFIGFRAME_H
