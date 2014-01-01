#ifndef FONTCONFIGFRAME_H
#define FONTCONFIGFRAME_H

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

private:
    Ui::FontConfigFrame *ui;
};

#endif // FONTCONFIGFRAME_H
