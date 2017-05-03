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

if [ ! $SOURCE_DIR ] ; then
  warn "\$SOURCE_DIR undefined! Setting it to: ${PWD}"
  SOURCE_DIR=${PWD}
fi

if [ ! $BUILD_DIR ] ; then
  warn "\$BUILD_DIR undefined! Setting it to: ${SOURCE_DIR}/build"
  BUILD_DIR=${SOURCE_DIR}/build
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

info "Building GCC Release"
cd ${BUILD_DIR}/gcc
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_BUILD_TYPE=Release \
  -G Ninja -DCMAKE_MAKE_PROGRAM=ninja \
  ${SOURCE_DIR}
ninja -j8
if [ $? -ne 0 ]; then
    error "There are compile errors!"
    exit 2
else
  success "Successfully built GCC Release"
fi

info "Building GCC Debug"
cd ${BUILD_DIR}/gcc/debug
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_BUILD_TYPE=Debug \
  -G Ninja -DCMAKE_MAKE_PROGRAM=ninja  \
  -DSODA_BUILD_TESTS=ON \
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
    info "Running tests and Generate coverage"
    kcov --exclude-path=/usr/ --exclude-pattern=moc_ . bin/tests
    if [ ${UPLOAD_COVERAGE} ]; then
        info "Uploading report to CodeCov"
        bash <(curl -s https://codecov.io/bash) || error "Codecov did not collect coverage reports"
    fi
else 
    if [ ${RUN_TESTS} ] ; then
        info "Running tests on GCC Debug build"
        ./bin/tests
    fi
fi

