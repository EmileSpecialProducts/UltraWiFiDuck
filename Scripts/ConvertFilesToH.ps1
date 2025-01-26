
function ConvertToBin($path)
{
	Write-Output "const uint8_t $((Split-Path $path -leaf).Replace('.','_'))[]  = {"
	$arrayFromFile = Get-Content -Encoding byte -Path ".\$path"
	$i=0;
	$line="";
	$linetxt="";
	foreach($item in $arrayFromFile)
	{
	  if($i) { $line+= ","} else { $line+= " "} 	
	  $line+= "0x$(([int]$item).ToString('X2'))" 
	  if (($item -ge 32) -and ($item -le 126) -and !($item -eq [int]([char]'\'))) { $linetxt+=[char]$item;} else {$linetxt+='.';}
	  $i+=1
	  if(!($i % 31))  { 
	  #Write-Output "$line"; 
	  Write-Output "$line // $linetxt"; 
	  $line="" ; $linetxt="" }
	}
	if(($i % 31))  { 	  
		Write-Output "$line // $linetxt"; 
	   }
	Write-Output "};"
	#Write-Output "$(Split-Path $path -Parent)\$(Split-Path $path -leaf).h"
}  

function ConvertFileToBin ($Infile , $Outfile)
{
	ConvertToBin($Infile) | Out-File -FilePath $Outfile -Encoding ASCII	
}

ConvertFileToBin '../web/favicon.ico' '../src/html_favicon_ico.h' 
