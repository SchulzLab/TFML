#include "peakcallingdialog.h"
#include "analysismanager.h"
#include <iostream>

using namespace std;

PeakCallingDialog::PeakCallingDialog(QWidget *parent)
     : QDialog(parent)
{

    QGroupBox *inputWidgetBox = createInputWidgets();
    QDialogButtonBox *buttonBox = createButtons();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(inputWidgetBox);
    layout->addWidget(buttonBox);
    setLayout(layout);

    setWindowTitle(tr("Peak Calling"));
}

QGroupBox *PeakCallingDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox(tr("Peak Calling"));

    QLabel *sampleLabel = new QLabel(tr("Sample Directory:"));
    QLabel *genomeLabel = new QLabel(tr("Genome File:"));
    QLabel *outputLabel = new QLabel(tr("Output Directory:"));

    sampleEditor = new QLineEdit;
    genomeEditor = new QLineEdit;
    outputEditor = new QLineEdit;

    sampleButton = new QPushButton(tr("Select Directory"));
    genomeButton = new QPushButton(tr("Select File"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(sampleLabel, 0, 0);
    layout->addWidget(sampleEditor, 0, 1);
    layout->addWidget(genomeLabel, 1, 0);
    layout->addWidget(genomeEditor, 1, 1);
    layout->addWidget(outputLabel, 2, 0);
    layout->addWidget(outputEditor, 2, 1);
    layout->addWidget(sampleButton, 0, 2);
    layout->addWidget(genomeButton, 1, 2);
    connect(sampleButton, SIGNAL(clicked()), this, SLOT(selectDirectory()));
    connect(genomeButton, SIGNAL(clicked()), this, SLOT(selectFile()));
    //layout->addWidget(tracksLabel, 3, 0, 1, 2);
    //layout->addWidget(tracksEditor, 4, 0, 1, 2);
    box->setLayout(layout);

    return box;
}

QDialogButtonBox *PeakCallingDialog::createButtons()
{
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));
    QPushButton *okButton = new QPushButton(tr("&OK"));

    cancelButton->setDefault(true);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(okButton, SIGNAL(clicked()), this, SLOT(ok()));
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(okButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}

void PeakCallingDialog::selectDirectory()
{
    QFileDialog *dialog = new QFileDialog();
    QString directoryName = dialog->getExistingDirectory(this,tr("select file"), "/home", QFileDialog::ShowDirsOnly
                                               | QFileDialog::DontResolveSymlinks);
    sampleEditor->setText(directoryName);
}

void PeakCallingDialog::selectFile()
{
    QFileDialog *dialog = new QFileDialog();
    QString fileName = dialog->getOpenFileName(this,tr("select file"));
    genomeEditor->setText(fileName);
}

void PeakCallingDialog::ok()
{
    if (sampleEditor->text().isEmpty() ||  genomeEditor->text().isEmpty() || outputEditor->text().isEmpty()) {
        cout << "empty" << endl;
    }
    else {
        accept();
        AnalysisManager::getAnalysisManager()->peakCalling(sampleEditor->text(), genomeEditor->text(), outputEditor->text());
    }
}
