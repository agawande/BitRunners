<?php
$file="test.txt";
ob_start();
var_dump($_POST);
$data = ob_get_clean();


$d = $POST['input'];

$f = fopen("testfile.txt", "w");
fwrite($f, $data);
fwrite($f, "\nhello".$d);
fclose($f);
?>