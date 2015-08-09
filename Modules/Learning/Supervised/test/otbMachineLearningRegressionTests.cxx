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


#include "otbNeuralNetworkMachineLearningModel.h"
#include "otbSVMMachineLearningModel.h"

typedef float PrecisionType;
typedef otb::MachineLearningModel<PrecisionType,PrecisionType>   MachineLearningModelRegressionType;
typedef MachineLearningModelRegressionType::InputValueType       InputValueRegressionType;
typedef MachineLearningModelRegressionType::InputSampleType      InputSampleRegressionType;
typedef MachineLearningModelRegressionType::InputListSampleType  InputListSampleRegressionType;
typedef MachineLearningModelRegressionType::TargetValueType      TargetValueRegressionType;
typedef MachineLearningModelRegressionType::TargetSampleType     TargetSampleRegressionType;
typedef MachineLearningModelRegressionType::TargetListSampleType TargetListSampleRegressionType;

const double epsilon = 0.1;

template <typename TPrecision>
struct LinearFunctionSampleGenerator
{
  typedef TPrecision PrecisionType;
  LinearFunctionSampleGenerator(TPrecision a, TPrecision b)
    : m_a(a), m_b(b), m_NbInputVars(1), m_NbOutputVars(1) {
    m_isl = InputListSampleRegressionType::New();
    m_tsl = TargetListSampleRegressionType::New();
    std::srand(0);
  };
  void GenerateSamples(TPrecision sMin, TPrecision sMax, size_t nbSamples)
  {
    m_isl->SetMeasurementVectorSize(m_NbInputVars);
    m_tsl->SetMeasurementVectorSize(m_NbOutputVars);

    TPrecision sampleStep = (sMax-sMin)/nbSamples;
    for(size_t i=0; i<nbSamples; ++i)
      {
      InputSampleRegressionType inputSample;
      inputSample.Reserve(m_NbInputVars);
      TPrecision x = std::rand()/static_cast<TPrecision>(RAND_MAX)*nbSamples;
      TPrecision inputValue = sMin+ x*sampleStep;
      inputSample[0] = inputValue;
      TPrecision outputValue = m_a*inputValue+m_b;
      m_isl->PushBack(inputSample);
      m_tsl->PushBack(outputValue);
      }
  }

  TPrecision m_a;
  TPrecision m_b;
  const size_t m_NbInputVars;
  const size_t m_NbOutputVars;
  InputListSampleRegressionType::Pointer m_isl;
  TargetListSampleRegressionType::Pointer m_tsl;

};

template <typename SampleGeneratorType, typename RegressionType>
int validate(SampleGeneratorType& sg, RegressionType& rgrsn)
{
  std::cout << "Validation\n";
  //Check the prediction accuracy
  typename InputListSampleRegressionType::Iterator sampleIt = sg.m_isl->Begin();
  typename TargetListSampleRegressionType::Iterator resultIt = sg.m_tsl->Begin();
  typename InputListSampleRegressionType::Iterator sampleLast = sg.m_isl->End();
  typename TargetListSampleRegressionType::Iterator resultLast = sg.m_tsl->End();
  typename SampleGeneratorType::PrecisionType rmse = 0.0;
  size_t nbSamples = 0;
  while(sampleIt != sampleLast && resultIt != resultLast)
    {
    typename SampleGeneratorType::PrecisionType invalue = sampleIt.GetMeasurementVector()[0];
    typename SampleGeneratorType::PrecisionType prediction = rgrsn->Predict(sampleIt.GetMeasurementVector())[0];
    typename SampleGeneratorType::PrecisionType expected = resultIt.GetMeasurementVector()[0];
    rmse += pow(prediction - expected, 2.0);
    ++sampleIt;
    ++resultIt;
    ++nbSamples;
    } 

  rmse /= nbSamples;
  if(rmse > epsilon)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

int otbNeuralNetworkRegressionLinearMonovariate(int itkNotUsed(argc), 
                                                char * itkNotUsed(argv) [])
{

  LinearFunctionSampleGenerator<PrecisionType> lfsg(1.0, 0.0);
  std::cout << "Generating samples\n";
  lfsg.GenerateSamples(-0.5, 0.5, 20000);
  typedef otb::NeuralNetworkMachineLearningModel<InputValueRegressionType,
                                                 TargetValueRegressionType> 
    NeuralNetworkType;
  NeuralNetworkType::Pointer regression = NeuralNetworkType::New();

  regression->SetRegressionMode(1);
  regression->SetTrainMethod(CvANN_MLP_TrainParams::BACKPROP);
  std::vector<unsigned int> layerSizes;
  layerSizes.push_back(1);
  layerSizes.push_back(5);
  layerSizes.push_back(1);
  regression->SetLayerSizes(layerSizes);
  regression->SetActivateFunction(CvANN_MLP::SIGMOID_SYM);
  regression->SetAlpha(1.0);
  regression->SetBeta(1.0);
  regression->SetBackPropDWScale(0.1);
  regression->SetBackPropMomentScale(0.1);
  regression->SetRegPropDW0(0.1);
  regression->SetRegPropDWMin(1e-7);
  regression->SetTermCriteriaType(CV_TERMCRIT_EPS);
  regression->SetEpsilon(1e-5);
  regression->SetMaxIter(1e20);

  regression->SetInputListSample(lfsg.m_isl);
  regression->SetTargetListSample(lfsg.m_tsl);
  std::cout << "Training\n";
  regression->Train();

  return validate(lfsg, regression);
}

  
int otbSVMRegressionLinearMonovariate(int itkNotUsed(argc), 
                                      char * itkNotUsed(argv) [])
{

  LinearFunctionSampleGenerator<PrecisionType> lfsg(1.0, 0.0);
  std::cout << "Generating samples\n";
  lfsg.GenerateSamples(-0.5, 0.5, 200);
  typedef otb::SVMMachineLearningModel<InputValueRegressionType,
                                       TargetValueRegressionType> 
    SVMType;
  SVMType::Pointer regression = SVMType::New();

  regression->SetRegressionMode(1);
  regression->SetNu(0.5);
  regression->SetKernelType(CvSVM::RBF);
  regression->SetTermCriteriaType(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS);
  regression->SetMaxIter(100000);
  regression->SetEpsilon(1e-5);
  regression->SetParameterOptimization(true);

  regression->SetInputListSample(lfsg.m_isl);
  regression->SetTargetListSample(lfsg.m_tsl);
  std::cout << "Training\n";
  regression->Train();

  return validate(lfsg, regression);
}
