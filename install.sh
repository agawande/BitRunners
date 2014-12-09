#!/bin/sh
cd src/
sudo cp -r * /var/www/html/
cd /var/www/
echo "Giving everybody the permission to write to the html folder:"
sudo chmod -R o+w html/
cd html/engine
sudo chmod a+x compile.sh
./compile.sh
