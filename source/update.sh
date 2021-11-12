rm -f ../mrtest.c ../mrtest.h
cd ./implementation && python3 ./combine_files.py && cd ..
mv ./implementation/mrtest.c ../mrtest.c
mv ./implementation/mrtest.h ../mrtest.h
