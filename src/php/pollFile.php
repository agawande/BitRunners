<?php

$results = "/var/www/html/src/engine/results.txt";
$current = "/var/www/html/src/engine/update";
$data = "waiting";

if(file_exists($results) || file_exists($current))
{
	if(file_exists($results))
	{
		$data = "results".file_get_contents($results);
	}
	else
	{
		$data = file_get_contents($current);
		unlink($current);
		$myfile = fopen("/var/www/html/src/engine/_acknowledged", "w");
		fclose($myfile);
	}
	echo $data;
}
else
{
	echo "waiting";
}
?>
