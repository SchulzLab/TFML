#ifndef PEAKCALLINGDIALOG_H
#define PEAKCALLINGDIALOG_H
#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class PeakCallingDialog : public QDialog
{
    Q_OBJECT

public:
    PeakCallingDialog(QWidget *parent = 0);

private slots:
    void selectDirectory();
    void selectFile();
    void ok();

private:
    QDialogButtonBox *createButtons();
    QGroupBox *createInputWidgets();

    QLineEdit *tracksEditor;
    QLineEdit *sampleEditor;
    QLineEdit *genomeEditor;
    QLineEdit *outputEditor;
    QPushButton *sampleButton;
    QPushButton *genomeButton;
};
#endif // PEAKCALLINGDIALOG_H
