#! /bin/bash

PWD=/usr/local/bin/temp

wget -q http://192.168.0.220/xml -O "$PWD"/temp.xml

TEMPF=$(cat "$PWD"/temp.xml | grep '<TF>' | awk -F'>' '{print  $2}' | awk -F'<' '{print $1}')
TEMPG=$(cat "$PWD"/temp.xml | grep '<TG>' | awk -F'>' '{print  $2}' | awk -F'<' '{print $1}')
TEMPO=$(cat "$PWD"/temp.xml | grep '<TO>' | awk -F'>' '{print  $2}' | awk -F'<' '{print $1}')

echo -e "TEMPF=$TEMPF
TEMPG=$TEMPG
TEMPO=$TEMPO" >> /var/log/temps.log

mv "$PWD"/temp.xml /var/www/html/xml/

rrdtool update "$PWD"/tempo.rrd --template tempf:tempg:tempo N:$TEMPF:$TEMPG:$TEMPO
