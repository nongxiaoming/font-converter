#ifndef FONTCREATOR_H
#define FONTCREATOR_H

#include <QObject>
#include "fontconfig.h"
#include <QThread>
#include "fontpage.h"

class Converter : public QObject

{
    Q_OBJECT
public :
    explicit Converter(QObject *parent = 0);
    explicit Converter(QFont font,int width,int height,bool re,bool lsb);
public slots:
   void Convert(const QString &str);
signals:
    void progress(int finish,int total);
    void finished(QString &result);
private:
    int font_width;
    int font_heigh;
    int font_ascent;
    bool isReverse;
    bool isLSB;
    QFont chFont;
    QString result;
    QList<FontPage *> page_list;
    QChar* gb2312_qsort(QString &str);
    void page_qsort();
    void Convert_One_Char(QChar &ch);
};

class FontCreator : public QObject
{
    Q_OBJECT
public:
    explicit FontCreator(QObject *parent = 0);
    explicit FontCreator(QObject *parent,FontConfig *config);
    void setFontConfig(FontConfig *config);
    void start();
signals:
    void start_convert(const QString &str);
    void progress(int finish,int total);
public slots:
    void finished(QString &result);
private :
    QThread ConvertThread;

    FontConfig *font_config;
};

#endif // FONTCREATOR_H
