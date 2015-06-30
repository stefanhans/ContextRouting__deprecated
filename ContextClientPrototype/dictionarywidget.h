#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include "abstractwidget.h"
#include "dictionarytree.h"
#include "dictionaryreader.h"

#include <QTreeView>

class DictionaryWidget : public AbstractWidget
{
    Q_OBJECT

public:
    DictionaryWidget(QWidget *parent = 0);

    bool loadFile(QString fileName);

private:
    DictionaryReader *reader;

    QVBoxLayout *newLayout;
    QGroupBox *dictTreeGBox;

    QVBoxLayout *dictTreeLayout;
    QTreeView *dictTreeView;

    DictionaryTree *dictTree;

};
#endif // DICTIONARYWIDGET_H

