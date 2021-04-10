rm images/*.pam
rm images/*.png

cp './lua/utils.lua' 'bin/'

cd bin
for s in ../lua/*.lua ; do \
  echo $s; \
  lua $s; \
done

cd ..

make images