#ifndef BITMATRIXMODEL_H
#define BITMATRIXMODEL_H

#include <QAbstractTableModel>

class BitMatrixModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    BitMatrixModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

};

#endif // BITMATRIXMODEL_H

