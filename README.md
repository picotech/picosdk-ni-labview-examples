# picosdk-ni-labview-examples

*picosdk-ni-labview-examples* is a set of National Instruments LabVIEW examples for PicoScope<sup>®</sup> oscilloscope and PicoLog<sup>®</sup> data logger products.

Examples are provided as a set of LabVIEW vi and llb files grouped by driver name, with sub-folders for 32-bit and 64-bit examples.

## Getting started

### Prerequisites

#### Microsoft Windows

* National Instruments LabVIEW Base Development System 10 or later (32-bit or 64-bit)

**Notes:** 

* Some files are saved with LabVIEW Base Development System 8.5 versions.

### Example dependencies

Some example vi files require common sub-vi files (e.g. PicoScopeAdcToVolts.vi for conversion of ADC counts to volts) which can be located in the shared folder.
If downloading files or the repository zip file you will need to download the contents of the shared folder from https://github.com/picotech/picosdk-ni-labview-shared. As this is a sub module.
If using Git the command is-
`git submodule update --init --recursive`

#### Zip Download files;

Main - https://github.com/picotech/picosdk-ni-labview-examples/archive/refs/heads/master.zip
Shared - https://github.com/picotech/picosdk-ni-labview-shared/archive/refs/heads/master.zip

### Installing drivers

Drivers are available via a separate driver package installer.

Wrappers binaries are available via a separate git repository.
*Note wrapper dll's are are only required for streaming or PicoConnect/Intelligent Probe examples.*

#### Windows

* Download and install the PicoSDK (32-bit or 64-bit) driver installer from our [Downloads page](https://www.picotech.com/downloads).

* Download the PicoSDK driver wrapper dll's (contains both 32-bit and 64-bit files). Contents can be downloaded as a zip file [here](https://github.com/picotech/picosdk-c-wrappers-binaries/archive/refs/heads/master.zip).

Unzip the package.

For 32-bit LabVIEW-

Copy the contents of the folder `Windows 32-bit` into location of the SDK dll files-

`C:\Program Files (x86)\Pico Technology\SDK\lib`

For 64-bit LabVIEW-

Copy the contents of the folder `Windows 64-bit` into location of the SDK dll files-

`C:\Program Files\Pico Technology\SDK\lib`

#### Note the following drivers/APIs are 64-bit only
psospa

### Programmer's Guides

You can download Programmer's Guides providing a description of the API functions for the relevant PicoScope or PicoLog driver from our [Documentation page](https://www.picotech.com/library/documentation).

## Obtaining support

Please visit our [Support page](https://www.picotech.com/tech-support) to contact us directly or visit our [Test and Measurement Forum](https://www.picotech.com/support/forum20.html) to post questions.

## Contributing

Contributions are welcome. Please refer to our [guidelines for contributing](.github/CONTRIBUTING.md) for further information.

## Contributions (excluding merged requests)

Code and ideas used for memory pointers used with 5000a streaming example-
https://github.com/picotech/picosdk-ni-labview-examples/pull/2/commits/c943c29d1e697c0e4a6fb1d5e91bb4a77d0d82e7

## Copyright and licensing

See [LICENSE.md](LICENSE.md) for license terms.

*PicoScope* and *PicoLog* are registered trademarks of Pico Technology Ltd. 

*Windows* is a registered trademark of Microsoft Corporation.

*LabVIEW* is a registered trademark of National Instruments Corporation.

Copyright © 2005-2023 Pico Technology Ltd. All rights reserved.

