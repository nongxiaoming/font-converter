#ifndef FONTCONFIGFRAME_H
#define FONTCONFIGFRAME_H
#include <QFontDialog>
#include <QWidget>

namespace Ui {
class FontConfigFrame;
}

class FontConfigFrame : public QWidget
{
    Q_OBJECT

public:
    explicit FontConfigFrame(QWidget *parent = 0);
    ~FontConfigFrame();
public slots:
    void fontSetting();
private:
    Ui::FontConfigFrame *ui;
    QFontDialog *font_dialog;
    void FontConfigFrame_Init();

};

#endif // FONTCONFIGFRAME_H
