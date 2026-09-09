#ifndef CAR_H
#define CAR_H

#include <QString>

class Car
{
public:
    Car(const QString& marka, const QString& model, const QString& year,
        const QString& gosNumber, const QString& engine, const QString& options);

    void saveToFile(const QString& filename);

private:
    QString m_marka;
    QString m_model;
    QString m_year;
    QString m_gosNumber;
    QString m_engine;
    QString m_options;
};

#endif
