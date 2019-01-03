#include "blProjectDataView.h"
#include "../model/blProjectModel.h"
#include "HierarchicalHeaderView.h"

class ExampleModel: public QAbstractTableModel
{
        QStandardItemModel _horizontalHeaderModel;
        QStandardItemModel _verticalHeaderModel;
        blProjectModel *m_model;

        QMap<int, blSubColumnInfo> m_subColumnsInfo;
        QMap<int, int> m_subColumnIdxInTable;
        int m_colCount;

        void fillHeaderModel(QStandardItemModel& headerModel)
        {

            QList<QStandardItem*> l;
            QList<blMainColumnInfo> mainColumnsInfo = m_model->mainColumns();
            int colIdx = -1;
            for (int i = 0 ; i < mainColumnsInfo.count() ; i++){
                qDebug() << "fillTableHeader add main column";
                QStandardItem* cell=new QStandardItem(mainColumnsInfo[i].name());
                QList<blSubColumnInfo> subColumn = m_model->subColumns(mainColumnsInfo[i].id());
                l.clear();
                for (int j = 0 ; j < subColumn.count() ; j++){
                    colIdx++;
                    l.clear();
                    qDebug() << "fillTableHeader add sub column:" << subColumn[j].name();
                    l.push_back(new QStandardItem(subColumn[j].name()));
                    cell->appendColumn(l);
                    m_subColumnsInfo[subColumn[j].id()] = subColumn[j];
                    m_subColumnIdxInTable[subColumn[j].id()] = colIdx;

                }
                headerModel.setItem(0, i, cell);
            }
            m_colCount = colIdx+1;
        }
public:
        QMap<int, blSubColumnInfo> getcolInfoMap(){
            return m_subColumnsInfo;
        }

        QMap<int, int> getColIdxInTable(){
            return m_subColumnIdxInTable;
        }
        void setDataBaseModel(blProjectModel *model){
            m_model = model;
        }
    public:
        ExampleModel(blProjectModel *model, QObject* parent=0): QAbstractTableModel(parent)
        {
            m_model = model;
            fillHeaderModel(_horizontalHeaderModel);
            fillHeaderModel(_verticalHeaderModel);
        }

    int rowCount(const QModelIndex& ) const
    {
                return m_model->index()->maxLineIdx()+1;
    }

    int columnCount(const QModelIndex& ) const
    {
        return m_colCount;
    }

    QVariant data(const QModelIndex& index, int role) const
    {
        if(role==HierarchicalHeaderView::HorizontalHeaderDataRole)
        {
            QVariant v;
            v.setValue((QObject*)&_horizontalHeaderModel);
            return v;
        }
        if(role==HierarchicalHeaderView::VerticalHeaderDataRole)
        {
            QVariant v;
            v.setValue((QObject*)&_verticalHeaderModel);
            return v;
        }
        if(role==Qt::DisplayRole && index.isValid())
        {
            return "";//QString("index(%1, %2)").arg(index.row()).arg(index.column());
        }
        return QVariant();
    }
};


// ///////////////////////////////////////////////////////// //
//                  blProjectDataView
// ///////////////////////////////////////////////////////// //
blProjectDataView::blProjectDataView(QWidget *parent)
    :QWidget(parent){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    m_tableView = new QTableView(this);
    layout->addWidget(m_tableView);
}

void blProjectDataView::fillTable(blProjectModel *model){

    this->fillTableHeader(model);
    this->fillTableContent(model);
}

void blProjectDataView::fillTableHeader(blProjectModel *model){



    em = new ExampleModel(model, m_tableView);
    //em.setDataBaseModel(model);
    HierarchicalHeaderView* hv=new HierarchicalHeaderView(Qt::Horizontal, m_tableView);
    hv->setHighlightSections(true);
    hv->setSectionsClickable(true);
    m_tableView->setHorizontalHeader(hv);

    m_tableView->setModel(em);
    m_tableView->resizeColumnsToContents();
    m_tableView->resizeRowsToContents();
    m_subColumnIdxInTable = em->getColIdxInTable();
    m_subColumnsInfo = em->getcolInfoMap();

}

void blProjectDataView::load(blProjectModel *model){
    this->fillTable(model);
}

void blProjectDataView::fillTableContent(blProjectModel *model){

    int maxLineIdx = model->index()->maxLineIdx();
    //m_tableView->setRowCount(maxLineIdx+1);
    int line = 0;
    for(int l = 0 ; l <= maxLineIdx ; l++ ){
        QList<blDataInfo> lineDataInfo = model->index()->getDataLine(l);
        for(int d = 0 ; d < lineDataInfo.count() ; d++){
            blDataInfo curentData = lineDataInfo[d];
            //qDebug() << "set item sub subcolumn id = " <<  curentData.id_sub_column();
            //qDebug() << "setItem (" << line << ", " << m_subColumnIdxInTable[curentData.id_sub_column()] << ") = " << curentData.url();

            QString datatype = model->index()->getSubColDataType(curentData.id_sub_column());
            if (datatype == "tag"){
                QString tg = model->index()->tagName(curentData.url().toInt());
                m_tableView->setIndexWidget(em->index(line, m_subColumnIdxInTable[curentData.id_sub_column()]), new QLabel(tg, m_tableView));
            }
            else{
                m_tableView->setIndexWidget(em->index(line, m_subColumnIdxInTable[curentData.id_sub_column()]), new QLabel(curentData.url(), m_tableView));
            }
            //m_tableView->setItem(line, m_subColumnIdxInTable[curentData.id_sub_column()], new QTableWidgetItem(curentData.url()));
        }
        line++;
    }

}
