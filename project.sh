#!/bin/bash

BUILD_DIRECTORY=build




#script begin

REPO_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source $REPO_ROOT_DIR/completion.sh
cd $REPO_ROOT_DIR

function __build {
    mkdir -p $BUILD_DIRECTORY
    cd $BUILD_DIRECTORY
    cmake ..
    make
    cd $REPO_ROOT_DIR
}

function __run {
    cd $BUILD_DIRECTORY
    ./project172
    cd $REPO_ROOT_DIR
}

function __debug {
    cd $BUILD_DIRECTORY
    gdb ./project172
    cd $REPO_ROOT_DIR
}

function __solve_dependencies {
    sudo apt update
    #sdl
    sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
    #vulkan
    sudo apt install vulkan-sdk
}

function __help {
    printf "This script can do some job with the project\n\nhelp:\n"
    printf "\tbuild              - build project\n"
    printf "\trun                - run built project\n"
    printf "\tdebug              - run in debug mode\n"
    printf "\tbuild-run          - first build, than run\n"
    printf "\tbuild-debug        - first build, than debug\n"
    printf "\tsolve-dependencies - install all libraries\n"
    printf "\thelp               - help\n"
    printf "\nTo enable auto completion type: source ./completion.sh\n"
}


if [[ "$1" == "build" ]]; then
__build
elif [[ "$1" == "build-run" ]]; then
__build
__run
elif [[ "$1" == "build-debug" ]]; then
__build
__debug
elif [[ "$1" == "run" ]]; then
__run
elif [[ "$1" == "debug" ]]; then
__debug
elif [[ "$1" == "solve-dependencies" ]]; then
__solve_dependencies
elif [[ "$1" == "help" ]]; then
__help
else
echo "No arguments set. Print: ./project.sh help"
fi

