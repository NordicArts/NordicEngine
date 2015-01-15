NordicEngine
========
- OS interactions
- Rendering
- Maths [glm](https://github.com/g-truc/glm)
- Lua Integration [LuaBridge](https://github.com/Nulifier/LuaBridge)
- Storage support (using SQLite) {very very basic query builder}
- UnitTests using [Catch](https://github.com/philsquared/Catch)

- Option to build OS parts only with the build script

=== Build Script ===
This script can build, clean, and grab new versions,
    Rebuild = Clean and Build
    Pull = Clean, Pull Dependencies and Build

OPTIONS:
    -h  Show this message
    -v  Verbose    
    -p  Pull, pulls the latest code and all its gitmodules
    -t  Test Build, once built run the unit tests
    -o  Option, can be 'build', 'rebuild', 'full' or 'os' [default: build]
