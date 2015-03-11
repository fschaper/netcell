<?php

/* 
 * Florian Schaper <florian.schaper@jedox.com>
 * Copyright ' 2008 Jedox AG, Freiburg, Germany
 */

// --------------------------------------------------------------------------------------------
// configuration
// --------------------------------------------------------------------------------------------

define( 'MANTIS_WSDL', 'http://bugs.palo.net/mantis/api/soap/mantisconnect.php?wsdl' );
define( 'MANTIS_ACCOUNT_USERNAME', "auto_report_admin" );
define( 'MANTIS_ACCOUNT_PASSWORD', "root" );
define( 'MANTIS_REPORTER_ACCESS_LEVEL', 25 );
define( 'MANTIS_PROJECT_ID', 3 );
define( 'MANTIS_CATEGORY', "server_crash_reports" );
define( 'UPLOAD_PATH', 'upload' );

// --------------------------------------------------------------------------------------------

// move crash report to the upload directory and assign an unique id to it
$report_file_name_and_path =  UPLOAD_PATH . "/crash_report_".uniqid().".dmp";
move_uploaded_file( $_FILES['crash_dump_file']['tmp_name'], $report_file_name_and_path );

// connect to mantis's webservice
$soap_clinet = new SoapClient( MANTIS_WSDL );

// get the report details from the user report from the post variables
$report_product_details = $_POST['product'];
$report_client_details = $_POST['client'];

// see if the user reporting the issue has an mantis account
// if he has one, remember his account id
$mantis_user_id = -1;
if( $report_client_details['email'] ) {
	$mantis_users = $soap_clinet->mc_project_get_users( MANTIS_ACCOUNT_USERNAME, MANTIS_ACCOUNT_PASSWORD, MANTIS_PROJECT_ID, MANTIS_REPORTER_ACCESS_LEVEL );

	foreach( $mantis_users as $current_user ) {
		if( $current_user->email ==  $report_client_details['email'] ) {
			$mantis_user_id = $current_user->id;
			break;
		}
	}
}

if( ! empty( $report_product_details['version'] ) ) {
	$known_product_version = false;

	$product_versions = $soap_clinet->mc_project_get_versions( MANTIS_ACCOUNT_USERNAME, MANTIS_ACCOUNT_PASSWORD, MANTIS_PROJECT_ID );

	foreach( $product_versions as $current_version ) {
		if( $current_version->name ==  $report_product_details['version'] ) {
			$known_product_version = true;
			break;
		}
	}

	if( ! $known_product_version ) {
		$new_product_version = array(
			  'name' => $report_product_details['version']
			, 'project_id' => MANTIS_PROJECT_ID
			, 'description' => "added by crash reporter. please update."
			, 'released' => true
			, 'date_order' => strftime( "%Y-%m-%dT%H:%i:%s" )
		);
		$soap_clinet->mc_project_version_add( MANTIS_ACCOUNT_USERNAME, MANTIS_ACCOUNT_PASSWORD, $new_product_version );
	}
}

/*
	-----------------------------------------------------------------------------
	valid parameters for issue entry
	-----------------------------------------------------------------------------
	<xsd:element name="id" type="xsd:integer" minOccurs="0"/>
	<xsd:element name="view_state" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="last_updated" type="xsd:dateTime" minOccurs="0"/>
	<xsd:element name="project" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="category" type="xsd:string" minOccurs="0"/>
	<xsd:element name="priority" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="severity" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="status" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="reporter" type="tns:AccountData" minOccurs="0"/>
	<xsd:element name="summary" type="xsd:string" minOccurs="0"/>
	<xsd:element name="version" type="xsd:string" minOccurs="0"/>
	<xsd:element name="build" type="xsd:string" minOccurs="0"/>
	<xsd:element name="platform" type="xsd:string" minOccurs="0"/>
	<xsd:element name="os" type="xsd:string" minOccurs="0"/>
	<xsd:element name="os_build" type="xsd:string" minOccurs="0"/>
	<xsd:element name="reproducibility" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="date_submitted" type="xsd:dateTime" minOccurs="0"/>
	<xsd:element name="sponsorship_total" type="xsd:integer" minOccurs="0"/>
	<xsd:element name="handler" type="tns:AccountData" minOccurs="0"/>
	<xsd:element name="projection" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="eta" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="resolution" type="tns:ObjectRef" minOccurs="0"/>
	<xsd:element name="fixed_in_version" type="xsd:string" minOccurs="0"/>
	<xsd:element name="description" type="xsd:string" minOccurs="0"/>
	<xsd:element name="steps_to_reproduce" type="xsd:string" minOccurs="0"/>
	<xsd:element name="additional_information" type="xsd:string" minOccurs="0"/>
	<xsd:element name="attachments" type="tns:AttachmentDataArray" minOccurs="0"/>
	<xsd:element name="relationships" type="tns:RelationshipDataArray" minOccurs="0"/>
	<xsd:element name="notes" type="tns:IssueNoteDataArray" minOccurs="0"/>
	<xsd:element name="custom_fields" type="tns:CustomFieldValueForIssueDataArray" minOccurs="0"/>
*/

// create the report with all the details that are available to us at this point
$new_issue = array( 
	'project' => array( 'id' => MANTIS_PROJECT_ID )
  , 'summary' => 'automated crash-handler report'
  , 'description' => (!empty( $report_client_details['report'] ) 
						? $report_client_details['report'] 
						: "the report contained no detail information")
  , 'priority' => array( 'id' => 'normal' )
  , 'severity' => array( 'name' => 'crash' )
  , 'status' => array( 'id' => 1 )
  , 'reproducibility' => array( 'name' => 'N/A' )
  , 'resolution' => array( 'id' => 1 )
  , 'projection' => array( 'id' => 1 )
  , 'eta' => array( 'id' => 1 )
  , 'view_state' => array( 'name' => 'private' )
  , 'category' => MANTIS_CATEGORY
);

// if the user is known to the system we enter him directly as the reporter of
// the incident. 
if( $mantis_user_id != -1 ) {
	$new_issue['reporter'] = array("id" => $mantis_user_id );
} else if ( !empty( $report_client_details['email'] ) ) {
	$new_issue['additional_information'] = "unknown reporter or contact address: ".$report_client_details['email'];
}
// if an product version was passed to the reporting clinet add it.
if( ! empty( $report_product_details['version'] ) ) {
	$new_issue['version'] = $report_product_details['version'];
}

$issue_id = $soap_clinet->mc_issue_add( MANTIS_ACCOUNT_USERNAME, MANTIS_ACCOUNT_PASSWORD, $new_issue );
$soap_clinet->mc_issue_attachment_add( MANTIS_ACCOUNT_USERNAME, MANTIS_ACCOUNT_PASSWORD, $issue_id, "core_dump", "core_dump", base64_encode( file_get_contents( $report_file_name_and_path ) ) );

printf("%07d",$issue_id);

?>