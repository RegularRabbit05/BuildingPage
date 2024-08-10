./build.sh > /dev/null
cd dist && python3 -m http.server $1 --bind 0.0.0.0