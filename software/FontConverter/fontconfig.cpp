#include "fontconfig.h"
#include <QStandardPaths>
#include <QPaintDevice>

FontConfig::FontConfig(QObject *parent) :
    QObject(parent)
{
    input_text = defaultCharacters();
    m_hinting = HintingDefault;
    m_render_missing = false;
    m_antialiased = true;
    font_bold = 0;
    font_italic = false;
    font_width = 16;
    font_height = 16;
    current_font.setFamily(tr("宋体"));
    current_font.setPointSize(12);
    this->save_file=tr("d:/myfont.c");
    this->Reverse=false;
    this->LSB=false;

}


const QString& FontConfig::defaultCharacters() const {
    static const QString def = " !\"#$%&'()*+,-./0123456789:;<=>?@"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                               "abcdefghijklmnopqrstuvwxyz{|}~";
    return def;
}


void FontConfig::setFont(QFont font)
{
    this->current_font=font;
}
void FontConfig::setStyle(const QString& style) {
    if (font_style!=style) {
        font_style = style;
        nameChanged();
    }
}

void FontConfig::setSize(int size) {
    if (font_size!=size) {
        font_size = size;
        sizeChanged();
    }
}


void FontConfig::setText(const QString& text) {
    if (input_text!=text) {
        input_text=text;
        textChanged();
    }
}

void FontConfig::setSaveFontName(const QString &txt)
{
    this->save_file=txt;
}
void FontConfig::setHinting(int h) {
    if (m_hinting!=h) {
        m_hinting = h;
        renderingOptionsChanged();
    }
}

void FontConfig::setAntialiased(bool b) {
    if (m_antialiased!=b) {
        m_antialiased = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setRenderMissing(bool b) {
    if (m_render_missing!=b) {
        m_render_missing = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setItalic(int b) {
    if (font_italic!=b) {
        font_italic = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setBold(int b) {
    if (font_bold!=b) {
        font_bold = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setWidth(int w) {
    if (font_width!=w) {
        font_width = w;
        sizeChanged();
    }
}

void FontConfig::setHeight(int h) {
    if (font_height!=h) {
        font_height = h;
        sizeChanged();
    }
}

void FontConfig::setReverse(bool b)
{
    this->Reverse=b;
    sizeChanged();
}

void FontConfig::setLSB(bool b)
{
    this->LSB=b;
}

void FontConfig::emmitChange() {
    nameChanged();
    sizeChanged();
}


void FontConfig::normalize() {
    switch (m_hinting) {
    case HintingDisable:
    case HintingDefault:
    case HintingForceFreetypeAuto:
    case HintingDisableFreetypeAuto:
        break;
    default:
        m_hinting = HintingDefault;
        break;
    }
}
