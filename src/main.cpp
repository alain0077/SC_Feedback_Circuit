#include "Simulation/MgrSim.h"
#include "Simulation/CBRT.h"
#include "Simulation/DIV.h"

using namespace std;

int main()
{
  auto sim = make_shared<Sim_CBRT>();

  make_shared<MgrSim>(sim)->run();
  
  return EXIT_SUCCESS;
}