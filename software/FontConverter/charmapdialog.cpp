#include "charmapdialog.h"
#include "ui_charmapdialog.h"

CharMapDialog::CharMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharMapDialog)
{
    ui->setupUi(this);
    ui->widget->setCodes(&m_codes);

    const struct {
        QString name;
        uint begin;
        uint end;
    } ranges[] = {
        {"000000 Controls and Basic Latin",         0x0000,0x007F },
        {"000080 Controls and Latin-1 Supplement",  0x0080,0x00FF },
        {"000100 Latin Extended-A",                 0x0100,0x017F },
        {"000180 Latin Extended-B",                 0x0180,0x024F },
        {"000250 IPA Extensions",                   0x0250,0x02AF },
        {"0002B0 Spacing Modifier Letters",         0x02B0,0x02FF },
        {"000370 Greek and Coptic",                 0x0370,0x03FF },
        {"000400 Cyrillic",                         0x0400,0x04FF },
        {"000500 Cyrillic Supplementary",           0x0500,0x052F },
        {"000530 Armenian",                         0x0530,0x058F },
        {"000590 Hebrew",                           0x0590,0x05FF },
        {"000600 Arabic",                           0x0600,0x06FF },
        {"000700 Syriac",                           0x0700,0x074F },
        {"000780 Thaana",                           0x0780,0x07BF },
        {"000900 Devanagari",                       0x0900,0x097F },
        {"000980 Bengali",                          0x0980,0x09FF },
        {"000A00 Gurmukhi",                         0x0A00,0x0A7F },
        {"000A80 Gujarati",                         0x0A80,0x0AFF },
        {"000B00 Oriya",                            0x0B00,0x0B7F },
        {"000B80 Tamil",                            0x0B80,0x0BFF },
        {"000C00 Telugu",                           0x0C00,0x0C7F },
        {"000C80 Kannada",                          0x0C80,0x0CFF },
        {"000D00 Malayalam",                        0x0D00,0x0D7F },
        {"000D80 Sinhala",                          0x0D80,0x0DFF },
        {"000E00 Thai",                             0x0E00,0x0E7F },
        {"000E80 Lao",                              0x0E80,0x0EFF },
        {"000F00 Tibetan",                          0x0F00,0x0FFF },
        {"001000 Myanmar",                          0x1000,0x109F },
        {"0010A0 Georgian",                         0x10A0,0x10FF },
        {"001100 Hangul Jamo",                      0x1100,0x11FF },
        {"001200 Ethiopic",                         0x1200,0x137F },
        {"0013A0 Cherokee",                         0x13A0,0x13FF },
        {"001680 Ogham",                            0x1680,0x169F },
        {"0016A0 Runic",                            0x16A0,0x16FF },
        {"001700 Tagalog",                          0x1700,0x171F },
        {"001720 Hanunoo",                          0x1720,0x173F },
        {"001740 Buhid",                            0x1740,0x175F },
        {"001760 Tagbanwa",                         0x1760,0x177F },
        {"001780 Khmer",                            0x1780,0x17FF },
        {"001800 Mongolian",                        0x1800,0x18AF },
        {"001900 Limbu",                            0x1900,0x194F },
        {"001950 Tai Le",                           0x1950,0x197F },
        {"0019E0 Khmer Symbols",                    0x19E0,0x19FF },
        {"001D00 Phonetic Extensions",              0x1D00,0x1D7F },
        {"001E00 Latin Extended Additional",        0x1E00,0x1EFF },
        {"001F00 Greek Extended",                   0x1F00,0x1FFF },
        {"002000 General Punctuation",              0x2000,0x206F },
        {"002070 Superscripts and Subscripts",      0x2070,0x209F },
        {"0020A0 Currency Symbols",                 0x20A0,0x20CF },
        {"0020D0 Combining Diacritical Marks for Symbols", 0x20D0,0x20FF },
        {"002100 Letterlike Symbols",               0x2100,0x214F },
        {"002150 Number Forms",                     0x2150,0x218F },
        {"002190 Arrows",                           0x2190,0x21FF },
        {"002200 Mathematical Operators",           0x2200,0x22FF },
        {"002300 Miscellaneous Technical",          0x2300,0x23FF },
        {"002400 Control Pictures",                 0x2400,0x243F },
        {"002440 Optical Character Recognition",    0x2440,0x245F },
        {"002460 Enclosed Alphanumerics",           0x2460,0x24FF },
        {"002500 Box Drawing",                      0x2500,0x257F },
        {"002580 Block Elements",                   0x2580,0x259F },
        {"0025A0 Geometric Shapes",                 0x25A0,0x25FF },
        {"002600 Miscellaneous Symbols",            0x2600,0x26FF },
        {"002700 Dingbats",                         0x2700,0x27BF },
        {"004E00 CJK Unified Ideographs",           0x4E00,0x4EFF },
        {"004F00 CJK Unified Ideographs",           0x4F00,0x4FFF },
        {"005000 CJK Unified Ideographs",           0x5000,0x50FF },
        {"005100 CJK Unified Ideographs",           0x5100,0x51FF },
        {"005200 CJK Unified Ideographs",           0x5200,0x52FF },
        {"005300 CJK Unified Ideographs",           0x5300,0x53FF },
        {"005400 CJK Unified Ideographs",           0x5400,0x54FF },
        {"005500 CJK Unified Ideographs",           0x5500,0x55FF },
        {"005600 CJK Unified Ideographs",           0x5600,0x56FF },
        {"005700 CJK Unified Ideographs",           0x5700,0x57FF },
        {"005800 CJK Unified Ideographs",           0x5800,0x58FF },
        {"005900 CJK Unified Ideographs",           0x5900,0x59FF },
        {"005A00 CJK Unified Ideographs",           0x5A00,0x5AFF },
        {"005B00 CJK Unified Ideographs",           0x5B00,0x5BFF },
        {"005C00 CJK Unified Ideographs",           0x5C00,0x5CFF },
        {"005D00 CJK Unified Ideographs",           0x5D00,0x5DFF },
        {"005E00 CJK Unified Ideographs",           0x5E00,0x5EFF },
        {"005F00 CJK Unified Ideographs",           0x5F00,0x5FFF },
        {"006000 CJK Unified Ideographs",           0x6000,0x60FF },
        {"006100 CJK Unified Ideographs",           0x6100,0x61FF },
        {"006200 CJK Unified Ideographs",           0x6200,0x62FF },
        {"006300 CJK Unified Ideographs",           0x6300,0x63FF },
        {"006400 CJK Unified Ideographs",           0x6400,0x64FF },
        {"006500 CJK Unified Ideographs",           0x6500,0x65FF },
        {"006600 CJK Unified Ideographs",           0x6600,0x66FF },
        {"006700 CJK Unified Ideographs",           0x6700,0x67FF },
        {"006800 CJK Unified Ideographs",           0x6800,0x68FF },
        {"006900 CJK Unified Ideographs",           0x6900,0x69FF },
        {"006A00 CJK Unified Ideographs",           0x6A00,0x6AFF },
        {"006B00 CJK Unified Ideographs",           0x6B00,0x6BFF },
        {"006C00 CJK Unified Ideographs",           0x6C00,0x6CFF },
        {"006D00 CJK Unified Ideographs",           0x6D00,0x6DFF },
        {"006E00 CJK Unified Ideographs",           0x6E00,0x6EFF },
        {"006F00 CJK Unified Ideographs",           0x6F00,0x6FFF },
        {"007000 CJK Unified Ideographs",           0x7000,0x70FF },
        {"007100 CJK Unified Ideographs",           0x7100,0x71FF },
        {"007200 CJK Unified Ideographs",           0x7200,0x72FF },
        {"007300 CJK Unified Ideographs",           0x7300,0x73FF },
        {"007400 CJK Unified Ideographs",           0x7400,0x74FF },
        {"007500 CJK Unified Ideographs",           0x7500,0x75FF },
        {"007600 CJK Unified Ideographs",           0x7600,0x76FF },
        {"007700 CJK Unified Ideographs",           0x7700,0x77FF },
        {"007800 CJK Unified Ideographs",           0x7800,0x78FF },
        {"007900 CJK Unified Ideographs",           0x7900,0x79FF },
        {"007A00 CJK Unified Ideographs",           0x7A00,0x7AFF },
        {"007B00 CJK Unified Ideographs",           0x7B00,0x7BFF },
        {"007C00 CJK Unified Ideographs",           0x7C00,0x7CFF },
        {"007D00 CJK Unified Ideographs",           0x7D00,0x7DFF },
        {"007E00 CJK Unified Ideographs",           0x7E00,0x7EFF },
        {"007F00 CJK Unified Ideographs",           0x7F00,0x7FFF },
        {"008000 CJK Unified Ideographs",           0x8000,0x80FF },
        {"008100 CJK Unified Ideographs",           0x8100,0x81FF },
        {"008200 CJK Unified Ideographs",           0x8200,0x82FF },
        {"008300 CJK Unified Ideographs",           0x8300,0x83FF },
        {"008400 CJK Unified Ideographs",           0x8400,0x84FF },
        {"008500 CJK Unified Ideographs",           0x8500,0x85FF },
        {"008600 CJK Unified Ideographs",           0x8600,0x86FF },
        {"008700 CJK Unified Ideographs",           0x8700,0x87FF },
        {"008800 CJK Unified Ideographs",           0x8800,0x88FF },
        {"008900 CJK Unified Ideographs",           0x8900,0x89FF },
        {"008A00 CJK Unified Ideographs",           0x8A00,0x8AFF },
        {"008B00 CJK Unified Ideographs",           0x8B00,0x8BFF },
        {"008C00 CJK Unified Ideographs",           0x8C00,0x8CFF },
        {"008D00 CJK Unified Ideographs",           0x8D00,0x8DFF },
        {"008E00 CJK Unified Ideographs",           0x8E00,0x8EFF },
        {"008F00 CJK Unified Ideographs",           0x8F00,0x8FFF },
        {"009000 CJK Unified Ideographs",           0x9000,0x90FF },
        {"009100 CJK Unified Ideographs",           0x9100,0x91FF },
        {"009200 CJK Unified Ideographs",           0x9200,0x92FF },
        {"009300 CJK Unified Ideographs",           0x9300,0x93FF },
        {"009400 CJK Unified Ideographs",           0x9400,0x94FF },
        {"009500 CJK Unified Ideographs",           0x9500,0x95FF },
        {"009600 CJK Unified Ideographs",           0x9600,0x96FF },
        {"009700 CJK Unified Ideographs",           0x9700,0x97FF },
        {"009800 CJK Unified Ideographs",           0x9800,0x98FF },
        {"009900 CJK Unified Ideographs",           0x9900,0x99FF },
        {"009A00 CJK Unified Ideographs",           0x9A00,0x9AFF },
        {"009B00 CJK Unified Ideographs",           0x9B00,0x9BFF },
        {"009C00 CJK Unified Ideographs",           0x9C00,0x9CFF },
        {"009D00 CJK Unified Ideographs",           0x9D00,0x9DFF },
        {"009E00 CJK Unified Ideographs",           0x9E00,0x9EFF },
        {"009F00 CJK Unified Ideographs",           0x9F00,0x9FFF },
        {"00FB00 Alphabetic Presentation Forms",    0xFB00,0xFB4F },
        {"00FB50 Arabic Presentation Forms-A",      0xFB50,0xFDFF },
    };

    for (size_t i=0;i<sizeof(ranges)/sizeof(ranges[0]);i++) {
        QListWidgetItem* item = new QListWidgetItem(ranges[i].name,ui->listWidget);
        uint begin = ranges[i].begin;
        uint end = ranges[i].end;
        bool have = false;

        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckState(have ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole+1,begin);
        item->setData(Qt::UserRole+2,end);
    }

    connect(ui->widget,SIGNAL(codesChanged(uint,bool)),this,SLOT(onCharsChanged(uint,bool)));
}

