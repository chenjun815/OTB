/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "otbExtern.h"

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

// Monteverdi includes (sorted by alphabetic order)
#include "mvdApplicationsBrowser.h"

int mvdApplicationsBrowserTest(int argc, char* argv[])
{ 
  //
  // instantiate applications browser
  mvd::ApplicationsBrowser *  browser = new mvd::ApplicationsBrowser();

  //
  // is search path set 
  if (argc > 1)
    {
    browser->SetAutoLoadPath(argv[1]);
    }

  //
  // print available applications or exit with failure
  if ( browser->GetAvailableApplications().size() == 0 )
    return EXIT_FAILURE;

  // return ok
  return EXIT_SUCCESS;
}
