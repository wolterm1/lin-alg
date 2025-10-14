#include "EvalResult.hpp"

std::ostream& operator<<(std::ostream& os, const EvalResult& Eval) {
  os << " Accuracy: " << Eval.accuracy <<
       " Precision: " << Eval.precision << 
       " F1 Score: " << Eval.f1Score ;
  return os;
}
