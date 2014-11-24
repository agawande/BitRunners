<?php

$f = fopen("results.txt", "w");
$i = 0;
while ($i < 2)
{
	if(filesize("results.txt") != 0)
	{
		fwrite($f, "success polls");
	}
	fwrite($f, "success polls");
	sleep(10);
	$i+=1;
}
?>