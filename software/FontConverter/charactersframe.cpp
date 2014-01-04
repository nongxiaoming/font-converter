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
    font_config = 0;
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
    if (font_config) {
        font_config->setText(sortChars(removeDuplicates(getCharacters())));
    }
}

void CharactersFrame::setConfig(FontConfig* config) {
    font_config = config;
    ui->plainTextEdit->setPlainText(config->text());
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
    ui->plainTextEdit->setPlainText(font_config->defaultCharacters());
}

void CharactersFrame::on_pushButton_SelectFromCharsMap_clicked()
{
    CharMapDialog dialog(this);
    dialog.setModal(true);
    dialog.setText(font_config->text());

    int result = dialog.exec();
    (void)result;
    if (dialog.result()==QDialog::Accepted) {
        font_config->setText(sortChars(removeDuplicates(dialog.getText())));
        bool block = ui->plainTextEdit->blockSignals(true);
        ui->plainTextEdit->setPlainText(font_config->text());
        ui->plainTextEdit->blockSignals(block);
    }
}

