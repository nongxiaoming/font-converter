#ifndef FONTPREVIEW_H
#define FONTPREVIEW_H

#include <QWidget>

namespace Ui {
class FontPreview;
}

class FontPreview : public QWidget
{
    Q_OBJECT
protected:
    virtual void	paintEvent ( QPaintEvent * event );
public:
    explicit FontPreview(QWidget *parent = 0);
    ~FontPreview();
   void setText(QString &text);
   void setFont(QFont *font);
private:

    Ui::FontPreview *ui;
};

#endif // FONTPREVIEW_H
