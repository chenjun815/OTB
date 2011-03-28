/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbWrapperQtWidgetParameterGroup_h
#define __otbWrapperQtWidgetParameterGroup_h

#include <QtGui>
#include "otbWrapperParameterList.h"

namespace otb
{
namespace Wrapper
{

/** \class
 * \brief
 */
class QtWidgetParameterGroup : public QWidget
{
  Q_OBJECT
public:
  QtWidgetParameterGroup(ParameterList);
  virtual ~QtWidgetParameterGroup();

private:
  QtWidgetParameterGroup(const QtWidgetParameterGroup&); //purposely not implemented
  void operator=(const QtWidgetParameterGroup&); //purposely not implemented

  void CreateWidget();

  ParameterList m_ParamList;

};


}
}

#endif
