<?php

$results = "../engine/results";
$current = "../engine/update";
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
		$myfile = fopen("../engine/_acknowledged", "w");
		fclose($myfile);
	}
	echo $data;
}
else
{
	echo "waiting";
}
?>
