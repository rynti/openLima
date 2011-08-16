# Create the "bin"-directory (If not already exists)
mkdir ./bin

# Create the "resources"-directory (If not already exists)
mkdir ./bin/resources

# Copy the resources
cp ./resources/* ./bin/resources/

# Compile the program
g++ -lopenlima -o ./bin/limabeans main.cpp