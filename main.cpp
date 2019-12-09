#include "iostream"
#include "./include/interface/Interface.hpp"
#include <QWidget>
#include <QApplication>
#include <QLabel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Interface vv;
    vv.show();
    return app.exec();
}

// #include "./include/Device.hpp"
// #include "./include/Buffer.hpp"
// #include "./include/Source.hpp"
// #include "./include/interface/Auto.hpp"
// #include "./include/TimeManager.hpp"
// #include "./include/StatManager.hpp"
// #include "./include/ModulingUnit.hpp"

// #include <ctime>

// int main(int argc, char * argv[]) {
//     QApplication app(argc, argv);

//     ModulingUnit * modulingUnit = new ModulingUnit(3, 3, 3, 1000, 3, 0, 1);

//     Auto otsos(3,3, modulingUnit);

//     otsos.show();

//     return app.exec();


// //     std::srand(std::time(nullptr));

// //     const int SourceValue =	std::stoi(argv[1]);
// // 	const int BufferValue =	std::stoi(argv[2]);
// // 	const int DeviceValue =	std::stoi(argv[3]);
// // 	const int L =	std::stoi(argv[4]);

// //   StatManager statManager(L, SourceValue, DeviceValue);
// //   TimeManager timeManager(L, &statManager);
// //   Buffer buffer(&timeManager, &statManager, BufferValue);
// //   Source source(&timeManager, &buffer, &statManager, SourceValue);
// //   Device device(&timeManager, &buffer, &statManager, DeviceValue);

// //   while (!timeManager.done() || !source.done() || !buffer.isEmpty() || !device.done()) {
// // 		source.work();
// // 		device.work();
// // 		timeManager.work();
// // 	}
// //   statManager.printResult(timeManager.getCurrentTime());
// //   return 0;
// }