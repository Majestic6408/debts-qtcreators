#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onReset();
    void onSave();

private:
    bool validateAllFields(QString &errorMessage);

    QLineEdit *m_markaEdit;
    QLineEdit *m_modelEdit;
    QLineEdit *m_yearEdit;
    QLineEdit *m_gosNumberEdit;

    QRadioButton *m_benzineRadio;
    QRadioButton *m_dieselRadio;

    QCheckBox *m_seatHeatCheck;
    QCheckBox *m_parktronicCheck;
    QCheckBox *m_matsCheck;
};

#endif
