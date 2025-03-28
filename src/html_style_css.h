const uint8_t style_css[] = R"rawliteral(
/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
/* Global */

body {
	background: #36393e;
  margin: 0;
  color: #bfbfbf;
	font-family: sans-serif;
}

main {
	width: 60vw;
	margin-left: auto;
	margin-right: auto;
}

section {
	margin-top: 50px;
}

footer {
	font-size: .95em;
	text-align: center;
	margin-top: 3em;
	margin-bottom: 3em;
}

h1 {
	font-size: 1.4rem;
	margin-top: 1rem;
	background:
	#2f3136;
	padding: 10px;
	border-radius: 4px;
	border-left: solid #20c20e 5px;
	font-weight: 100;
	letter-spacing: 5px;
}

h2 {
	font-size: 1.2rem;
	margin-top: 1rem;
	background: #2f3136;
	padding: 10px;
	border-radius: 4px;
	border-left: solid #20c20e 5px;
	font-weight: 100;
	letter-spacing: 5px;
}

h3 {
	font-size: 1rem;
	margin-top: 1rem;
	background: #2f3136;
	padding: 10px;
	border-radius: 4px;
	border-left: solid #20c20e 5px;
	font-weight: 100;
	letter-spacing: 5px;
}

label {
	line-height: 44px;
}

p {
	margin: .5em 0;
}

/* Navigation bar */
nav {
	display: block;
	background: #2f3136;
	font-weight: bold;
}
  
nav a {
	color: inherit;
}

.menu {
	width: 60vw;
	list-style-type: none;
	margin: 0;
	padding: 0;
	margin: 0 auto;
	display: flex;
	flex-direction: row;
	display:block;
}

.menu li {
	margin: 10px 5px 10px 0;
	display: inline-block;
}

.menu li:nth-last-child(-n+2) {
	float: right;
}

.menu a {
	padding: .75em;
	border-radius: 4px;
}

.menu a:hover {
	background: #42444a;
}

code {
	background: #ccc;
	padding: 3px;
	border-radius: 3px;
	word-break: keep-all !important;
	color: #000;
	line-height: 24px;
}

.white {
  color: #bfbfbf;
}

.warn {
	color: #ffc107;
}

.danger {
	color: #F04747;
}

.success {
	color: #43B581;
}

.primary {
	color: #0092db;
}

.select {
  	width: 98px !important;
  	padding: 0 !important;
}

.selected {
  	background: #4974a9;
}

.clickable {
  	cursor: pointer;
}

.code {
  	font-family: "Courier New", Courier, monospace;
}

.reload {
    float: right;
    line-height: 1.1rem;
    cursor: pointer;
	font-size: 1.5rem;
	margin-top: 4px;
}

.reload:hover {
    text-decoration: none;
}

#status {
	text-align: center;
	text-transform: capitalize;
	padding: 5px;
	color: #fff;
	position: sticky;
	top: 0;
	z-index: 99;
}

.debugger {
  font-family: monospace;
	background: #2f3136;
	border-radius: 4px;
	padding: 10px;
	margin-bottom: 4px;
}

#editor-primary-buttons {
	float: right;
}

#editor-primary-buttons p {
	text-align: right;
}

/* ===== CHECKBOX ===== */
/* Customize the label (the container) */
.checkBoxContainer {
	display: block;
	position: relative;
	padding-left: 35px;
	margin-bottom: 12px;
	cursor: pointer;
	font-size: 22px;
	-webkit-user-select: none;
	-moz-user-select: none;
	-ms-user-select: none;
	user-select: none;
	height: 32px;
}

/* Hide the browser's default checkbox */
.checkBoxContainer input {
	position: absolute;
	opacity: 0;
	cursor: pointer;
}

/* Create a custom checkbox */
.checkmark {
	position: absolute;
	top: 8px;
	left: 0;
	height: 28px;
	width: 28px;
	background-color: #2F3136;
	border-radius: 4px;
}

/* Create the checkmark/indicator (hidden when not checked) */
.checkmark:after {
	content: "";
	position: absolute;
	display: none;
}

/* Show the checkmark when checked */
.checkBoxContainer input:checked~.checkmark:after {
	display: block;
}

.checkBoxContainer .checkmark:after {
	left: 10px;
	top: 7px;
	width: 4px;
	height: 10px;
	border: solid white;
	border-width: 0 3px 3px 0;
	-webkit-transform: rotate(45deg);
	-ms-transform: rotate(45deg);
	transform: rotate(45deg);
}

/* ERROR */
.hide {
	display: none;
}

.show {
	display: block !important;
	animation-name: fadeIn;
	animation-duration: 1s;
}

@keyframes fadeIn {
	0% {
		opacity: 0;
	}

	100% {
		opacity: 1;
	}
}

