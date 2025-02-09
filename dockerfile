# Use Ubuntu 24.00 as the base image
FROM gcc:13.2.0

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    wget \
    software-properties-common 

# Verify GCC installation
RUN gcc --version && \
    g++ --version
# Verify CMake installation
RUN cmake --version

# Set the working directory inside the container
WORKDIR /app

# Copy the project files into the container
COPY . .

# Create build directory
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Run the tests
RUN ctest

# Set the default command to run the executable
CMD ["./build/GCCTest"]