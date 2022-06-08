<?php
// required headers
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: access");
header("Access-Control-Allow-Headers: Authorization, Content-Type,      Accept");

header("Access-Control-Allow-Methods: POST");
header("Access-Control-Allow-Credentials: true");
header('Content-Type: application/json');

// include database and object files
include_once '../config/database.php';
include_once '../objects/gcode.php';

//http_response_code(200);echo json_encode(array("message" => "Kayit TAMAM.."));die();
// get database connection
$database = new Database();
$db = $database->getConnection();


// set ID property of record to read
$json = file_get_contents('php://input');
//echo json_encode(array("message" => json_decode($json)));
// Converts it into a PHP object
$data = json_decode($json);


$id = isset($data->id) ? $data->id : die();
$record_type = isset($data->record_type) ? $data->record_type : die();

//echo json_encode(array("message" => $data->dosyalar));

// prepare product object
$gcode = new GCode($db);

if($record_type==1)
$status=$gcode->tumunuGetir();

if($status==true){

    http_response_code(200);
    echo json_encode(array("message" => "TAMAM"));

}

else{

    http_response_code(404);
    echo json_encode(array("message" => "Kayit Edilmedi.."));
}
?>
