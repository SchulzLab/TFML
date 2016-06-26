/*********************************************************************
*
*   MODULE NAME:
*       Dialog.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "Dialog.hpp"

int uniqueAlbumId;
int uniqueArtistId;

Dialog::Dialog(QWidget *parent)
     : QDialog(parent)
{

    mLogText = new QTextEdit();
    QDialogButtonBox *buttonBox = createButtons();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mLogText);
    layout->addWidget(buttonBox);
    setLayout(layout);
    setWindowTitle(tr("Log"));
}

QDialogButtonBox *Dialog::createButtons()
{
    mCloseButton = new QPushButton(tr("&Close"));
    mCloseButton->setEnabled(false);
    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(close()));
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(mCloseButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}

void Dialog::receiveFinished(int aCode, QProcess::ExitStatus aStatus)
{
    mCloseButton->setEnabled(true);
}

void Dialog::setText(QString aText)
{
    mLogText->insertPlainText(aText);
}
