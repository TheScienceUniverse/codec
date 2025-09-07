echo "Cleaning residue..."
rm -rf ./codec/

echo "Fetching latest version..."
git clone https://github.com/TheScienceUniverse/codec.git

cd ./codec/

sh ./configure.sh

echo "Setting up directories..."
mkdir -p ./obj/ ./lib/ ./bin/

echo "Building library..."
make clean
make all

echo "Cleaning up...";
mv ./DSA/inc/ ./tmp/
rm -rf ./DSA/*
mv ./tmp/ ./DSA/inc/
rm -rf ./archive/
rm -rf ./.git/ ./.github/ ./aft/ ./bin/ ./cov/ ./doc/ ./font/ ./log/ ./media/ ./obj/ ./src/ ./tst/
rm -f .gitignore LICENSE
rm -f Makefile rerun
rm -f *.c *.sh

cd ../
echo "...Installation Done!"
