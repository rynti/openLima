# Create the "bin"-directory (If not already exists)
mkdir ./bin

# Compile the engine
g++ -shared -fPIC -lglut -lGLU -lboost_signals -o ./bin/libopenlima.so ./src/openlima/input/*.cpp ./src/openlima/graphics/*.cpp

# Copy the source into /usr/include
sudo cp -r ./src/* /usr/include

# Copy the library binary file into /usr/lib
sudo cp ./bin/* /usr/lib