hr {
	background: #3e4146;
	border-top: 1px dotted#fff;
	border-bottom: none;
	margin: 0;
}

a {
	color: #1ca8eb;
  	text-decoration: none;
}

a:hover {
	color: #fff;
	text-decoration: underline dotted;
}

/* Meter */
.meter_background {
	background: #42464D;
	width: 100%;
	word-break: normal;
	min-width: 100px;
}

.meter_forground {
	color: #fff;
	padding: 4px 0;
	/* + one of the colors below
		(width will be set by the JS) */
}

.meter_green {
	background: #43B581;
}

.meter_orange {
  	background: #FAA61A;
}

.meter_red {
  	background: #F04747;
}

.meter_value {
  	padding-left: 8px;
}

/* Tables */
table {
	width: 100%;
	min-width: 400px;
	margin-bottom: 2em;
	border-collapse: collapse;
}

th {
  	word-break: break-word;
}

th, td {
	padding: 10px 6px;
	text-align: left;
	border-bottom: 1px solid #5d5d5d;
}

#ducky-functions-table td {
  	min-width: 180px;
}

@media only screen and (max-width: 768px), (min-device-width: 768px) and (max-device-width: 1024px) {

	.menu {
		width: 90vw;
	}

	main {
		width: 90vw !important;
	}

	/* Force table to not be like tables anymore */
	#ducky-functions-table table, #ducky-functions-table thead, #ducky-functions-table tbody, #ducky-functions-table th, #ducky-functions-table td, #ducky-functions-table tr {
		display: block;
	}

	/* Hide table headers (but not display: none;, for accessibility) */
	#ducky-functions-table thead tr {
		position: absolute;
		top: -9999px;
		left: -9999px;
	}

	#ducky-functions-table tr {
		border: none;
	}

	#ducky-functions-table tr:nth-child(odd) {
		background: #2f3136;
		border-radius: 4px;
	}

	#ducky-functions-table td {
		/* Behave  like a "row" */
		border: none;
		border-bottom: 2px solid transparent;
		position: relative;
		padding-left: 120px;
		line-height: 1.8rem;
	}

	#ducky-functions-table td:before {
		/* Now like a table header */
		position: absolute;
		/* Top/left values mimic padding */
		top: 6px;
		left: 6px;
		width: 120px;
		padding-right: 10px;
		white-space: nowrap;
	}

	/*
		Label the data
		*/
	#ducky-functions-table td:nth-of-type(1):before {
		content: "Command";
	}

	#ducky-functions-table td:nth-of-type(2):before {
		content: "Example";
	}

	#ducky-functions-table td:nth-of-type(3):before {
		content: "Description";
	}
}

/* Inputs and buttons */
textarea {
	color: #bfbfbf;
	resize: vertical;
	width: 100%;
	height: 400px;
	padding: 15px;
	border: none;
	border-radius: 4px;
	background: #2f3136;
	font-family: "Courier New", Courier, monospace;
	box-sizing: border-box;
	-moz-box-sizing: border-box;
	-webkit-box-sizing: border-box;
}

input[type="file"] {
	padding: 7px 20px;
}

input[type="text"] {
	color: #bfbfbf;
	text-transform: none;
	width: 10em;
}

input[type="text"]:hover {
	cursor: text;
}

input, button {
	padding: 10px 20px;
	border: none;
	border-radius: 4px;
	background: #2f3136;
	letter-spacing: .1rem;
	text-transform: uppercase;
	margin: 2px 0;
}

input:hover, button:hover {
	background: #42444a;
	cursor: pointer;
}

.setting {
	width: 100% !important;
	max-width: 284px !important;
}

/* GRID SYSTEM */
.row {
	position: relative;
	width: 100%;
	margin-top: 10px;
}

.row [class^="col"] {
	float: left;
}

.col-1,
.col-2,
.col-3,
.col-4,
.col-5,
.col-6,
.col-7,
.col-8,
.col-9,
.col-10,
.col-11,
.col-12 {
  width: 96%;
}

.row::after {
  content: "";
  display: table;
  clear: both;
}

.hidden-sm {
  display: none;
}

@media only screen and (min-width: 24em) {
  .col-1 {
    width: 4.33%;
  }

  .col-2 {
    width: 12.66%;
  }

  .col-3 {
    width: 21%;
  }

  .col-4 {
    width: 29.33%;
  }

  .col-5 {
    width: 37.66%;
  }

  .col-6 {
    width: 46%;
  }

  .col-7 {
    width: 54.33%;
  }

  .col-8 {
    width: 62.66%;
  }

  .col-9 {
    width: 71%;
  }

  .col-10 {
    width: 79.33%;
  }

  .col-11 {
    width: 87.66%;
  }

  .col-12 {
    width: 96%;
  }

  .hidden-sm {
    display: block;
  }
}
)rawliteral";