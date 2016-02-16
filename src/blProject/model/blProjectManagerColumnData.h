#pragma once

#include <QString>

/// \class khProjectManagerColumnData
/// \brief Contains one line data for a given
/// column of the table of project manager
class khProjectManagerColumnData
{
public:
    /// \fn khProjectManagerColumnData();
    /// \brief Constructor
    khProjectManagerColumnData();
    /// \fn khProjectManagerColumnData(unsigned int lineId, QString data);
    /// \brief Constructor
    /// \param[in] lineId Id of the line in the column
    /// \param[in] data Data as an url or string
    khProjectManagerColumnData(unsigned int lineId, QString data);
    /// \fn khProjectManagerColumnData(unsigned int lineId, float data);
    /// \brief Constructor
    /// \param[in] lineId Id of the line in the column
    /// \param[in] data Data as a number
    khProjectManagerColumnData(unsigned int lineId, float data);

public:
    /// \fn unsigned int lineId();
    /// \return the Id of the line in the column
    unsigned int lineId();
    /// \fn QString dataString();
    /// \return the data as an url or string
    QString dataString();
    /// \fn float dataNumber();
    /// \return the data as a number
    float dataNumber();

public:
    /// \fn void setLineId(unsigned int lineId);
    /// \param[in] lineId Id of the line in the column
    void setLineId(unsigned int lineId);
    /// \fn void setDataString(QString dataString);
    /// \param[in] dataString Data as an url or string
    void setDataString(QString dataString);
    /// \fn void setDataNumber(float dataNumber);
    /// \brief dataNumber Data as a number
    void setDataNumber(float dataNumber);

private:
    unsigned int m_lineId; ///< id of the line in the column
    QString m_dataUrl; ///< data as an url or string
    float m_dataNumber; ///< data as a number
};

