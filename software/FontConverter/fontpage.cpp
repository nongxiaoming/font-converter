#include "fontpage.h"

FontPage::FontPage(QObject *parent) :
    QObject(parent)
{

}
void FontPage::setPage (quint8 p)
{
    this->page_num=p;
}
void FontPage::FontDataAppend (const QString &dat)
{
    this->FontData+=dat;
}
