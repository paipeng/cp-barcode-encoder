#ifndef CPBARCODE_H
#define CPBARCODE_H

#include <QImage>

class CPBarcode
{
public:
    CPBarcode();
    QImage encodeQrcode(const QString& data, int encoding=25, int margin=0, int ecc=3, int version=0, int maskPattern = 8);
    QStringList getCharacterSets();
};

#endif // CPBARCODE_H
