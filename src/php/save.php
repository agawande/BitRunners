<?php

$d = $_POST["input"];

$f = fopen("engine/sample_input", "w");
fwrite($f, $d);
fclose($f);
?>
