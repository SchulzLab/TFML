#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H
#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QtXml>

class AnalysisManager : public QObject
{
    Q_OBJECT
public:
    static AnalysisManager* getAnalysisManager();
    ~AnalysisManager();
    void peakCalling(QString sampleDirectory, QString genomeFile, QString outputPath);
    void analyseBedFile( QString aFilePath );

public slots:
    void updateText();
    void receiveFinished(int aCode, QProcess::ExitStatus aStatus);

signals:
    void mProcessOutputDone(QString path);
    void mUpdateLog(QString aStdOut, QString aStdErr);

private:
    AnalysisManager();
    QProcess *mProcess;
    QMessageBox *mResultBox;
    QString mOutputPath;
    static AnalysisManager* sAnalysisManager;

};

#endif // ANALYSISMANAGER_H
