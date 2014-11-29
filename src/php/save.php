<?php

$d = $_POST["input"];

$f = fopen("/var/www/html/src/engine/sample_input", "w");

fwrite($f, $d);
fclose($f);
?>
