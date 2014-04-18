#ifndef FONTCONFIG_H
#define FONTCONFIG_H

#include <QObject>
#include <QColor>
#include <QFont>

class FontConfig : public QObject
{
Q_OBJECT
Q_ENUMS(HintingMethod)
public:
    explicit FontConfig(QObject *parent = 0);

    void normalize();

    enum HintingMethod {
        HintingDisable,
        HintingDefault,
        HintingForceFreetypeAuto,
        HintingDisableFreetypeAuto
    };



    QFont font()const { return current_font;}
    void setFont(QFont font);
    Q_PROPERTY( QFont font READ font WRITE setFont )

    const QString& style() const { return font_style; }
    void setStyle(const QString& style);
    Q_PROPERTY( QString style READ style WRITE setStyle )

    int size() const { return font_size;}
    void setSize(int size);
    Q_PROPERTY( int size READ size WRITE setSize )

    const QString& text() const { return input_text; }
    void setText(const QString& txt);
    Q_PROPERTY( QString text READ text WRITE setText )

    const QString& defaultCharacters() const;

    int hinting() const { return m_hinting;}
    void setHinting(int b);
    void resetHinting() { m_hinting = HintingDefault;}
    Q_PROPERTY( int hinting READ hinting WRITE setHinting RESET resetHinting )

    bool renderMissing() const { return m_render_missing;}
    void setRenderMissing(bool b);
    Q_PROPERTY( bool renderMissing READ renderMissing WRITE setRenderMissing )

    bool antialiased() const { return m_antialiased;}
    void setAntialiased(bool b);
    Q_PROPERTY( bool antialiased READ antialiased WRITE setAntialiased )

    int bold() const { return font_bold;}
    void setBold(int b);
    Q_PROPERTY( int bold READ bold WRITE setBold )

    int italic() const { return font_italic;}
    void setItalic(int b);
    Q_PROPERTY( int italic READ italic WRITE setItalic )

    int width() const { return font_width;}
    void setWidth(int b);
    Q_PROPERTY( int width READ width WRITE setWidth )

    int height() const { return font_height;}
    void setHeight(int h);
    Q_PROPERTY( int height READ height WRITE setHeight )

    bool isReverse() const { return Reverse;}
    void setReverse(bool b);

    bool isLSB() const { return LSB;}
    void setLSB(bool b);

    const QString& saveFontName() const { return save_file; }
    void setSaveFontName(const QString& txt);


    void emmitChange();
private:
    QString save_file;
    QFont  current_font;  //字体
    QString font_style;   //字体风格
    int font_size;        //字体大小
    QString input_text;   //输入的取模字符
    int    m_hinting;
    bool    m_render_missing;
    bool    m_antialiased;
    int    font_bold;    //是否加粗
    int    font_italic;  //是否倾斜
    int   font_width;    //字体宽度
    int   font_height;  //字体高度
    bool  Reverse;    //是否反白显示
    bool  LSB;        //指定数据储存方式是否为LSB，或MSB
signals:
    void nameChanged();
    void sizeChanged();
    void textChanged();
    void renderingOptionsChanged();
    void spacingChanged();
public slots:

};


#endif // FONTCONFIG_H
