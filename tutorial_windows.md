# Building TensorFlow C++ Library for Windows 11

Compiling the TensorFlow C++ library on Windows 11 requires navigating different challenges compared to macOS, mainly due to the differences in available development tools and the operating system's architecture. This guide walks you through compiling TensorFlow v2.15.0 and running a C++ example on Windows 11.

## Prerequisites

Before starting, ensure you have Python, Bazel, and other necessary tools installed. Here's how to set up your environment:

1. **Install Python 3.11**:
   Download the following installer from the [official Python downloads page](https://www.python.org/ftp/python/3.11.7/python-3.11.7-amd64.exe), install and follow the instructions. Make sure to check the "Add Python to PATH" option during installation. or add it manually from the system settings.

   ```cmd
   python --version
   ```

2. **Install Microsoft Visual C++ Redistributable**:
   Download and install the latest Visual C++ Redistributable from the [Microsoft Download Center](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0), or directly from [here](https://aka.ms/vs/17/release/vc_redist.x64.exe)


3. **Install Visual Studio Code (optional for easy development)**:
   Download and install Visual Studio Code from the [official website](https://code.visualstudio.com/)
   - Install the C/C++ extension from the Extensions view (`Ctrl+Shift+X`).
   - Install the C++ extension from the Extensions view (`Ctrl+Shift+X`).
   - Install the CMake Tools extension from the Extensions view (`Ctrl+Shift+X`).
   - Install Python extension from the Extensions view (`Ctrl+Shift+X`).
   - Install Jupyter Notebook extension from the Extensions view (`Ctrl+Shift+X`).


4. **Install Bazel**:
   - Download Bazelisk from [GitHub](https://github.com/bazelbuild/bazelisk/releases/download/v1.19.0/bazelisk-windows-amd64.exe).
   - Rename the downloaded file to `bazel.exe` and add it to your system's PATH.
   - Verify the installation by running:
     ```cmd
     bazel --version
     ```
   - Bazelisk is a wrapper for Bazel that automatically downloads the correct version of Bazel for your project.


5. **Install Git**:
   If not already installed, download and install Git from [Git for Windows](https://git-scm.com/download/win), or directly from [here](https://github.com/git-for-windows/git/releases/download/v2.43.0.windows.1/Git-2.43.0-64-bit.exe).

## Building TensorFlow

With the prerequisites in place, you're ready to build TensorFlow:

1. **Open a Command Prompt**:
   Right-click on the Start menu, select "Command Prompt (Admin)" or "Windows PowerShell (Admin)", and navigate to your desired working directory.

2. **Clone TensorFlow Repository**:
   ```cmd
   git clone https://github.com/tensorflow/tensorflow.git
   cd tensorflow
   git checkout v2.15.0
   ```

3. **Configure TensorFlow Build**:
   TensorFlow's configuration on Windows will prompt you for various options, such as Python and CUDA paths. Run the configuration script:
   ```cmd
   .\configure
   # click Enter for all to accept the default values
   ```
   Answer the prompts according to your setup. For a basic CPU-only build, you can decline CUDA support.

4. **Build TensorFlow C++ Library**:
   Use Bazel to build the TensorFlow C++ library:
   ```cmd
   bazel build --config=opt //tensorflow:tensorflow_cc.dll
   ```
   This command compiles the TensorFlow C++ library (`tensorflow_cc.dll`) optimized for Windows.

## Extracting TensorFlow Headers and Libraries

After building TensorFlow, you need to collect the compiled libraries and header files:

1. **Locate Compiled Libraries**:
   Find `tensorflow_cc.dll` and `tensorflow_framework.dll` in the `bazel-bin\tensorflow` directory. Copy them to your project or a known location.

2. **Copy Header Files**:
   TensorFlow header files are located within the source tree. Copy the entire `tensorflow\include` directory to your project or another known location for easy access.

## Test with a C++ Example

Verify the setup by compiling a simple TensorFlow C++ example:

1. **Create a C++ Example File**:
   Save an example TensorFlow C++ file, such as `example_trainer.cc`, in your project directory.

2. **Compile Your C++ Example**:
   Use Visual Studio's `cl.exe` or another C++ compiler that's compatible with your setup, ensuring to include the TensorFlow headers and link against the TensorFlow libraries. The exact command will vary based on your compiler and setup.

3. **Run Your Example**:
   Execute the compiled program from the Command Prompt or PowerShell to see it in action.


## Extra Steps for Installing C compiler and support for CMake

1. **Install CMake**:
   - Download the latest CMake installer from the [official website](https://cmake.org/download/).
   - Run the installer and follow the instructions.
   - Add CMake to your system's PATH.
   - Verify the installation by running:
     ```cmd
     cmake --version
     ```
2. **Install C++ Compiler**:
3. **Install Visual Studio Build Tools**:
   - Download the Visual Studio Build Tools installer from the [official website](https://visualstudio.microsoft.com/visual-cpp-build-tools/).
   - Run the installer and select the "C++ build tools" workload.
   - Follow the instructions to complete the installation.
   - Verify the installation by running:
     ```cmd
     cl
     ```
   - If the command is not recognized, ensure that the Visual Studio Build Tools are correctly installed and added to your system's PATH.
   - If you have Visual Studio installed, you can use the Developer Command Prompt for Visual Studio to access the `cl` compiler.
   - If you have MinGW or another C++ compiler installed, you can use it instead of the Visual Studio Build Tools.
   - Make sure to adjust the compiler and linker flags in your C++ build commands accordingly.
   - For example, you might use `g++` as the compiler and `-ltensorflow_cc -ltensorflow_framework` as the linker flags when compiling your C++ example.

## Troubleshooting
- for C compiler check this [link](https://code.visualstudio.com/docs/languages/cpp)
- For Installing Bazelisk check this [link](https://github.com/bazelbuild/bazelisk)
- For Building TensorFlow on Windows check this [link](https://www.tensorflow.org/install/source_windows)
- For C++ API check this [link](https://www.tensorflow.org/api_docs/cc)
- check these commands [here](https://github.com/ylipacbio/tfccs/blob/master/script/install-tf/compile-tensorflow-c%2B%2B.sh)
- [here](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/tools/lib_package/README.md)
## Conclusion

This guide has outlined the steps to build and use the TensorFlow C++ library on Windows 11, covering the setup of necessary tools, building TensorFlow from source, and compiling a simple C++ example to verify the installation.


This adjusted tutorial provides an overview for Windows 11 users, highlighting key differences like tool installation and build commands. Make sure to follow the linked official documentation for detailed steps on installing prerequisites like Bazel and Visual Studio Build Tools.