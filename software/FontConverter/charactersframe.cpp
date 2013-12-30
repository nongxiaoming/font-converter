#include "charactersframe.h"
#include "ui_charactersframe.h"
#include <QFileDialog>
#include "fontconfig.h"
#include "charmapdialog.h"

CharactersFrame::CharactersFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharactersFrame)
{
    ui->setupUi(this);
    m_config = 0;
}

CharactersFrame::~CharactersFrame()
{
    delete ui;
}

void CharactersFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CharactersFrame::on_pushButtonImport_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Select file"),
                                                QString(),
                                                tr("Text file(*.txt)"));
    if (!file.isEmpty()) {
        QFile f(file);
        if (f.open(QFile::ReadOnly | QFile::Text)) {
            QByteArray data = f.readAll();
            QString text = QString::fromUtf8(data.constData(),data.size());
            text = sortChars(removeDuplicates(text));
            ui->plainTextEdit->setPlainText(text);
        }
    }
}

void CharactersFrame::on_pushButtonExport_clicked()
{
    QString file = QFileDialog::getSaveFileName(this,tr("Select file"),
                                                QString(),
                                                tr("Text file(*.txt)"));
    if (!file.isEmpty()) {
        QFile f(file);
        if (f.open(QFile::WriteOnly | QFile::Text)) {
            QByteArray data =
                ui->plainTextEdit->document()->toPlainText().toUtf8();
            f.write(data);
        }
    }
}


QString CharactersFrame::getCharacters() const {
    return ui->plainTextEdit->document()->toPlainText();
}

void CharactersFrame::on_plainTextEdit_textChanged()
{
    if (m_config) {
        m_config->setCharacters(sortChars(removeDuplicates(getCharacters())));
    }
}

void CharactersFrame::setConfig(FontConfig* config) {
    m_config = config;
    ui->plainTextEdit->setPlainText(config->characters());
}

QString CharactersFrame::removeDuplicates(const QString& text) const {
    QString res;
    foreach (QChar c, text) {
        if (!res.contains(c))
            res.append(c);
    }
    return res;
}

QString CharactersFrame::sortChars(const QString& text) const {
    QString res = text;
    qSort(res.begin(),res.end());
    return res;
}


void CharactersFrame::on_pushButtonDefault_clicked()
{
    ui->plainTextEdit->setPlainText(m_config->defaultCharacters());
}

void CharactersFrame::on_pushButton_SelectFromCharsMap_clicked()
{
    CharMapDialog dialog(this);
    dialog.setModal(true);
    dialog.setChars(m_config->characters());

    int result = dialog.exec();
    (void)result;
    if (dialog.result()==QDialog::Accepted) {
        m_config->setCharacters(sortChars(removeDuplicates(dialog.getCharacters())));
        bool block = ui->plainTextEdit->blockSignals(true);
        ui->plainTextEdit->setPlainText(m_config->characters());
        ui->plainTextEdit->blockSignals(block);
    }
}

void CharactersFrame::on_pushButtonRefresh_clicked()
{
    bool block = ui->plainTextEdit->blockSignals(true);
    ui->plainTextEdit->setPlainText(m_config->characters());
    ui->plainTextEdit->blockSignals(block);
}
