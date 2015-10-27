/// \file searchwidget.h
/// \brief SearchWidget class declaration
/// \author PRIGENT S.
/// \version 0.1
/// \date December 2012

#pragma once

#include <QtWidgets>
#include <QLineEdit>

#include "blWidgetsExport.h"

/// \class blSearchBarWidget
/// \brief Class defining a search bar. This widget emit a signal with a string containing the request.
class BLWIDGETS_EXPORT blSearchBarWidget : public QLineEdit
{
    Q_OBJECT
public:
    /// \fn explicit blSearchBarWidget(QWidget *parent = 0);
    /// \brief Constructor
    explicit blSearchBarWidget(QWidget *parent = 0);

public:
    void setAutoComplete(QStringList wordList);

signals:
    /// \fn void search(QString text);
    /// \brief Signal emitted when the search is done (ie enter pressed or icon clicked)
    /// \param[in] text Text writen in the search line edit
    void search(QString text);

private slots:
    /// \fn void emitSearch();
    /// \brief Slot that emit the validation signal
    void emitSearch();

    /// \fn void removeSearch();
    /// \remove the word search from the line edit
    void removeSearch();

protected:
    QString m_defaultText; ///< default text
};

