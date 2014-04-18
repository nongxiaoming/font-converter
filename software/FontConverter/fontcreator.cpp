#include "fontcreator.h"
#include <QImage>
#include <QPainter>
#include <QTextCodec>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>

#define NEW_LINE tr("\n")
#define FILE_HEAHER tr("#include <ugl/driver/font/udbmffnt.h>")
Converter::Converter(QObject *parent) :
    QObject(parent)
{

}
Converter::Converter(QFont font, int width, int height, bool re, bool lsb) :
    QObject()
{
    this->font_width = width;
    this->font_heigh = height;
    this->chFont = QFont(font);
    this->isReverse = re;
    this->isLSB = lsb;
    QFontMetrics *fontMetrics = new QFontMetrics(this->chFont);
    this->font_ascent = fontMetrics->ascent();
}
//冒泡法排序
QChar *Converter::gb2312_qsort(QString &str)
{
    QTextCodec *codec = QTextCodec::codecForName("gb2312");
    QChar temp = 0;
    quint16 str1_code = 0, str2_code = 0;
    QByteArray data;
    int total = str.length() * 2;
    QChar *ch = str.data();
    for (int i = 0; i < str.length(); i++)
    {
        for (int j = 0; j < str.length() - i; j++)
        {
            data = codec->fromUnicode(*(ch + j));
            if (data.length() < 2)
            {
                str1_code = (quint16)(data.at(0));
            }
            else
            {
                str1_code = ((quint16)data.at(1) << 8 | data.at(0));
            }
            data = codec->fromUnicode(*(ch + j + 1));
            if (data.length() < 2)
            {
                str2_code = (quint16)(data.at(0));
            }
            else
            {
                str2_code = ((quint16)data.at(1) << 8 | data.at(0));
            }
            if (str1_code > str2_code)
            {
                temp = *(ch + j);
                *(ch + j) = *(ch + j + 1);
                *(ch + j + 1) = temp;
            }
        }
        emit progress(i, total);
    }
    // for(int i=0;i<str->length();i++){qDebug()<<*(ch+i);}
    return ch;
    // qDebug()<<*str;
}
void Converter::page_qsort()
{
    for (int i = 0; i < page_list.count(); i++)
    {
        for (int j = 0; j < page_list.count() - 1; j++)
        {
            if (page_list.at(j)->page() > page_list.at(j + 1)->page())
            {
                page_list.move(j, j + 1);
            }
        }
    }
}
void Converter::Convert(const QString &str)
{
    QString txt(str);
    int total = str.length();

    QChar *ch = txt.data(); //gb2312_qsort(txt);
    for (int i = 0; i < str.length(); i++)
    {
        Convert_One_Char(*(ch + i));
        emit progress(i, total);
    }
    QString pageArray_str;
    pageArray_str.append(tr("UGL_LOCAL const unsigned char * const pageArray[] = "));
    pageArray_str.append(NEW_LINE);
    pageArray_str.append(tr("    {"));
    pageArray_str.append(NEW_LINE);
    //页排序
    page_qsort();
    int index = 0;
    foreach(FontPage * fpage, page_list)
    {
        result.append(tr("UGL_LOCAL const unsigned char page%1Data[] =").arg(QString::number(index)));
        result.append(NEW_LINE);
        result.append(tr("    {"));
        result.append(NEW_LINE);
        result.append(fpage->fontData());
        result.append(tr("       0,0,0,0 /*end of page%1*/").arg(QString::number(index)));
        result.append(NEW_LINE);
        result.append(tr("    };"));
        result.append(NEW_LINE);
        result.append(NEW_LINE);
        pageArray_str.append(tr("    page%1Data,").arg(QString::number(index)));
        pageArray_str.append(NEW_LINE);
        index++;
    }
    pageArray_str.append(tr("    UGL_NULL"));
    pageArray_str.append(NEW_LINE);
    pageArray_str.append(tr("    };"));
    pageArray_str.append(NEW_LINE);
    result.append(pageArray_str);
    emit progress(total, total);
    emit finished(result);
}
void Converter::Convert_One_Char(QChar &ch)
{
    int font_w = this->font_width;
    quint16 unicode = ch.unicode();
    quint8 page = (quint8)((unicode >> 8) & 0xff);
    quint8 index = (quint8)((unicode) & 0xff);

    //生成注释
    QString text = QString("    /*font *- %1(0x%2) -*/" + NEW_LINE)
                   .arg(ch).arg(ch.unicode(), 4, 16, QLatin1Char('0'));
    //QString text = QString("    /*font *- %1(0x%2%3) -*/"+NEW_LINE)
    //            .arg(ch).arg(page,2,16,QLatin1Char('0')).arg (index,2,16,QLatin1Char('0'));
    text.append(tr("       0x%1 ,  /* page */").arg(page, 2, 16, QLatin1Char('0')) + NEW_LINE);
    text.append(tr("       0x%1 ,  /* index */").arg(index, 2, 16, QLatin1Char('0')) + NEW_LINE);
    text.append(tr("       0    ,  /* size (MSB) */") + NEW_LINE);
    if (page == 0)
    {
        font_w = font_w / 2;
    }
    QImage fontImage;
    if (this->isLSB)
    {
        fontImage = QImage(font_w, font_heigh, QImage::Format_MonoLSB);
    }
    else
    {
        fontImage = QImage(font_w, font_heigh, QImage::Format_Mono);
    }
    QPainter painter(&fontImage);
    painter.setPen(Qt::white); //设置白色画笔
    painter.setFont(this->chFont);
    painter.fillRect(fontImage.rect(), Qt::black);//设置黑色背景
    painter.drawText(fontImage.rect(), Qt::AlignCenter, QChar(ch));


    int useBytes = (font_w + 7) / 8;  // 计算存储用到的字节数
    int totalBytes = (font_w * font_heigh + 7) / 8;
    text.append(tr("       %1   ,  /* size (LSB) */").arg(QString::number(totalBytes + 4)) + NEW_LINE);
    text.append(tr("       %1   ,  /* width */").arg(QString::number(font_w)) + NEW_LINE);
    text.append(tr("       %1   ,  /* height */").arg(QString::number(font_heigh)) + NEW_LINE);
    text.append(tr("       %1   ,  /* ascent */").arg(QString::number(font_ascent)) + NEW_LINE);
    // QByteArray bytes;
    text.append(tr("      "));
    //规则方式取模，宽为8的整数倍
    if ((font_w % 8) == 0)
    {
        for (int line = 0; line < fontImage.height(); ++line)
        {
            const uchar *pLineBits = fontImage.scanLine(line);
            for (int i = 0; i < useBytes; i++)
            {
                uchar byte = *(pLineBits + i);
                if (this->isReverse)
                {
                    byte ^= 0xFF;
                }
                text.append(tr("0x%1").arg((quint8)byte, 2, 16, QLatin1Char('0')));
                text.append(",");
            }
        }
    }
    else
    {  int count=0;
        uchar byte=0;
        QRgb c_index;
        for (int y = 0; y < fontImage.height(); y++)
        {
          for(int x=0;x<fontImage.width();x++)
          {
              c_index=fontImage.pixel(x,y);
              //qDebug()<<tr("%1").arg(c_index,4)
              if((c_index&RGB_MASK)!=0)
              {
                  if(this->isLSB)
                  {
                      byte|=(0x01<<(count%8));
                  }else
                  {
                       byte|=(0x80>>(count%8));
                  }
              }
              count++;
              if((count%8)==0)
              {
                  if (this->isReverse)
                  {
                      byte ^= 0xFF;
                  }
                  text.append(tr("0x%1").arg((quint8)byte, 2, 16, QLatin1Char('0')));
                  text.append(",");
                  byte=0;
              }
          }
        }
    }
    text.append("/* data */" + NEW_LINE + NEW_LINE);
    FontPage *font_page = NULL;
    foreach(FontPage * fpage, page_list)
    {
        if (fpage->page() == page)
        {
            font_page = fpage;
            break;
        }
    }
    if (font_page == NULL)
    {
        font_page = new FontPage();
        font_page->setPage(page);
        font_page->FontDataAppend(text);
        page_list.append(font_page);
    }
    else
    {
        font_page->FontDataAppend(text);
    }
}
FontCreator::FontCreator(QObject *parent) :
    QObject(parent)
{

}
FontCreator::FontCreator(QObject *parent, FontConfig *config) :
    QObject(parent)
{
    this->font_config = config;
}
void FontCreator::setFontConfig(FontConfig *config)
{
    this->font_config = config;

}
void FontCreator::start()
{
    Converter *converter = new Converter(font_config->font(), font_config->width(), font_config->height(), font_config->isReverse(), font_config->isLSB());

    //  converter->moveToThread(&ConvertThread);
    // connect(&ConvertThread, SIGNAL(finished()), converter, SLOT(deleteLater()));
    connect(this, &FontCreator::start_convert, converter, &Converter::Convert);
    connect(converter, &Converter::progress, this, &FontCreator::progress);
    connect(converter, &Converter::finished, this, &FontCreator::finished);
    // ConvertThread.start();

    emit start_convert(font_config->text());
}
void FontCreator::finished(QString &result)
{
//qDebug()<<result;
    QString file = this->font_config->saveFontName();
    QFontMetrics *fontMetrics = new QFontMetrics(font_config->font());
    QFileInfo fileinfo(file);
    QFile File(file);
    // qDebug()<<file;

    //qDebug()<<fileinfo.baseName();
    if (File.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream out(&File);
        out.setCodec(QTextCodec::codecForName("utf-8"));
        out << tr("/* %1 - %2%3 font for BMF font driver */").arg(fileinfo.fileName()).arg(font_config->font().family()).arg(QString::number(font_config->width())) << endl << endl << endl;
        out << tr("/*") << endl;
        out << tr("********************************************************************************") << endl;
        out << tr("*								vworks windML  font							     ") << endl;
        out << tr("*					Characters bmf code of   %1%2                                ").arg(font_config->font().family()).arg(QString::number(font_config->width())) << endl;
        out << tr("*			               (c) Copyright %1, rt-thread				             ").arg(QDateTime::currentDateTime().toString("yyyy")) << endl;
        out << tr("********************************************************************************") << endl;
        out << tr("*/") << endl << endl << endl;
        out << tr("#include <ugl/driver/font/udbmffnt.h>") << endl;
        out << result << endl;
        out << tr("const UGL_BMF_FONT_DESC  uglBMFFont_%1_%2 = ").arg(fileinfo.baseName()).arg(QString::number(font_config->width())) << endl << tr("{") << endl;
        out << tr("/* UGL_FONT_DESC structure */") << endl;
        out << tr("    {") << endl;
        out << tr("		{ %1, %2},		/*pixelSize*/").arg(QString::number(font_config->width())).arg(QString::number(font_config->height())) << endl;
        out << tr("		{UGL_FONT_BOLD_OFF, UGL_FONT_BOLD_OFF},		/*weight*/") << endl;
        out << tr("		UGL_FONT_UPRIGHT,		/*italic*/") << endl;
        out << tr("		UGL_FONT_PROPORTIONAL,		/*spacing*/") << endl;
        out << tr("		UGL_FONT_GB2312,		    /*char set*/") << endl;
        out << tr("		\"%1 %2\",		/*face name*/").arg(font_config->font().family()).arg(QString::number(font_config->width())) << endl;
        out << tr("		\"%1\",		/*family name*/").arg(font_config->font().family()) << endl;
        out << tr("     },") << endl;
        out << tr("    %1,		/*leading*/").arg(QString::number(fontMetrics->leading())) << endl;
        out << tr("    %1,		/*maxAscent*/").arg(QString::number(fontMetrics->ascent())) << endl;
        out << tr("    %1,		/*maxDescent*/").arg(QString::number(fontMetrics->descent())) << endl;
        out << tr("    %1,		/*maxAdvance*/").arg(QString::number(fontMetrics->descent())) << endl;
        out << tr("    pageArray	/*glyph pages*/") << endl;
        out << tr("};") << endl;
        out << tr("/*end of %1 file */").arg(fileinfo.fileName()) << endl;
    }
}
