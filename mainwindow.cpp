#include "MainWindow.h"
#include "Car.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Блок "Авто"
    QGroupBox *autoGroup = new QGroupBox("Авто");
    QFormLayout *formLayout = new QFormLayout(autoGroup);

    m_markaEdit = new QLineEdit();
    m_modelEdit = new QLineEdit();
    m_yearEdit = new QLineEdit();
    m_gosNumberEdit = new QLineEdit();

    formLayout->addRow("Марка (капс анг/рус):", m_markaEdit);
    formLayout->addRow("Модель:", m_modelEdit);
    formLayout->addRow("Год выпуска (4 цифры):", m_yearEdit);
    formLayout->addRow("Гос. номер (A111AA22 или A111AA222):", m_gosNumberEdit);

    mainLayout->addWidget(autoGroup);

    // Блок "Двигатель"
    QGroupBox *engineGroup = new QGroupBox("Двигатель");
    QHBoxLayout *engineLayout = new QHBoxLayout(engineGroup);

    m_benzineRadio = new QRadioButton("Бензин");
    m_dieselRadio = new QRadioButton("Дизель");

    engineLayout->addWidget(m_benzineRadio);
    engineLayout->addWidget(m_dieselRadio);
    engineLayout->addStretch();

    mainLayout->addWidget(engineGroup);

    // Блок "Опции"
    QGroupBox *optionsGroup = new QGroupBox("Опции");
    QVBoxLayout *optionsLayout = new QVBoxLayout(optionsGroup);

    m_seatHeatCheck = new QCheckBox("Подогрев сидений");
    m_parktronicCheck = new QCheckBox("Парктроники");
    m_matsCheck = new QCheckBox("Коврики");

    optionsLayout->addWidget(m_seatHeatCheck);
    optionsLayout->addWidget(m_parktronicCheck);
    optionsLayout->addWidget(m_matsCheck);

    mainLayout->addWidget(optionsGroup);

    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *resetBtn = new QPushButton("Сброс");
    QPushButton *saveBtn = new QPushButton("Сохранить");

    saveBtn->setStyleSheet("background-color: lightblue;");

    buttonLayout->addStretch();
    buttonLayout->addWidget(resetBtn);
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    setWindowTitle("Авто - Лабораторная работа 4");

    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::onSave);
}

MainWindow::~MainWindow() {}

void MainWindow::onReset()
{
    m_markaEdit->clear();
    m_modelEdit->clear();
    m_yearEdit->clear();
    m_gosNumberEdit->clear();

    m_benzineRadio->setAutoExclusive(false);
    m_dieselRadio->setAutoExclusive(false);
    m_benzineRadio->setChecked(false);
    m_dieselRadio->setChecked(false);
    m_benzineRadio->setAutoExclusive(true);
    m_dieselRadio->setAutoExclusive(true);

    m_seatHeatCheck->setChecked(false);
    m_parktronicCheck->setChecked(false);
    m_matsCheck->setChecked(false);
}

bool MainWindow::validateAllFields(QString &errorMessage)
{
    QString marka = m_markaEdit->text().trimmed();
    QRegularExpression markaRegex("^[A-ZА-Я]+$");
    if (marka.isEmpty()) {
        errorMessage = "Марка: обязательное поле!";
        return false;
    }
    if (!markaRegex.match(marka).hasMatch()) {
        errorMessage = "Марка: только ЗАГЛАВНЫЕ буквы (A-Z или А-Я)!";
        return false;
    }

    if (m_modelEdit->text().trimmed().isEmpty()) {
        errorMessage = "Модель: обязательное поле!";
        return false;
    }

    QString year = m_yearEdit->text().trimmed();
    QRegularExpression yearRegex("^\\d{4}$");
    if (year.isEmpty()) {
        errorMessage = "Год выпуска: обязательное поле!";
        return false;
    }
    if (!yearRegex.match(year).hasMatch()) {
        errorMessage = "Год выпуска: введите 4 цифры (например, 2002)!";
        return false;
    }

    QString gosNum = m_gosNumberEdit->text().trimmed().toUpper();
    QRegularExpression gosRegex("^([ABEKMHOPCTXY]\\d{3}[ABEKMHOPCTXY]{2}(\\d{2}|101|111))$");
    if (gosNum.isEmpty()) {
        errorMessage = "Гос. номер: обязательное поле!";
        return false;
    }
    if (!gosRegex.match(gosNum).hasMatch()) {
        errorMessage = "Гос. номер: формат A111AA22 или A111AA222!\nБуквы только: A,B,E,K,M,H,O,P,C,T,X,Y\nРегион: 2 любые цифры или 101/111";
        return false;
    }

    if (!m_benzineRadio->isChecked() && !m_dieselRadio->isChecked()) {
        errorMessage = "Двигатель: выберите тип (Бензин или Дизель)!";
        return false;
    }

    return true;
}

void MainWindow::onSave()
{
    QString errorMsg;
    if (!validateAllFields(errorMsg)) {
        QMessageBox::critical(this, "Ошибка!", errorMsg);
        return;
    }

    QStringList optionsList;
    if (m_seatHeatCheck->isChecked()) optionsList << "Подогрев сидений";
    if (m_parktronicCheck->isChecked()) optionsList << "Парктроники";
    if (m_matsCheck->isChecked()) optionsList << "Коврики";

    QString options = optionsList.join(", ");
    QString engine = m_benzineRadio->isChecked() ? "Бензин" : "Дизель";

    Car car(
        m_markaEdit->text().trimmed(),
        m_modelEdit->text().trimmed(),
        m_yearEdit->text().trimmed(),
        m_gosNumberEdit->text().trimmed().toUpper(),
        engine,
        options
        );

    car.saveToFile("result.txt");
    QMessageBox::information(this, "Успех!", "Данные сохранены в файл result.txt");
    onReset();
}
