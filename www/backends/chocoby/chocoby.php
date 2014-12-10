<?php namespace CO;
require_once __DIR__."/idiorm.php";
require_once __DIR__."/chocoby_err.php";
require_once __DIR__."/chocoby_config.php";
	
$fetch_src = null;
$in_buffer = Array();
$out_buffer = Array();
$autocommits = Array();
$errno = ERR\NONE;
$aborted = false;

/* interfaces */
function in($in_ary){
	GLOBAL $in_bufer;

	foreach($in_ary as $key => $value){
		$in_buffer[$key] = $value;

		$parsed = lex_opts($value);
		process_in_opts($key, $parsed);
	}
}
function out($out_ary){
	GLOBAL $out_buffer;

	foreach($out_ary as $key => $value){
		$parsed = lex_opts($value);
		$out_buffer[$key] = $parsed;
	}
}
function set_errno($no){
	GLOBAL $errno;
	$errno = $no;
}
function abort($no, $reason){
	GLOBAL $aborted;

	set_errno($no);

	if( CONFIG\DEBUG ){
		$result = 
			[CONFIG\RESULT_KEY => $no,
			CONFIG\REASON_KEY => $reason];
	}
	else{
		$result = 
			[CONFIG\RESULT_KEY => $no];
	}

	$aborted = true;

	exit(json_encode(
		$result));
}

function session($key, $value=null){
	/* getter */
	if( $value == null ){
		if( array_key_exists($key, $_SESSION) )
			return $_SESSION[$key];
		else
			return null;
	}
	/* setter */
	else
		$_SESSION[$key] = $value;
}

/* backends */
function flush_db(){
	GLOBAL $autocommits;

	foreach($autocommits as $row){
		if( $row != null )
			$row->save();
	}
}

function array_xml($arr, $num_prefix = "num_") {
        if(!is_array($arr)) return $arr;
        $result = '';
        foreach($arr as $key => $val) {
                $key = (is_numeric($key)? $num_prefix.$key : $key);
                $result .= "<".$key.">".array_xml($val, $num_prefix)."</".$key.">";
        }
        return $result;
}
function on_response(){
	GLOBAL $out_buffer;
	GLOBAL $errno, $aborted;

	if( $aborted )
		return;

	$responses = Array();
	$responses[CONFIG\RESULT_KEY] = 0;

	foreach($out_buffer as $key => $opts){
		$value = process_out_opts($key, $opts);
		$responses[$key] = $value;
	}

	flush_db();
	
	switch( CONFIG\OUT_FORM ){
		case "json":
			echo json_encode( $responses );
			break;
		case "xml":
			header('Content-type: text/xml'); 
			echo "<?xml version='1.0' encoding='UTF-8'?>\n";
			echo array_xml( $responses );	
			break;
	}

}

function configure(){
	GLOBAL $fetch_src;

	/* fetch_src */
	switch( CONFIG\IN_SRC ){
		case "get":
			$fetch_src = $_GET;
			break;
		case "post":
			$fetch_src = $_POST;
			break;
		case "custom":
			$fetch_src = call_user_func(
				CONFIG\CUSTOM_INIT_FUNC);
			break;
	}

	/* db */
	\ORM::configure('mysql:host=' . CONFIG\DB_HOST
		.';dbname=' . CONFIG\DB_NAME);
	\ORM::configure('username', CONFIG\DB_USER);
	\ORM::configure('password', CONFIG\DB_PASSWORD);
}
function initialize(){
	session_start();
	register_shutdown_function("\CO\on_response");

	configure();
}

function lex_opts($opts){
	$parsed = Array();
	$tokens = split(" ", $opts);

	foreach($tokens as $token){
		preg_match_all("/^(?<opt>[^\[]+)(\[(?<params>.+)\])?/", $token, $result);
		
		$opt = null;
		$params = null;
		if( $result["opt"] != null)
			$opt = $result["opt"][0];
		if( $result["params"] != null )
			$params = split(",", $result["params"][0]);

		array_push($parsed,
			["opt" => $opt, "params" => $params]);
	}

	return $parsed;
}

function process_in_opts($key, $opts){
	GLOBAL $fetch_src;
	GLOBAL $autocommits;

	$orm_object = false;
	$autocommit = true;
	$invalid_value = false;
	$glob_name = $key;
	$value = null;
	$dst_value = null;
	$required = true;

	if( array_key_exists($key, $fetch_src) ){
		$value = $fetch_src[$key];
		$dst_value = $value;
	}

	foreach($opts as $opt){
		$params = $opt["params"];

		switch( $opt["opt"] ){
			case "required":
				break;
			case "optional":
				$required = false;
				break;

			case "as":
				$glob_name = $params[0];
				break;

			/* pk [table,(column_name)] */
			case "pk":
				if( count($params) == 1 )
					$column_name = $key;
				else
					$column_name = $params[1];

				$table = \ORM::for_table($params[0]);
				$row = $table
					->where($column_name, $value)
					->find_one();
				$dst_value = $row;
				$orm_object = true;
				break;
			case "disable_autocommit":
				$autocommit = false;
				break;

			case "session":
				$dst_value = session($key);
				break;
			case "session_key":
				session_id( $value );
				break;

			case "va-rex":
				if( preg_match($params[0], $value) != 1 )
					$invalid_value = true;
				break;
			case "va-range":
				if( is_numeric($value) != 1 )
					$invalid_value = true;
				else{
					if( $value < $params[0] ||
						$value > $params[1] )
						$invalid_value = true;
				}
				break;
			case "va-length":
				$param_count = count($params);
				$len = strlen($value);
				
				/* validate length == param[0] */
				if( $param_count == 1 ){
					if( $len != $params[0] )
						$invalid_value = true;
				}
				/* validate length in_range(param[0], param[1]) */
				else if( $param_count == 2 ){
					if( $len < $params[0] ||
						$len > $params[1] )
						$invalid_value = true;
				}
				break;
		}
	}

	if( $required == true && $value == null )
		$invalid_value = true;

	$GLOBALS[$glob_name] = $dst_value;

	if( $invalid_value ){
		abort(
			ERR\INVALID_PARAM,
			"invalid parameter - in::${key}");
	}
	if( $autocommit && $orm_object )
		array_push($autocommits, $row);
}
function process_out_opts($key, $opts){
	$glob_name = $key;
	$required = true;
	
	$dst_value = null;
	if( array_key_exists($key, $GLOBALS) )
		$dst_value = $GLOBALS[$key];

	foreach($opts as $opt){
		$params = $opt["params"];

		switch( $opt["opt"] ){
			case "required":
				break;
			case "optional":
				$required = false;
				break;

			case "from":
				$dst_value = $GLOBALS[$params[0]];
				break;

			case "session_key":
				$dst_value = session_id();
				break;

			case "errno":
				return $errno;
			case "timestamp":
				return time();
		}
	}

	if( $dst_value != null )
		return $dst_value;
	else if( $required )
		abort(
			ERR\INTERNAL_ERROR,
			"required field is null - out::${key}");
	else
		return null;
}

initialize();
?>