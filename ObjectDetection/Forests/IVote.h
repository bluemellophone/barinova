#pragma once

#include "vector"
#include "HoughSample.h"
#include <fstream>

class IVote
{
public:
  IVote(){};
  virtual ~IVote(){};

  virtual void ResetVote() = 0;

  virtual void UpdateVote(HoughSample *hs) = 0;

  virtual void WriteToFile(FILE *out) = 0;
  
  virtual void ReadFromFileVote(FILE *in, std::ofstream &monitor) = 0;
  // virtual void ReadFromFileVote(FILE *in) = 0;

  virtual void SetBlurRadius(double in_dBlurRadius) = 0;
};