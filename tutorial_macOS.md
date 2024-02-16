# Building TensorFlow C++ Library for macOS M2

Building the TensorFlow C++ library for macOS, especially on the newer M2 chips, requires careful setup due to the architecture differences and dependencies. Here's how to successfully compile TensorFlow v2.15.0 and run a C++ example on macOS with an M2 chip.

## Prerequisites

Ensure you have Python, Bazel, and other necessary tools installed. If not, follow these steps:

1. **Install Homebrew**:
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install Python and Bazel**:
   ```bash
   brew install python bazel
   ```

3. **Install Additional Dependencies**:
   ```bash
   brew install coreutils automake libtool wget
   ```

## Building TensorFlow

Follow these steps to build the TensorFlow library:

1. **Create a Virtual Environment** (optional but recommended):
   ```bash
   python3 -m venv ~/tensorflow_venv
   source ~/tensorflow_venv/bin/activate
   pip install --upgrade pip numpy six
   ```

2. **Clone TensorFlow Repository**:
   ```bash
   git clone https://github.com/tensorflow/tensorflow.git
   cd tensorflow
   git checkout v2.15.0
   ```

3. **Configure TensorFlow Build**:
   Configure TensorFlow by running `./configure`. When asked, opt out of CUDA support unless you're specifically targeting GPU acceleration with external GPUs compatible with macOS.

4. **Build TensorFlow C++ Library**:
   Now, compile the TensorFlow C++ library targeting the ARM architecture of the M2 chip.
   ```bash
   bazel build --config=macos_arm64 //tensorflow:libtensorflow_cc.dylib
   ```

## Extracting TensorFlow Headers and Libraries

After building TensorFlow, extract the necessary libraries and headers:

1. **Extract TensorFlow C++ Library**:
   Locate and copy the built TensorFlow libraries (`libtensorflow_cc.so` and `libtensorflow_framework.so`) to your desired directory, e.g., `~/tensorflow_lib`.

2. **Copy Header Files**:
   TensorFlow's header files need to be collected from the source tree and copied to your include directory, e.g., `~/tensorflow_include`.

## Test with a C++ Example

Compile a simple TensorFlow C++ example to verify the installation:

1. **Example C++ Code**:
   Write or use an existing TensorFlow C++ example, such as `example_trainer.cc`, and save it to a file.

2. **Compile Your C++ Example**:
   Use `clang++` or `g++` with the appropriate flags to include the TensorFlow headers and link against the TensorFlow libraries.
   ```bash
   clang++ -std=c++14 -I${HOME}/tensorflow_include -L${HOME}/tensorflow_lib -ltensorflow_cc -ltensorflow_framework -o example_trainer example_trainer.cc
   ```

3. **Run Your Example**:
   Ensure that the dynamic libraries are found by setting the `DYLD_LIBRARY_PATH` environment variable before running your executable.
   ```bash
   export DYLD_LIBRARY_PATH=${HOME}/tensorflow_lib:$DYLD_LIBRARY_PATH
   ./example_trainer
   ```

**Note**: The above steps are tailored for macOS environments, specifically targeting ARM64 architecture found in M2 chips. Adjust paths and library names as necessary based on where you chose to extract TensorFlow libraries and headers.

## Conclusion
This tutorial simplifies the process of building and using the TensorFlow C++ library on macOS with M2 chips, covering everything from setting up the environment to compiling and running a simple TensorFlow C++ example.