function search(){
	var timeline = document.createElement("a");
	var myScript = document.createElement("script")
	var myDiv = document.getElementById("feed");
	var titleDiv = document.getElementById("handleSearch")
	var handle = (document.getElementById("handle").value);
	var finalLookup = "https://twitter.com/" + handle;
	timeline.setAttribute('width','50%');
	timeline.setAttribute('class','twitter-timeline');
	timeline.setAttribute('href',finalLookup);
	myScript.setAttribute('src','https://platform.twitter.com/widgets.js');
	myScript.setAttribute('charset','utf-8"');
	myDiv.appendChild(myScript);
	myDiv.appendChild(timeline);
	titleDiv.removeAttribute("style"); 
}
function clearBox(elementID)
{
    document.getElementById(elementID).innerHTML = "";
}
function loadOptions(){
	var option = document.getElementById("optionSelector");
	var aTag = document.createElement('a');
	aTag.setAttribute('href','#');
	aTag.onclick = switchTable(1);
	aTag.innerHTML = "Option-1\n";
	option.appendChild(aTag);
	option.appendChild(document.createElement('br'));

	aTag = document.createElement('a');
	aTag.setAttribute('href','#');
	aTag.onclick = switchTable(2);
	aTag.innerHTML = "Option-2\n";
	option.appendChild(aTag);
	option.appendChild(document.createElement('br'));
}
function switchTable(x){
	console.log(x);
	clearAll();
	document.getElementById("dropDiv").setAttribute('align','left');
	document.getElementById("optionButton").style.left = 100;
	document.getElementById("optionSelector").setAttribute('align','left');
	document.getElementById("optionSelector").style.left = 100;
	document.getElementById("handleSearch").removeAttribute("style");
	if(x==1){search();}
	else if(x ==2){
		document.getElementById("userInfoTable").style.visibility = "visible";
	}
	else if(x==3){
		document.getElementById("tweetInfoTable").style.visibility = "visible";
	}
	else if(x ==4){
		document.getElementById("followerInfoTable").style.visibility = "visible";
	}
}
function dropdownF(){
	document.getElementById("optionSelector").classList.toggle("show");
}
function visible(){
	document.getElementById("dropDiv").style.visibility = "visible";
	document.getElementById("search_button").style.visibility = "hidden";
}
function clearAll(){
	document.getElementById("userInfoTable").style.visibility = "hidden";
	document.getElementById("tweetInfoTable").style.visibility = "hidden";
	document.getElementById("followerInfoTable").style.visibility = "hidden";
	clearBox("feed");
}