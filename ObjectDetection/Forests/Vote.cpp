#include "Vote.h"
#include <fstream>

// ******************************************************************************
CVote::CVote()
{
  nSamples = 0;
  nFirst = 0;
  blurRadius = 0;
}

// ******************************************************************************
CVote::~CVote()
{    
}

// ******************************************************************************
void CVote::ResetVote() 
{
  nSamples = 0;
  offsets.clear();
  nFirst = 0;
}

// ******************************************************************************
void CVote::UpdateVote(HoughSample *hs)  
{
  if(hs->isObject)
  {
    offsets.push_back(hs->off);
    nFirst ++;
  }
  nSamples++;
}

// ******************************************************************************
void CVote::WriteToFile(FILE *out)  
{
  fwrite( (void *)&nSamples, sizeof(int), 1, out);
  int nOffsets = offsets.size();
  fwrite( (void *)&nOffsets, sizeof(int), 1, out);


  for(int i = 0; i < nOffsets; i++)
  {
    int offsetx = offsets[i].x;
    int offsety = offsets[i].y;
    fwrite( (void *)&offsetx, sizeof(int), 1, out);
    fwrite( (void *)&offsety, sizeof(int), 1, out);
  }
}

// ******************************************************************************
void CVote::ReadFromFileVote(FILE *in, std::ofstream &monitor)
// void CVote::ReadFromFileVote(FILE *in)  
{
  monitor << "[Leaf] ";

  fread( (void *)&nSamples, sizeof(int), 1, in);
  monitor << "sizeTotal<ratio>(" << nSamples << ") ";

  int nOffsets;
  fread( (void *)&nOffsets, sizeof(int), 1, in);
  monitor << "size(" << nOffsets << ") ";

  // std::cout << nSamples << " " << nOffsets << std::endl;
  offsets.clear();
  nFirst = nOffsets;
  offsets.reserve(nOffsets);
  monitor << "vector[";
  for(int i = 0; i < nOffsets; i++)
  {
    CvPoint2D64f off;
    int dx, dy;

    fread( (void *)&dx, sizeof(int), 1, in);    
    fread( (void *)&dy, sizeof(int), 1, in);
    monitor << "(x[" << dx << "] , y[" << dy << "]) ";

    if(dx > 1000 || dy > 1000)
    {
      std::cout << dx << " " << dy << std::endl;
    }

    off.x = dx;
    off.y = dy;
    offsets.push_back(off);
  }
  monitor << "]" << std::endl;
  // std::cout << ftell(in) << std::endl << std::endl << std::endl;
  
}



// ******************************************************************************
void CVote::SetBlurRadius(double in_dBlurRadius)
{
  blurRadius = in_dBlurRadius;
}