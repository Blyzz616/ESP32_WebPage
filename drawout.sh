#! /bin/bash

RRDTOOL=/usr/bin/rrdtool
PWD=/usr/local/bin/temp

# Set some colours
COLCANVAS=#36393f00
COLGRID=#888888
COLOUT=#5b80e0
#COLDAY=#00ff00
#COLWEEK=#995be0
#COLMONTH=#f760a7
#COLYEAR=#f760a7
#COLDECADE=#f760a7
COLRANK=#fff700
# Set the resolution of the graphs
RES="-w 425 -h 200"
# Set the image crop size
CROP="-crop 392x200+20+0"
SPACE="   "

# DRAW 90-Minute graph
$RRDTOOL graph "$PWD"/outhour.png \
    --start now-5400s --end now \
    --alt-autoscale \
    $RES \
    --full-size-mode \
    --title "Last 90 Minutes" \
    --color CANVAS$COLCANVAS \
    --color BACK$COLCANVAS \
    --color FONT$COLOUT \
    --color GRID$COLGRID \
    --color MGRID$COLGRID \
    --color SHADEA$COLCANVAS \
    --color SHADEB$COLCANVAS \
    --x-grid MINUTE:5:HOUR:20:MINUTE:30:0:%M \
    --alt-y-grid \
    --left-axis-format %2.0lf \
    --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
    DEF:tempo="$PWD"/tempo.rrd:tempo:AVERAGE \
    CDEF:up=tempo,0,*,0,EQ,0,1,IF \
    TICK:up#3b455e:1.0 \
    LINE2:tempo$COLOUT \
    GPRINT:tempo:LAST:"$SPACE Current\:%2.0lf" \
    GPRINT:tempo:AVERAGE:"Average\:%2.1lf" \
    GPRINT:tempo:MAX:"Maximum\:%2.0lf $SPACE" >/dev/null

# Crop Image
mogrify $CROP "$PWD"/outhour.png
mv "$PWD"/outhour.png /var/www/html/img/

# DRAW 36-Hour  graph
$RRDTOOL graph "$PWD"/outday.png \
    --start now-36h --end now \
    --alt-autoscale \
    $RES \
    --full-size-mode \
    --title "Last 36 hours" \
    --color CANVAS$COLCANVAS \
    --color BACK$COLCANVAS \
    --color FONT$COLOUT \
    --color GRID$COLGRID \
    --color MGRID$COLGRID \
    --color SHADEA$COLCANVAS \
    --color SHADEB$COLCANVAS \
    --border 0 \
    --x-grid HOUR:6:HOUR:80:HOUR:6:0:"%H:%M" \
    --left-axis-format %2.0lf \
    --rigid \
    --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
    DEF:tempo="$PWD"/tempo.rrd:tempo:AVERAGE \
    CDEF:up=tempo,0,*,0,EQ,0,1,IF \
    TICK:up#3b455e:1.0 \
    LINE2:tempo$COLOUT \
    GPRINT:tempo:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
    GPRINT:tempo:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# Crop Image
mogrify $CROP "$PWD"/outday.png
mv "$PWD"/outday.png /var/www/html/img/

# DRAW 10-Day graph
$RRDTOOL graph "$PWD"/outweek.png \
    --start now-10d --end now \
    --alt-autoscale \
    $RES \
    --full-size-mode \
    --lower-limit 0 \
    --title "Last 10 Days" \
    --color CANVAS$COLCANVAS \
    --color BACK$COLCANVAS \
    --color FONT$COLOUT \
    --color GRID$COLGRID \
    --color MGRID$COLGRID \
    --color SHADEA$COLCANVAS \
    --color SHADEB$COLCANVAS \
    --border 0 \
    --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
    --left-axis-format %2.0lf \
    --rigid \
    --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
    DEF:tempo="$PWD"/tempo.rrd:tempo:AVERAGE \
    CDEF:up=tempo,0,*,0,EQ,0,1,IF \
    TICK:up#3b455e:1.0 \
    LINE2:tempo$COLOUT \
    GPRINT:tempo:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
    GPRINT:tempo:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# Crop Image
