/*=========================================================================

Library:   TubeTK

Copyright 2010 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved. 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <itkImage.h>
#include "itkFilterWatcher.h"
#include <itkExceptionObject.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkNJetImageFunction.h>

int itkNJetImageFunctionTest(int argc, char* argv [] ) 
{
  if( argc < 4 )
    {
    std::cerr << "Missing arguments." << std::endl;
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " function inputImage outputImage" << std::endl;
    return EXIT_FAILURE;
    }
  
  // Define the dimension of the images
  const unsigned int Dimension = 2;

  // Define the pixel type
  typedef float PixelType;
  
  // Declare the types of the images
  typedef itk::Image<PixelType, Dimension>  ImageType;

  // Declare the reader and writer
  typedef itk::ImageFileReader< ImageType > ReaderType;
  typedef itk::ImageFileWriter< ImageType > WriterType;
  
 
  // Declare the type for the Filter
  typedef itk::NJetImageFunction< ImageType > FunctionType;

  // Create the reader and writer
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[2] );
  try
    {
    reader->Update();
    }
  catch (itk::ExceptionObject& e)
    {
    std::cerr << "Exception caught during read:\n"  << e;
    return EXIT_FAILURE;
    }

  ImageType::Pointer inputImage = reader->GetOutput();

  typedef itk::NJetImageFunction< ImageType >   FunctionType;
  FunctionType::Pointer func = FunctionType::New();
  func->SetInputImage( inputImage );

  ImageType::Pointer outputImage = ImageType::New();
  outputImage->CopyInformation( inputImage );
  outputImage->SetRegions( inputImage->GetLargestPossibleRegion() );
  outputImage->Allocate();

  bool error = false;

  func->ComputeStatistics();
  func->SetUseProjection( false );
  double minI = 0;
  double maxI = 255;
  if( func->GetMin() != 0 )
    {
    error = true;
    std::cerr << "Min = " << func->GetMin() << " != " << minI << std::endl;
    }
  if( func->GetMax() != maxI )
    {
    error = true;
    std::cerr << "Max = " << func->GetMax() << " != " << maxI << std::endl;
    }

  double scale = 4.0;

  FunctionType::VectorType v1, v2, d;
  FunctionType::MatrixType h;
  v1.Fill(0);
  v2.Fill(0);
  v1[0] = 1;
  v2[1] = 1;
  double val;

  int function = atoi( argv[1] );

  itk::ImageRegionIteratorWithIndex< ImageType > outIter( outputImage,
    outputImage->GetLargestPossibleRegion() );
  ImageType::PointType pnt;
  outIter.GoToBegin();
  while( !outIter.IsAtEnd() )
    {
    inputImage->TransformIndexToPhysicalPoint( outIter.GetIndex(), pnt);
    switch( function )
      {
      case 0:
        {
        outIter.Set( func->Evaluate( pnt, scale ) );
        break;
        }
      case 1:
        {
        outIter.Set( func->Evaluate( pnt, v1, scale ) );
        break;
        }
      case 2:
        {
        outIter.Set( func->Evaluate( pnt, v1, v2, scale ) );
        break;
        }
      case 3:
        {
        outIter.Set( func->EvaluateAtIndex( outIter.GetIndex(), scale ) );
        break;
        }
      case 4:
        {
        outIter.Set( func->EvaluateAtIndex( outIter.GetIndex(), v1, scale ) );
        break;
        }
      case 5:
        {
        outIter.Set( func->EvaluateAtIndex( outIter.GetIndex(),
            v1, v2, scale ) );
        break;
        }
      case 6:
        {
        func->Derivative( pnt, scale, d );
        outIter.Set( d[0]+d[1] );
        break;
        }
      case 7:
        {
        func->Derivative( pnt, v1, scale, d );
        outIter.Set( d[0]+d[1] );
        break;
        }
      case 8:
        {
        func->Derivative( pnt, v1, v2, scale, d );
        outIter.Set( d[0]+d[1] );
        break;
        }
      case 9:
        {
        func->DerivativeAtIndex( outIter.GetIndex(), scale, d );
        outIter.Set( d[0]+d[1] );
        break;
        }
      case 10:
        {
        func->DerivativeAtIndex( outIter.GetIndex(), v1, scale, d );
        outIter.Set( d[0]+d[1] );
        break;
        }
      case 11:
        {
        func->DerivativeAtIndex( outIter.GetIndex(), v1, v2, scale, d );
        outIter.Set( d[0]+d[1] );
        break;
        }
      case 12:
        {
        val = func->ValueAndDerivative(pnt, scale, d );
        outIter.Set( val+(d[0]+d[1]) );
        break;
        }
      case 13:
        {
        val = func->ValueAndDerivative(pnt, v1, scale, d );
        outIter.Set( val+(d[0]+d[1]) );
        break;
        }
      case 14:
        {
        val = func->ValueAndDerivative(pnt, v1, v2, scale, d );
        outIter.Set( val+(d[0]+d[1]) );
        break;
        }
      case 15:
        {
        val = func->ValueAndDerivativeAtIndex( outIter.GetIndex(), scale,
          d );
        outIter.Set( val+(d[0]+d[1]) );
        break;
        }
      case 16:
        {
        val = func->ValueAndDerivativeAtIndex( outIter.GetIndex(),
          v1, scale, d );
        outIter.Set( val+(d[0]+d[1]) );
        break;
        }
      case 17:
        {
        val = func->ValueAndDerivativeAtIndex( outIter.GetIndex(),
          v1, v2, scale, d );
        outIter.Set( val+(d[0]+d[1]) );
        break;
        }
      case 18:
        {
        val = func->Jet( pnt, d, h, scale );
        outIter.Set( val+d[0]+d[1]+(h[0][0]+h[1][1]) );
        break;
        }
      case 19:
        {
        val = func->JetAtIndex( outIter.GetIndex(), d, h, scale );
        outIter.Set( val+d[0]+d[1]+(h[0][0]+h[1][1]) );
        break;
        }
      case 20:
        {
        val = func->Ridgeness( pnt, scale );
        outIter.Set( val );
        break;
        }
      case 21:
        {
        val = func->Ridgeness( pnt, v1, scale );
        outIter.Set( val );
        break;
        }
      case 22:
        {
        val = func->Ridgeness( pnt, v1, v2, scale );
        outIter.Set( val );
        break;
        }
      case 23:
        {
        val = func->RidgenessAtIndex( outIter.GetIndex(), scale );
        outIter.Set( val );
        break;
        }
      case 24:
        {
        val = func->RidgenessAtIndex( outIter.GetIndex(), v1, scale );
        outIter.Set( val );
        break;
        }
      case 25:
        {
        val = func->RidgenessAtIndex( outIter.GetIndex(), v1, v2, scale );
        outIter.Set( val );
        break;
        }
      case 26:
        {
        val = func->RidgenessAndDerivative( pnt, scale, d );
        outIter.Set( val );
        break;
        }
      case 27:
        {
        val = func->RidgenessAndDerivative( pnt, v1, scale, d );
        outIter.Set( val );
        break;
        }
      case 28:
        {
        val = func->RidgenessAndDerivative( pnt, v1, v2, scale, d );
        outIter.Set( val );
        break;
        }
      case 29:
        {
        val = func->RidgenessAndDerivativeAtIndex( outIter.GetIndex(), 
          scale, d );
        outIter.Set( val+d[0]+d[1] );
        break;
        }
      case 30:
        {
        val = func->RidgenessAndDerivativeAtIndex( outIter.GetIndex(),
          v1, scale, d );
        outIter.Set( val+d[0]+d[1] );
        break;
        }
      case 31:
        {
        val = func->RidgenessAndDerivativeAtIndex( outIter.GetIndex(),
          v1, v2, scale, d );
        outIter.Set( val+d[0]+d[1] );
        break;
        }
      case 32:
        {
        func->Hessian( pnt, scale, h );
        outIter.Set( h[0][0]+h[1][1] );
        break;
        }
      case 33:
        {
        func->Hessian( pnt, v1, scale, h );
        outIter.Set( h[0][0]+h[1][1] );
        break;
        }
      case 34:
        {
        func->Hessian( pnt, v1, v2, scale, h );
        outIter.Set( h[0][0]+h[1][1] );
        break;
        }
      case 35:
        {
        func->HessianAtIndex( outIter.GetIndex(), scale, h );
        outIter.Set( h[0][0]+h[1][1] );
        break;
        }
      case 36:
        {
        func->HessianAtIndex( outIter.GetIndex(), v1, scale, h );
        outIter.Set( h[0][0]+h[1][1] );
        break;
        }
      case 37:
        {
        func->HessianAtIndex( outIter.GetIndex(), v1, v2, scale, h );
        outIter.Set( h[0][0]+h[1][1] );
        break;
        }
      }
    ++outIter;
    }

  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[3] );
  writer->SetInput( outputImage );
  writer->SetUseCompression( true );
  
  try
    {
    writer->Update();
    }
  catch (itk::ExceptionObject& e)
    {
    std::cerr << "Exception caught during write:\n"  << e;
    return EXIT_FAILURE;
    }

  // All objects should be automatically destroyed at this point
  return EXIT_SUCCESS;

}

