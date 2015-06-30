#ifndef DICTIONARYCODINGELEMENT_H
#define DICTIONARYCODINGELEMENT_H

#include "abstractcodingelement.h"


class DictionaryCodingElement : public AbstractCodingElement
{
    Q_OBJECT

public:
    DictionaryCodingElement(QWidget *parent = 0);

    // Selection
    QString getSelection() const {
        return selectedTextLnEd->text();
    }
    void setSelection(QString selection) {
        selectedTextLnEd->setText(selection);
    }

    // Content
    QString getContent() const {
        return selectedContentLnEd->text();
    }
    void setContent(QString content) {
        selectedContentLnEd->setText(content);
    }

    // Mask
    QString getMask() const {
        return selectedMaskLnEd->text();
    }
    void setMask(QString mask) {
        selectedMaskLnEd->setText(mask);
    }



private:
    QGridLayout *selectedLayout;
    QGroupBox *selectedGBox;

    QLabel *selectedTextLbl;
    QLineEdit *selectedTextLnEd;
    QLabel *selectedContentLbl;
    QLineEdit *selectedContentLnEd;
    QLabel *selectedMaskLbl;
    QLineEdit *selectedMaskLnEd;

    QVBoxLayout *newLayout;
};
#endif // DICTIONARYCODINGELEMENT_H

