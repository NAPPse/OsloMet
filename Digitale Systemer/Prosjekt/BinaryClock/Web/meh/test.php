<?php
$url = 'https://www.nordicmafia.org/index.php?p=game_dice';
$data = array('innsats' => '100', 'password' => 'hemmelig', 'passwordProtected' => '1', 'players' => '2', 'startGame' => 'Start+spill');
$options = array(
        'http' => array(
        'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
        'method'  => 'POST',
        'content' => http_build_query($data),
    )
);

$context  = stream_context_create($options);
$result = file_get_contents($url, false, $context);
var_dump($result);
?>
