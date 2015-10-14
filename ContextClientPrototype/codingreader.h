#ifndef CODINGREADER_H
#define CODINGREADER_H

#include "abstractreader.h"
#include "abstractwidget.h"
#include "abstractcodingelement.h"

#include "codingwidget.h"
#include "dictionarytree.h"

#include <QXmlStreamReader>

class CodingReader : public AbstractReader
{
    Q_OBJECT

public:
    CodingReader();

    AbstractCodingElement *codingElement;

    bool read(QIODevice *device, AbstractWidget *widget);

    QString errorString() const;

signals:
    void requestContextData();
    void answerContextData(QList<QVariant> data);

private:
    QVBoxLayout *dictLayout;
    QGroupBox *dictGBox;

};
#endif // CODINGREADER_H

