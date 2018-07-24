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

#include "itkMacro.h"

#include "otbMultiChannelRAndBAndNIRIndexImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

template<class TInputImage, class TOutputImage, class TFunction>
int generic_MultiChannelRAndBAndNIRVegetationIndexImageFilter(int itkNotUsed(argc), char * argv[])
{
  typedef otb::ImageFileReader<TInputImage>  ReaderType;
  typedef otb::ImageFileWriter<TOutputImage> WriterType;

  typedef otb::MultiChannelRAndBAndNIRIndexImageFilter<TInputImage, TOutputImage, TFunction>
  MultiChannelRAndBAndNIRIndexImageFilterType;

  // Instantiating object
  typename MultiChannelRAndBAndNIRIndexImageFilterType::Pointer filter =
    MultiChannelRAndBAndNIRIndexImageFilterType::New();
  typename ReaderType::Pointer reader = ReaderType::New();
  typename WriterType::Pointer writer = WriterType::New();

  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];
  unsigned int redChannel(::atoi(argv[3]));
  unsigned int blueChannel(::atoi(argv[4]));
  unsigned int nirChannel(::atoi(argv[5]));
  double       gamma(::atof(argv[6]));
  reader->SetFileName(inputFilename);
  writer->SetFileName(outputFilename);
  filter->SetRedIndex(redChannel);
  filter->SetBlueIndex(blueChannel);
  filter->SetNIRIndex(nirChannel);
  filter->GetFunctor().SetGamma(gamma);
  filter->SetInput(reader->GetOutput());
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

int otbMultiChannelRAndBAndNIRVegetationIndexImageFilter(int argc, char * argv[])
{
  const unsigned int Dimension = 2;
  typedef otb::VectorImage<double, Dimension> InputImageType;
  typedef otb::Image<double, Dimension>       OutputImageType;

  std::string strArgv(argv[1]);
  argc--;
  argv++;
  if (strArgv == "ARVI")
    return (generic_MultiChannelRAndBAndNIRVegetationIndexImageFilter<InputImageType, OutputImageType,
                otb::Functor::ARVI<InputImageType::
                    InternalPixelType,
                    InputImageType::
                    InternalPixelType,
                    InputImageType::
                    InternalPixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
