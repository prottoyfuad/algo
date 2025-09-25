
g++ -DLOCAL asn.cpp -o asn
g++ -DLOCAL brute.cpp -o brt
g++ -DLOCAL gen.cpp -o gen

for((tc = 1; ; ++tc)); do
  echo $tc
  ./gen.exe $tc >in
  ./asn.exe <in >out
  ./brt.exe <in >res
  diff -w res out || break
done
