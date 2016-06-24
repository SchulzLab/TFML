#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    FileDialog();
private:
    QDialogButtonBox *createButtons();
    QGroupBox *createInputWidgets();
    QLineEdit *artistEditor;
    QLineEdit *titleEditor;
    QSpinBox *yearEditor;
    QLineEdit *tracksEditor;
};

#endif // FILEDIALOG_H
