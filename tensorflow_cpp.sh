#!/bin/bash

# Install Homebrew if not already installed
if ! command -v brew &> /dev/null
then
    echo "Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
    echo "Homebrew is already installed."
fi

# Install Python, Bazel, and other necessary dependencies
echo "Installing Python, Bazelisk, and additional dependencies..."
brew install python bazel coreutils automake libtool wget

# Clone TensorFlow repository and checkout the desired version (v2.15.0 as an example)
echo "Cloning TensorFlow repository..."
git clone https://github.com/tensorflow/tensorflow.git
cd tensorflow
git checkout v2.15.0

# Configure TensorFlow build
echo "Configuring TensorFlow build..."
# Note: This step may require manual intervention to select build options
./configure

# Build TensorFlow C++ library
echo "Building TensorFlow C++ library..."
bazel build --config=macos_arm64 //tensorflow:libtensorflow_cc.dylib

# The following steps would typically involve copying the built libraries and headers to your project
# This example assumes you want to copy them to ~/tensorflow_lib and ~/tensorflow_include
# You might need to adjust these commands based on your specific requirements

# Make directories for libraries and headers
mkdir -p ~/tensorflow_lib
mkdir -p ~/tensorflow_include

# Copy the TensorFlow C++ library to the library directory
cp bazel-bin/tensorflow/libtensorflow_cc.dylib ~/tensorflow_lib/

# Copy TensorFlow headers to the include directory
# This step is more complex due to the headers being spread across multiple directories
# The command below is a simplified example and may need adjustments
cp -R bazel-tensorflow/external/eigen_archive/Eigen ~/tensorflow_include/
cp -R bazel-tensorflow/external/eigen_archive/unsupported ~/tensorflow_include/
cp -R bazel-genfiles/tensorflow ~/tensorflow_include/
cp -R tensorflow ~/tensorflow_include/
cp -R third_party ~/tensorflow_include/

echo "TensorFlow C++ installation and setup completed."
