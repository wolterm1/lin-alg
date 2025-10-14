#pragma once
#include <iostream>

struct EvalResult {
  float accuracy;
  float precision;
  float f1Score;
  friend std::ostream& operator<<(std::ostream& os, const EvalResult& Eval);
};
