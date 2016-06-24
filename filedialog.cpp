#include "filedialog.h"

FileDialog::FileDialog()
    : QFileDialog()
{

    setWindowTitle(tr("Open file"));

}

QGroupBox *FileDialog::createInputWidgets()
{
    QGroupBox *box = new QGroupBox(tr("Add Album"));

    QLabel *artistLabel = new QLabel(tr("Artist:"));
    QLabel *titleLabel = new QLabel(tr("Title:"));
    QLabel *yearLabel = new QLabel(tr("Year:"));
    QLabel *tracksLabel = new QLabel(tr("Tracks (separated by comma):"));

    artistEditor = new QLineEdit;
    titleEditor = new QLineEdit;

    yearEditor = new QSpinBox;
    yearEditor->setMinimum(1900);
  //  yearEditor->setMaximum(QDate::currentDate().year());
    yearEditor->setValue(yearEditor->maximum());
    yearEditor->setReadOnly(false);

    tracksEditor = new QLineEdit;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(artistLabel, 0, 0);
    layout->addWidget(artistEditor, 0, 1);
    layout->addWidget(titleLabel, 1, 0);
    layout->addWidget(titleEditor, 1, 1);
    layout->addWidget(yearLabel, 2, 0);
    layout->addWidget(yearEditor, 2, 1);
    layout->addWidget(tracksLabel, 3, 0, 1, 2);
    layout->addWidget(tracksEditor, 4, 0, 1, 2);
    box->setLayout(layout);

    return box;
}

QDialogButtonBox *FileDialog::createButtons()
{
    QPushButton *closeButton = new QPushButton(tr("&Close"));
    QPushButton *revertButton = new QPushButton(tr("&Revert"));
    QPushButton *submitButton = new QPushButton(tr("&Submit"));

    closeButton->setDefault(true);

    /*connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(revertButton, SIGNAL(clicked()), this, SLOT(revert()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
*/
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(submitButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}
