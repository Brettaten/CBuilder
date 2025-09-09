
# CBuilder 

## A simple builder and test framework for c, that is able to create and compile a project automatically

# Features

* Create a new project: `cbuilder create [-p PATH]`
    * Path specifies the location of the project
    * Path can be relative or absolute
    * If path is omitted, the cwd is used
    * No other CBuilder project is allowed to exist somewhere up the directory tree
    * This command will create a [CBuilder project](#architecture) at the specified path
* Build a project: `cbuilder build [-d] [-p PATH]`
    * All path relating rules from the first command apply here as well
    * CBuilder looks for a CBuilder project by going up the directory tree
    * The statement above implies, that the command does not have to be executed from the project root
    * The **-d** flag can be set to compile with debug information
    * When using this command, all c files in `src/main/c` will be compiled to object files, which will <br>
    be placed in `target/prod` or `target/debug`, depending on the **-d** flag 
    * C files will not be compiled, if the corresponding object file exists and was created after the c file was last modified
    * After compilation, all object files in `target/prod` or `target/debug` will be linked to an executable, <br>
    that is placed in `bin`
* Clear a project: `cbuilder clear [-p PATH]`
    * All path relating rules from the first command apply here as well
    * CBuilder looks for a CBuilder project by going up the directory tree
    * The statement above implies, that the command does not have to be executed from the project root
    * This command will delete all files and sub directories in `target/prod` and `target/debug`
* Build the tests: `cbuilder test_build [-p PATH]`
    * All path relating rules from the first command apply here as well
    * CBuilder looks for a CBuilder project by going up the directory tree
    * The statement above implies, that the command does not have to be executed from the project root
    * CBuilder copies all c files from the `src/main/c` directory into the `test/src/project` directory
    * The c files are splitted into smaller c files, that contain just one function definition each and everything else <br>
    like function declarations will be the same for all split files. The static keyword will be removed
    * Because of this process, problems can occur. For instance, a static function might share one name with another function, after the file was split
    * Then the tests in `test/src/main/c` will be generated, thus there is no reason to add a main function in the test files
    * Use the assert function at `c/util/cbuilderTest.h`
    * Only files that start with \"test\" will be considered and only for functions that start with \"test\", a test will be generated
    * Functions that start with \"util\" will be ignored(copied), while every other function will be treated as a mock
    * Then every test will be compiled and linked with the split files. Debug information will be enabled, always
    * If a test contains a mock, cbuilder will look for a file that contains a function with that name among the split files <br>
    and if it finds it, this file will be excluded from linking. If the test does not contain a mock all files will be linked
    * There will be an executable at `test/bin` that concatenates all tests to one and separate executables in `test/bin/separate`
    * When calling tests separatly, use the argument \"1\" to signal that this will be the last test. This will ensure that the stats will be displayed and resetted
* Clear the tests: `cbuilder test_clear [-p PATH]`
    * All path relating rules from the first command apply here as well
    * CBuilder looks for a CBuilder project by going up the directory tree
    * The statement above implies, that the command does not have to be executed from the project root
    * This command will delete all files and sub directories in `test/src/project`, `test/src/main/genTests`, `test/target/project` and `test/target/test`
* Help: `cbuilder`, `cbuilder -h` or `cbuilder COMMAND -h`

# Architecture

```
CBuilder-project/                   |   The project root
├──bin/                             |   The location of the executable
├──src/                             |   The directory, where the entire development will take place
│    ├──main/                       |   The main directory
│    │    ├──c/                     |   The directory, where all c and header files will be located
│    │    └──ressources/            |   The directory, where additional ressources can be stored
│    └──test/                       |   The test directory
│         ├──bin/                   |   The location of the test executables
│         ├──src/                   |   The directory of the test source files
│         │    ├──main/             |   The main directory for tests
│         │    │    ├──c/           |   The directory, were all tests are located
│         │    │    │  └──util/     |   The directory, were test utils like the assert function are located 
│         │    │    └──genTests/    |   The directroy, were the generated tests will be stored
│         │    └──project/          |   The directory, were the copied and splitted files will be stored
│         └──target/                |   The directory, were all object files will be stored
│               ├──project/         |   The directory, were the object files of the project will be stored
│               └──test/            |   The directory, were the object files of the tests are stored
├──target/                          |   The directory, where all object files are located
│    ├──prod/                       |   The directory, where all object files without debug information are stored
│    └──debug/                      |   The directory, where all object files with debug information are stored
└──cbuilderfile                     |   The cbuilderfile
```

# cbuilderfile

* The cbuilderfile is used to achieve compiler independence
* The default compiler is gcc
* It is possible to alter the cbuilderfile
* It is not possible to add new commands
* To change the default, modifie the cbuilderfile of this repository at `src/main/ressources/cbuilderfile`

Each new CBuilder project generates a cbuilderfile, which looks like this:

```
build {
    cmd: "gcc -c $CFILE -o $OBJFILE"
}

debug {
    cmd: "gcc -c -g $CFILE -o $OBJFILE"
}

link {
    cmd: "gcc $OBJFILES -o $BINPATH/app"
}

linkTest {
    cmd: "gcc $OBJFILES -o $BINPATH"
}
```

* build
    * compiles one c file to an object file
    * **$CFILE** is a placeholder for the path to a c file
    * **$OBJFILE** is a placeholder for the path to the object file
* debug
    * compiles one c file to an object file with debug information
    * **$CFILE** is a placeholder for the path to a c file
    * **$OBJFILE** is a placeholder for the path to the object file
* link
    * links object files to create an executable
    * **$OBJFILES** is a placeholder for all paths to all object files located at <br>
    `target/prod` or `target/debug`
    * **$BINPATH** is a placeholder for the path to the **bin** directory of the project
* linkTest
    * links object files to create an executable
    * **$OBJFILES** is a placeholder for all paths to all object files located at <br>
    `target/prod` or `target/debug`
    * **$BINPATH** is a placeholder for the path to the **bin** directory of the project
    * the only difference to `link` is, that no name is specified, which allows the program <br>
    to create multiple executables in the same directory with custom names

# Support

* Windows
* Linux
* Mac

# Installation

1. Chose a directory for this repository and navigate to it <br>
    `cd PATH`
2. Clone this repository <br>
    `git clone https://github.com/Brettaten/CBuilder.git`
3. Add the path to the executable as an environment variable, based on your operating system <br>
    Windows: `PATH/CBuilder/bin/windows` <br>
    Linux: `PATH/CBuilder/bin/linux` <br>
    Mac: `PATH/CBuilder/bin/mac` <br>