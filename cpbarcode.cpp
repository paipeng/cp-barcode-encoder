#include "cpbarcode.h"

#include "BarcodeFormat.h"
#include "BitMatrix.h"
#include "BitMatrixIO.h"
#include "CharacterSet.h"
#include "MultiFormatWriter.h"
#include <QDebug>
#include <QErrorMessage>

using namespace ZXing;

CPBarcode::CPBarcode()
{

}


QImage CPBarcode::encode(const QString& data) {
    QImage barcode;
    try {
        int width = 400, height = 400;
        BarcodeFormat format = BarcodeFormat::QRCode;
        int margin = 0;
        CharacterSet encoding = CharacterSet::Unknown;
        int eccLevel = 8;

        auto writer = MultiFormatWriter(format).setMargin(margin).setEncoding(encoding).setEccLevel(eccLevel);

        BitMatrix matrix = writer.encode(data.toStdWString(), width, height);
        //auto bitmap = ToMatrix<uint8_t>(matrix);
        qDebug() << "matrix size: " << matrix.width() << "-" << matrix.height();

        barcode = QImage(width, height, QImage::Format_Grayscale8);
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
