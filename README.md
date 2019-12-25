# ContractNotifier
An application for my school's principal to notify him for contracts expiry.
The main cause of this application is to store contracts, and notify the user of the expiry date of the contract.
I know that there is probably alot of solutions out there. But apparently my school principle found non, and then resorted to me.

# Features
- Store millions of contracts (impractically huge number) and organize them into categories. <br>
- Ability to notify the user in two ways, by email, and notifications. Both can be enabled/disables seperately. <br>
- Mutli-threaded capabilities. <br>
- Reliably export and import databases for easy backups/transfers. <br>

## Benchmarks:
The applicaiton is quite fast, with ability to search 1M contracts in ```0.890232``` seconds.

## Getting Started for Consumers
The binaries can be found at the releases section at the top of this page.

## Getting Started for Developers

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

On linux you would need the qt5 development set. Can be found [here](https://wiki.qt.io/Install_Qt_5_on_Ubuntu). <br>

On windows on the other hand you would need to download vcpkg, MAKE SURE YOU INSTALL IT in "C:\", [here](https://wiki.qt.io/Install_Qt_5_on_Ubuntu)

### Building

#### On Linux

To build DEBUG:
```
./build.sh
```

To build RELEASE:
```
./buildRelease.sh
```

#### On Windows:

NOTE: Make sure the following commands are run on the visual studio command prompt.

To build DEBUG:
```
build.bat
```

To build RELEASE:
```
build.bat
```

#### Running the app:

On linux just go to bin and run ```./contractNotifier``` <br>

On windows, copy the files of ```icon.png``` and ```notifue.exe``` to the respective DEBUG/RELEASE folder. <br>
Then run ```contractNotifier.exe```

## Running the benchmars

Currently there are two benchmarks available.
The examples are build automatically, and should be found in the ```bin```/```bin/${RELEASE/DEBUG}```, on
linux and windows respectfully.

### Running dataBenchmark
This tests the speed of serializing and deserializing the data. <br>
To run the benchmark simply hope on a terminal/vsconsole and run ```./dataBenchmark```/```dataBenchmark.exe```

### Running searchBencmark
This test the speed of searching a 1M entry database. <br>
To run the benchmark simply hope on a terminal/vsconsole and run ```./searchBenchmark```/```searchBenchmark.exe```

## Deployment

Currently binary installer are only supported on windows.
To build installer on windows:
- Run ```buildRelease.bat```.
- Open project solution in ```build``` directory.
- Click ```PACKAGE``` -> ```Build Project```.
- Installer now should be in ```build/_CPack_Packages```.

## Built With

* [C++](https://en.wikipedia.org/wiki/C%2B%2B) - Language.
* [CMake](https://cmake.org/) - Build system.
* [vcpkg](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019) - Windows Dependency Manager.
* [Boost](https://www.boost.org/) - Serialization/Deserialization.
* [Qt5](https://en.wikipedia.org/wiki/Qt_(software)) - Window Library.

## Authors

* **altffour** - *Initial work* - [altffour](https://github.com/realaltffour)

## License

This project is licensed under the GPL-v3.0 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip for my school principle for the idea
