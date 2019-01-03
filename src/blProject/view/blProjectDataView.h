#ifndef blProjectDataView_H
#define blProjectDataView_H

#include <QtWidgets>
#include "../model/blProjectModel.h"


class ExampleModel;
class blProjectDataView : public QWidget
{
    Q_OBJECT
public:
    explicit blProjectDataView(QWidget *parent = 0);

signals:

public slots:
    void fillTable(blProjectModel *model);
    void load(blProjectModel *model);

private:
    void fillTableHeader(blProjectModel *model);
    void fillTableContent(blProjectModel *model);

private:
    QTableView *m_tableView;
    QMap<int, blSubColumnInfo> m_subColumnsInfo;
    QMap<int, int> m_subColumnIdxInTable;
    ExampleModel *em;

};

#endif // blProjectDataView_H
