#pragma once
#include "IVote.h"
#include <fstream>

class CVote : public IVote
{
public:
  CVote();
  virtual ~CVote();

  void ResetVote();

  void UpdateVote(HoughSample *hs);

  void WriteToFile(FILE *out);
  
  void ReadFromFileVote(FILE *in, std::ofstream &monitor);
  // void ReadFromFileVote(FILE *in);

  void SetBlurRadius(double in_dBlurRadius);
  
  int nSamples;
  int nFirst;
  std::vector<CvPoint2D64f> offsets;
  double blurRadius;

}; // end of class CVote
