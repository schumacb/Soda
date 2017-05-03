#! /bin/bash

NC='\033[0m'     # No Color
EC='\033[0;31m'  # Red
SC='\033[0;32m'  # Green
WC='\033[0;33m'  # Orange
IC='\033[0;34m'  # Blue

info() { echo -e "${IC}$1${NC}"; }
warn() { echo -e "${WC}Warning:${NC} $1"; }
error() { >&2 echo -e "${EC}Error: $1${NC}"; }
success() { echo -e "${SC}$1${NC}"; }

if [ ! $CC ] ; then
  warn "\$CC undefined! Setting it to: gcc"
  CC=gcc
fi

if [ ! $CXX ] ; then
  warn "\$CXX undefined! Setting it to: g++"
  CXX=g++
fi

if [ ! $SOURCE_DIR ] ; then
  warn "\$SOURCE_DIR undefined! Setting it to: ${PWD}"
  SOURCE_DIR=${PWD}
fi

if [ ! $BUILD_DIR ] ; then
  warn "\$BUILD_DIR undefined! Setting it to: ${SOURCE_DIR}/build"
  BUILD_DIR=${SOURCE_DIR}/build
fi

if [ ! $RUN_TESTS ] ; then
  warn "\$RUN_TESTS undefined! Setting it to: OFF"
  RUN_TESTS=OFF
fi

info "Setting up build directories"
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
mkdir -p gcc/release && mkdir -p gcc/debug
if [ $? -ne 0 ]; then
  error "Could not setup build directories!"
  exit 1
else
  success "Successfully generated build directories."
fi

info "Building Release"
cd ${BUILD_DIR}/${CC}/release
cmake -DCMAKE_BUILD_TYPE=Release \
  -G Ninja -DCMAKE_MAKE_PROGRAM=ninja \
  -DSODA_BUILD_TESTS=${RUN_TESTS} \
  ${SOURCE_DIR}
ninja -j8
if [ $? -ne 0 ]; then
  error "There are compile errors!"
  exit 2
else
  success "Successfully built Release"
fi

info "Building Debug"
cd ${BUILD_DIR}/${CC}/debug
cmake -DCMAKE_BUILD_TYPE=Debug \
  -G Ninja -DCMAKE_MAKE_PROGRAM=ninja  \
  -DSODA_BUILD_TESTS=OFF \
  ${SOURCE_DIR}
ninja -j8
if [ $? -ne 0 ]; then
  error "There are compile errors!"
  exit 3
else
  success "Successfully built GCC Debug"
fi

cd ${SOURCE_DIR}
if [ ${GENERATE_COVERAGE} ]; then
  info "Building GCC Release with debug info and --coverage"
  mkdir -p ${BUILD_DIR}/gcc/coverage
  cd ${BUILD_DIR}/gcc/coverage
  cmake  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++\
    -DCMAKE_CXX_FLAGS=--coverage \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -G Ninja -DCMAKE_MAKE_PROGRAM=ninja \
    -DSODA_BUILD_TESTS=ON -DSODA_GENERATE_COVERAGE=ON\
    ${SOURCE_DIR}
  ninja -j8 TestCoverage
  if [ $? -ne 0 ]; then
    error "There are compile errors!"
    exit 2
  else
    success "Successfully built clang Release for Test coverage"
  fi

  info "Running tests and Generate coverage"
  # capture coverage info
  lcov --directory . --capture --output-file coverage.info
  # filter result
  lcov --remove coverage.info '/usr/*' --output-file coverage.info
  lcov --remove coverage.info 'moc_*' --output-file coverage.info
  lcov --remove coverage.info 'test/' --output-file coverage.info
  # display results
  lcov --list coverage.info
  if [ ${UPLOAD_COVERAGE} ]; then
    info "Uploading report to CodeCov"
    bash <(curl -s https://codecov.io/bash) || error "Codecov did not collect coverage reports"
  fi
else 
  if [ ${RUN_TESTS} ] ; then
    info "Running tests on GCC Debug build"
    ${SOURCE_DIR}/bin/tests
  fi
fi
