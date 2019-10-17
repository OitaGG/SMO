#include "Device.hpp"
#include "Buffer.hpp"
#include "Source.hpp"
#include "TimeManager.hpp"

#include <ctime>

int main(int argc, char * argv[]) {
  std::srand(std::time(nullptr));

  const int SourceValue =	std::stoi(argv[1]);
	const int BufferValue =	std::stoi(argv[2]);
	const int DeviceValue =	std::stoi(argv[3]);
	const int L =	std::stoi(argv[4]);

  TimeManager timeManager(L);
  Buffer buffer(&timeManager, BufferValue);
  Source source(&timeManager, &buffer, SourceValue);
  Device device(&timeManager, &buffer, DeviceValue);

  while (!timeManager.done()) {
		source.work();
		device.work();
		timeManager.work();
	}
  
  return 0;
}