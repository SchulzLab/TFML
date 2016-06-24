#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    void setText(QString aText);

public slots:
    void receiveFinished(int aCode, QProcess::ExitStatus aStatus);

private:
    QDialogButtonBox *createButtons();
    QTextEdit *mLogText;
    QPushButton *mCloseButton;
};

#endif
