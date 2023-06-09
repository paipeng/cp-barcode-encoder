#ifndef CPBARCODE_H
#define CPBARCODE_H

#include <QImage>

class CPBarcode
{
public:
    CPBarcode();
    QImage encode(const QString& data);
    QStringList getCharacterSets();
};

#endif // CPBARCODE_H
