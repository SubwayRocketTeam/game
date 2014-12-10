<?php
require_once "chocoby/chocoby.php";

CO\in([
	"user_id" => "va-length[6,16]",
	"user_pw" => "va-length[6,16]",
	"nickname" => "va-length[3,16]"
	]);
CO\out([
	"user_id" => ""
	]);

$account =
	ORM::for_table("accounts")->create();

$account->user_id = $user_id;
$account->user_pw = $user_pw;
$account->nickname = $nickname;

$account->save();
?>