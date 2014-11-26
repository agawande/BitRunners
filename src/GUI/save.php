<?php

$d = $_POST["input"];

$f = fopen("testfile.txt", "w");
fwrite($f, $d);
fclose($f);
?>