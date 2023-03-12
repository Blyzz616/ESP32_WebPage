<?php
    header("Refresh:60");
    $xml = simplexml_load_file('xml/temp.xml');
    $tf = (string) $xml->TF;
    $to = (string) $xml->TO;
    $tg = (string) $xml->TG;
    $g0 = (string) $xml->G0;

    if ($g0 == "Open") {
        $class = 'blink-red';
    } else if ($g0 == "Ajar") {
        $class = 'blink-org';
    } else {
        $class = 'tabledata';
    }

    $current_date = date("Y/m/d");
    $current_time = date("H:i");

?>

<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="css/main.css">
</head>
<body>
	<header>
		<div class="navbar fixed-top">
			<div class="container">
				<div class="navtitle">Garage Status</div>
				<div class="navdata" id = "date"><?php echo $current_date ?></div>
				<div class="navheading">DATE</div><br/>
				<div class="navdata" id = "time"><?php  echo $current_time ?></div>
				<div class="navheading">TIME</div>
			</div>
		</div>
	</header>
	<main class="container" style="margin-top:70px">
		<div style="border-radius: 10px !important;">
			<table class="toptable">
				<tr>
					<td><div class="bodytext"><center>Freezer temp</center></div></td>
					<td><div class="tabledata" id="tempF"><?php echo "$tf"; ?></div></td>
				</tr>
				<tr>
					<td><div class="bodytext"><center>Garage temp</center></div></td>
					<td><div class="tabledata" id = "tempO"><?php echo "$to"; ?></div></td>
				</tr>
				<tr>
					<td><div class="bodytext"><center>Outside temp</center></div></td>
					<td><div class="tabledata" id = "tempG"><?php echo "$tg"; ?></div></td>
				</tr>
				<tr>
					<td><div class="bodytext"><center>Door Status</center></div></td>
					<td><div id="garage" class="  <?php echo $class ?>"><?php echo "$g0"; ?></div></td>
				</tr>
				<tr>
					<td colspan="2" align ="center">
					<button type="button" class = "btn" id = "btn1" onclick="ButtonPress()">Activate Garage Door</button>
					</td>
				</tr>
			</table>
			<table id="tabGraphs">
				<tr>
					<td id="frehead">
						<center>FREEZER</center>
					</td>
					<td id="outhead">
						<center>OUTSIDE</center>
					</td>
					<td id="garhead">
						<center>GARAGE</center>
					</td>
				</tr>
				<tr>
					<td class="tdGraphs" id="freHour">
					</td>
					<td class="tdGraphs" id="outHour">
					</td>
					<td class="tdGraphs" id="garHour">
					</td>
				</tr>
				<tr>
					<td class="tdGraphs" id="freDay">
					</td>
					<td class="tdGraphs" id="outDay">
					</td>
					<td class="tdGraphs" id="garDay">
					</td>
				</tr>
				<tr>
					<td class="tdGraphs" id="freWeek">
					</td>
					<td class="tdGraphs" id="outWeek">
					</td>
					<td class="tdGraphs" id="garWeek">
					</td>
				</tr>
				<!--<tr>
					<td class="tdGraphs" id="freMonth">
					</td>
					<td class="tdGraphs" id="outMonth">
					</td>
					<td class="tdGraphs" id="garMonth">
					</td>
				</tr>
				<tr>
					<td class="tdGraphs" id="freYear">
					</td>
					<td class="tdGraphs" id="outYear">
					</td>
					<td class="tdGraphs" id="garYear">
					</td>
				</tr>
				<tr>
					<td class="tdGraphs" id="freDecade">
					</td>
					<td class="tdGraphs" id="outDecade">
					</td>
					<td class="tdGraphs" id="garDecade">
					</td>
				</tr>-->
			</table>
		</div>
	</main>

		<?php
		?>

</body>
</html>
