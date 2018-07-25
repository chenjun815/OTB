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

#include "otbObjectListExtern.h"

namespace otb {

// Explicit instanciation of common types
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<unsigned int, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<int, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<unsigned char, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<char, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<unsigned short, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<short, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<float, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<double, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<std::complex<int>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<std::complex<short>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<std::complex<float>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::Image<std::complex<double>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<unsigned int, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<int, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<unsigned char, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<char, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<unsigned short, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<short, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<float, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<double, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<std::complex<int>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<std::complex<short>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<std::complex<float>, 2>>;
template class OTBExtern_EXPORT_EXPLICIT_TEMPLATE ObjectList<otb::VectorImage<std::complex<double>, 2>>;

}