#ifndef FONTPREVIEW_H
#define FONTPREVIEW_H

#include <QWidget>
#include <fontconfig.h>

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
   void setFontConfig(FontConfig *config);
   void drawFont(QPainter &painter);
   void drawMainGrid(QPainter& painter);
public slots:
   void bgcolor_changed(QColor c);
   void gridcolor_changed(QColor c);
   void fillcolor_changed(QColor c);
   void showgrid_changed(bool b);
   void gridsize_changed(int size);
   void text_changed(const QString &txt);
private:
    Ui::FontPreview *ui;
    FontConfig *font_config;
    QString disp_text;
    QColor bg_color,grid_color,fill_color;
    int grid_size;
    bool show_grid;
};

#endif // FONTPREVIEW_H
