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
    font_line_spacing = 0;
    current_font.setFamily(tr("宋体"));
    current_font.setPointSize(12);
    font_char_spacing = 0;
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
//    int dpi_x= QPaintDevice::logicalDpiX();
//    int dpi_y= QPaintDevice::logicalDpiY();
//    int width=  font.pointSize()*dpi_x/72;
//    int height=  font.pointSize()*dpi_y/72;
//    this->setHeight(height);
//    this->setWidth(width);
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

void FontConfig::emmitChange() {
    nameChanged();
    sizeChanged();
}

void FontConfig::setLineSpacing(int s) {
    if (font_line_spacing!=s) {
        font_line_spacing = s;
        spacingChanged();
    }
}

void FontConfig::setCharSpacing(int s) {
    if (font_char_spacing!=s) {
        font_char_spacing = s;
        spacingChanged();
    }
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