CharMapDialog::~CharMapDialog()
{
    delete ui;
}

void CharMapDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CharMapDialog::setText(const QString& string) {
    m_codes.clear();
    const ushort* codes = string.utf16();
    while (*codes) {
        m_codes.insert(*codes);
        onTextChanged(*codes,true);
        codes++;
    }

}

QString CharMapDialog::getText() const {
    QString str;
    foreach( uint code , m_codes) {
        str.append(QString().fromUcs4(&code,1));
    }
    return str;
}

void CharMapDialog::onTextChanged(uint code,bool add) {
    for (int row=0 ; row<ui->listWidget->count();row++) {
        QListWidgetItem* item = ui->listWidget->item(row);
        uint begin = item->data(Qt::UserRole+1).toInt();
        uint end = item->data(Qt::UserRole+2).toInt();
        if (code>=begin && code<=end) {
            bool block = ui->listWidget->blockSignals(true);
            if (add) {
                item->setCheckState(Qt::Checked);
            } else {
                bool have = false;
                foreach (uint c, m_codes ) {
                    if (c>=begin && c<=end) {
                        have = true;
                        break;
                    }
                }
                item->setCheckState(have ? Qt::Checked : Qt::Unchecked );
            }
            ui->listWidget->blockSignals(block);
        }
    }
}

void CharMapDialog::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous);
    uint begin = current->data(Qt::UserRole+1).toInt();
    uint end = current->data(Qt::UserRole+2).toInt();
    ui->widget->setRange(begin,end);
}

void CharMapDialog::on_listWidget_itemChanged(QListWidgetItem* item)
{
    bool checked = item->checkState() == Qt::Checked;
    uint begin = item->data(Qt::UserRole+1).toInt();
    uint end = item->data(Qt::UserRole+2).toInt();
    if (checked) {
        for (uint i=begin;i<=end;i++) {
            m_codes.insert(i);
        }
    } else {
        for (uint i=begin;i<=end;i++) {
            QSet<uint>::Iterator it = m_codes.find(i);
            if (it!=m_codes.end())
                m_codes.erase(it);
        }
    }
    ui->widget->update();
}
