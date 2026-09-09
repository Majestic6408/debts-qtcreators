#include "Car.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Car::Car(const QString& marka, const QString& model, const QString& year,
         const QString& gosNumber, const QString& engine, const QString& options)
    : m_marka(marka)
    , m_model(model)
    , m_year(year)
    , m_gosNumber(gosNumber)
    , m_engine(engine)
    , m_options(options)
{
}

void Car::saveToFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл";
        return;
    }

    QTextStream out(&file);
    out << "========================================\n";
    out << "Марка: " << m_marka << "\n";
    out << "Модель: " << m_model << "\n";
    out << "Год выпуска: " << m_year << "\n";
    out << "Гос. номер: " << m_gosNumber << "\n";
    out << "Двигатель: " << m_engine << "\n";
    out << "Опции: " << (m_options.isEmpty() ? "Нет" : m_options) << "\n";
    out << "========================================\n\n";

    file.close();
}
