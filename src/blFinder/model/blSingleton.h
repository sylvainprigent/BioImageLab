/// \file blSingleton.h
/// \brief blSingleton
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QtCore>

/// \class blSingleton
/// \brief templated singleton patern that can be applied to any class
template <typename T>
class blSingleton
{
protected:
    /// \fn blSingleton();
    /// \brief Constructor
    blSingleton(){}
    /// \fn ~blSingleton();
    /// \brief Destructor
    ~blSingleton(){}

public:
    // Publique interace
    /// \brief Instanciate the singleton
    /// \return an instance of the templated class
    static T *instance ()  {
        if (m_singleton == NULL)
        {
            //std::cout << "creating singleton." << std::endl;
            m_singleton = new T;
        }
        else
        {
            //std::cout << "singleton already created!" << std::endl;
        }

        return (static_cast<T*> (m_singleton));
    }

    /// \brief free the instance of the class
    static void kill(){
      if (NULL != m_singleton)
        {
          delete m_singleton;
          m_singleton = NULL;
        }
    }

private:
    static T *m_singleton; ///< Unique instance
};

template <typename T>
T *blSingleton<T>::m_singleton = NULL;
