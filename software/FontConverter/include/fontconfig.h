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

    int lineSpacing() const { return font_line_spacing;}
    void setLineSpacing(int s);
    Q_PROPERTY( int lineSpacing READ lineSpacing WRITE setLineSpacing )

    int charSpacing() const { return font_char_spacing;}
    void setCharSpacing(int s);
    Q_PROPERTY( int charSpacing READ charSpacing WRITE setCharSpacing )


    void emmitChange();
private:
    QFont  current_font;
    QString font_style;
    int font_size;
    QString input_text;
    int    m_hinting;
    bool    m_render_missing;
    bool    m_antialiased;
    int    font_bold;
    int    font_italic;
    int   font_width;
    int   font_height;
    int font_char_spacing;
    int font_line_spacing;
signals:
    void nameChanged();
    void sizeChanged();
    void textChanged();
    void renderingOptionsChanged();
    void spacingChanged();
public slots:

};


#endif // FONTCONFIG_H
