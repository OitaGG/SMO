#include "Device.hpp"
#include "Buffer.hpp"
#include "Source.hpp"
#include "TimeManager.hpp"
#include "StatManager.hpp"

#include <ctime>

int main(int argc, char * argv[]) {
  std::srand(std::time(nullptr));

  const int SourceValue =	std::stoi(argv[1]);
	const int BufferValue =	std::stoi(argv[2]);
	const int DeviceValue =	std::stoi(argv[3]);
	const int L =	std::stoi(argv[4]);

  StatManager statManager(L, SourceValue, DeviceValue);
  TimeManager timeManager(L, &statManager);
  Buffer buffer(&timeManager, &statManager, BufferValue);
  Source source(&timeManager, &buffer, &statManager, SourceValue);
  Device device(&timeManager, &buffer, &statManager, DeviceValue);

  while (!timeManager.done() || !source.done() || !buffer.isEmpty() || !device.done()) {
		source.work();
		device.work();
		timeManager.work();
	}
  statManager.printResult(timeManager.getCurrentTime());
  return 0;
}