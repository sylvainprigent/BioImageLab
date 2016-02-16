/// \file blProjectControler.h
/// \brief blProjectControler
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include "blProject/model/blProjectModel.h"
#include "blProjectView.h"
#include "blProject/model/blCreateMiniature.h"
#include "blToolCore/model/blToolExecViewer.h"

/// \class blProjectControler
/// \brief Controler for the patern MVC of the project data
/// management
class BLPROJECT_EXPORT blProjectControler : public QObject{
    Q_OBJECT

public:
    /// \fn blProjectControler();
    /// \brief Constructor
    blProjectControler(blProjectModel* model, blProjectView* view, QString viewersDir, QString binariesDir);

signals:
    /// \fn void dataAdded();
    /// \brief Signal emitted when an image have been added to the project
    void dataAdded();
    void addRemoveSubColumnDone();
    /// \fn void addDataError(QString);
    /// \brief Signal emitted when the controler failed to add
    /// data to the project
    /// \param[in] message Error message
    void addDataError(QString message);

public slots:
    // Load / save
    /// \fn void saveProject();
    /// \brief save the project
    void saveProject();
    /// \fn void loadProject(QString projectURL);
    /// \brief load data to model, and set it to the vue
    /// \param[in] projectURL URL of the project
    void loadProject(QString projectURL);
    /// \fn void saveProject(QString projectURL);
    /// \brief save the model into a file
    /// \param[in] projectURL URL of the project
    void saveProject(QString projectURL);
    /// \fn void setProjectName(QString projectName);
    /// \param[in] projectName Name of the project
    void setProjectName(QString projectName);
    /// \fn QString projectName();
    /// \return the name of the project
    QString projectName();

public slots:
    // create
    /// \fn void createProject(QString projectURL);
    /// \brief create an empty view and model
    /// \param[in] projectURL URL of the project
    void createProject(QString projectURL);
    /// \fn void addMainColumn(QString name);
    /// \brief add main column to the model and update the view
    /// \param[in] name
    void addMainColumn(QString name);
    /// \fn void addColumn(QString mainColumnName, QString columnName, bool isMultiLine, QString dataType);
    /// \brief add column to a main column model and update the view
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] isMultiLine True if there is an entry for each line
    /// \param[in] dataType Data type (see blProjectModelColumn)
    void addColumn(QString mainColumnName, QString columnName, bool isMultiLine, QString dataType);
    void deleteColumn(QString columnName);
    void calculateColumnThumbnails(QString columnName);
    void addRemoveSubColumn(QString mainColumnName, QString subColumnName,bool add);

public slots:
    // columns operations setters
    /// \fn void columnAddData(QString mainColumnName, QString columnName, unsigned int lineId, QString data, bool useDataType = false);
    /// \brief add a line to a column
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] lineId Id of the line to edit
    /// \param[in] data Data to set
    /// \param[in] useDataType True if use the data type to fill the view (otherwise fill the view with the string)
    void columnAddData(QString mainColumnName, QString columnName, unsigned int lineId, QString data, bool useDataType = false);
    /// \fn void columnAddData(QString mainColumnName, QString columnName, unsigned int lineId, float data);
    /// \brief add a line to a column
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] lineId Id of the line to edit
    /// \param[in] data Data to set
    void columnAddData(QString mainColumnName, QString columnName, unsigned int lineId, float data);
    /// \fn void columnUpdateDataModel(QString mainColumnName, QString columnName, unsigned int lineId, QString data);
    /// \brief Update the data in the model but does not affect the view
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] lineId Id of the line to edit
    /// \param[in] data Data to set
    void columnUpdateDataModel(QString mainColumnName, QString columnName, unsigned int lineId, QString data);
    /// \fn void columnUpdateData(QString mainColumnName, QString columnName, unsigned int lineId, float data);
    /// \brief add a line to a column
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] lineId Id of the line to edit
    /// \param[in] data Data to set
    /// \param[in] useDataType True if use the data type to fill the view (otherwise fill the view with the string)
    void columnUpdateData(QString mainColumnName, QString columnName, unsigned int lineId, QString data,bool useDataType = false);
    /// \fn void columnUpdateData(QString mainColumnName, QString columnName, unsigned int lineId, float data);
    /// \brief Update the data in the model but does not affect the view
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] lineId Id of the line to edit
    /// \param[in] data Data to set
    void columnUpdateData(QString mainColumnName, QString columnName, unsigned int lineId, float data);
    /// \fn void columnUpdateDataType(QString mainColumnName, QString columnName, QString dataType);
    /// \brief Change the data type of a column
    /// \param[in] mainColumnName Name of the main column
    /// \param[in] columnName Name of the column
    /// \param[in] dataType Data type (see blProjectModelColumn)
    void columnUpdateDataType(QString mainColumnName, QString columnName, QString dataType);
    /// \fn void addSingleImage(QString imagePath);
    /// \brief add an image to the project
    /// \param[in] imagePath Path of the image to add/import
    void addSingleImage(QString imagePath);
    /// \fn void addProject(blProjectControler* controler);
    /// \brief Append a project data to this project
    /// \param[in] controler Controler of the project to append
    void addProject(blProjectControler* controler);

    void editThumbnail(QString mainColumnName, unsigned int row, unsigned int col, QString imgName);

private slots:
    void showViewerExecError(QString message);

public:
    /// \fn blProjectView* view();
    /// \brief return the view
    blProjectView* view();
    /// \fn blProjectModel* model();
    /// \brief return the model
    blProjectModel* model();


private:
    /// \fn void addEmptyLineToNonDataColumns();
    /// \brief Add an empty lines to each of the non data columns so
    /// that all the tables have the same number of colums
    void addEmptyLineToNonDataColumns();

private:
    QString m_projectURL; ///< URL of the project
    blProjectModel* m_model; ///< pointer to the model
    blProjectView* m_view; ///< pointer to the view
    blToolExecViewer* m_toolExecViewer; ///< pointer to the data viewer
    blCreateMiniatureThread *m_thumbnailThread; ///< thread to calculate thumbnails images
};
