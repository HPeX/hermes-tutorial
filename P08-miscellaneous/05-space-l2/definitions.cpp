#include "definitions.h"

double CustomExactSolution::value (double x, double y) const 
{
  return - pow(x, 4) * pow(y, 5); 
}

void CustomExactSolution::derivatives (double x, double y, double& dx, double& dy) const 
{
  dx = 0; // Not needed for L2 projections.
  dy = 0; // Not needed for L2 projections.
}

Ord CustomExactSolution::ord(Ord x, Ord y) const 
{
  return - pow(x, 4) * pow(y, 5);
}
