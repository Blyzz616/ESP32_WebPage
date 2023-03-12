#! /bin/bash

RRDTOOL=/usr/bin/rrdtool
PWD=/usr/local/bin/temp

# Set some colours
COLCANVAS=#36393f00
COLGRID=#888888
COLGAR=#f760a7
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
$RRDTOOL graph "$PWD"/garhour.png \
    --start now-5400s --end now \
    --alt-autoscale \
    $RES \
    --full-size-mode \
    --title "Last 90 Minutes" \
    --color CANVAS$COLCANVAS \
    --color BACK$COLCANVAS \
    --color FONT$COLGAR \
    --color GRID$COLGRID \
    --color MGRID$COLGRID \
    --color SHADEA$COLCANVAS \
    --color SHADEB$COLCANVAS \
    --x-grid MINUTE:5:HOUR:20:MINUTE:30:0:%M \
    --alt-y-grid \
    --left-axis-format %2.0lf \
    --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
    DEF:tempg="$PWD"/tempo.rrd:tempg:AVERAGE \
    CDEF:up=tempg,0,*,0,EQ,0,1,IF \
    TICK:up#5a3e52:1.0 \
    LINE2:tempg$COLGAR \
    GPRINT:tempg:LAST:"$SPACE Current\:%2.0lf" \
    GPRINT:tempg:AVERAGE:"Average\:%2.1lf" \
    GPRINT:tempg:MAX:"Maximum\:%2.0lf $SPACE" >/dev/null

# Crop Image
mogrify $CROP "$PWD"/garhour.png
mv "$PWD"/garhour.png /var/www/html/img/

# DRAW 36-Hour graph
$RRDTOOL graph "$PWD"/garday.png \
    --start now-36h --end now \
    --alt-autoscale \
    $RES \
    --full-size-mode \
    --title "Last 36 hours" \
    --color CANVAS$COLCANVAS \
    --color BACK$COLCANVAS \
    --color FONT$COLGAR \
    --color GRID$COLGRID \
    --color MGRID$COLGRID \
    --color SHADEA$COLCANVAS \
    --color SHADEB$COLCANVAS \
    --border 0 \
    --x-grid HOUR:6:HOUR:80:HOUR:6:0:"%H:%M" \
    --left-axis-format %2.0lf \
    --rigid \
    --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
    DEF:tempg="$PWD"/tempo.rrd:tempg:AVERAGE \
    CDEF:up=tempg,0,*,0,EQ,0,1,IF \
    TICK:up#5a3e52:1.0 \
    LINE2:tempg$COLGAR \
    GPRINT:tempg:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
    GPRINT:tempg:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# Crop Image
mogrify $CROP "$PWD"/garday.png
mv "$PWD"/garday.png /var/www/html/img/

# DRAW 10-Day graph
$RRDTOOL graph "$PWD"/garweek.png \
    --start now-10d --end now \
    --alt-autoscale \
    $RES \
    --full-size-mode \
    --title "Last 10 Days" \
    --color CANVAS$COLCANVAS \
    --color BACK$COLCANVAS \
    --color FONT$COLGAR \
    --color GRID$COLGRID \
    --color MGRID$COLGRID \
    --color SHADEA$COLCANVAS \
    --color SHADEB$COLCANVAS \
    --border 0 \
    --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
    --left-axis-format %2.0lf \
    --rigid \
    --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
    DEF:tempg="$PWD"/tempo.rrd:tempg:AVERAGE \
    CDEF:up=tempg,0,*,0,EQ,0,1,IF \
    TICK:up#5a3e52:1.0 \
    LINE2:tempg$COLGAR \
    GPRINT:tempg:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
    GPRINT:tempg:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# Crop Image
mogrify $CROP "$PWD"/garweek.png
mv "$PWD"/garweek.png /var/www/html/img/

# # DRAW 45-Day graph
# $RRDTOOL graph "$PWD"/garmonth.png \
#     --start now-45d --end now \
#     --alt-autoscale \
#     $RES \
#     --full-size-mode \
#     --title "Last 45 Days" \
#     --color CANVAS$COLCANVAS \
#     --color BACK$COLCANVAS \
#     --color FONT$COLGAR \
#     --color GRID$COLGRID \
#     --color MGRID$COLGRID \
#     --color SHADEA$COLCANVAS \
#     --color SHADEB$COLCANVAS \
#     --border 0 \
#     --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
#     --left-axis-format %2.0lf \
#     --rigid \
#     --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
#     DEF:tempg="$PWD"/tempo.rrd:tempg:AVERAGE \
#     CDEF:up=tempg,0,*,0,EQ,0,1,IF \
#     TICK:up#5a3e52:1.0 \
#     LINE2:tempg$COLGAR \
#     GPRINT:tempg:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
#     GPRINT:tempg:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# # Crop Image
# mogrify $CROP "$PWD"/garmonth.png
# mv "$PWD"/garmonth.png /var/www/html/img/

# # DRAW 18-Month graph
# $RRDTOOL graph "$PWD"/garyear.png \
#     --start now-18mon --end now \
#     --alt-autoscale \
#     $RES \
#     --full-size-mode \
#     --title "Last 10 Days" \
#     --color CANVAS$COLCANVAS \
#     --color BACK$COLCANVAS \
#     --color FONT$COLGAR \
#     --color GRID$COLGRID \
#     --color MGRID$COLGRID \
#     --color SHADEA$COLCANVAS \
#     --color SHADEB$COLCANVAS \
#     --border 0 \
#     --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
#     --left-axis-format %2.0lf \
#     --rigid \
#     --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
#     DEF:tempg="$PWD"/tempo.rrd:tempg:AVERAGE \
#     CDEF:up=tempg,0,*,0,EQ,0,1,IF \
#     TICK:up#5a3e52:1.0 \
#     LINE2:tempg$COLGAR \
#     GPRINT:tempg:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
#     GPRINT:tempg:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# # Crop Image
# mogrify $CROP "$PWD"/garyear.png
# mv "$PWD"/garyear.png /var/www/html/img/

# # DRAW 10-Year graph
# $RRDTOOL graph "$PWD"/gardecade.png \
#     --start now-10y --end now \
#     --alt-autoscale \
#     $RES \
#     --full-size-mode \
#     --title "Last 10 Days" \
#     --color CANVAS$COLCANVAS \
#     --color BACK$COLCANVAS \
#     --color FONT$COLGAR \
#     --color GRID$COLGRID \
#     --color MGRID$COLGRID \
#     --color SHADEA$COLCANVAS \
#     --color SHADEB$COLCANVAS \
#     --border 0 \
#     --x-grid DAY:1:DAY:12:DAY:2:0:"%m/%d" \
#     --left-axis-format %2.0lf \
#     --rigid \
#     --watermark "$(date +'%a %b %d %H:%M %Z %Y')" \
#     DEF:tempg="$PWD"/tempo.rrd:tempg:AVERAGE \
#     CDEF:up=tempg,0,*,0,EQ,0,1,IF \
#     TICK:up#5a3e52:1.0 \
#     LINE2:tempg$COLGAR \
#     GPRINT:tempg:AVERAGE:"$SPACE $SPACE Average\:%2.1lf" \
#     GPRINT:tempg:MAX:"Maximum\:%2.0lf $SPACE $SPACE" >/dev/null

# # Crop Image
# mogrify $CROP "$PWD"/gardecade.png
# mv "$PWD"/gardecade.png /var/www/html/img/

chown -R www-data:www-data /var/www/html

