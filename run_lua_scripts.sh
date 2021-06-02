# The lua files need to be run from the ./bin folder, or I need to fix the lua path (lua doesn't resolve paths for libraries)
# I've created this shell script for cleaning up, running all the lua files, and then creating the images

rm images/*.pam
rm images/*.png
rm images/*.jpg

cp './lua/utils.lua' 'bin/'

cd bin
for s in ../lua/*.lua ; do \
  echo $s; \
  lua $s; \
done

cd ..

make images