#include "cpbarcode.h"

#include "BarcodeFormat.h"
#include "BitMatrix.h"
#include "BitMatrixIO.h"
#include "CharacterSet.h"
#include "MultiFormatWriter.h"
#include "qrcode/QRWriter.h"
#include "qrcode/QRErrorCorrectionLevel.h"

#include <QDebug>
#include <QErrorMessage>

using namespace ZXing;
using namespace QRCode;

CPBarcode::CPBarcode()
{

}


QImage CPBarcode::encode(const QString& data) {
    QImage barcode;
    try {
        int width = 0, height = 0;
        BarcodeFormat format = BarcodeFormat::QRCode;
        int margin = 0;
        CharacterSet encoding = CharacterSet::GB18030;
        int eccLevel = 8;

        QRCode::ErrorCorrectionLevel ecc = QRCode::ErrorCorrectionLevel::High;

        //auto writer = MultiFormatWriter(format).setMargin(margin).setEncoding(encoding).setEccLevel(eccLevel);

        auto writer = QRCode::Writer().setEncoding(encoding).setMargin(margin).setErrorCorrectionLevel(ecc).setVersion(10);


        BitMatrix matrix = writer.encode(data.toStdWString(), width, height);
        //auto bitmap = ToMatrix<uint8_t>(matrix);
        qDebug() << "matrix size: " << matrix.width() << "-" << matrix.height();

        barcode = QImage(matrix.width(), matrix.height(), QImage::Format_Grayscale8);
        for (int i = 0; i < matrix.height(); i++) {
            for (int j = 0; j < matrix.width(); j++) {
                if (matrix.get(j, i)) {
                    //qDebug() << "FF" << 1;
                    barcode.setPixel(j,i, 0xFF000000);
                } else {
                    //qDebug() << "00" << 1;
                    barcode.setPixel(j,i, 0xFFFFFFFF);
                }
            }
        }

    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    return barcode;
}

QStringList CPBarcode::getCharacterSets() {
    int size = (int)CharacterSet::CharsetCount;

    QStringList characterSets;

    characterSets.append("Unknown");
    characterSets.append("ASCII");
    characterSets.append("ISO8859_1");
    characterSets.append("ISO8859_2");
    characterSets.append("ISO8859_3");
    characterSets.append("ISO8859_4");
    characterSets.append("ISO8859_5");
    characterSets.append("ISO8859_6");
    characterSets.append("ISO8859_7");
    characterSets.append("ISO8859_8");
    characterSets.append("ISO8859_9");
    characterSets.append("ISO8859_10");
    characterSets.append("ISO8859_11");
    characterSets.append("ISO8859_13");
    characterSets.append("ISO8859_14");
    characterSets.append("ISO8859_15");
    characterSets.append("ISO8859_16");

    characterSets.append("Cp437");
    characterSets.append("Cp1250");
    characterSets.append("Cp1251");
    characterSets.append("Cp1252");
    characterSets.append("Cp1256");

    characterSets.append("Shift_JIS");
    characterSets.append("Big5");
    characterSets.append("GB2312");
    characterSets.append("GB18030");
    characterSets.append("EUC_JP");
    characterSets.append("EUC_KR");
    characterSets.append("UnicodeBig");
    characterSets.append("UTF8");
    characterSets.append("BINARY");

    if (characterSets.size() != size) {
        characterSets.clear();
    }

    return characterSets;
}
