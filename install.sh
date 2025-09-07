prj_dir=$(pwd)
cd ../

if [ -d "./codec/" ]
then
	cd ./codec/

	if [ ! -d "./.git/" ]
	then
		git init
		git remote add origin https://github.com/TheScienceUniverse/codec.git
	fi;

	echo "Updating codec project..."
	git pull origin master

	cd ../
else
	echo "Fetching codec project..."
	git clone https://github.com/TheScienceUniverse/codec.git --single-branch --depth 1
fi;

cd ./codec/

echo "Configuring project for fresh build..."
sh configure.sh

echo "Building library..."
make clean
make again
make check &> /dev/null

echo "Creating log directory (DON'T DELETE)..."
mkdir -p ../log/
#cp ./inc/* ../inc/
#cp ./lib/libdsa.so ../lib/

cd $prj_dir
echo "...Installation Done!"
