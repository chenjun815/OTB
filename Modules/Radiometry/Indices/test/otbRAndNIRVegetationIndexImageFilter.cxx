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

#include "otbRAndNIRIndexImageFilter.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"

template<class TInputRImage, class TInputNIRImage, class TOutputImage, class TFunction>
int generic_RAndNIRVegetationIndexImageFilter(int itkNotUsed(argc), char * argv[])
{
  typedef otb::ImageFileReader<TInputRImage>   RReaderType;
  typedef otb::ImageFileReader<TInputNIRImage> NIRReaderType;
  typedef otb::ImageFileWriter<TOutputImage>   WriterType;

  typedef otb::RAndNIRIndexImageFilter<TInputRImage, TInputNIRImage, TOutputImage, TFunction>
  RAndNIRIndexImageFilterType;

  // Instantiating object
  typename RAndNIRIndexImageFilterType::Pointer filter = RAndNIRIndexImageFilterType::New();
  typename RReaderType::Pointer readerR = RReaderType::New();
  typename NIRReaderType::Pointer readerNIR = NIRReaderType::New();
  typename WriterType::Pointer writer = WriterType::New();

  const char * inputFilenameR  = argv[1];
  const char * inputFilenameNIR  = argv[2];
  const char * outputFilename = argv[3];

  readerR->SetFileName(inputFilenameR);
  readerNIR->SetFileName(inputFilenameNIR);
  writer->SetFileName(outputFilename);
  filter->SetInputR(readerR->GetOutput());
  filter->SetInputNIR(readerNIR->GetOutput());
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

int otbRAndNIRVegetationIndexImageFilter(int argc, char * argv[])
{
  const unsigned int Dimension = 2;
  typedef double                   PixelType;
  typedef otb::Image<PixelType, Dimension> InputRImageType;
  typedef otb::Image<PixelType, Dimension> InputNIRImageType;
  typedef otb::Image<double, Dimension>    OutputImageType;

  std::string strArgv(argv[1]);
  argc--;
  argv++;
  if (strArgv == "NDVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::NDVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "RVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::RVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "SAVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::SAVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "TSAVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::TSAVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "MSAVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::MSAVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "MSAVI2")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::MSAVI2<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "GEMI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::GEMI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "IPVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::IPVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "TNDVI")
    return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                otb::Functor::TNDVI<InputRImageType::PixelType,
                    InputNIRImageType::PixelType,
                    OutputImageType::PixelType> >
              (argc, argv));
  else if (strArgv == "LAIFormosat2")
      return (generic_RAndNIRVegetationIndexImageFilter<InputRImageType, InputNIRImageType, OutputImageType,
                  otb::Functor::LAIFromNDVIFormosat2Functor<InputRImageType::PixelType,
                      InputNIRImageType::PixelType,
                      OutputImageType::PixelType> >
                (argc, argv));
  else return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
