<?php

header("Access-Control-Allow-Origin: same-origin");
header("Content-Type: application/json");

$jsonString = file_get_contents('php://input');
$json = json_decode($jsonString, true);

// get user creds
$ucid = isset($json["ucid"]) ? $json["ucid"] : 'NULL';
$pass = isset($json["pass"]) ? $json["pass"] : 'NULL';

$data = [
    'ucid' => $ucid,
    'pass' => $pass,
];

echo loginNJIT($data);

// validate user creds against NJIT web-auth
function loginNJIT($json)
{
    // $data = array('ucid' => $ucid, 'pass' => $pass);
    $postForm = curl_init();

    curl_setopt($postForm, CURLOPT_URL, "https://aevitepr2.njit.edu/myhousing/login.cfm");
    curl_setopt($postForm, CURLOPT_POST, 1);
    curl_setopt($postForm, CURLOPT_HTTPHEADER, array('Content-Type: application/x-www-form-urlencoded'));
    curl_setopt($postForm, CURLOPT_POSTFIELDS, json_encode($json));

    $res = curl_exec($postForm);
    curl_close($postForm);

    return res;
}

// validate user creds against database
function loginDB($ucid, $pass)
{
    $data = array('ucid' => $ucid, 'pass' => $pass);
}
