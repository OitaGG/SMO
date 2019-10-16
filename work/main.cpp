#include "Device.hpp"
#include "Buffer.hpp"
#include "Source.hpp"

#include <ctime>

int main(int argc, char * argv[]) {
  std::srand(std::time(nullptr));

  int N1 	 = 	std::stoi(argv[1]);
	int N2 	 = 	std::stoi(argv[2]);
	int N3 	 = 	std::stoi(argv[3]);
	int L 	 = 	std::stoi(argv[4]);

  TimeManager timeManager(L);
  Source source(&timeManager, N1);
  Buffer buffer(&timeManager, N2);
  Device device(&timeManager, N3);

  while (!timeManager.done() || !source.done() || !buffer.isEmpty() || !device.done()) {
		source.work();
		device.work();
		timeManager.work();
	}
  
  return 0;
}