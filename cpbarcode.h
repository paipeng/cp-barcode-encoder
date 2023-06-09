#ifndef CPBARCODE_H
#define CPBARCODE_H

#include <QImage>

class CPBarcode
{
public:
    CPBarcode();
    QImage encode(const QString& data);
};

#endif // CPBARCODE_H
