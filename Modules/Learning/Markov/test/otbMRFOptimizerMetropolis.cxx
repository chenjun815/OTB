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



#include "otbMRFOptimizerMetropolis.h"
#include <fstream>
#include <cstdlib>

int otbMRFOptimizerMetropolis(int itkNotUsed(argc), char * argv[])
{
  const char * outputFile = argv[1];

  typedef otb::MRFOptimizerMetropolis MRFOptimizerType;

  MRFOptimizerType::Pointer object = MRFOptimizerType::New();

  MRFOptimizerType::ParametersType param(1);
  param.Fill(10.);
  object->SetParameters(param);
  object->InitializeSeed(0); // USED TO OVERPASS RANDOM CALCULATION

  std::ofstream file;
  file.open(outputFile);

  file << "Compute(0)                                       : " << object->Compute(0.) << std::endl;
  file << "Compute(-1.)                                     : " << object->Compute(-1.) << std::endl;

  file.close();

  return EXIT_SUCCESS;
}