mogrify $CROP "$PWD"/outweek.png
mv "$PWD"/outweek.png /var/www/html/img/

# # DRAW 45-Day graph
# $RRDTOOL graph "$PWD"/outmonth.png \
#     --start now-45d --end now \
#     --alt-autoscale \
#     $RES \
#     --full-size-mode \
#     --lower-limit 0 \
#     --title "Last 45 Days" \
#     --color CANVAS$COLCANVAS \
#     --color BACK$COLCANVAS \
#     --color FONT$COLOUT \
#     --color GRID$COLGRID \
#     --color MGRID$COLGRID \
#     --color SHADEA$COLCANVAS \
#     --color SHADEB$COLCANVAS \
#     --border 0 \
#     --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
#     --left-axis-format %2.0lf \
#     --rigid \
#     --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
#     DEF:tempo="$PWD"/tempo.rrd:tempo:AVERAGE \
#     CDEF:up=tempo,0,*,0,EQ,0,1,IF \
#     TICK:up#3b455e:1.0 \
#     LINE2:tempo$COLOUT \
#     GPRINT:tempo:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
#     GPRINT:tempo:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# # Crop Image
# mogrify $CROP "$PWD"/outmonth.png
# mv "$PWD"/outmonth.png /var/www/html/img/

# # DRAW 18-Month graph
# $RRDTOOL graph "$PWD"/outyear.png \
#     --start now-18mon --end now \
#     --alt-autoscale \
#     $RES \
#     --full-size-mode \
#     --lower-limit 0 \
#     --title "Last 10 Days" \
#     --color CANVAS$COLCANVAS \
#     --color BACK$COLCANVAS \
#     --color FONT$COLOUT \
#     --color GRID$COLGRID \
#     --color MGRID$COLGRID \
#     --color SHADEA$COLCANVAS \
#     --color SHADEB$COLCANVAS \
#     --border 0 \
#     --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
#     --left-axis-format %2.0lf \
#     --rigid \
#     --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
#     DEF:tempo="$PWD"/tempo.rrd:tempo:AVERAGE \
#     CDEF:up=tempo,0,*,0,EQ,0,1,IF \
#     TICK:up#3b455e:1.0 \
#     LINE2:tempo$COLOUT \
#     GPRINT:tempo:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
#     GPRINT:tempo:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# # Crop Image
# mogrify $CROP "$PWD"/outyear.png
# mv "$PWD"/outyear.png /var/www/html/img/

# # DRAW 10-Year graph
# $RRDTOOL graph "$PWD"/outdecade.png \
#     --start now-10y --end now \
#     --alt-autoscale \
#     $RES \
#     --full-size-mode \
#     --lower-limit 0 \
#     --title "Last 10 Days" \
#     --color CANVAS$COLCANVAS \
#     --color BACK$COLCANVAS \
#     --color FONT$COLOUT \
#     --color GRID$COLGRID \
#     --color MGRID$COLGRID \
#     --color SHADEA$COLCANVAS \
#     --color SHADEB$COLCANVAS \
#     --border 0 \
#     --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
#     --left-axis-format %2.0lf \
#     --rigid \
#     --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
#     DEF:tempo="$PWD"/tempo.rrd:tempo:AVERAGE \
#     CDEF:up=tempo,0,*,0,EQ,0,1,IF \
#     TICK:up#3b455e:1.0 \
#     LINE2:tempo$COLOUT \
#     GPRINT:tempo:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
#     GPRINT:tempo:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# # Crop Image
# mogrify $CROP "$PWD"/outdecade.png
# mv "$PWD"/outdecade.png /var/www/html/img/

chown -R www-data:www-data /var/www/html

