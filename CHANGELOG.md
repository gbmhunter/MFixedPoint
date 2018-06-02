# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html) (as of v7.0.0).

## [Unreleased]

## [v8.0.1] - 2018-06-02

### Fixed
- Fixed bug where `std::string` and `std::ostream` headers were not included in `FpF.hpp`, closes #95.

## [v8.0.0] - 2018-02-12

### Added
- Added CLion project files, closes 92.
- Added overload support for printing To ostream using '<<' (and a 'ToString()' method), closes #67.
- Added unit tests for arithmetic between 'FpF' and 'int' objects.

### Fixed
- Fixed bug where code coverage library was looked for even if COVERAGE set to false, closes #91.
- Removed un-used 'CountLeadingZeros()' and 'fixinv()' functions from 'FpF.hpp'.
- Improved speed of FpF division and fixed incorrect result when BaseType was greater than 32 bits, closes #93.

## [v8.0.0-beta.2] - 2018-01-11

### Added
- Added compile time check to `FpF` class to make sure template parameters are the same before doing multiplication.
- Added README code to a new example folder (to make sure it compiles correctly).
- Added conversion methods, casting capabilities and associated unit tests for the `FpF` class.

### Fixed
- Removed reference to non-existant MFixedPoint library when linking the benchmark and unit test code.
- Fixed failing `sudo make install` command.
- Fixed failing FpF multiplication.
- Fixed bug where `FpF` constructor accepting a double was first converting value to a float.
- Example in README now compiles correctly.
- Fixed bug where bit-shifting was overflowing in fixed-point constructors from doubles because '1' was not being cast to BaseType first.

## [v8.0.0-beta.1] - 2018-01-09

### Added
- Added Visual Studio Code project files, closes #89.
- Added generic fixed-point classes (both slow and fast) with storage type for bits (aka base type) and overflow type templated, closes #90.

### Changed
- Improved the comments and code formatting of Fp32f.hpp.

### Removed
- All existing fixed-point classes! This is in favour of the generic fixed-point classes mentioned in the 'Added' section.

## [v7.0.1] - 2018-01-04

### Added
- Added MIT license as LICENSE.txt, closes #88.

## [v7.0.0] - 2017-12-13

### Added
- Added enclosing `mn` namespace for all source code, closes #84.
- Added this CHANGELOG.md file, closes #85.
- Added documentation to 'docs/', closes #87.
- Added code coverage support.

### Changed
- Changed the `Fp` namespace to `MFixedPoint` (to reflect actual project name), closes #86.
- Modified header guard macros to include the text `MN_MFIXEDPOINT_...` (to include organization/project name).

[Unreleased]: https://github.com/mbedded-ninja/CppTemplate/compare/v8.0.0...HEAD
[v8.0.0]: https://github.com/mbedded-ninja/CppTemplate/compare/v8.0.0-beta.2...v8.0.0
[v8.0.0-beta.2]: https://github.com/mbedded-ninja/CppTemplate/compare/v8.0.0-beta.1...v8.0.0-beta.2
[v8.0.0-beta.1]: https://github.com/mbedded-ninja/CppTemplate/compare/v7.0.1...v8.0.0-beta.1
[v7.0.1]: https://github.com/mbedded-ninja/CppTemplate/compare/v7.0.0...v7.0.1