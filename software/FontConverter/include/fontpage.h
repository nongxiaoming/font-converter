#ifndef FONTPAGE_H
#define FONTPAGE_H

#include <QObject>
#include <QStringBuilder>

class FontPage : public QObject
{
    Q_OBJECT
public:
    explicit FontPage(QObject *parent = 0);
    const quint8& page() const { return page_num; }
    void setPage(quint8 p);
    const QString& fontData() const{ return FontData;}
    void FontDataAppend(const QString &dat);
signals:

public slots:
private :
    quint8 page_num;
    QString FontData;
};

#endif // FONTPAGE_H
