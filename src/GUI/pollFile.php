<?php

$results = "results.txt";
$current = "current.txt";
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
		$myfile = fopen("acknowledged", "w");
	}
	echo $data;
}
else
{
	echo "waiting";
}
?>