rm images/*.pam
rm images/*.png

cd bin

for s in ../lua/*.lua ; do \
  echo $s; \
  lua $s; \
done

cd ..

make images